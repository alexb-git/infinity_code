/****************************************************************************
** Filename:    - bit_array_test.cpp
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - bits array data structure testing
** Date:        - 31/1/2018
** Version:     - 1
*****************************************************************************/
#include <iostream>    /* cin, cout */
#include "bit_array.h" /* Bits array data structure */

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

#define PrintStatus(BitArr, len)\
std::cout << BitArr <<"   ";\
std::cout << CYA "BitsOn = " << BitArr.CountSetBit() << RES;\
PrintOKorERR(BitArr.CountSetBit() == len);


int main(int argc, char const *argv[])
{
    ilrd::BitsArray<5> local_1;
    ilrd::BitsArray<5> local_2;
    ilrd::BitsArray<6> local_3;

    PrintInYellow("\n-> Init three BitArrays\n");
    PrintStatus(local_1, 0);

    PrintInYellow("\n\n-> local_1 == local_2 ");
    PrintOKorERR((local_1 == local_2) == true);

    PrintInYellow("\n-> local_1 != local_2 ");
    PrintOKorERR((local_1 != local_2) == false);

    // /* does not compile ! types do not match */
    // PrintInYellow("-> local_1 == local_3");
    // PrintOKorERR((local_1 == local_3) == true);

    PrintInYellow("\n\n-> local_1.FlipAll()\n");
    local_1.FlipAll();
    PrintStatus(local_1, 5);

    PrintInYellow("\n\n-> local_1.SetBit(0,0)\n");
    local_1.SetBit(0, 0);
    PrintStatus(local_1, 4);

    PrintInYellow("\n\n-> local_1.FlipBit(2)\n");
    local_1.FlipBit(2);
    PrintStatus(local_1, 3);

    PrintInYellow("\n\n-> local_1.FlipAll()\n");
    local_1.FlipAll();
    PrintStatus(local_1, 2);

    PrintInYellow("\n\n-> local_2 |= local_1\n");
    PrintStatus(local_1, 2); std::cout << std::endl;
    PrintStatus(local_2, 0); std::cout << std::endl;
    local_2 |= local_1;
    PrintStatus(local_2, 2); std::cout << std::endl;

    PrintInYellow("\n\n-> local_2 ^= local_1\n");
    PrintStatus(local_1, 2); std::cout << std::endl;
    PrintStatus(local_2, 2); std::cout << std::endl;
    local_2 ^= local_1;
    PrintStatus(local_2, 0); std::cout << std::endl;

    PrintInYellow("\n\n-> local_2.FlipAll()");
    local_2.FlipAll();
    PrintInYellow("\n-> local_2 &= local_1\n");
    PrintStatus(local_1, 2); std::cout << std::endl;
    PrintStatus(local_2, 5); std::cout << std::endl;
    local_2 &= local_1;
    PrintStatus(local_2, 2); std::cout << std::endl;

    PrintInYellow("\n\n-> local_1[1]\n");
    local_1[1] = 1;
    PrintStatus(local_1, 3);

    PrintInYellow("\n\n-> local_1[1] == 1 (!=)\n");
    PrintOKorERR((local_1[1] == 1) == true);
    PrintOKorERR((local_1[1] != 1) == false);

    PrintInYellow("\n\n-> local_1[4] = local_2[0]\n");
    local_1[4] = local_2[0];
    PrintStatus(local_1, 4);

    PrintInYellow("\n\n-> local_1[5] == local_2[0] (!=)\n");
    PrintOKorERR((local_1[4] == local_2[0]) == true);
    PrintOKorERR((local_1[4] != local_2[0]) == false);

    ilrd::BitsArray<65> local_4;
    PrintInYellow("\n\n-> create BitsArray<65> + flip every even bit\n");
    for ( int i = 0 ; i < 65 ; i = i + 2 )
    {
        local_4.FlipBit(i);
    }
    PrintStatus(local_4, 33);

    PrintInYellow("\n\n-> local_4.FlipAll()\n");
    local_4.FlipAll();
    PrintStatus(local_4, 32);

    PrintInYellow("\n\n->  for i < 65: local_4[i] = local_4[i + 1]\n");
    for ( int i = 0 ; i < 65 ; i = i + 2 )
    {
        local_4[i] = local_4[i + 1];
    }
    PrintStatus(local_4, 64);




    std::cout << std::endl;
    return 0;
}
