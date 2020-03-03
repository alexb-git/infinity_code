/****************************************************************************
** Filename:    - scoped_lock.h
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - implementation of Scoped lock class
** Date:        - 6/2/2018
** Version:     - 1
*****************************************************************************/
#ifndef __SHARED_PTR_HPP__
#define __SHARED_PTR_HPP__

#include <iostream>  /* ostream, istream */

namespace ilrd
{

/*===========================  Class SharedPtr  ===========================*/
template<typename B>
class SharedPtr
{
private:
    template < typename >
    friend class SharedPtr;

public:
    explicit inline SharedPtr(B* ptr); // Ctor

    inline SharedPtr(const SharedPtr<B>& self_); // CCtor to self

    template<typename D>
    inline SharedPtr(const SharedPtr<D>& other_); // CCtor to other

    inline SharedPtr<B>& operator=(const SharedPtr<B>& self_); // =to self

    template<typename D>
    inline SharedPtr<B>& operator=(const SharedPtr<D>& other_); // =to other

    inline ~SharedPtr(); // Dtor

    inline B& operator*();
    inline B* operator->();
    inline B* GetPtr() const;

private:
    void ImpDeleteORCnt();  // deallocate OR decrease count reference
    B       *m_ptr;         // ptr to user allocated memory
    size_t  *m_cnt;         // pointer to reference count
};

/****************************************************************************
                    ==========  Implementations  ==========
*****************************************************************************/
/* for testing */
#ifdef _DEBUG
#define PrintStatus(ptr, cont, message)\
std::cout << "m_ptr " << ptr;\
std::cout << "  | cont = " << cont;\
std::cout << "  | " << message << std::endl;
#endif

/*==============================  ImpDeleteORCnt  ==========================*/
template<typename B>
void SharedPtr<B>::ImpDeleteORCnt()
{
    if( *m_cnt > 1 )
    {
        --*m_cnt;

        #ifdef _DEBUG
            PrintStatus(m_ptr, *m_cnt, "ImpDeleteORCnt --");
        #endif
    }
    else
    {
        #ifdef _DEBUG
            PrintStatus(m_ptr, *m_cnt, "ImpDeleteORCnt call Dtor");
        #endif

        delete m_ptr;
        m_ptr = NULL;
        delete m_cnt;
        m_cnt = NULL;
    }
}

/*==============================  SharedPtr ctor  ==========================*/
template<typename B>
SharedPtr<B>::SharedPtr(B* ptr) :
                                m_ptr(ptr),
                                m_cnt(new size_t(1))
{
    #ifdef _DEBUG
        PrintStatus(m_ptr, *m_cnt, "SharedPtr CTOR");
    #endif
}

/*==============================  SharedPtr CCtor to other  ================*/
template<typename B>
template<typename D>
inline SharedPtr<B>::SharedPtr(const SharedPtr<D>& other_) :
                                                    m_ptr(other_.m_ptr),
                                                    m_cnt(other_.m_cnt)
{
    ++*other_.m_cnt;

    #ifdef _DEBUG
        PrintStatus(m_ptr, *m_cnt, "SharedPtr CCTOR (other)");
    #endif
}

/*==============================  SharedPtr CCtor to self  =================*/
template<typename B>
inline SharedPtr<B>::SharedPtr(const SharedPtr<B>& self_) :
                                                    m_ptr(self_.m_ptr),
                                                    m_cnt(self_.m_cnt)
{
    ++*self_.m_cnt;

    #ifdef _DEBUG
        PrintStatus(m_ptr, *m_cnt, "SharedPtr CCTOR (self)");
    #endif
}

/*==============================  ~SharedPtr  ==============================*/
template<typename B>
inline SharedPtr<B>::~SharedPtr()
{
    ImpDeleteORCnt(); // deallocate OR decrease count reference
}

/*==============================  operator '=to self' ======================*/
template<typename B>
inline SharedPtr<B>& SharedPtr<B>::operator=(const SharedPtr<B>& other_)
{
    ++*other_.m_cnt;    // increase reference count
    ImpDeleteORCnt();   // deallocate OR decrease count reference

    m_ptr = other_.m_ptr;
    m_cnt = other_.m_cnt;

    #ifdef _DEBUG
        PrintStatus(m_ptr, *m_cnt, "SharedPtr operator= (self)");
    #endif

    return *this;
}

/*==============================  operator '=to other' ======================*/
template<typename B>
template<typename D>
inline SharedPtr<B>& SharedPtr<B>::operator=(const SharedPtr<D>& other_)
{
    ++*other_.m_cnt;    // increase reference count
    ImpDeleteORCnt();   // deallocate OR decrease count reference

    m_ptr = other_.m_ptr;
    m_cnt = other_.m_cnt;

    #ifdef _DEBUG
        PrintStatus(m_ptr, *m_cnt, "SharedPtr operator= (other)");
    #endif

    return *this;
}

/*==============================  operator*  ===============================*/
template<typename B>
inline B& SharedPtr<B>::operator*()
{
    return *m_ptr;
}

/*==============================  operator->  ==============================*/
template<typename B>
inline B* SharedPtr<B>::operator->()
{
    return m_ptr;
}

/*==============================  GetPtr  ==================================*/
template<typename B>
inline B* SharedPtr<B>::GetPtr() const
{
    return m_ptr;
}







} // namespace ilrd

#endif /*__SHARED_PTR_HPP__ */
