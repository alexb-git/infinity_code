/****************************************************************************
** Filename:    - posix_mutex.cpp
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - my posix_mutex
** Date:        - 6/2/2018
** Version:     - 1
*****************************************************************************/
#include "posix_mutex.hpp"    /* my posix_mutex header */


namespace ilrd
{

/****************************************************************************
    class PosixMutex. will be used in PosixMutexScopedLock
*****************************************************************************/
PosixMutex::PosixMutex()
{
	pthread_mutex_init(&m_mutex, NULL);
}

PosixMutex::~PosixMutex()
{
	pthread_mutex_destroy(&m_mutex);
}

void PosixMutex::PosixMutexLock()
{
	pthread_mutex_lock(&m_mutex);
}

void PosixMutex::PosixMutexUnlock()
{
	pthread_mutex_unlock(&m_mutex);
}


/****************************************************************************
    class PosixMutexScopedLock. acts as smart mutex lock (releases itself)
*****************************************************************************/
PosixMutexScopedLock::PosixMutexScopedLock(PosixMutex *mutex):
	   						                              m_scoped_lock(mutex)
{}


} // end of namespace ilrd
