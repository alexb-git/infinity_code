/****************************************************************************
** Filename:    - thread_pool.hpp
** Code Author: - HRD1
** Date:        - 01/03/2018
** Version:     - 1
*****************************************************************************/
#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <pthread.h>              // posix thread
#include <thread>                 // hardware_concurrency()
#include <vector>                 // std::vector
#include <tr1/memory>             // shared_ptr
#include <boost/atomic.hpp>       // boost::atomic
#include <boost/noncopyable.hpp>  // noncopyable

#include "priority_queue.hpp"

namespace ilrd
{

/****************************************************************************
                          class ThreadPool declaration
*****************************************************************************/
class ThreadPool: private boost::noncopyable
{
private:
    /* nested classes */
    class PoisonedTask;
    class PTask;

public:
    /* nested classes - visible to user */
    class BaseTask;

    // by default num_threads == number of cpu cores
    explicit ThreadPool(size_t num_threads = 4
                                        /*std::thread::hardware_concurrency()*/);
    ~ThreadPool();

    // task priority level (higher priority - preferably dequeued first)
    enum Priority { LOW = 1, MEDIUM = 2, HIGH = 3 };

    void AddTask( std::tr1::shared_ptr<BaseTask> t,
                  Priority priority = LOW         );
    void ChangeThreadSize(size_t new_num_threads);
    void Run();
    void Stop(size_t time_out = 2000);   // in milliseconds
    void Pause();
    void Resume();

    /************************************************************************
        Nested class BaseTask declaration - abstract class. visible to user
    ************************************************************************/
    class BaseTask
    {
    public:
        explicit BaseTask();
        virtual ~BaseTask();
        virtual void run() = 0; // user is required to overload this method
    };

private:
    /*********************** Variable Section *******************************/

    // num of usable threads
    size_t m_num_threads;

    // vector of threads
    std::vector<pthread_t> m_threads;

    // flag used in stop
    boost::atomic<bool> m_stop;

    // for pausing and resuming
    boost::atomic<bool> m_pause;

    // object (task) that can close threads
    std::tr1::shared_ptr<BaseTask> m_poisoned_task;

    // the tasks queue
    PQueue < std::tr1::shared_ptr<PTask> > m_tasks;


    // main function
    static void* RunTask(void *thread_pool);

    /************************************************************************
        Nested class wrapper class for priority queue
    ************************************************************************/
    class PTask
    {
    public:
        explicit PTask( std::tr1::shared_ptr<BaseTask> t ,
                        int priority                     );
        bool operator<(const PTask& other) const;
        std::tr1::shared_ptr<BaseTask> GetTask();

    private:
        std::tr1::shared_ptr<BaseTask> m_t;
        int m_priority;
    }; // PTask

    /************************************************************************
        Nested class killing task , the executing thread will remove
        himself from the thread_vector and die
    ************************************************************************/
    class PoisonedTask: public BaseTask
    {
    public:
      PoisonedTask(ThreadPool& tp);
      ~PoisonedTask();
      void run();


    private:
        friend class ThreadPool; // needs service from thread pool to remove
        static const int admin_priority_h = HIGH + 10;
        std::tr1::shared_ptr<pthread_mutex_t> m_vector_mutex;
    }; // PoisonedTask

};

} // namespace ilrd

#endif // __THREAD_POOL_HPP__
