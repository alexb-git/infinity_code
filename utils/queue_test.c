/****************************************************************************
** Filename:    - queue_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.come
** Purpose:     - testing the Queue Data Structure
** Date:        - 27/09/2017
** Version:     - 4
*****************************************************************************/

#include <stdio.h>	/* printf */
#include "queue.h"

#define GREEN	"\x1b[32m"
#define RED		"\x1b[31m"
#define YELLOW	"\x1b[93m"
#define RESET	"\x1b[0m"
#define BLUE	"\x1B[34m"
#define WHITE	"\x1B[37m"

/****************************************************************************
    Helpful defines
*****************************************************************************/
#define PrintHeader(X)      printf( BLUE "\n\t-----This is a test for "\
                                    X" function-----\n" RESET)

#define PrintBottomHeader(X) printf(BLUE "\n\t-----end of test for "\
                                    X" function-----\n"RESET)

#define PrintInYellow(X)  ( printf(YELLOW X RESET) )
#define PrintInGreen(X)   ( printf(GREEN  X RESET) )
#define PrintInRed(X)     ( printf(RED    X RESET) )
#define PrintOK           ( printf(GREEN "%-12s" RESET, "OK") )
#define PrintERR          ( printf(RED "%-12s" RESET, "ERR") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )

#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************/
void QInfoAndComp(queue_t *queue, int ex_is_em, size_t ex_size)
{
    printf("%-12d", QueueIsEmpty(queue));                   /* |IsEmpty|    */
    (QueueIsEmpty(queue)==ex_is_em)?(PrintOK):(PrintERR);   /* |T IsEmpty|  */
    printf("%-12ld", QueueSize(queue));                     /* |Size|       */
    (QueueSize(queue)==ex_size)?(PrintOK):(PrintERR);       /* |T Size|     */
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

/***************************************************************************/
void TestEnqueueDequeue()
{
	long arr[] = {1,2,3,4,5,6,7,8,9,10};
	queue_t *queue = QueueCreate();
    int i = 0;

    PrintHeader("~QueueEnqueue and QueueDequeue~");

    PrintInYellow("-->Enqueuing 1 elements and then Dequeuing it:\n\n");
    PrintTableHeader();
    QInfoAndComp(queue, 1, 0);      /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    QueueEnqueue(queue, &arr[0]);
    QInfoAndComp(queue, 0, 1);      /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    QueueDequeue(queue);
    QInfoAndComp(queue, 1, 0);      /* |IsEmpty| |T IsEmpty| |Size| |T Size| */

/****************************************************************************
    Enqueuing 10 elements
*****************************************************************************/
    PrintInYellow("\n-->Enqueuing 10 elements:\n");

    /* init table header */
    printf(YELLOW "%-12s" RESET, "|Enqueue|");
    PrintTableHeader();

    /* print info of the created queue */
    printf("%-12c", '-');      /* |Enqueue|    */
    QInfoAndComp(queue, 1, 0); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */

    /* enqueuing 10 elements to the queue and printing the queue info */
    for( i = 0 ; i < SizeArr(arr) ; ++i )
    {
        if ( QueueEnqueue(queue, &arr[i]) == 0 )
        {
            PrintInYellow("\nQueueEnqueue failed at some point!\n");
            break;
        }

        /* print info of queue after each insertion */
        printf("%-12ld", arr[i]);    /* |Enqueue|    */
        QInfoAndComp(queue, 0, i+1); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    }

/****************************************************************************
    Dequeuing 10 elements till queue is empty
*****************************************************************************/
    PrintInYellow("\n-->Dequeuing 10 elements:\n");

    printf( YELLOW "%-12s%-12s%-12s" RESET
            , "|Peek|", "|Dequeue|", "|Dequeue T|");
    PrintTableHeader();

    /* print info of the created queue */
    printf("%-12c", '-');       /* |Peek|       */
    printf("%-12c", '-');       /* |Dequeue|    */
    printf("%-12c", '-');       /* |Dequeue T|  */
    QInfoAndComp(queue, 0, 10); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */


    /* dequeuing 10 elements from the queue and printing the queue info */
    for( i = 0 ; i < SizeArr(arr) ; ++i )
    {
        void *ptr_peek    = NULL;
        void *ptr_enqueue = NULL;

        ptr_peek    = QueuePeek(queue);
        ptr_enqueue = QueueDequeue(queue);

        /* print info of queue after each insertion */
        printf("%-12ld", *(long*)ptr_peek);     /* |Peek|       */
        printf("%-12ld", *(long*)ptr_enqueue);  /* |Dequeue|    */
        PrintOKorERR(ptr_enqueue==&arr[i]);     /* |Dequeue T|  */

        QInfoAndComp(queue, (i==9), 9-i); /*|IsEmpty||T IsEmpty||Size||T Size|*/
    }

    PrintInYellow("\n\n-->QueuePeek on empty queue: ");
    (NULL==QueuePeek(queue))
    ? PrintInGreen("NULL returned")
    : PrintInRed("NULL was not returned");

    PrintInYellow("\n-->QueueDequeue on empty queue: ");
    (NULL==QueueDequeue(queue))
    ? PrintInGreen("NULL returned")
    : PrintInRed("NULL was not returned");

	QueueDestroy(queue);

	PrintBottomHeader("~QueueEnqueue and QueueDequeue~");
}


/****************************************************************************/
void TestQueueAppend()
{
    int i = 0;
    int merged_size = 0;

    long arr_1[] = {1,2,3};
    queue_t *queue_1 = QueueCreate();

    long arr_2[] = {4,5,6,7,8,9};
    queue_t *queue_2 = QueueCreate();

    long extra = 10;

    PrintHeader("~QueueAppend~");

    /* enqueuing 5 elements to the queue_1 */
    for( i = 0 ; i < SizeArr(arr_1) ; ++i )
    {
        if ( QueueEnqueue(queue_1, &arr_1[i]) == 0 )
        {
            PrintInYellow("\nQueueEnqueue failed at some point!\n");
            break;
        }
    }

    /* enqueuing 5 elements to the queue_2 */
    for( i = 0 ; i < SizeArr(arr_2) ; ++i )
    {
        if ( QueueEnqueue(queue_2, &arr_2[i]) == 0 )
        {
            PrintInYellow("\nQueueEnqueue failed at some point!\n");
            break;
        }
    }

    PrintInYellow("\nQueue #1 contains: ");
    for( i = 0 ; i < SizeArr(arr_1) ; ++i )
    {
        printf("<-| %ld |", arr_1[i]);
    }
    printf("\nQueueSize(queue_1) = %ld\n", QueueSize(queue_1));

    PrintInYellow("\nQueue #2 contains: ");
    for( i = 0 ; i < SizeArr(arr_2) ; ++i )
    {
        printf("<-| %ld |", arr_2[i]);
    }
    printf("\nQueueSize(queue_2) = %ld\n", QueueSize(queue_2));


/****************************************************************************
    Append queue_2 to queue_1
*****************************************************************************/
    PrintInYellow("\n-->Append queue_2 to queue_1:\n");
    QueueAppend(queue_1, queue_2);
    PrintTableHeader();
    QInfoAndComp(queue_1, 0, 9);    /* |IsEmpty| |T IsEmpty| |Size| |T Size| */

/****************************************************************************
    Add one more element to the appended queue (queue_1)
*****************************************************************************/
    PrintInYellow("\n-->Add one more element to the appended queue_1:\n");
    QueueEnqueue(queue_1, &extra);
    PrintTableHeader();
    QInfoAndComp(queue_1, 0, 10);   /* |IsEmpty| |T IsEmpty| |Size| |T Size| */

    printf("\nQueueIsEmpty(queue_2) = %d - ", QueueIsEmpty(queue_2));
    PrintOKorERR(QueueIsEmpty(queue_2)==1);
    printf("\nQueueSize(queue_2)    = %ld - ", QueueSize(queue_2));
    PrintOKorERR(QueueSize(queue_2)==0);
    printf("\n\n");

/****************************************************************************
    Begin to QueueDequeue till queue_1 is empty
*****************************************************************************/
    PrintInYellow("\n-->Begin to QueueDequeue:\n");
    printf( YELLOW "%-12s%-12s%-12s" RESET
            , "|Peek|", "|Dequeue|", "|Dequeue T|");
    PrintTableHeader();

    /* print info of the created queue */
    printf("%-12c%-12c%-12c", '-', '-', '-');/* |Peek| |Dequeue| |Dequeue T| */
    QInfoAndComp(queue_1, 0, 10);    /* |IsEmpty| |T IsEmpty| |Size| |T Size| */

    merged_size = SizeArr(arr_1) + SizeArr(arr_2) + 1;
    /* dequeuing 10 elements from the queue and printing the queue info */
    for( i = 0 ; i < merged_size ; ++i )
    {
        void *ptr_peek     = NULL;
        void *ptr_denqueue = NULL;

        ptr_peek    = QueuePeek(queue_1);
        ptr_denqueue = QueueDequeue(queue_1);

        /* print info of queue after each insertion */
        printf("%-12ld", *(long*)ptr_peek);          /* |Peek|       */
        printf("%-12ld", *(long*)ptr_denqueue);      /* |Dequeue|    */
        PrintOKorERR(*(long*)ptr_denqueue==i+1);     /* |Dequeue T|  */

        QInfoAndComp(queue_1, i==9, 9-i); /*|IsEmpty||T IsEmpty||Size||T Size|*/
    }

/****************************************************************************
    Inserting element to Queue_2 (the one that we've emptied before)
*****************************************************************************/
    PrintInYellow("\n-->Inserting element to Queue_2 ");
    PrintInYellow("(the one that we've emptied before):");

    QueueEnqueue(queue_2, &arr_1[0]); /* test was suggested by Miri */
    printf("\nQueueIsEmpty(queue_2) = %d - ", QueueIsEmpty(queue_2));
    PrintOKorERR(QueueIsEmpty(queue_2)==0);
    printf("\tQueueSize(queue_2)    = %ld - ", QueueSize(queue_2));
    PrintOKorERR(QueueSize(queue_2)==1);
    printf("\n");

    QueueDequeue(queue_2);

/****************************************************************************
    Append queue_2 to queue_1 (both empty)
*****************************************************************************/
    PrintInYellow("\n-->Append queue_2 to queue_1 (both empty):");
    QueueAppend(queue_1, queue_2);

    printf("\nQueueIsEmpty(queue_1) = %d - ", QueueIsEmpty(queue_1));
    PrintOKorERR(QueueIsEmpty(queue_1)==1);
    printf("\tQueueSize(queue_1)    = %ld - ", QueueSize(queue_1));
    PrintOKorERR(QueueSize(queue_1)==0);

    printf("\nQueueIsEmpty(queue_2) = %d - ", QueueIsEmpty(queue_2));
    PrintOKorERR(QueueIsEmpty(queue_2)==1);
    printf("\tQueueSize(queue_2)    = %ld - ", QueueSize(queue_2));
    PrintOKorERR(QueueSize(queue_2)==0);

    printf("\n");

/****************************************************************************
    Append queue_2 to queue_1 (queue_2 empty, queue_1 not)
*****************************************************************************/
    PrintInYellow("\n-->Append queue_2 (3 elements) to queue_1 (empty):");
    QueueEnqueue(queue_2, &arr_1[0]);
    QueueEnqueue(queue_2, &arr_1[1]);
    QueueEnqueue(queue_2, &arr_1[2]);
    QueueAppend(queue_1, queue_2);

    printf("\nQueueIsEmpty(queue_1) = %d - ", QueueIsEmpty(queue_1));
    PrintOKorERR(QueueIsEmpty(queue_1)==0);
    printf("\tQueueSize(queue_1)    = %ld - ", QueueSize(queue_1));
    PrintOKorERR(QueueSize(queue_1)==3);

    printf("\nQueueIsEmpty(queue_2) = %d - ", QueueIsEmpty(queue_2));
    PrintOKorERR(QueueIsEmpty(queue_2)==1);
    printf("\tQueueSize(queue_2)    = %ld - ", QueueSize(queue_2));
    PrintOKorERR(QueueSize(queue_2)==0);

    printf("\n");

    QueueDestroy(queue_1);
    QueueDestroy(queue_2);

    PrintBottomHeader("~QueueAppend~");
}

/***************************************************************************/
void TestQueue()
{
    TestEnqueueDequeue();
    TestQueueAppend();
}


int main()
{
	TestQueue();

    return 0;
}
