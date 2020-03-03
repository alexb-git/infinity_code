/****************************************************************************
** Filename:    - avl_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - AVL tree testing
** Date:        - 20/11/2017
** Version:     - 3
***************************************************/
#include <stdlib.h> /* calloc */
#include <stdio.h>	/* printf */
#include <time.h>   /* time   */
#include <string.h> /* strlen, strcmp, strncmp */

#include "avl.h"   /* Stack data structure */

/* gd avl.c avl_test.c queue.c slist.c -lm */
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
#define PrintOK           ( printf(GREEN "%s" RESET, "-OK") )
#define PrintERR          ( printf(RED "%s" RESET, "-ERR") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************
    Macros for this program
*****************************************************************************/


/*=========================  FUNCTION DECLARATION  =========================*/
extern void print(void *handler);
extern void IsBalanced(void *handler);

int Compare(const void* data1, const void* data2)
{
    return *(long*)data1 - *(long*)data2;
}

int IsEqual(void* data, const void* param)
{
    return *(long*)data != *(long*)param;
}

int TreeSum(void* data, const void* param)
{
    *(long*)param += *(long*)data;
    return 1;
}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
    long arr[] = {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
                   20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 21, 22 };

    long  param;
    void *found;

    long  tree_sum  = 0;
    long  array_sum = 0;


    /*===================  Check the newly created tree  ===================*/
    avl_handler_t* handler = AVLCreate(Compare);
    size_t i = 0;

    for( i = 0 ; i < SizeArr(arr) ; ++i )
    {
        array_sum += arr[i];
        AVLInsert(handler, arr + i );
    }

    printf( "size after insertion: %ld depth :%ld",
            AVLSize(handler), AVLHeight(handler));
    PrintOKorERR( AVLSize(handler) == SizeArr(arr) );

    AVLForEach(handler, TreeSum, &tree_sum);

    printf("\n");
    IsBalanced(handler);
    print(handler);

    /*===================  Erase Element from the tree  ====================*/
    param = 16; tree_sum = 0;
    printf(YELLOWS "\nErase element %ld " RESET, param);
    AVLRemove(handler, &param);

    AVLForEach(handler, TreeSum, &tree_sum);
    array_sum -= param;
    PrintOKorERR(array_sum == tree_sum);

    printf("\n");
    IsBalanced(handler);
    print(handler);

    /*===================  Erase Element from the tree  ====================*/
    param = 22; tree_sum = 0;
    printf(YELLOWS "\nErase element %ld " RESET, param);
    AVLRemove(handler, &param);

    AVLForEach(handler, TreeSum, &tree_sum);
    array_sum -= param;
    PrintOKorERR(array_sum == tree_sum);

    printf("\n");
    IsBalanced(handler);
    print(handler);

    /*===================  Erase Element from the tree  ====================*/
    param = 21; tree_sum = 0;
    printf(YELLOWS "\nErase element %ld " RESET, param);
    AVLRemove(handler, &param);

    AVLForEach(handler, TreeSum, &tree_sum);
    array_sum -= param;
    PrintOKorERR(array_sum == tree_sum);

    printf("\n");
    IsBalanced(handler);
    print(handler);

    /*===================  Erase Element from the tree  ====================*/
    param = 17; tree_sum = 0;
    printf(YELLOWS "\nErase element %ld " RESET, param);
    AVLRemove(handler, &param);

    AVLForEach(handler, TreeSum, &tree_sum);
    array_sum -= param;
    PrintOKorERR(array_sum == tree_sum);

    printf("\n");
    IsBalanced(handler);
    print(handler);

    /*===================  Erase Element from the tree  ====================*/
    param = 8; tree_sum = 0;
    printf(YELLOWS "\nErase element %ld " RESET, param);
    AVLRemove(handler, &param);

    AVLForEach(handler, TreeSum, &tree_sum);
    array_sum -= param;
    PrintOKorERR(array_sum == tree_sum);

    printf("\n");
    IsBalanced(handler);
    print(handler);

    /*===================  AVLForEach function test  ========================*/
    param = 20;
    printf(YELLOWS "\nFind element %ld " RESET, param);
    found = AVLForEach(handler, IsEqual, &param);
    printf("\nFound element = %d  ", *(int*)found);
    PrintOKorERR( *(int*)found == param );

    param = 200;
    printf(YELLOWS "\nFind element %ld " RESET, param);
    found = AVLForEach(handler, IsEqual, &param);
    printf("\n(should be) NULL  ");
    PrintOKorERR( found == NULL );

    printf("\n");
    print(handler);

    /*===================  AVLFind function test  ========================*/
    param = 19;
    printf(YELLOWS "\nAVLFind element %ld " RESET, param);
    found = AVLFind(handler, &param);
    printf("\nFound element = %d  ", *(int*)found);
    PrintOKorERR( *(int*)found == param );

    /*===================  AVLFind function test  ========================*/
    param = 200;
    printf(YELLOWS "\nAVLFind element %ld " RESET, param);
    found = AVLFind(handler, &param);
    printf("\n(should be) NULL  ");
    PrintOKorERR( found == NULL );


    printf("\n");
    AVLDestroy(handler);
    return 0;
}
