#include <pthread.h>/* thread functions */
#include <stdio.h>  /* printf */
#include <time.h>   /* time */
#include <string.h> /* memset */
#include <unistd.h> /* sleep */
#include <semaphore.h> /* semaphore */

#include "cbuffer.h"    /* circular_buffer */

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
#define NUM_OF_PRODUCERS (3) /* NOTE: should be */
#define NUM_OF_CONSUMERS (3) /*       CONSUMERS >= PRODUCERS , else DEADLOCK*/
#define NUM_OF_DEALS     (Max(NUM_OF_PRODUCERS, NUM_OF_CONSUMERS))

/*=====================  Global Variables  =====================*/

pthread_mutex_t mutex_consumers = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_producers = PTHREAD_MUTEX_INITIALIZER;

sem_t full;  /* semaphore, indicates full buffer, write cannot be performed */
sem_t empty; /* semaphore, indicates empty buffer, read cannot be performed */

size_t produced = 0; /* global verification variable */
size_t consumed = 0; /* global verification variable */

/*=====================  Structs for this program  =====================*/
typedef struct trade
{
    size_t     trade_id;      /* id of consumer or producer */
    size_t     num_of_trade;  /* number of trades to perform */
    cbuffer_t *cbuffer;       /* cbuffer handler, buffer */

    long    *arr;           /* pointer to array in main */

} trade_t;

/*=====================  PRODUCER FUNCTION  =====================*/
void* Produce(void* buffer)
{
    size_t i = 0;
    trade_t *trade = (trade_t*) buffer;

    size_t bytes_w; /* bytes written by CBufferWrite */

    while ( i < trade->num_of_trade )
    {
        sem_wait(&full); /* semaphore if buffer is full */

        pthread_mutex_lock (&mutex_producers);

        bytes_w = CBufferWrite( trade->cbuffer          ,
                                trade->arr + i          ,
                                sizeof(trade->arr[0])   );

        fprintf(stderr, RED "pth_self: %-2lu "         RES, pthread_self()%100);
        fprintf(stderr, RED "| Trade ID %-2ld "        RES, trade->trade_id);
        fprintf(stderr, RED "| Produce %-2ld "         RES, trade->arr[i]);
        fprintf(stderr, RED "| bytes written %-2lu \n" RES, bytes_w);

        ++i;
        ++produced;  /* global verification variable */
        sem_post(&empty); /* update empty semaphore */
        pthread_mutex_unlock (&mutex_producers);
    }

    return NULL;
}

/*=====================  CONSUMER FUNCTION  =====================*/
void* Consume(void* buffer)
{
    size_t i = 0;
    trade_t *trade = (trade_t*) buffer;

    long   read_dest;
    size_t bytes_r;

    while ( i < trade->num_of_trade )
    {
        sem_wait(&empty); /* semaphore if buffer is empty */

        pthread_mutex_lock (&mutex_consumers);

        bytes_r = CBufferRead( trade->cbuffer        ,
                               &read_dest            ,
                               sizeof(trade->arr[0]) );

        fprintf(stderr, GRE "pth_self: %-2lu "      RES, pthread_self()%100);
        fprintf(stderr, GRE "| Trade ID %-2ld "     RES, trade->trade_id);
        fprintf(stderr, GRE "| Consume %-2ld "      RES, read_dest);
        fprintf(stderr, GRE "| bytes read %-2lu \n" RES, bytes_r);

        ++i;
        ++consumed; /* global verification variable */
        sem_post(&full); /* update full semaphore */
        pthread_mutex_unlock (&mutex_consumers);
    }

    return NULL;
}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main ()
{
    size_t i, j;
    size_t buffer_elements = 3;

    pthread_t consumer[NUM_OF_CONSUMERS];
    pthread_t producer[NUM_OF_PRODUCERS];

    trade_t trade[NUM_OF_DEALS];

    long       arr[NUM_OF_DEALS * NUM_OF_DEALS];
    cbuffer_t *cbuffer = CBufferCreate(buffer_elements * sizeof(arr[0]));

    sem_init(&full , 0, buffer_elements);
    sem_init(&empty, 0, 0);

    /* init source array */
    for ( i = 0 ; i < NUM_OF_DEALS; ++i )
    {
        for ( j = 0 ; j < NUM_OF_DEALS ; ++j )
        {
            arr[i * NUM_OF_DEALS + j] = 30 + (i * 10 ) + j;
        }
    }

    /* initialize trades */
    for ( i = 0 ; i < NUM_OF_DEALS ; ++i )
    {
        trade[i].trade_id     = i;
        trade[i].cbuffer      = cbuffer;
        trade[i].num_of_trade = NUM_OF_DEALS;
        trade[i].arr          = (long*)(arr + i * NUM_OF_DEALS);
    }

    /*============  create threads for consumers an producers  ============*/
    for ( i = 0 ; i < NUM_OF_PRODUCERS ; ++i )
    {
        pthread_create(&producer[i], NULL, Produce, &trade[i]);
    }

    for ( i = 0 ; i < NUM_OF_CONSUMERS ; ++i )
    {
        pthread_create(&consumer[i], NULL, Consume, &trade[i]);
    }

    /*=================  Release/deallocate the threads  =================*/
    for ( i = 0 ; i < NUM_OF_PRODUCERS ; ++i )
    {
        pthread_join(producer[i], NULL);
    }

    for ( i = 0 ; i < NUM_OF_CONSUMERS ; ++i )
    {
        pthread_join(consumer[i], NULL);
    }

    /*==================  Print statuses  ==================*/
    printf("\nconsumed = %lu | produced = %lu", consumed, produced);
    PrintOKorERR(consumed == produced);

    printf("\nCBufferIsEmpty %d", CBufferIsEmpty(cbuffer));
    PrintOKorERR(1 == CBufferIsEmpty(cbuffer));

    CBufferDestroy(cbuffer);
    printf("\n" RES);
    return 0;
}
