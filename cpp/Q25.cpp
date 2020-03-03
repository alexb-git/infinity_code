/****************************************************************************
** Filename:    - Q25.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Intoduction question to c++
** Date:        - 5/1/2018
** Version:     - 25
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
/****************************************************************************/


struct ABC
{
    explicit ABC(int);
    ~ABC();

    void Foo();
    void Bar() const;

    int  m_a;
    int *m_p;

private:
    void PrintInfo(const char *str, const char *clr, int m_a, int *m_p) const
    {
        std::cout << clr
        << std::left << std::setw(15) << str
        <<  " | m_a = "<< std::left << std::setw(2)  <<  m_a
        <<  " | m_p = "<< std::left << std::setw(6)  <<  m_p
        << " | *m_p = "<< std::left << std::setw(6)  << *m_p
        << std::endl;

    }
};

/*==========================  Ctor  ==========================*/
ABC::ABC(int a_): m_a(a_), m_p(new int(a_))
{
    PrintInfo("Ctor", GRE, m_a, m_p);
}

/*==========================  Dtor  ==========================*/
ABC::~ABC()
{
    PrintInfo("beg of Dtor", RED, m_a, m_p);

    delete m_p;
    m_p = NULL;
}

/*==========================  Foo Func  ==========================*/
void ABC::Foo()
{
    ++m_a;
    --(*m_p);

    PrintInfo("end of Foo func", BLU, m_a, m_p);
}

/*==========================  Bar Func  ==========================*/
void ABC::Bar() const
{
    // m_a = 0; //---1---
    // m_p = 0; //---2---
    // *m_p = 42; //---3---

    PrintInfo("end of Bar func", CYA, m_a, m_p);
}

/*==========================  Fifi Func  ==========================*/
void Fifi(const ABC &x_)
{
    // x_.Foo(); //---4---
    x_.Bar();
}

/*=======================  MAIN FUNCTION  =======================*/
int main(int argc, char const *argv[])
{
    ABC x1(1);

    x1.Foo();
    Fifi(x1);

    x1.Bar();

    return 0;
}
