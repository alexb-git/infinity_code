/****************************************************************************
** Filename:    - scoped_lock_test.cpp
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - testing the Scoped lock class
** Date:        - 6/2/2018
** Version:     - 1
*****************************************************************************/
#include <iostream>      /* cin, cout */
#include <pthread.h>     /* pthread_mutex_t */

#include "scoped_lock.hpp" /* implementation of Scoped lock class */


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

/****************************************************************************
    Helpful defines and inline functions
*****************************************************************************/
inline void PrintHeader(const char *str)
{
    std::cout << BLU BLD "\n\t------------  This is a test for: "
              << str << " ------------\n" RES << std::endl;
}

inline void PrintInYellow(const char *str)\
{ std::cout << YLL << str << RES;}
inline void PrintOK()  { std::cout << GRE "-OK" RES; }
inline void PrintERR() { std::cout << RED "-ERR" RES; }

#define Alighl(X)         ( std::left << setw(X) )
#define PrintOKorERR(X)   ( (X)?(PrintOK()):(PrintERR()) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )
/****************************************************************************/


/*================  simples class to test the scoped_lock  =================*/
class PrimitiveManual
{
public:

    void Lock()
    {
        std::cout << BLU "PrimitiveManual LOCK" RES << std::endl;
    }

    void UnLock()
    {
        std::cout << BLU UDL "PrimitiveManual UNLOCK" RES << std::endl;
    }
};


/*==================  wrapper around C pthread_mutex_t  ==================*/
class RealMutex
{
public:
    void Lock()
    {
        pthread_mutex_lock(&m_mutex);
        std::cout << CYA "RealMutex Ctor LOCK" RES << std::endl;
    }

    void UnLock()
    {
        pthread_mutex_unlock(&m_mutex);
        std::cout << CYA UDL "RealMutex Dtor UNLOCK" RES << std::endl;
    }

private:
    pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;
};


/*==============================  THE MAIN  ===============================*/
int main(int argc, char const *argv[])
{
    {
        PrimitiveManual my_mutex;
        ilrd::ScopedLock <  PrimitiveManual         ,
                           &PrimitiveManual::Lock   ,
                           &PrimitiveManual::UnLock >  myLock(&my_mutex);
    }

    RealMutex real_mutex;
    ilrd::ScopedLock <  RealMutex           ,
                       &RealMutex::Lock     ,
                       &RealMutex::UnLock   >   scop_lock_mutex(&real_mutex);

    return 0;
}
