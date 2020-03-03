/****************************************************************************
** Filename:    - posix_mutex.hpp
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - my posix_mutex
** Date:        - 6/2/2018
** Version:     - 1
*****************************************************************************/
#ifndef __POSIX_MUTEX_HPP_
#define __POSIX_MUTEX_HPP_

#include <pthread.h>                /* pthread_mutex_t */
#include <boost/noncopyable.hpp>    /* noncopyable */

#include "scoped_lock.hpp" /* implementation of Scoped lock class */

/*==================  wrapper around C pthread_mutex_t  ==================*/
namespace ilrd
{

/****************************************************************************
    class PosixMutex. will be used in PosixMutexScopedLock
*****************************************************************************/
class PosixMutex: private boost::noncopyable
{
public:
	explicit PosixMutex();
	~PosixMutex();
	void PosixMutexLock();
	void PosixMutexUnlock();

private:
	pthread_mutex_t m_mutex;

}; // end of class PosixMutex


/****************************************************************************
    class PosixMutexScopedLock. acts as smart mutex lock (releases itself)
*****************************************************************************/
class PosixMutexScopedLock: private boost::noncopyable
{
public:
	explicit PosixMutexScopedLock(PosixMutex *mutex);

private:
	ScopedLock <  PosixMutex                   ,
			     &PosixMutex::PosixMutexLock   ,
			     &PosixMutex::PosixMutexUnlock > m_scoped_lock;

}; // end of class PosixMutexScopedLock


} // end of namespace ilrd

#endif // __POSIX_MUTEX_HPP_
