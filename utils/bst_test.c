/****************************************************************************
** Filename:    - bst_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Binary Search Tree testing
** Date:        - 9/11/2017
** Version:     - 1
***************************************************/
#include <stdio.h>	/* printf 	*/
#include <stdlib.h> /* rand 	*/
#include <time.h>   /* time 	*/

#include "bst.h"    /* Header file for Binary Search Tree */

extern void print(const bst_handler_t *handler);

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

#define PrintInYellow(X)  ( printf(YELLOWS X RESET) )
#define PrintInGreen(X)   ( printf(GREEN   X RESET) )
#define PrintInRed(X)     ( printf(RED     X RESET) )
#define PrintOK           ( printf(GREEN "%s" RESET, "-OK\n") )
#define PrintERR          ( printf(RED "%s" RESET, "-ERR\n") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************
    Macros for this program
*****************************************************************************/
int myLongCmp(const void *data_1, const void *data_2, const void *param)
{
    return ( *(long*)data_1 - *(long*)data_2 );
}

int IsBiggerThanTen(void* element, const void *param)
{
    if ( *(long*)element > 10 )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*================ init the given array with random numbers ================*/
void InitArr(long arr[], long test_array[], size_t size)
{
	size_t i = 0;
    time_t t;

    srand((unsigned) time(&t));

	for ( ; i < size ; ++i)
	{
        arr[i] = rand() % size;
		test_array[i] = arr[i];
	}
}

/*============================ InsertAndCheck =============================*/
void InitTree(long arr[], size_t size, bst_handler_t *tree)
{
	size_t i = 0;
	size_t count_good_insertions = 0;

	for ( ; i < size ; ++i )
	{
		count_good_insertions += BSTInsert(tree, &arr[i]);
	}

    PrintOKorERR(count_good_insertions == size);
}

/*============================ InsertAndCheck =============================*/
void VerifyOrder(bst_handler_t *tree)
{
    bst_itr_t itr = BSTBegin(tree);
    bst_itr_t end = BSTEnd(tree);
    long prev_val = *(long*)BSTGetData(BSTBegin(tree));
    long curr_val;

    PrintInYellow("\nVerify order of the tree ");

    for ( ; itr != end ; itr = BSTNext(itr) )
    {
        curr_val = *(long*)BSTGetData(itr);

        if ( prev_val > curr_val )
        {
            PrintERR;
            return;
        }
    }

    PrintOK;
}


/*===========================  InsertionTestBst  ===========================*/
void InsertionTestBst()
{
    long elm2find;
	long arr[] = {  50,
                    25,75,
                    12,37,63,87,
                    6,18,31,43,57,70,80,95,
                    2,4,16,20,29,33,40,45,55,60,68,72,78,82,93,97,
                    1,7,13,22,39,47,62,83,100,74,5,0,52,51,59,58,94,14,24,38,
                    71,77,76,79,91,90,67,65,69,44,32,35};

    bst_handler_t *tree = BSTCreate(myLongCmp, NULL);
    bst_itr_t itr = NULL;

	PrintHeader("Binary Search Tree testing");

    /*===================  Check the newly created tree  ===================*/
	PrintInYellow("Counting on empty tree\n");
    printf("BSTIsEmpty(tree) == 1 ");
    PrintOKorERR(BSTIsEmpty(tree) == 1);
    printf("BSTCount(tree) == 0 ");
    PrintOKorERR(BSTCount(tree) == 0);

    /*============  Insert values into the tree, verify order  =============*/
	printf(YELLOWS "\nInserting %ld elements" RESET, SizeArr(arr));
	InitTree(arr, SizeArr(arr), tree);

    printf("\n");
    print(tree);
    printf("\n");

	PrintInYellow("Count and IsEmpty after inserting elements\n");
    printf("BSTIsEmpty(tree) == 0 ");
    PrintOKorERR(BSTIsEmpty(tree) == 0);
    printf("BSTCount(tree) == %ld ", SizeArr(arr));
    PrintOKorERR(BSTCount(tree) == SizeArr(arr));

    VerifyOrder(tree);

    /*====================  Find element and remove it  ====================*/
    elm2find = 75;
    printf(YELLOWS "\nFind Elemet %ld  " RESET, elm2find);
    itr = BSTFind(tree, &elm2find);
    PrintOKorERR(elm2find == *(long*)BSTGetData(itr));

    PrintInYellow("\nBSTRemove the found element\n");
    BSTRemove(itr);

    printf("\n");
    print(tree);
    printf("\n");

    /*====================  Find element and remove it  ====================*/
    elm2find = 50;
    printf(YELLOWS "\nFind Elemet %ld  " RESET, elm2find);
    itr = BSTFind(tree, &elm2find);
    PrintOKorERR(elm2find == *(long*)BSTGetData(itr));

    PrintInYellow("\nBSTRemove the found element\n");
    BSTRemove(itr);

    printf("\n");
    print(tree);
    printf("\n");

    /*====================  Check BSTForEach function  ====================*/
    PrintInYellow("\nFind first element that is bigger than 10 - ");
    itr = BSTForEach(BSTBegin(tree), BSTEnd(tree), IsBiggerThanTen, NULL);
    printf("%ld  ", *(long*)BSTGetData(itr));
    PrintOKorERR(10 < *(long*)BSTGetData(itr));

    /*============  Iterate over the tree and romove each node  ============*/
    itr = BSTBegin(tree);
    while ( !BSTIsEmpty(tree) )
    {
        itr = BSTRemove(itr);
    }

    PrintInYellow("\nAfter removing all checking for count 0 and is empty 1\n");
    PrintOKorERR(BSTCount(tree) == 0);
    PrintOKorERR(BSTIsEmpty(tree) == 1);

	BSTDestroy(tree);
}


/* ========================== THE MAIN FUNCTIONS ========================== */
int main(int argc, char const *argv[])
{
    InsertionTestBst();

    printf("\n");
    return 0;
}
/* ========================= END OF MAIN FUNCTIONS ========================*/
