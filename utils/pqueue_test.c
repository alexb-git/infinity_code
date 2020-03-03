/****************************************************************************
** Filename:    - pqueue_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.come
** Purpose:     - testing the Priority List Data Structure
** Date:        - 08/10/2017
** Version:     - 6
*****************************************************************************/

#include <stdio.h>	   /* printf */
#include "pqueue.h"    /* Priority List DS */

#define GREEN	"\x1b[92m"
#define RED		"\x1b[91m"
#define YELLOW	"\x1b[93m"
#define YELLOWS	"\x1b[33m"
#define RESET	"\x1b[0m"
#define BLUE	"\x1B[94m"
#define WHITE	"\x1B[37m"

/****************************************************************************
    Helpful defines
*****************************************************************************/
#define PrintHeader(X)      printf(BLUE "\n\t--------- This is a test for: ~"\
                                    X" ---------\n" RESET)

#define PrintInYellow(X)  ( printf(YELLOW X RESET) )
#define PrintInGreen(X)   ( printf(GREEN  X RESET) )
#define PrintInRed(X)     ( printf(RED    X RESET) )
#define PrintOK           ( printf(GREEN "%-12s" RESET, "-OK") )
#define PrintERR          ( printf(RED "%-12s" RESET, "-ERR") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )

#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************
** description:  Created to test the PQueueCreate function.
**               This function converts the priority values of two args
**               into long type and substracts them.
** return value:                 0 - IF data is equal,
**                negative integer - if 2 is bigger than 1,
**                positive integer - if 1 is bigger than 2.
*****************************************************************************/
int myDoubleCmp( const void *data_1, const void *data_2)
{
    long element = (long)((*(double*)data_1)*10)%10;
    long input   = (long)((*(double*)data_2)*10)%10;

    return (element - input);
}

/***************************************************************************
	Created to test the PQueueErase function.
    This function converts the two arguments into long,
    filtering the value, and compares them.
***************************************************************************/
int ISsmallerThanParam(const void *element, void *param)
{
    return ( *(long*)element < *(long*)param );
}

/***************************************************************************
	Created to test the PQueueErase function.
    This function converts the two arguments into long,
    filtering the priority, and compares them.
***************************************************************************/
int ISPriorityAsParam(const void *data, void *param)
{
    long element = (long)((*(double*)data )*10)%10;
    long input   = (long)((*(double*)param)*10)%10;

    return (element == input);
}

/****************************************************************************/
void PQInfoAndComp(pqueue_t *pqueue, int ex_is_em, size_t ex_size)
{
    printf("%-12d", PQueueIsEmpty(pqueue));                   /* |IsEmpty|    */
    (PQueueIsEmpty(pqueue) == ex_is_em)?(PrintOK):(PrintERR); /* |T IsEmpty|  */
    printf("%-12ld", PQueueCount(pqueue));                    /* |Size|       */
    (PQueueCount(pqueue)   == ex_size)?(PrintOK):(PrintERR);  /* |T Size|     */
    printf("\n");
}

/****************************************************************************/
void PrintTableHeader(void)
{
    /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    printf(YELLOW "%-12s%-12s%-12s%-12s\n" RESET
            , "|IsEmpty|" , "|T IsEmpty|"
            , "|Size|"    , "|T Size|" );
}

/****************************************************************************/
void PrintTableHeaderDequeue(void)
{
    printf( YELLOW "%-12s%-12s%-12s" RESET
            , "|Peek|", "|Dequeue|", "|Dequeue T|");
    PrintTableHeader();

    /* print info of the created pqueue */
    /* |Peek| |Dequeue| */
    printf("%-12c%-12c%-12c", '-', '-', '-');
}

/****************************************************************************/
void InitPQlist(pqueue_t *pqueue, double *arr, size_t size)
{
    int i = 0;

    /* init table header */
    printf(YELLOW "%-12s" RESET, "|Enqueue|");
    PrintTableHeader();

    /* print info of the created pqueue */
    printf("%-12c", '-');        /* |Enqueue|    */
    PQInfoAndComp(pqueue, 1, 0); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */

    /*  enqueuing 10 elements in a shuffled way to the pqueue
        and printing the pqueue info */
    for( i = 0 ; i < size ; ++i )
    {
        if ( PQueueEnqueue(pqueue, &arr[i]) == 0 )
        {
            PrintInYellow("\nQueueEnqueue failed at some point!\n");
            break;
        }

        /* print info of pqueue after each insertion */
        printf("%-12.1f", arr[i]);    /* |Enqueue|    */
        PQInfoAndComp(pqueue, 0, i+1); /*IsEmpty|T IsEmpty|Size|T Size*/
    }
}

/****************************************************************************/
void PrintAndCmpDequeue(pqueue_t *pqueue, size_t size)
{
    int  i = 0;
    void *prev_peek = PQueuePeek(pqueue);

    PrintTableHeaderDequeue();

    /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PQInfoAndComp(pqueue, 0, size);

    while ( !PQueueIsEmpty(pqueue) )
    {
        void *ptr_peek    = PQueuePeek(pqueue);

        void *ptr_dequeue = PQueueDequeue(pqueue);

        /* print info of pqueue after each insertion */
        printf("%-12.1f", *(double*)ptr_peek);      /* |Peek|       */
        printf("%-12.1f", *(double*)ptr_dequeue);   /* |Dequeue|    */

        /*  verify priority of ptr_peek (current)
            is bigger than priority of prev_peek (previous)*/
        /*|Dequeue T|*/
        PrintOKorERR( *(double*)ptr_peek >= *(double*)prev_peek );

        /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
        PQInfoAndComp(pqueue, (i==size-1), size-1-i);
        ++i;

        prev_peek = ptr_peek;
    }
}

/****************************************************************************
    Testing PQueueEnqueue and PQueueDequeue
*****************************************************************************/
void TestEnqueueDequeue()
{
	double arr[] = { 40.4, 48.4, 49.4,
                     31.3, 35.3, 39.3,
                     20.2, 25.2,
                     10.1, 11.1 };


	pqueue_t *pqueue = PQueueCreate(myDoubleCmp);

    PrintHeader("PQueueEnqueue and PQueueDequeue");

    PrintInYellow("-->Enqueuing 1 elements and then Dequeuing it:\n\n");
    PrintTableHeader();
    PQInfoAndComp(pqueue, 1, 0);     /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PQueueEnqueue(pqueue, &arr[0]);
    PQInfoAndComp(pqueue, 0, 1);     /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PQueueDequeue(pqueue);
    PQInfoAndComp(pqueue, 1, 0);     /* |IsEmpty| |T IsEmpty| |Size| |T Size| */

 /****************************************************************************
    Enqueuing 10 elements
 *****************************************************************************/
    PrintInYellow("\n-->Enqueuing 10 elements:\n");
    InitPQlist(pqueue, arr, SizeArr(arr));

 /****************************************************************************
    Dequeuing 10 elements till pqueue is empty
 *****************************************************************************/
    PrintInYellow("\n-->Dequeuing till empty:\n");

    /* dequeuing till empty and printing the pqueue info */
    PrintAndCmpDequeue(pqueue, SizeArr(arr));

    PrintInYellow("\n\n-->PQueuePeek on empty pqueue: ");
    (NULL==PQueuePeek(pqueue))
    ? PrintInGreen("NULL returned")
    : PrintInRed("NULL was not returned");

    PrintInYellow("\n-->PQueueDequeue on empty pqueue: ");
    (NULL==PQueueDequeue(pqueue))
    ? PrintInGreen("NULL returned")
    : PrintInRed("NULL was not returned");

    printf("\n");
	PQueueDestroy(pqueue);
}


/****************************************************************************/
void TestQueueEraseClear()
{
    double arr[] = { 40.4, 48.4, 49.4,
                     31.3, 35.3, 39.3,
                     20.2, 25.2,
                     10.1, 11.1 };

	pqueue_t *pqueue = PQueueCreate(myDoubleCmp);
    double     param = 0;

    PrintHeader("PQueueErase (by priority) and PQueueClear");

 /****************************************************************************
   Enqueuing 10 elements
 *****************************************************************************/
   PrintInYellow("\n-->Enqueuing 10 elements:\n");
   InitPQlist(pqueue, arr, SizeArr(arr));

    PrintInYellow("\n-->PQueueErase elements with priority 2:\n");
    param = 0.2;
    while ( PQueueErase(pqueue, ISPriorityAsParam, &param) != NULL );
    PrintAndCmpDequeue(pqueue,  8);

    PrintInYellow("\n-->PQueueClear:\n");
    PQueueClear(pqueue);
    PrintTableHeader();
    PQInfoAndComp(pqueue, 1, 0);


    printf("\n");
    PQueueDestroy(pqueue);
}

/****************************************************************************/
void TestQueueErase2()
{
    double arr[] = { 40.4, 48.4, 49.4,
                     31.3, 35.3, 39.3,
                     20.2, 25.2,
                     10.1, 11.1 };

	pqueue_t *pqueue = PQueueCreate(myDoubleCmp);
    double     param = 0;
    size_t     size  = SizeArr(arr);
    int i = 0;

    PrintHeader("PQueueErase elements smaller than 35");

 /****************************************************************************
   Enqueuing 10 elements
 *****************************************************************************/
   PrintInYellow("\n-->Enqueuing 10 elements:\n");
   InitPQlist(pqueue, arr, SizeArr(arr));

    PrintInYellow("\n-->PQueueErase elements smaller than 35:\n");
    param = 35;
    while ( PQueueErase(pqueue, ISsmallerThanParam, &param) != NULL );
    size -= 5;

    PrintTableHeaderDequeue();

    /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PQInfoAndComp(pqueue, 0, size);

    while ( !PQueueIsEmpty(pqueue) )
    {
        void *ptr_peek    = PQueuePeek(pqueue);

        void *ptr_dequeue = PQueueDequeue(pqueue);

        /* print info of pqueue after each insertion */
        printf("%-12.1f", *(double*)ptr_peek);      /* |Peek|       */
        printf("%-12.1f", *(double*)ptr_dequeue);   /* |Dequeue|    */

        /*  verify priority of ptr_peek (current)
            is bigger than priority of prev_peek (previous)*/
        PrintOKorERR(*(long*)ptr_peek >= 35); /*|Dequeue T|*/

        /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
        PQInfoAndComp(pqueue, (i==size-1), size-1-i);
        ++i;
    }

    printf("\n");
    PQueueDestroy(pqueue);
}

/***************************************************************************/
void TestPQueue()
{
    TestEnqueueDequeue();
    TestQueueEraseClear();
    TestQueueErase2();
}


int main()
{
	TestPQueue();

    return 0;
}
