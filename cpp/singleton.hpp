/****************************************************************************
** Filename:    - singleton.hpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - design pattern - singleton (thread safe)
** Date:        - 20/2/2018
** Version:     - 1
*****************************************************************************/
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <pthread.h> /* m_lock, m_unlock, INITIALIZER,  */
#include <stdlib.h>  /* at-Exit */

#include <iostream>    /* functions_used */

namespace ilrd
{

template <typename T>
class Singleton
{
public:
    static T* GetSingltone();

private:
    Singleton();            /* Ctor is disabled (singleton) */
    static void Cleaner();  /* for the use of at-Exit function */
    static T *m_instance;   /* ptr to object that singleton guards */
};


/*===================  definition of static m_instance  ====================*/
template<typename T>
T* Singleton<T>::m_instance = NULL;


/*=====================  the main singleton function  ======================*/
template<typename T>
T* Singleton<T>::GetSingltone()
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    static volatile unsigned int ston_exists = false;

    /* double-checked locking */
    if ( !ston_exists )
    {
        pthread_mutex_lock(&mutex);
        if ( !ston_exists )
        {
            /* make object of required type */
            m_instance = new T;

            /* load the at-Exit function with cleaner function */
            ::atexit(Cleaner);

            /*  set 'ston_exists = 1' atomically
                full barrier - no memory operand is moved across the operation,
                       either forward or backward. Instructions are issued
                       as necessary to prevent the processor from speculating
                       loads across the operation and from queuing stores
                       after the operation. */
            __sync_fetch_and_or(&ston_exists, 1);
        }
        pthread_mutex_unlock(&mutex);
    }

    return m_instance;
}

/*==================  function to be called by at-Exit  ====================*/
template<typename T>
void Singleton<T>::Cleaner()
{
    delete m_instance;
    m_instance = NULL;
}

// *****************************************************************************
// *                            Animal Class Declaration                          *
// *****************************************************************************
class Animal
{
public:
    ~Animal() { std::cout <<"\x1b[34m"<< "Animal Dtor" <<"\x1b[0m"<< std::endl; }
    void PrintDetails() { std::cout << m_name << ' ' << m_age << std::endl; }
    void SetAge(unsigned int age) { m_age = age; }

private:
    std::string m_name;
    unsigned int m_age;

    Animal(const char *name = "Bob", unsigned int age = 48):
        m_name(std::string(name)), m_age(age)
    {
        std::cout <<"\x1b[34m"<< "Animal::Ctor" <<"\x1b[0m"<< std::endl;
    }

    friend class Singleton<Animal>;
};

Animal* Doo();
Animal* Voo();


} //namespace ilrd

#endif /* end of __SINGLETON_H__ */
