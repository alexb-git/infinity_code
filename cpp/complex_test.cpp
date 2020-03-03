/****************************************************************************
** Filename:    - complex_test.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - testing of complex (numbers) class
** Date:        - 9/1/2018
** Version:     - 2
*****************************************************************************/
#include <iostream> /* cout, cin */
#include <iomanip>  /* std::setw */
#include <sstream>  /* stringstream */
#include <cstring>  /* strcmp */

#include "complex.h"

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
inline void PrintStatus(const char *name, ilrd::Complex &c_)
{
    std::cout << name << " : " << CYA BLD << c_ << RES;
}

inline void CheckResult(ilrd::Complex &c_, double real, double imaginary)
{
    std::cout << "  ";
    PrintOKorERR(c_.GetRe() == real);
    PrintOKorERR(c_.GetIm() == imaginary);
    std::cout << std::endl;
}

inline void StatusAndChech(const char *name, ilrd::Complex &c_,
                      double real, double imaginary)
{
    PrintStatus(name, c_);
    CheckResult(c_, real, imaginary);
}
/*==========================  MAIN FUNCTION  ==========================*/
int main(int argc, char const *argv[])
{
    /*===========  Check constructors  ===========*/
    PrintInYellow("\n-> Check constructors\n");
    ilrd::Complex c1(1,2);
    ilrd::Complex c2(3,4);
    ilrd::Complex res;

    StatusAndChech("c1", c1, 1, 2);
    StatusAndChech("c2", c2, 3, 4);

    /*===========  Check c1 != c2  ===========*/
    PrintInYellow("\n-> Check c1 != c2\n");
    PrintOKorERR((c1 != c2) == true);

    /*=================  Check arithmetic operators  =================*/
    PrintInYellow("\n\n-> Check (1+2i)+(3+4i)\n");
    res = c1 + c2;
    StatusAndChech("res", res, 4, 6);

    PrintInYellow("-> Check (1+2i)-(3+4i)\n");
    res = c1 - c2;
    StatusAndChech("res", res, -2, -2);

    PrintInYellow("-> Check (1+2i)*(3+4i)\n");
    res = c1 * c2;
    StatusAndChech("res", res, -5, 10);

    PrintInYellow("-> Check (1+2i)/(3+4i)\n");
    res = c1 / c2;
    StatusAndChech("res", res, 0.44, 0.08);

    /*=================  Check global operators  =================*/
    std::stringstream out;

    PrintInYellow("\n-> Check 'operator<<' on (1+2i)+(3+4i)\n");
    out << c1 + c2;
    std::cout << out.str().c_str();
    PrintOKorERR(strcmp("4+6i", out.str().c_str()) == 0);

    out.str("");
    PrintInYellow("\n-> Check 'operator<<' on (1+2i)-(3+4i)\n");
    out << c1 - c2;
    std::cout << out.str().c_str();
    PrintOKorERR(strcmp("-2-2i", out.str().c_str()) == 0);

    out.str("");
    PrintInYellow("\n-> Check 'operator<<' on (1+2i)*(3+4i)\n");
    out << c1 * c2;
    std::cout << out.str().c_str();
    PrintOKorERR(strcmp("-5+10i", out.str().c_str()) == 0);

    out.str("");
    PrintInYellow("\n-> Check 'operator<<' on (1+2i)/(3+4i)\n");
    out << c1 / c2;
    std::cout << out.str().c_str();
    PrintOKorERR(strcmp("0.44+0.08i", out.str().c_str()) == 0);

    /*===========  Check c1 = c2  ===========*/
    PrintInYellow("\n\n-> Check c1 = c2\n");
    c1 = c2;
    PrintStatus("c1", c1);
    std::cout << std::endl;
    PrintStatus("c2", c2);
    PrintOKorERR((c1 == c2) == true);

    PrintInYellow("\n\n-> Check c2 = 666\n");
    c2 = 666;
    StatusAndChech("c2", c2, 666, 0);

    /*===========  Check c1 = c2  ===========*/
    PrintInYellow("\n-> Check  c1 += 6\n");
    c1 += 6;
    StatusAndChech("c1", c1, 9, 4);

    PrintInYellow("-> Check  c1 -= 3\n");
    c1 -= 3;
    StatusAndChech("c1", c1, 6, 4);

    PrintInYellow("-> Check  c1 *= 2\n");
    c1 *= 2;
    StatusAndChech("c1", c1, 12, 8);

    PrintInYellow("-> Check  c1 /= 4\n");
    c1 /= 4;
    StatusAndChech("c1", c1, 3, 2);

    /*===========  Check istream  ===========*/
    PrintInYellow("\n-> Check istream\n");
    std::stringstream in;

    in << "10+15i";
    in >> c1;
    StatusAndChech("c1", c1, 10, 15);

    in << "-3.14-3.14i";
    in >> c1;
    StatusAndChech("c1", c1, -3.14, -3.14);

    /*===========  Check istream  ===========*/
    std::cout << std::endl;
    in << "5+0i";
    in >> c1;
    PrintStatus("c1", c1);

    PrintInYellow("\n-> Check  c1 == 5\n");
    PrintOKorERR((c1 == 5) == true);

    PrintInYellow("\n\n-> Check  5 == c1\n");
    PrintOKorERR((5 == c1) == true);

    std::cout << std::endl;
    return 0;
}
