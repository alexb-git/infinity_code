/****************************************************************************
** Filename:    - Q41.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Intoduction question to c++
** Date:        - 6/2/2018
** Version:     - 41
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

/*==========================  X  ==========================*/
struct X
{
    X() {
        cerr << BLU BLD "X Ctor  " RES
             << RED UDL "(right b4 throw)" RES << endl;
        throw bad_cast();
    }

    X(int) { cerr << BLU BLD "X Ctor (int)" RES << endl; }

    ~X() { cerr << RED BLD "X Dtor" RES << endl; }
};

/*==========================  Y  ==========================*/
struct Y
{
     Y() { cerr << BLU BLD "Y Ctor" RES << endl; }
    ~Y() { cerr << RED BLD "Y Dtor" RES << endl; }
 };


/*==========================  L  ==========================*/
class L /* (creates X, Y on stack) */
{
public:
     L() : m_x(2) { cerr << BLU BLD "L Ctor" RES << endl; }
    ~L() { cerr << RED BLD "L Dtor" RES << endl; }

private:
    Y m_y; // struct Y
    X m_x; // struct X
};

/*==========================  M  ==========================*/
class M /* (creates X, Y on stack) */
{
public:
     M() { cerr << BLU BLD "M Ctor" RES << endl; }
    ~M() { cerr << RED BLD "M Dtor" RES << endl; }

private:
    X m_x; // struct X
    Y m_y; // struct Y
};

/*==========================  N  ==========================*/
class N /* (creates X, Y on stack) */
{
public:
     N() { cerr << BLU BLD "N Ctor" RES << endl; }
    ~N() { cerr << RED BLD "N Dtor" RES << endl; }

private:
    Y m_y;  // struct Y
    X m_x;  // struct X
};

/*==========================  J  ==========================*/
class J /* (allocates X, Y) */
{
public:
    J(): m_y(new Y),  // struct Y
         m_x(new X)   // struct X
    {
        cerr << BLU BLD "J Ctor" RES << endl;
    }

    ~J() {
        cerr << RED BLD "J Dtor" RES << endl;
        delete m_x;
        delete m_y;
    }

private:
    Y* m_y;
    X* m_x;
};

/*==========================  K  ==========================*/
class K /* (allocates X, Y) */
{
public:
    K() {
        cerr << BLU BLD "K Ctor" RES << endl;
        m_y = new Y;
        m_x = new X;
    }

    ~K() {
        cerr << RED BLD "K Dtor" RES << endl;
        delete m_x;
        delete m_y;
    }

private:
    Y* m_y;
    X* m_x;
};


void myterminate ()
{
    std::cerr << RED BLD UDL "terminate handler called" RES << std::endl;
    // abort();  // forces abnormal termination
}

/*==========================  THE MAIN  ==========================*/
int main(int argc, char const *argv[], char const *envp[])
{
    // std::set_terminate (myterminate);

    /* classes  L, M, N, (creates X, Y on stack)
                J, K     (allocates X, Y) */
    try
    {
        // L var1;  /* (Y, X(2)) OK */
        // M var1;  /* (X, Y) default Ctor of X throws exeption (bad_cast), Dtor for X is not called */
        // N var1;  /* (Y, X) default Ctor of X throws exeption (bad_cast), Dtor for X is not called, Y is constructed and destructed */
        // J var1;  /* (Y, X) default Ctor of X throws exeption (bad_cast), no Dtors are called (mem. leak) */
        K var1;  /* (Y, X) default Ctor of X throws exeption (bad_cast), no Dtors are called (mem. leak) */
    }
    catch (bad_alloc& e)
    {}
    catch (exception& e)
    {
        cerr << "exception cout. what: " << e.what() << RES << endl;
    }

    std::cout << BLD CYA "MADE IT TO THE END" RES << std::endl;
    return 0;
}
