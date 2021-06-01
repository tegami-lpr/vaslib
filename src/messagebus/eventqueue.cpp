#include "eventqueue.h"

//--------------------------------------------------------------------------------------------------------------------//

template<class T> NPEventQueue<T>::~NPEventQueue() {
    while (!m_eventQueue.empty()) {
        auto event = m_eventQueue.front();
        m_eventQueue.pop();
        delete event;
    }
}

//--------------------------------------------------------------------------------------------------------------------//

template<class T> void NPEventQueue<T>::AddEvent(T *event) {
    {
        //Taking mutex and put event to queue
        std::lock_guard<std::mutex> lk(m_mutex);
        m_eventQueue.push(event);
    }
    //Inform waiting thread about new  event in queue
    m_cv.notify_one();
}

//--------------------------------------------------------------------------------------------------------------------//

template<class T> T *NPEventQueue<T>::WaitEvent() {
    //Taking mutex
    std::unique_lock<std::mutex> lk(m_mutex);
    //and starting wait for new event in queue
    m_cv.wait(lk, [this]{return !m_eventQueue.empty();});
    //after new item in queue we can take it from queue
    auto event = m_eventQueue.front();
    m_eventQueue.pop();
    //releasing mutex
    lk.unlock();
    //и return event
    return event;
}
