/****************************************************************************
** Filename:    - allocator_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - testing the Allocator
** Date:        - 26/10/2017
** Version:     - 8659
***************************************************/
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc */

#include "allocator.h"    /* Fixed Size Allocator */

/****************************************************************************
    Helpful colors
*****************************************************************************/
#define GREEN	"\x1b[92m"
#define RED		"\x1b[91m"
#define YELLOW	"\x1b[93m"
#define YELLOWS	"\x1b[33m"
#define RESET	"\x1b[0m"
#define BLUE	"\x1B[34m"
#define CYAN	"\x1B[36m"
#define WHITE	"\x1B[37m"

/****************************************************************************
    Helpful defines
*****************************************************************************/
#define PrintHeader(X)      printf( BLUE "\n\t------------"\
                                    "  This is a test for: "\
                                    X" ------------\n" RESET)

#define PrintInYellow(X)  ( printf(YELLOW X RESET) )
#define PrintInGreen(X)   ( printf(GREEN  X RESET) )
#define PrintInRed(X)     ( printf(RED    X RESET) )
#define PrintOK           ( printf(GREEN "%5s" RESET, "-OK") )
#define PrintERR          ( printf(RED "%5s" RESET, "-ERR") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************/



/*==========================  TestAllocAndFree  ==========================*/
void TestAllocAndFree()
{
    long i = 0;
    size_t num_of_bytes  = 90;

	void *buffer = malloc(num_of_bytes);

	allocator_t *allocator = AllocatorCreate(buffer, num_of_bytes);

    void *element[5];

  	PrintHeader("Test Alloc And Free");

  	PrintInYellow("\n\n--> Try to allocate bigger than buffer ");
    PrintInYellow("block (should return NULL)");
    element[0] = AllocatorAlloc(allocator, 90);
    PrintOKorERR( element[0] == NULL );

    PrintInYellow("\n\n--> allocate 3 chunks of 10 bytes ");
    PrintInYellow("[(16+8)+(16+8)+(34) = 82 effectivly]");
  	for ( i = 0 ; i < 3 ; ++i )
  	{
  		element[i] = AllocatorAlloc(allocator, 10);
        PrintOKorERR( element[i] != NULL );
  	}

    PrintInYellow("\n\n--> allocate one more 1 byte chunk (should return NULL)");
    element[3] = AllocatorAlloc(allocator, 1);
    PrintOKorERR( element[i] == NULL );

    PrintInYellow("\n\n--> deallocate first two segments, then allocate ");
    PrintInYellow("one chunk of 25 bytes [48 effectivly]");
    AllocatorFree(allocator, element[0]);
    AllocatorFree(allocator, element[1]);
    element[0] = AllocatorAlloc(allocator, 25);
    PrintOKorERR( element[0] != NULL );

    PrintInYellow("\n\n--> allocate one more 1 byte chunk (should return NULL)");
    element[1] = AllocatorAlloc(allocator, 1);
    PrintOKorERR( element[i] == NULL );

    PrintInYellow("\n\n--> deallocate segments, then allocate ");
    PrintInYellow("one chunk of 1 bytes [16 effectivly]");
    AllocatorFree(allocator, element[0]);
    element[0] = AllocatorAlloc(allocator, 1);
    PrintOKorERR( element[0] != NULL );

    PrintInYellow("\n\n--> allocate one chunk of 9 bytes [32 effectivly]");
    element[1] = AllocatorAlloc(allocator, 9);
    PrintOKorERR( element[1] != NULL );

    PrintInYellow("\n\n--> allocate one chunk of 1 bytes ");
    PrintInYellow("(should return NULL)");
    element[2] = AllocatorAlloc(allocator, 1);
    PrintOKorERR( element[2] == NULL );

    printf("\n\n");
  	free(buffer);
}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
	TestAllocAndFree();

	return 0;
}
