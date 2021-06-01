#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

template <class T>
class NPEventQueue {
public:
    ~NPEventQueue();
    void AddEvent(T* event);
    T* WaitEvent();
private:
    std::queue<T*> m_eventQueue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};


#endif //EVENTQUEUE_H
