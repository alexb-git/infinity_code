/****************************************************************************
** Filename:    - my_scoped_lock.hpp
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - iplementation of Share pointer
** Date:        - 4/2/2018
** Version:     - 2
*****************************************************************************/
#ifndef __SCOPED_LOCK_WRAPPER_HPP__
#define __SCOPED_LOCK_WRAPPER_HPP__
#include <pthread.h>    /* mutex, pthread, lock, unlock */

namespace ilrd
{

/****************************************************************************
                    =========  Class ScopedLock =========
*****************************************************************************/
class ScopedLock
{
public:
    // Ctor - lock upon creation (RAII)
    explicit inline ScopedLock()
    {
        pthread_mutex_lock(&m_mutex);
    }

    // Dtor - un-lock upon destruction
    inline ~ScopedLock()
    {
        pthread_mutex_unlock(&m_mutex);
    }


private:
    // cctor disabled
    inline ScopedLock(const ScopedLock &other_);
    // assignment disabled
    inline ScopedLock& operator=(const ScopedLock &other_);

    pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;
};


} /* namespace ilrd */

#endif /* __SCOPED_LOCK_WRAPPER_HPP__ */
