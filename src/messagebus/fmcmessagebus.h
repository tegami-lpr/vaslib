#ifndef FMCMESSAGEBUS_H
#define FMCMESSAGEBUS_H

#include <QObject>
#include <QThread>

extern const QLatin1String ANY_RECV;

template <class T> class NPEventQueue;

class FMCMessage {
public:
    FMCMessage(QString sender, int32_t messageType);
    FMCMessage(QString sender, int32_t messageType, QString receiver);

    QString Sender();
    QString Receiver();

    QString m_sender;
    QString m_receiver = ANY_RECV;
    int32_t m_messageType;
};

//!Message bus for exchange data between components
class FMCMessageBus {
public:
    static FMCMessageBus* GetInstance();
    //!Destructor
    ~FMCMessageBus();
    //! Function for init messagebus loop
    void Init();

    //! Add message to the bus
    void PostMessage(FMCMessage *message);
    //! add new subscriber ot the bus
    void Subscribe(QObject *subscriber, const QString& id);

private:
    //! Constructor
    FMCMessageBus();
    //! Static pointer to message bus instance
    static FMCMessageBus *m_instance;
    //! Pointer to bus loop thread
    std::thread *m_loopThread;
    //! Mutex to stop loop
    std::mutex m_breakThreadMutex;
    //! Messages queue
    NPEventQueue<FMCMessage> *m_eventQueue;

    //! Mutex for handle subscribers access
    std::mutex m_subscribersMutex;
    QList<QPair<QObject*, QString>> m_subscribers;

    //! Function for message bus loop
    void threadFunction();
};


#endif //FMCMESSAGEBUS_H
