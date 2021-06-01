#include "fmcmessagebus.h"
#include "eventqueue.h"
#include "logger.h"

//--------------------------------------------------------------------------------------------------------------------//

const QLatin1String ANY_RECV = QLatin1String("*");

FMCMessageBus *FMCMessageBus::m_instance = nullptr;

//--------------------------------------------------------------------------------------------------------------------//

FMCMessage::FMCMessage(QString sender, int32_t messageType) : FMCMessage (sender, messageType, ANY_RECV){
}

FMCMessage::FMCMessage(QString sender, int32_t messageType, QString receiver) {
    m_sender = sender;
    m_messageType = messageType;
    m_receiver = receiver;
}

//--------------------------------------------------------------------------------------------------------------------//

QString FMCMessage::Sender() {
    return m_sender;
}

//--------------------------------------------------------------------------------------------------------------------//

QString FMCMessage::Receiver() {
    return m_receiver;
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

QString FMCBusSubscriber::SubscriberId() {
    return m_subscriberId;
}

//--------------------------------------------------------------------------------------------------------------------//

void FMCBusSubscriber::SetSubscriberId(const QString &id) {
    m_subscriberId = id;
}

//--------------------------------------------------------------------------------------------------------------------//

void FMCBusSubscriber::ReceiveMessage(FMCMessage *message) {

}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

FMCMessageBus *FMCMessageBus::GetInstance() {
    if (m_instance == nullptr) {
        m_instance = new FMCMessageBus();
    }
    return m_instance;
}

//--------------------------------------------------------------------------------------------------------------------//

FMCMessageBus::FMCMessageBus() {
    m_loopThread = nullptr;
    m_eventQueue = new NPEventQueue<FMCMessage>();
}


FMCMessageBus::~FMCMessageBus() {
    if (m_loopThread) {
        m_breakThreadMutex.unlock();
        //generate dummy message to unlock queue wait lock
        m_eventQueue->AddEvent(new FMCMessage(ANY_RECV, -1));
    }
    delete m_eventQueue;
}

//--------------------------------------------------------------------------------------------------------------------//

void FMCMessageBus::Init() {
    //Taking mutex
    m_breakThreadMutex.lock();
    //Start thread loop
    m_loopThread = new std::thread(&FMCMessageBus::threadFunction, this);
    Logger::log("MessageBus inited");
}

//--------------------------------------------------------------------------------------------------------------------//

void FMCMessageBus::PostMessage(FMCMessage *message) {
    m_eventQueue->AddEvent(message);
}

//--------------------------------------------------------------------------------------------------------------------//

void FMCMessageBus::Subscribe(FMCBusSubscriber *subscriber) {
    std::lock_guard<std::mutex> lk(m_subscribersMutex);
    if (!m_subscribers.contains(subscriber)) {
        m_subscribers.append(subscriber);
    }
}

//--------------------------------------------------------------------------------------------------------------------//

void FMCMessageBus::threadFunction() {
    QList<FMCBusSubscriber*> receivers;
    do {
        if (m_breakThreadMutex.try_lock()) {
            //if we can take mutex, then we must finish loop
            return;
        }

        auto event = m_eventQueue->WaitEvent();
        do {
            if (event == nullptr) break;

            std::unique_lock<std::mutex> lck (m_subscribersMutex);
            if (event->Receiver() == ANY_RECV) {
                receivers.append(m_subscribers);
                lck.unlock();
            } else {
                for (auto item : m_subscribers) {
                    if (item->SubscriberId() == event->Receiver()) {
                        receivers.append(item);
                    }
                }
                lck.unlock();
            }

            for (auto receiver : receivers) {

                QMetaObject::invokeMethod(receiver, "ReceiveMessage", Qt::QueuedConnection, Q_ARG(FMCMessage*, event));
            }
            receivers.clear();
        } while(false);
        std::this_thread::yield();
    } while(true);
}
