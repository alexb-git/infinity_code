/****************************************************************************
** Filename:    - heap_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Heap testing (based on Vector)
** Date:        - 23/11/2017
** Version:     - 1
***************************************************/
#include <stdio.h>	/* printf */

#include "heap.h"   /* Stack data structure */

/* gd hasht.c hasht_test.c dlist.c */
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
    Helpful defines
*****************************************************************************/
#define PrintHeader(X)      printf( BLU "\n\t------------"\
                                    "  This is a test for: "\
                                    X" ------------\n" RES)

#define PrintInYellow(X)  ( printf(YEL X RES) )
#define PrintInGreen(X)   ( printf(GRE X RES) )
#define PrintInRed(X)     ( printf(RED X RES) )
#define PrintOK           ( printf(GRE "%s" RES, "-OK") )
#define PrintERR          ( printf(RED "%s" RES, "-ERR"))
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************
    extern debug functions
*****************************************************************************/
extern void PrintHeap(heap_t *heap);
extern void IsBalanced(heap_t *heap);
extern long SumHeap(heap_t *heap);


/*=========================  FUNCTION DECLARATION  =========================*/
int MyCmp(const void *element1, const void *element2)
{
    return *(long*)element2 - *(long*)element1;
}

int RmvSumHeap(const void *element1, const void *param)
{
    *(long*)param += *(long*)element1;
    return 0;
}

int RmvBoolFunc(const void *element, const void *param)
{
    return *(long*)element == *(long*)param;
}

void VerifyHeapSum(heap_t *heap, long arr_sum)
{
    long heap_sum = 0;

    printf("\nVerifing sum");
    HeapRemove(heap, RmvSumHeap, &heap_sum);
/*    printf("\nheap_sum = %ld\n", heap_sum);
    printf("arr_sum = %ld\n", arr_sum);*/
    PrintOKorERR( arr_sum == heap_sum );
}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
    size_t i;
    long  arr[]   = { 13, 8, 6, 9, 5, 12, 7, 2, 4, 11, 3, 1, 10 };
    long  arr_sum = 0;
    long  param   = 0;
    void *result;


    heap_t *heap = HeapCreate(sizeof(void*), 30, MyCmp);

    /*===================  Checking Empty Heap  ===================*/
    PrintInYellow("\nChecking Empty Heap:");
    printf("\nHeapSize    = %ld", HeapSize(heap));
    PrintOKorERR( 0 == HeapSize(heap) );

    printf("\nHeapIsEmpty = %d" , HeapIsEmpty(heap));
    PrintOKorERR( 1 == HeapIsEmpty(heap) );

    printf("\nHeapPeek    = %p" , HeapPeek(heap));
    PrintOKorERR( NULL == HeapPeek(heap) );

    HeapPop(heap);
    /*===================  Fill the Heap  ===================*/
    for ( i = 0 ; i < SizeArr(arr) ; ++i )
    {
        HeapPush(heap, arr + i);
        arr_sum += arr[i];
    }

    PrintHeap(heap);
    IsBalanced(heap);

    /*===================  Checking Filled Heap  ===================*/
    PrintInYellow("\n\nChecking Filled Heap:");
    printf("\nHeapSize    = %ld", HeapSize(heap));
    PrintOKorERR( SizeArr(arr) == HeapSize(heap) );

    printf("\nHeapIsEmpty = %d" , HeapIsEmpty(heap));
    PrintOKorERR( 0 == HeapIsEmpty(heap) );

    printf("\nHeapPeek    = %ld" , *(long*)HeapPeek(heap));
    PrintOKorERR( 1 == *(long*)HeapPeek(heap) );

    VerifyHeapSum(heap, arr_sum);

    /*===================  pop elements and check  ===================*/
    PrintInYellow("\n\nHeapPop:");

    arr_sum -= *(long*) HeapPop(heap);

    VerifyHeapSum(heap, arr_sum);
    PrintHeap(heap);
    IsBalanced(heap);

    /*===================  pop elements and check  ===================*/
    PrintInYellow("\n\nHeapPop:");

    arr_sum -= *(long*) HeapPop(heap);

    VerifyHeapSum(heap, arr_sum);
    PrintHeap(heap);
    IsBalanced(heap);

    /*===================  HeapRemove  ===================*/
    param = 5; arr_sum -= param;
    PrintInYellow("\n\nTesting HeapRemove. ");
    printf(YEL "\nRemove %ld from the heap (using RmvBoolFunc)" RES, param);

    result = HeapRemove(heap, RmvBoolFunc, &param);
    printf("\n*HeapRemove return = %ld", *(long*)result);
    PrintOKorERR( param == *(long*)result );

    VerifyHeapSum(heap, arr_sum);
    PrintHeap(heap);
    IsBalanced(heap);

    /*===================  HeapRemove  ===================*/
    PrintInYellow("\n\nTesting HeapRemove. ");
    PrintInYellow("Remove all alements using RmvBoolFunc. ");

    for ( i = 0 ; i < SizeArr(arr) ; ++i )
    {
        HeapRemove(heap, RmvBoolFunc, arr + i);
    }

    /*===================  HeapRemove and VerifyHeapSum  ===================*/
    arr_sum = 0;
    for ( i = 0 ; i < SizeArr(arr) ; ++i )
    {
        HeapPush(heap, arr + i);
        arr_sum += arr[i];
    }

    for ( i = 0 ; i < SizeArr(arr) ; ++i )
    {
        printf("\n\nRemove %ld using RmvBoolFunc", arr[i]);
        arr_sum -= arr[i];
        HeapRemove(heap, RmvBoolFunc, arr + i);

        VerifyHeapSum(heap, arr_sum);
        PrintHeap(heap);
        IsBalanced(heap);
    }

    /*===================  Checking Emptied Heap  ===================*/
    PrintInYellow("\n\nChecking Emptied Heap:");
    printf("\nHeapSize    = %ld", HeapSize(heap));
    PrintOKorERR( 0 == HeapSize(heap) );

    printf("\nHeapIsEmpty = %d" , HeapIsEmpty(heap));
    PrintOKorERR( 1 == HeapIsEmpty(heap) );

    printf("\nHeapPeek    = %p" , HeapPeek(heap));
    PrintOKorERR( NULL == HeapPeek(heap) );

    /*================  Fill the Heap to chech HeapDestroy  ================*/
    for ( i = 0 ; i < SizeArr(arr) ; ++i )
    {
        HeapPush(heap, arr + i);
    }

    HeapDestroy(heap);
    printf("\n");
    return 0;
}
