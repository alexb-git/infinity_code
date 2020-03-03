/****************************************************************************
** Filename:    - slinkedl_test.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Tests for Singly Linked List (implemented with c++)
** Date:        - 5/1/2018
** Version:     - 4
*****************************************************************************/
#include <iostream> /* cout */
#include <iomanip>  /* std::setw */

#include "slist.h"

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
inline void PrintStatus(ilrd::SLinkedList &slist)
{
    std::cout << YEL "IsEmpty = " << slist.IsEmpty()
    << " | Size of list = " << slist.GetSize() << RES << std::endl;
}

/*==========================  MAIN FUNCTION  ==========================*/
int main(int argc, char const *argv[])
{
    ilrd::SLinkedList slist;

    PrintInYellow("-> SlinkedList created\n");
    PrintStatus(slist);

    PrintInYellow("\n-> Inserting 9 elements\n");
    long arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for( size_t i = 0 ; i < SizeArr(arr) ; ++i )
    {
        slist.PushFront(arr + i);
        PrintOKorERR( *reinterpret_cast<long*>(slist.Peek()) == arr[i]);
        std::cout << " | ";
        PrintStatus(slist);
    }
    // slist.PrintList(arr[0]);
    PrintInYellow("\n(?) Number of elements inserted  as required: ");
    PrintOKorERR(slist.GetSize() == 9);

    PrintInYellow("\n\n-> Pop elements till empty\n");
    for( size_t i = SizeArr(arr) - 1 ; !slist.IsEmpty() ; --i )
    {
        PrintOKorERR( *reinterpret_cast<long*>(slist.Peek()) == arr[i]);
        slist.PopFront();
        std::cout << " | ";
        PrintStatus(slist);
    }
    // slist.PrintList(arr[0]);
    PrintInYellow("\n(?) List is empty and Size is zero: ");
    PrintOKorERR(slist.IsEmpty() == 1);
    PrintOKorERR(slist.GetSize() == 0);

    PrintInYellow("\n\n-> Push the whole array to chech proper deallocation with vlg\n");
    for( size_t i = 0 ; i < SizeArr(arr) ; ++i )
    {
        slist.PushFront(arr + i);
    }

    std::cout << std::endl;
    return 0;
}
