/****************************************************************************
** Filename:    - thread_pool.cpp
** Code Author: - HRD1
** Date:        - 01/03/2018
** Version:     - 1
*****************************************************************************/
#include <iostream>    /* cout, endl */
#include <stdio.h>    /* fprintf */

#include "thread_pool.hpp"

/****************************************************************************
    Helpful colors
*****************************************************************************/
#define YLL	 "\x1b[93m"
#define GRE	 "\x1b[92m"
#define RED	 "\x1b[91m"
#define WHI	 "\x1B[37m"
#define CYA	 "\x1B[36m"
#define BLU	 "\x1B[34m"
#define YEL	 "\x1b[33m"
#define RES	 "\x1b[0m"
#define BLD  "\x1B[1m"
#define UDL  "\x1b[4m"

namespace ilrd
{

/****************************************************************************
                          class ThreadPool
*****************************************************************************/

/*==========================  ThreadPool Ctor  =============================*/
// by default num_threads == number of cpu cores
ThreadPool::ThreadPool(size_t num_threads) :
                                        m_num_threads(num_threads),
                                        m_threads(m_num_threads),
                                        m_stop(false),
                                        m_pause(false),
                                        m_poisoned_task(new PoisonedTask(*this))
{
    // empty
}

/*==========================  ThreadPool Dtor  =============================*/
ThreadPool::~ThreadPool()
{
    // empty
}

/*==========================  ThreadPool::AddTask  =========================*/
void ThreadPool::AddTask( std::tr1::shared_ptr<BaseTask> t ,
                          Priority priority                )
{
    std::tr1::shared_ptr<PTask> p_task( new PTask(t, priority) );

    m_tasks.Enqueue(p_task);
}

/*=======================  ThreadPool::ChangeThreadSize  ====================*/
void ThreadPool::ChangeThreadSize(size_t new_num_threads)
{
    /* if  (new_num_threads == m_num_threads) do nothing */

    // pthread_mutex_lock( PoisonedTask::m_vector_mutex );

    if ( new_num_threads > m_num_threads )
    {
        /* need to create new threads */
        m_threads.resize(new_num_threads);

        for(size_t i = m_num_threads ; i < new_num_threads ; ++i )
        {
            pthread_create(&m_threads[i], NULL, RunTask, this);
        }
    }
    else if ( new_num_threads < m_num_threads )
    {
        /* need to destroy some threads */
        size_t delta = m_num_threads - new_num_threads;


        while ( delta-- )
        {
            AddTask(m_poisoned_task, HIGH /* TODO */);
        }
    }

    m_num_threads = new_num_threads;
    
    // pthread_mutex_unlock(PoisonedTask::m_vector_mutex);
}

/*==========================  ThreadPool::RunTask  ==========================*/
void* ThreadPool::RunTask(void *thread_pool)
{
    std::tr1::shared_ptr<PTask> p_task;

    ThreadPool *t_pool = reinterpret_cast< ThreadPool* > (thread_pool);

    while ( !t_pool->m_stop )
    {
        if( t_pool->m_tasks.Dequeue(&p_task, 1) )
        {
            p_task.get()->GetTask()->run();
        }
    }

    return NULL;
}

/*==========================  ThreadPool::Run  ==============================*/
void ThreadPool::Run()
{
    for(size_t i = 0 ; i < m_num_threads ; ++i )
    {
        pthread_create(&m_threads[i], NULL, RunTask, this);
    }
}

/*==========================  ThreadPool::Stop  =============================*/
void ThreadPool::Stop(size_t time_out) // in milliseconds
{
    m_stop = true;

    /* timespec structure - to handle timeout */
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += time_out;

    for(size_t i = 0 ; i < m_num_threads ; ++i )
    {
        if( 0 != pthread_timedjoin_np( m_threads[i],
                                       NULL        ,
                                      &ts          ) )
        {
            pthread_cancel(m_threads[i]);

            fprintf(stderr, BLU BLD UDL "pthread_cancel\n");
        }
    }
}

/*==========================  ThreadPool::Pause  ============================*/
void ThreadPool::Pause()
{
    m_pause = 1;
}

/*==========================  ThreadPool::Resume  ===========================*/
void ThreadPool::Resume()
{
    m_pause = 0;
}



/************************************************************************
    Nested class BaseTask declaration - abstract class
************************************************************************/

/*====================  ThreadPool::BaseTask::BaseTask  ====================*/
ThreadPool::BaseTask::BaseTask()
{
    // empty
}

/*====================  ThreadPool::BaseTask::~BaseTask  ====================*/
ThreadPool::BaseTask::~BaseTask()
{
    // empty
}
// virtual void run() = 0;



/************************************************************************
    Nested class killing task , the executing thread will remove
    himself from the thread_vector and die
************************************************************************/
/*==================  ThreadPool::PoisonedTask::PoisonedTask  ===============*/
ThreadPool::PoisonedTask::PoisonedTask(ThreadPool& tp) :
                                            m_vector_mutex(new pthread_mutex_t)
{
    pthread_mutex_init( m_vector_mutex.get(), NULL);
    // TODO
}

/*==================  ThreadPool::PoisonedTask::~PoisonedTask  ==============*/
ThreadPool::PoisonedTask::~PoisonedTask()
{
    pthread_mutex_destroy(m_vector_mutex.get());
}

/*==================  ThreadPool::PoisonedTask::Run  ========================*/
void ThreadPool::PoisonedTask::run()
{
    pthread_cancel( pthread_self() );
}


/************************************************************************
    Nested class wrapper class for priority queue
************************************************************************/

/*==========================  filename  ==========================*/
ThreadPool::PTask::PTask( std::tr1::shared_ptr<BaseTask> t ,
                          int priority                     ):
                                            m_t(t),
                                            m_priority(priority)
{

}

/*==========================  filename  ==========================*/
bool ThreadPool::PTask::operator<(const PTask& other) const
{
    return m_priority < other.m_priority;
}

/*==========================  filename  ==========================*/
std::tr1::shared_ptr<ThreadPool::BaseTask> ThreadPool::PTask::GetTask()
{
    return m_t;
}




} // namespace ilrd
