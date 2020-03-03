/****************************************************************************
** Filename:    - Q40.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Intoduction question to c++
** Date:        - 6/2/2018
** Version:     - 40
*****************************************************************************/
#include <iostream>  /* cout */
#include <iomanip>   /* std::setw */
#include <cstdlib>   /* exit */
#include <cstring>   /* string */

#include <exception>      // std::set_terminate
#include <cstdlib>        // std::abort
#include <typeinfo>       // bas_cast
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

using namespace std;
/****************************************************************************
    Helpful defines and inline functions
*****************************************************************************/
inline void PrintHeader(const char *str)
{
    std::cout << BLU BLD "\n\t------------  This is a test for: "
              << str << " ------------\n" RES << std::endl;
}

inline void PrintInYellow(const char *str) {cout << YLL << str << RES;}
inline void PrintOK()  { std::cout << GRE "-OK" RES; }
inline void PrintERR() { std::cout << RED "-ERR" RES; }

#define Alighl(X)         ( std::left << std::setw(X) )
#define PrintOKorERR(X)   ( (X)?(PrintOK()):(PrintERR()) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )
/****************************************************************************/
int Foo(int) throw(bad_alloc)
{
    std::cout << YLL "Foo" RES << std::endl;
    return 123;
}

void Bar() throw(int)
{
    std::cout << YLL "Bar" RES << std::endl;
    throw(789);
}

class X
{
public:
    X(int i) : m_a(i)
    {
        std::cout << BLU BLD "X Ctor" RES << std::endl;
    }

    ~X()
    {
        std::cerr << Foo(m_a) << std::endl;
    }

private:
    int m_a;
};




/*==========================  THE MAIN  ==========================*/
int main(int argc, char const *argv[], char const *envp[])
{
    X x1(666);
    // ...

    Bar();
    // ...


    std::cout << BLD CYA "MADE IT TO THE END" RES << std::endl;
    return 0;
}
