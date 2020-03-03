/****************************************************************************
** Filename:    - fixed_allocator_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - testing the Fixed Size Allocator
** Date:        - 25/10/2017
** Version:     - 2
***************************************************/
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc */
#include <string.h>	/* memset */

#include "fixed_allocator.h"    /* Fixed Size Allocator */

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


/****************************************************************************
    check if the content inside the given buffer is as expected
*****************************************************************************/
void CheckValues(void **element, size_t num_of_elements)
{
	size_t i = 0;
    PrintInYellow("\n--> verify the content inside the buffer\n");

	for ( i = 0 ; i < num_of_elements ; ++i )
	{
        PrintOKorERR( *(char*)element[i] == i );
	}
}

/*==========================  TestAllocAndFree  ==========================*/
void TestAllocAndFree()
{
    size_t i;
    size_t num_of_elements  = 4;
    size_t block_size       = 5; /* in bytes */
    size_t buffer_min_size  = FAllocatorGetMinSize(num_of_elements, block_size);

	void *buffer = malloc(buffer_min_size);

	fallocator_t *allocator =
                        FAllocatorCreate(buffer, buffer_min_size, block_size);

	/* array of pointes to elements in the buffer + 1 for overflow check */
  	void *element[4 + 1];

  	PrintHeader("TestAllocAndFree");

  	PrintInYellow("--> Allocating 3 out of 4 block\n");
  	for ( i = 0 ; i < num_of_elements - 1 ; ++i )
  	{
  		element[i] = FAllocatorAlloc(allocator);
        PrintOKorERR( element[i] != NULL );
  		memset(element[i], i, block_size);
  	}

  	PrintInYellow("\n--> verify: there is only one more free block\n");
    PrintOKorERR( FAllocatorCountFree(allocator) == 1);

    PrintInYellow("\n--> fill the last block\n");
  	element[i++] = FAllocatorAlloc(allocator);
  	memset(element[i-1], i-1, block_size);
    PrintOKorERR( FAllocatorCountFree(allocator) == 0);

    PrintInYellow("\n--> try to allocate one more block (should return NULL)\n");
  	element[i] = FAllocatorAlloc(allocator);
    PrintOKorERR( element[i] == NULL );

  	CheckValues(element, num_of_elements);

    PrintInYellow("\n--> free 2 blocks of memory\n");
  	FAllocatorFree(allocator, element[0]);
  	FAllocatorFree(allocator, element[1]);
    PrintOKorERR( FAllocatorCountFree(allocator) == 2 );

  	PrintInYellow("\n--> allocate 2 blocks\n");
  	element[0] = FAllocatorAlloc(allocator);
    PrintOKorERR( element[1] != NULL);

  	element[1] = FAllocatorAlloc(allocator);
    PrintOKorERR( element[1] != NULL);

    printf("\n");
  	free(buffer);
}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
	TestAllocAndFree();

	return 0;
}
