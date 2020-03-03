/****************************************************************************
** Filename:    - string_test.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Tests for String library
** Date:        - 8/1/2018
** Version:     - 6
*****************************************************************************/
#include <iostream> /* cout, cin */
#include <cstdio>   /* puts */
#include <iomanip>  /* std::setw */
#include <cstring>  /* strcmp */
#include <sstream>  /* stringstream */

#include "string.h"

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
inline void PrintStatus(const char *name, ilrd::String &str)
{
    std::cout << name << " : " << YEL << "\"" << str << "\"" << RES
    << " | Length = " << str.Length() << std::endl;
}

/*==========================  MAIN FUNCTION  ==========================*/
int main(int argc, char const *argv[])
{
    /*===========  Check constructors  ===========*/
    PrintInYellow("\n-> Check constructors\n");
    ilrd::String s1 = "abcd";
    ilrd::String s2(s1);
    PrintStatus("s1", s1);
    PrintStatus("s2", s2);
    PrintOKorERR(s1 == s2);

    /*===========  Check puts  ===========*/
    PrintInYellow("\n\n-> Check self assignment problem in ctor\n");
    s1 = s1;
    PrintStatus("s1", s1);
    PrintOKorERR((s1 == s1) == true);

    /*===========  Check ostream  ===========*/
    PrintInYellow("\n\n-> Check ostream\n");
    std::stringstream out;
    out << s1;
    PrintOKorERR(strcmp(s1.GetString(), out.str().c_str()) == 0);

    /*===========  Check istream  ===========*/
    PrintInYellow("\n\n-> Check istream\n");
    // PrintInYellow("Enter some string : ");
    std::stringstream in;
    in << "istream test";
    in >> s2;
    // std::cin >> s2;
    PrintStatus("s2", s2);

    /*===========  Check s2 = s1  ===========*/
    PrintInYellow("\n-> Check s2 = s1\n");
    s1 = s2;
    PrintStatus("s1", s1);
    PrintStatus("s2", s2);
    PrintOKorERR(s1 == s2);

    /*===========  Check str ="1234" && '>'/'<'/'!='  ===========*/
    PrintInYellow("\n\n-> Check str = (string literal), '>'/'<'/'!='\n");
    s1 = "1234";
    s2 = "1233";
    PrintStatus("s1", s1);
    PrintStatus("s2", s2);
    PrintInYellow("\n(?) s1 != s2 : TRUE  "); PrintOKorERR((s1 != s2) == true);
    PrintInYellow("\n(?) s1 > s2  : TRUE  "); PrintOKorERR((s1  > s2) == true);
    PrintInYellow("\n(?) s1 < s2  : FALSE "); PrintOKorERR((s1  < s2) == false);

    /*===========  Check s1[2] = 'X' && s1[1]=='F' && 'F'==s1[1] ===========*/
    PrintInYellow("\n\n-> Check 'str[index] = (char)'\n");
    s1[1] = 'F';
    PrintStatus("s1", s1);

    PrintInYellow("-> Check 'str[index] == (char)'");
    PrintOKorERR((s1[1] == 'F') == true);

    PrintInYellow("\n-> Check '(char) == str[index]'");
    PrintOKorERR(('F' == s1[1]) == true);

    /*===========  Check Concat  ===========*/
    PrintInYellow("\n\n-> Check s1.Concat(s2)\n");
    s1.Concat(s2);
    PrintStatus("s1", s1);
    PrintOKorERR(s1 == "1F341233");

    /*===========  Check puts  ===========*/
    PrintInYellow("\n\n-> Check puts\n");
    puts(s1.GetString());


    // std::string mystr = "0123456789";
    //
    // std::cout << mystr << std::endl;
    // std::cout << mystr[4] << std::endl;
    // std::cout << mystr.length() << std::endl;
    // std::cout << "sizeof(mystr) " << sizeof(mystr) << std::endl;
    // std::cout << "std::string " << sizeof(std::string) << std::endl;
    //
    // mystr[1] = '\0';
    // mystr[2] = '\0';
    //
    // // mystr = "abcd";
    //
    // // mystr = "defg";
    // std::cout << mystr << std::endl;
    // std::cout << mystr[3] << std::endl;
    // std::cout << mystr.length() << std::endl;
    //
    // mystr = "abc";
    //
    // std::cout << mystr << std::endl;
    // std::cout << mystr[3] << std::endl;
    // std::cout << mystr.length() << std::endl;
    // // mystr.a

    std::cout << std::endl;
    return 0;
}
