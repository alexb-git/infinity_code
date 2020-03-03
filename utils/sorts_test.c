/****************************************************************************
** Filename:    - sorts_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - sorting algorithms testing
** Date:        - 21/11/2017
** Version:     - 6
****************************************************************************/
#include <stdio.h>      /* printf */
#include <time.h>       /* time */
#include <stdlib.h>     /* rand */

#include "sorts.h"      /* sorts */

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
#define PrintOK           ( printf(GREEN "%5s" RESET, "-OK\n") )
#define PrintERR          ( printf(RED "%5s" RESET, "-ERR\n") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************
    Macros for this program
*****************************************************************************/
#define TimeDiff(X) ( (double)(clock() - X)/CLOCKS_PER_SEC )
#define PrintTimeDiff printf("%f [seconds]", TimeDiff(befor))

#define ELEMENTS    (30000)

/*============= Experimenting with QUICK_SORT (no need th check) ============*/
long partition (long arr[], long low, long high);
void quickSort(long arr[], long low, long high);
void Swap(long *num1, long *num2);

/*=========================  PRINT ARRAY FUNCTION  ==========================*/
extern void PrintLongArr(void *arr, size_t size);


/*========================  LONG COMPARE FUNCTION  ========================*/
int LeftMinusRight(const void *left, const void *right)
{
    return ( *(long*)left - *(long*)right );
}

/*==========================  SET ARRAY FUNCTION  ==========================*/
void SetArrays(long arr[][ELEMENTS], size_t size )
{
    size_t i, j;
    srand(clock());

    for ( i = 0 ; i < ELEMENTS ; ++i )
    {
        arr[0][i] = rand() % ELEMENTS;

        for ( j = 1 ; j < size ; ++j )
        {
            arr[j][i] = arr[0][i];
        }
    }
}

/*======================  VERIFY ARRAY ORDER FUNCTION  =====================*/
void VerArr(long arr[])
{
    size_t i;

    for ( i = 0 ; i < ELEMENTS - 1 ; ++i )
    {
        if ( !(arr[i] <= arr[i+1]) )
        {
            PrintERR;
            return;
        }
    }
    PrintOK;
}

/***************************************************/
size_t GetWeight(void *element, void *param)
{
    return *(size_t*)element;
}

/***************************************************/
size_t GetHexWeight(void *element, void *param)
{
    return *(long*)element;
}

/*==========================  THE MAIN FUNCTIONS  ==========================*/
int main(int argc, char const *argv[])
{
    /*long arr2[] = { 10,9,8,7,6,5,4,3,2,1};*/
    clock_t befor;
    long arr[10][ELEMENTS];
    SetArrays(arr, 10);


    /*======================  Testing SelectionSort  ======================*/
    befor = clock(); PrintInYellow("\nSelectionSort\n");

    SortSelection(arr[0], ELEMENTS, sizeof(arr[0][0]), LeftMinusRight);

    PrintTimeDiff;
    VerArr(arr[0]);

    /*======================  Testing InsertionSort  ======================*/
    befor = clock(); PrintInYellow("\nInsertionSort\n");

    SortInsertion(arr[1], ELEMENTS, sizeof(arr[0][0]), LeftMinusRight);

    PrintTimeDiff;
    VerArr(arr[1]);

    /*======================  Testing BubbleSort  ======================*/
    befor = clock(); PrintInYellow("\nBubbleSort\n");

    SortBubble(arr[2], ELEMENTS, sizeof(arr[0][0]), LeftMinusRight);

    PrintTimeDiff;
    VerArr(arr[2]);
    /*======================  Testing qsort  ======================*/
    befor = clock(); PrintInYellow("\nqsort\n");

    qsort(arr[3], ELEMENTS, sizeof(arr[0][0]), LeftMinusRight);

    PrintTimeDiff;
    VerArr(arr[3]);

    /*======================  Testing SortCounting  ======================*/
    befor = clock(); PrintInYellow("\nSortCounting\n");

    SortCounting( arr[4], ELEMENTS, sizeof(arr[0][0]),
                  ELEMENTS, GetWeight, NULL);

    PrintTimeDiff;
    VerArr(arr[4]);

    /*======================  Testing SortRadix  ======================*/
    befor = clock(); PrintInYellow("\nSortRadix\n");

    SortRadix(arr[5], ELEMENTS, sizeof(arr[0][0]),
              GetHexWeight, NULL);

    PrintTimeDiff;
    VerArr(arr[5]);

    /*======================  Testing MergeSort  ======================*/
    befor = clock(); PrintInYellow("\nMergeSort\n");

    MergeSort(arr[6], ELEMENTS, sizeof(arr[0][0]), LeftMinusRight);

    PrintTimeDiff;
    VerArr(arr[6]);

    /*======================  Testing HeapSort  ======================*/
    befor = clock(); PrintInYellow("\nHeapSort\n");

    HeapSort(arr[7], ELEMENTS, sizeof(arr[0][0]), LeftMinusRight);

    PrintTimeDiff;
    VerArr(arr[7]);

    /*======================  Testing QuickSort  ======================*/
    befor = clock(); PrintInYellow("\nQuickSort\n");

    QuickSort(arr[8], ELEMENTS, sizeof(arr[0][0]), LeftMinusRight);

    PrintTimeDiff;
    VerArr(arr[8]);

    /*======================  Testing qsort  ======================*/
    befor = clock(); PrintInYellow("\nInternet QuickSort (not random)\n");

    quickSort(arr[9], 0, ELEMENTS - 1);

    PrintTimeDiff;
    VerArr(arr[9]);


    printf("\n");
    return 0;
}
/*=========================  END OF MAIN FUNCTIONS  =========================*/


/****************************************************************************
    SORT FUNCTION - QUICK_SORT
    (Copied from http://www.geeksforgeeks.org/quick-sort/ )
*****************************************************************************/
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
long partition (long arr[], long low, long high)
{
    long pivot = arr[high];
    long i = (low - 1); /* Index of smaller element */
    long j;

    for ( j = low; j <= high- 1; ++j)
    {
        /*  If current element is smaller than or equal to pivot  */
        if (arr[j] <= pivot)
        {
            ++i; /* increment index of smaller element */
            Swap( arr + i, arr + j);
        }
    }

    Swap( arr + i + 1, arr + high );
    return (i + 1);
}

/* The main function that implements QuickSort
    arr[] --> Array to be sorted,
    low   --> Starting index,
    high  --> Ending index */
void quickSort(long arr[], long low, long high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        long pi = partition(arr, low, high);

        /*  Separately sort elements before
            partition and after partition */
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void Swap(long *num1, long *num2)
{
    long temp = *num1;
        *num1 = *num2;
        *num2 = temp;
}
/****************************************************************************/
