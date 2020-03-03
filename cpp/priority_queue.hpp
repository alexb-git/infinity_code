/****************************************************************************
** Filename:    - priority_queue.hpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - thread dafe mutable waitable timeout priority queue
** Date:        - 27/2/2018
** Version:     - 1
*****************************************************************************/
/*************************************************************************
** Filename:    - priority_queue.hpp                                     *
** Purpose:     - Thread safe, mutable, waitable, timeout priority queue *
** Date:        - 27/02/2018                                             *
** Version:     - 1                                                      *
**************************************************************************/
#ifndef __PRIORITY_QUEUE_HPP__
#define __PRIORITY_QUEUE_HPP__

#include <iostream>     /* cou, endl */
#include <string.h>     /* memset */

#include <queue>        /* std::priority_queue */
#include <semaphore.h>  /* sem_t */

#include "posix_mutex.hpp"  /* smart mutex */

namespace ilrd
{

template <typename T>
class PQueue
{
public:
    explicit PQueue();
    ~PQueue();

    void Enqueue(const T& elem);

    // Attemp to dequeue top element from the queue with time out.
    // In case of an empty queue Dequeue will be blocked untill time out
    // or till element is enqueued.
    // The dequeued element will be written on 'T *elem' supplied by the user
    // Return value:  true  on success
    //                false on failure  (time out)
    bool Dequeue(T *elem, int time_out = 0); // does peek and pop

private:
    std::priority_queue<T> m_queue;
    PosixMutex my_lock;

    struct timespec m_time_out; /* support time format */
    sem_t           m_sem;      /* cout resource: empty queue */
};

/*==========================  IMPLEMENTATION  ==========================*/
template <typename T>
PQueue<T>::PQueue()
{
    sem_init(&m_sem, 0, 0);
}

template <typename T>
PQueue<T>::~PQueue()
{
    sem_destroy(&m_sem);
}

template <typename T>
void PQueue<T>::Enqueue(const T& elem)
{
    PosixMutexScopedLock smart_lock(&my_lock);

    m_queue.push(elem);

    sem_post(&m_sem);
}


template <typename T>
bool PQueue<T>::Dequeue(T *elem, int time_out)
{
    /* taking care of timespec structure */
    memset(&m_time_out, 0, sizeof(m_time_out));
    clock_gettime(CLOCK_REALTIME, &m_time_out);
    m_time_out.tv_sec  += time_out;


    /* sem wait on the resource with possibility of time out */
    if ( sem_timedwait(&m_sem, &m_time_out) )
    {
        /* failed ! - no element in the queue */

        return false;
    }
    else
    {
        /* success ! - there is at least one element in the queue */

        PosixMutexScopedLock smart_lock(&my_lock);

        *elem = m_queue.top();

        #ifdef _DEBUG
            std::cout << "|" << *elem << "|\n";
        #endif

        m_queue.pop();

        return true;
    }
}


} // namespace ilrd

#endif // __PRIORITY_QUEUE_HPP__
