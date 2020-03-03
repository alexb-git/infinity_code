/****************************************************************************
** Filename:    - search_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - searching algorithms testing
** Date:        - 29/11/2017
** Version:     - 1
*****************************************************************************/
#include <stdio.h>      /* printf */
#include <time.h>       /* time */
#include <stdlib.h>     /* rand */

#include "search.h"      /* searching algorithms */

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
#define PrintOK           ( printf(GREEN "%s" RESET, "-OK") )
#define PrintERR          ( printf(RED "%s" RESET, "-ERR") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************
    Macros for this program
*****************************************************************************/
#define TimeDiff(X) ( (double)(clock() - X)/CLOCKS_PER_SEC )
#define PrintTimeDiff printf("%f [seconds]", TimeDiff(befor))

#define ELEMENTS    (30000)
#define TO_FIND     (10000)

/*========================  LONG COMPARE FUNCTION  ========================*/
int LeftMinusRight(const void *left, const void *right)
{
    return ( *(long*)left - *(long*)right );
}

/*==========================  SetArrays FUNCTION  ==========================*/
void SetArrays(long arr[], size_t size )
{
    size_t i;
    srand(clock());

    for ( i = 0 ; i < size ; ++i )
    {
        arr[i] = rand() % ELEMENTS;
    }
}

/*==========================  SetSearch FUNCTION  ==========================*/
void SetSearch(long to_find[], size_t find_size, long arr[], size_t arr_size)
{
    size_t i;
    srand(clock());

    for ( i = 0 ; i < find_size ; ++i )
    {
        size_t index = rand() % arr_size;
        to_find[i] = arr[index];
    }
}

/*==========================  PrintLongArr FUNCTION  ==========================*/
void PrintLongArr(void *arr, size_t size)
{
    long *arr_long = (long*)arr;
    size_t i = 0;

    printf("{");
    for ( ; i < size ; ++i)
    {
        printf(" %ld,", arr_long[i]);

    }
    printf("}\n");
}

/*==========================  THE MAIN FUNCTIONS  ==========================*/
int main(int argc, char const *argv[])
{
    /*long arr2[] = { 1,2,3,4,5,6,7,8,9,10};*/
    int     err_flag = 0;
    clock_t befor;
    size_t  i;

    long  arr[ELEMENTS];
    long  to_find[TO_FIND];
    long  unreachable = 1000000000;
    void *result = NULL;

    /* set array to randomized numbers */
    SetArrays( arr, ELEMENTS);

    /* sort randomized array */
    qsort(arr, ELEMENTS, sizeof(arr[0]), LeftMinusRight);

    /* set to search ('to_find') array */
    SetSearch(to_find, TO_FIND, arr, ELEMENTS);

    printf( YELLOWS
            "For each search. Search for %d elements in %d element array\n"RESET,
            TO_FIND, ELEMENTS);

    /*======================  Testing IterBinarySearch  ======================*/
    befor = clock(); PrintInYellow("\nIterBinarySearch  "); err_flag = 0;

    for ( i = 0 ; i < TO_FIND ; ++i )
    {
        result = IterBinarySearch( arr, SizeArr(arr), sizeof(arr[0]),
                                   LeftMinusRight, to_find + i      );

        /*printf("\nto_find = %ld | result = %ld ", *(long*)result, to_find[i] );*/
        /*PrintOKorERR( *(long*)result == to_find[i] );*/

        if ( *(long*)result != to_find[i] )
        {
            err_flag = 1;
            break;
        }
    }
    (err_flag)?(PrintERR):(PrintOK);

    result = IterBinarySearch( arr, SizeArr(arr), sizeof(arr[0]),
                               LeftMinusRight, &unreachable     );
    PrintOKorERR( result == NULL);


    printf("\n"); PrintTimeDiff; printf("\n");

    /*======================  Testing RecBinarySearch  ======================*/
    befor = clock(); PrintInYellow("\nRecBinarySearch  "); err_flag = 0;

    for ( i = 0 ; i < TO_FIND ; ++i )
    {
        result = RecBinarySearch( arr, SizeArr(arr), sizeof(arr[0]),
                                  LeftMinusRight, to_find + i      );

        /*printf("\nto_find = %ld | result = %ld ", *(long*)result, to_find[i] );*/
        /*PrintOKorERR( *(long*)result == to_find[i] );*/

        if ( *(long*)result != to_find[i] )
        {
            err_flag = 1;
            break;
        }
    }
    (err_flag)?(PrintERR):(PrintOK);

    result = RecBinarySearch( arr, SizeArr(arr), sizeof(arr[0]),
                              LeftMinusRight, &unreachable     );
    PrintOKorERR( result == NULL);

    printf("\n"); PrintTimeDiff; printf("\n");

    /*======================  Testing JumpSearch  ======================*/
    befor = clock(); PrintInYellow("\nJumpSearch  "); err_flag = 0;

    for ( i = 0 ; i < TO_FIND ; ++i )
    {
        result = JumpSearch( arr, SizeArr(arr), sizeof(arr[0]),
                             LeftMinusRight, to_find + i      );

        /*printf("\nto_find = %ld | result = %ld ", *(long*)result, to_find[i] );*/
        /*PrintOKorERR( *(long*)result == to_find[i] );*/

        if ( *(long*)result != to_find[i] )
        {
            err_flag = 1;
            break;
        }
    }
    (err_flag)?(PrintERR):(PrintOK);

    result = JumpSearch( arr, SizeArr(arr), sizeof(arr[0]),
                         LeftMinusRight, &unreachable     );
    PrintOKorERR( result == NULL);

    printf("\n"); PrintTimeDiff; printf("\n");




    printf("\n");
    return 0;
}
/*=========================  END OF MAIN FUNCTIONS  =========================*/
