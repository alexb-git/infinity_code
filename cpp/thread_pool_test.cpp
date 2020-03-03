/****************************************************************************
** Filename:    - thread_pool_test.cpp
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     -
** Date:        - 1/3/2018
** Version:     - 1
*****************************************************************************/
#include <iostream> /* count, cin */
#include <stdio.h>    /* fprintf */

#include "thread_pool.hpp"    /* thread_pool dp */
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

inline void PrintInYellow(const char *str) { std::cout << YLL << str << RES;}
inline void PrintOK()  { std::cout << GRE "-OK" RES; }
inline void PrintERR() { std::cout << RED "-ERR" RES; }

#define Alighl(X)         ( std::left << setw(X) )
#define PrintOKorERR(X)   ( (X)?(PrintOK()):(PrintERR()) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )
/****************************************************************************/

template <typename T>
inline void PrintMes(const char* color, const char* message, T var)
{
    std::cout << color << message << " " << RES << var << std::endl;
}


class Base_X : public ilrd::ThreadPool::BaseTask
{
public:
    Base_X() : m_life_span(500000) {};

    virtual void run()
    {
        while ( --m_life_span /*1*/ )
        {
            fprintf(stderr, GRE "X" RES);
            // std::cout << GRE "X" RES;
        }
        // sleep(1);
    }
private:
    int m_life_span;
};

class Base_Y : public ilrd::ThreadPool::BaseTask
{
public:
    Base_Y() : m_life_span(50) {};

    virtual void run()
    {
        while ( /*--m_life_span*/ 1 )
        {
            fprintf(stderr, RED "Y" RES);
            // std::cout << RED "Y" RES;
        }
        // sleep(1);
    }
private:
    int m_life_span;
};

// ThreadPool(4) to;
// OfUser ustask;
// to.AddTask(ustask, HIGH);
// to.Run();
/*==========================  THE MAIN  ==========================*/
int main(int argc, char const *argv[])
{
    ilrd::ThreadPool pool(2);

    std::tr1::shared_ptr<ilrd::ThreadPool::BaseTask> ptr_1(new Base_X());
    pool.AddTask(ptr_1, ilrd::ThreadPool::LOW);

    std::tr1::shared_ptr<ilrd::ThreadPool::BaseTask> ptr_2(new Base_Y());
    pool.AddTask(ptr_2, ilrd::ThreadPool::LOW);

    pool.Run();

    sleep(2);

    pool.Stop(2);

    std::cout << "\n\n" << std::endl;
    return 0;
}
