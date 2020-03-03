/****************************************************************************
** Filename:    - shared_ptr.h
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - iplementation of Share pointer
** Date:        - 4/2/2018
** Version:     - 2
*****************************************************************************/
#ifndef __SCOPED_LOCK_HPP__
#define __SCOPED_LOCK_HPP__

#include <iostream>  /* ostream, istream */

namespace ilrd
{

/****************************************************************************
                    =========  Class ScopedLock =========
*****************************************************************************/
template <  typename OBJ_T        ,  /* object type */
            void(OBJ_T::*FUNC1)() ,  /*   lock */
            void(OBJ_T::*FUNC2)() >  /* unlock */
class ScopedLock
{
public:
    explicit inline ScopedLock(OBJ_T* ptr); // Ctor
    inline ~ScopedLock();                   // Dtor


private:
    // cctor disabled
    inline ScopedLock(const ScopedLock<OBJ_T, FUNC1, FUNC2> &other_);
    // assignment disabled
    inline ScopedLock<OBJ_T, FUNC1, FUNC2>& operator=
                        (const ScopedLock<OBJ_T, FUNC1, FUNC2> &other_);
    OBJ_T *m_obj_ptr;
};


/*==========================  ScopedLock Ctor  ==========================*/
template <  typename OBJ_T        ,  /* object type */
            void(OBJ_T::*FUNC1)() ,  /*   lock */
            void(OBJ_T::*FUNC2)() >  /* unlock */
inline ScopedLock<OBJ_T, FUNC1, FUNC2>::ScopedLock(OBJ_T* ptr) :
                                                            m_obj_ptr(ptr)
{
    (m_obj_ptr->*FUNC1)();
}

/*==========================  ~ScopedLock Dtor  ==========================*/
template <  typename OBJ_T        ,  /* object type */
            void(OBJ_T::*FUNC1)() ,  /*   lock */
            void(OBJ_T::*FUNC2)() >  /* unlock */
inline ScopedLock<OBJ_T, FUNC1, FUNC2>::~ScopedLock()
{
    (m_obj_ptr->*FUNC2)();
}


} /* namespace ilrd */

#endif /* __SCOPED_LOCK_HPP__ */
