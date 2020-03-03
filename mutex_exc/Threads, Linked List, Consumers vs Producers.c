#include <pthread.h>/* thread functions */
#include <stdio.h>  /* printf */
#include <time.h>   /* time */
#include <string.h> /* memset */
#include <unistd.h> /* sleep */
#include <semaphore.h> /* semaphore */

#include "dlist.h"    /* Linked list */

/****************************************************************************
    Helpful defines
*****************************************************************************/
#define PrintHeader(X)      printf( BLUE "\n\t------------"\
                                    "  This is a test for: "\
                                    X" ------------\n" RESET)

#define PrintInYellow(X)  ( printf(YLL X RES) )
#define PrintInGreen(X)   ( printf(GRE X RES) )
#define PrintInRed(X)     ( printf(RED X RES) )
#define PrintOK           ( printf(GRE "%s" RES, "-OK") )
#define PrintERR          ( printf(RED "%s" RES, "-ERR") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )
#define Max(a,b)          ( (a > b)?(a):(b))

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


/*=====================  Defines for this program  =====================*/
#define NUM_OF_PRODUCERS (3)
#define NUM_OF_CONSUMERS (3)
#define NUM_OF_DEALS     (Max(NUM_OF_PRODUCERS, NUM_OF_CONSUMERS))

/*=====================  Global Variables  =====================*/

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t semaphore;

/*=====================  Structs for this program  =====================*/
typedef struct trade
{
    size_t   trade_id;      /* id of consumer or producer */
    size_t   num_of_trade;  /* number of trades to perform */
    dlist_t *dlist;         /* dlist handler, buffer */

    long    *arr;           /* pointer to array in main */

} trade_t;

/*=====================  PRODUCER FUNCTION  =====================*/
void* Produce(void* buffer)
{
    size_t i = 0;
    trade_t *trade = (trade_t*) buffer;

    while ( i < trade->num_of_trade )
    {
        pthread_mutex_lock (&mutex);

        sem_post(&semaphore);

        DlistPushBack(trade->dlist, trade->arr + i );

        printf(RED "pth_self: %-2lu | Trade ID %-2ld | Produce %-2ld \n" RES,
                pthread_self() % 100,
                trade->trade_id,
                trade->arr[i] );

        fflush(stdout);

        ++i;

        pthread_mutex_unlock (&mutex);
    }

    return NULL;
}

/*=====================  CONSUMER FUNCTION  =====================*/
void* Consume(void* buffer)
{
    size_t i = 0;
    trade_t *trade = (trade_t*) buffer;

    while ( i < trade->num_of_trade )
    {
        sem_wait(&semaphore);

        pthread_mutex_lock (&mutex);

        printf(GRE "pth_self: %-2lu | Trade ID %-2ld | Consume %-2ld\n" RES,
                pthread_self() % 100,
                trade->trade_id,
                *(long*) DlistGetData( DlistBegin(trade->dlist) ));

        fflush(stdout);

        DlistPopFront(trade->dlist);

        ++i;

        pthread_mutex_unlock (&mutex);

    }

    return NULL;
}


/*==========================  THE MAIN FUNCTION  ==========================*/
int main ()
{
    size_t i;
    pthread_t consumer[NUM_OF_CONSUMERS];
    pthread_t producer[NUM_OF_PRODUCERS];

    trade_t trade[NUM_OF_DEALS];

    dlist_t *dlist = DlistCreate();
    long     arr[NUM_OF_DEALS];

    sem_init(&semaphore, 0, 0);

    /* init source array */
    for ( i = 0 ; i < NUM_OF_DEALS ; ++i )
    {
        arr[i] = 30 + i;
    }

    for ( i = 0 ; i < NUM_OF_PRODUCERS ; ++i )
    {
        trade[i].trade_id     = i;
        trade[i].dlist        = dlist;
        trade[i].num_of_trade = NUM_OF_DEALS;
        trade[i].arr          = arr;

        pthread_create(&producer[i], NULL, Produce, &trade[i]);
    }

    for ( i = 0 ; i < NUM_OF_CONSUMERS ; ++i )
    {
        pthread_create(&consumer[i], NULL, Consume, &trade[i]);
    }

    /*=====================  Release the threads  =====================*/
    for ( i = 0 ; i < NUM_OF_PRODUCERS ; ++i )
    {
        pthread_join(producer[i], NULL);
    }

    for ( i = 0 ; i < NUM_OF_CONSUMERS ; ++i )
    {
        pthread_join(consumer[i], NULL);
    }

    printf("\nDlist Count %lu", DlistCount(dlist));
    PrintOKorERR(0 == DlistCount(dlist));

    DlistDestroy(dlist);
    printf("\n" RES);
    return 0;
}

