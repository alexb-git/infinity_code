/****************************************************************************
** Filename:    - Q26.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Intoduction question to c++
** Date:        - 5/1/2018
** Version:     - 26
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

#define Alighl(X)         ( std::cout << std::left << std::setw(X) )
#define PrintOKorERR(X)   ( (X)?(PrintOK()):(PrintERR()) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )
/****************************************************************************/

class ABC;
int operator+ (const ABC &x1_, const ABC &x2_)
{
    return 666;
}

/*==========================  ABC class definition  ==========================*/
class ABC
{
public:
    ABC(): m_r(1), m_i(7) {}

    bool operator== (const ABC& o_) const
    {
        return ((m_r == o_.m_r) && (m_i == o_.m_i));
    }

private:
    friend std::ostream& operator<<(std::ostream& OS_, const ABC& x_);
    int m_r;
    int m_i;
};

std::ostream& operator<<(std::ostream& OS_, const ABC& x_)
{
    // x_.m_r = 123; /* ! read only ! */
    OS_ << x_.m_r << "+" << x_.m_i << "i";

    return OS_;
}

/*=======================  MAIN FUNCTION  =======================*/
int main(int argc, char const *argv[])
{
    ABC x1;
    ABC x2;

    Alighl(12) << "x1: ";
    std::cout << x1 << std::endl;

    Alighl(12) << "x2: ";
    std::cout << x2 << std::endl;

    Alighl(12) << "x1+x2: ";
    std::cout << x1 + x2 << std::endl;

    Alighl(12) << "(x1 == x2): ";
    std::cout << (x1==x2) << std::endl;


    return 0;
}
