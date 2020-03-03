/****************************************************************************
** Filename:    - Q32.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Intoduction question to c++
** Date:        - 17/1/2018
** Version:     - 32
*****************************************************************************/
#include <iostream>    /* cout */
#include <iomanip>     /* std::setw */

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

using std::cout;
using std::endl;
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

inline void PrintStatus( const char *color   , const char *caller,
                         const char *descr   , /*double      input ,*/
                         void       *this_ptr)
{
    cout << color
    << std::left << std::setw(9) << caller
    << "| "
    << "this : " << this_ptr << " | "
    << std::left << std::setw(9) << descr
    /*<< input << " | id = " << id*/
    << RES << endl << std::flush;
}

/*========================== CLASS Parent =================================*/
class Base
{
public:
    Base(double d_) : m_a(d_)
    {
        PrintStatus(BLU, "Base", "Ctor", this);
        std::cout << BLU << "\t\t\t\t\tm_a = " << m_a << RES << std::endl;
    }

    Base(const Base& ref) : m_a(ref.m_a)
    {
        PrintStatus(BLU, "Base", "CCtor", this);
        std::cout << BLU << "\t\t\t\t\tm_a = " << m_a << RES << std::endl;
    }

    virtual Base& operator=(const Base& ref)
    {
        m_a = ref.m_a;
        PrintStatus(BLU, "Base", "operator=",  this);
        return *this;
    }

    virtual ~Base()
    {
        PrintStatus(RED, "~Base", "Dtor",  this);
        std::cout << RED << "\t\t\t\t\tm_a = " << m_a << RES << std::endl;
    }

    /*virtual*/ void PrintInternals()
    {
        std::cout << BLU << "In Base Class    : m_a = "
        << m_a << RES << std::endl;
    }

private:
    double m_a;
};

/*============================== CLASS Child =====================================*/
class Derived: public Base
{
public:
    Derived(double d_, int i_) : Base(d_), m_b(i_)
    {
        PrintStatus(CYA, "Derived", "Ctor", this);
        std::cout << CYA << "\t\t\t\t\tm_b = " << m_b << RES << std::endl;
    }

    Derived(const Derived& ref) : Base(666.666), m_b(ref.m_b)
    {
        PrintStatus(CYA, "Derived", "CCtor", this);
        std::cout << CYA << "\t\t\t\t\tm_b = " << m_b << RES << std::endl;
    }

    virtual Derived& operator=(const Derived& ref)
    {
        this->Base::operator=(ref);
        m_b = ref.m_b;
        PrintStatus(CYA, "Derived", "operator=",  this);
        return *this;
    }

    virtual ~Derived()
    {
        PrintStatus(RED, "~Derived", "Dtor",  this);
        std::cout << RED << "\t\t\t\t\tm_b = " << m_b << RES << std::endl;
    }

    virtual void PrintInternals()
    {
        this->Base::PrintInternals();
        std::cout << CYA << "In Derived Class : m_b = "
        << m_b << RES << std::endl;
    }

private:
    int m_b;
};


/*==========================  THE MAIN  ==========================*/
int main(int argc, char const *argv[], char const *envp[])
{
    PrintInYellow("\nAbout to create 4 derived objects\n");
    Derived d1(0.0  , 0),
            d2(14.2 , 5),
            d3(0.0  , 0),
            d4(14.2 , 5);

    PrintInYellow("\nAbout to create reference\n");
    Base &b1 = d1;
    Base &b2 = d2;

    PrintInYellow("\nAbout to asign base pointer (b1 = b2)\n");
    b1 = b2;

    PrintInYellow("\nAbout to asign base pointer (d3 = d4)\n");
    d3 = d4;

    PrintInYellow("\nAbout to print derived statuses:\n");
    std::cout << "d1: \n";
    d1.PrintInternals();

    std::cout << "d2: \n";
    d2.PrintInternals();

    std::cout << "d3: \n";
    d3.PrintInternals();

    std::cout << "d4: \n";
    d4.PrintInternals();

    PrintInYellow("\nAbout to print base statuses:\n");
    std::cout << "b1: \n";
    b1.PrintInternals();

    std::cout << "b2: \n";
    b2.PrintInternals();

    PrintInYellow("\nAbout to exit the program, call dtors\n");
    return 0;
}
