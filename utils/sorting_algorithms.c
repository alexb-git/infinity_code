/****************************************************************************
** Filename:    - sorting_algorithms.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - sorting algorithms testing and writing
** Date:        - 1/1/2017
** Version:     - 1
***************************************************/
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* malloc, free */
#include <string.h>     /* memcpy */

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


/*==========================  PRINT ARRAY FUNCTION  ==========================*/
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

/*==========================  SWAP FUNCTION  ==========================*/
void Swap (void *cell_1, void *cell_2, size_t elem_size)
{
    void *temp = malloc ( elem_size );

    memcpy( temp  , cell_1, elem_size );
    memcpy( cell_1, cell_2, elem_size );
    memcpy( cell_2, temp  , elem_size );

    free(temp);
    temp = NULL;
}

#define Next(X) ( (char*)X + size )
#define Prev(X) ( (char*)X - size )
/****************************************************************************
    SORT FUNCTION - SELECTION_SORT
*****************************************************************************/
void SelectionSort( void *base, size_t nmemb, size_t size,
                    int (*compar)(const void *, const void *) )
{
    void *last_element = (char*)base + nmemb * size;
    void *before_last  = (char*)last_element - size;

    void *for_print = base; /* TODO: delete in release */

    for ( ; base < before_last ; base = Next(base) )
    {
        void *cur_min = base;
        void  *runner = Next(base);

        PrintLongArr(for_print, nmemb); /* TODO: delete in release */

        for ( ; runner < last_element ; runner = Next(runner) )
        {
            if ( compar(runner, cur_min) )
            {
                cur_min = runner;
            }
        }

        Swap( base, cur_min, size );
    }
}


/****************************************************************************
    SORT FUNCTION - INSERTION_SORT
*****************************************************************************/
void InsertionSort( void *base, size_t nmemb, size_t size,
                    int (*compar)(const void *, const void *) )
{
    void *start         = base;
    void *last_element  = (char*)base + nmemb * size;
    void *to_insert     = malloc(size);

    for ( base = Next(base) ; base < last_element ; base = Next(base) )
    {
        void *runner    = base;
        memcpy(to_insert, base, size);

        for ( ; runner > start ; runner = Prev(runner) )
        {
            if ( compar( Prev(runner), to_insert) )
            {
                /* position for insertion found */
                break;
            }

            /* shift the sorted part to right */
            memcpy(runner, Prev(runner), size);
        }

        memcpy(runner, to_insert, size);

        PrintLongArr(start, nmemb); /* TODO: delete in release */
    }

    free(to_insert);
    to_insert = NULL;
}

/****************************************************************************
    SORT FUNCTION - BUBBLE_SORT
*****************************************************************************/
void BubbleSort ( void *base, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *) )
{
    void *start = base;
    base  = (char*)base + ( nmemb - 1 ) * size;

    for ( ; base >= start ; base = Prev(base) )
    {
        void *runner = start;

        /* bubble up */
        for ( ; (char*)runner <= Prev(base) ; runner = Next(runner) )
        {
            if ( compar( Next(runner), runner) )
            {
                Swap(runner, Next(runner), size );
            }
        }
        PrintLongArr(start, nmemb);
    }
}

/*========================  LONG COMPARE FUNCTION  ========================*/
int IsLeftSmaller(const void *left, const void *right)
{
    return ( *(long*)left < *(long*)right );
}


/*==========================  THE MAIN FUNCTIONS  ==========================*/
int main(int argc, char const *argv[])
{
    long arr_1[] = {2, 3, 1, 9, 5, 6, 4, 7, 8, 0};
    long arr_2[] = {2, 3, 1, 9, 5, 6, 4, 7, 8, 0};
    long arr_3[] = {2, 3, 1, 9, 5, 6, 4, 7, 8, 0};

    PrintInYellow("\nSelectionSort\n");
    SelectionSort(arr_1, SizeArr(arr_1), sizeof(arr_1[0]), IsLeftSmaller);

    PrintInYellow("\nInsertionSort\n");
    InsertionSort(arr_2, SizeArr(arr_2), sizeof(arr_2[0]), IsLeftSmaller);

    PrintInYellow("\nBubbleSort\n");
    BubbleSort(arr_3, SizeArr(arr_3), sizeof(arr_3[0]), IsLeftSmaller);

    return 0;
}
