#include <pthread.h>/* thread functions */
#include <stdio.h>  /* printf */
#include <time.h>   /* time */
#include <string.h> /* memset */
#include <unistd.h> /* sleep */
#include <semaphore.h> /* semaphore */

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
#define NUM_OF_PRODUCERS (1) /* NOTE: should be */
#define NUM_OF_CONSUMERS (3) /*       CONSUMERS >= PRODUCERS , else DEADLOCK*/

#define N_BROADCAST     (5)  /* number of messages to send */

/*=====================  Global Variables  =====================*/

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t   cond = PTHREAD_COND_INITIALIZER;

sem_t semi;

size_t received = 0; /* global verification variable */

/*=====================  Structs for this program  =====================*/
typedef struct trade
{
    size_t num_of_messages; /* number of trades to perform */

    long  cbuffer;          /* buffer */
    long *arr;              /* pointer to array in main */

} trade_t;

/*=====================  PRODUCER FUNCTION  =====================*/
void* Produce(void* buffer)
{
    size_t i = 0;
    trade_t *trade = (trade_t*) buffer;

    while ( i < trade->num_of_messages )
    {
        size_t j;
        for ( j = 0 ; j < NUM_OF_CONSUMERS ; ++j )
        {
            sem_wait(&semi); /* "--semaphore" */
        }

        pthread_mutex_lock(&mutex);
        trade->cbuffer = trade->arr[i];
        pthread_cond_broadcast(&cond);

        fprintf(stderr, RED "Thread: %-2lu |"  RES, pthread_self()%100);
        fprintf(stderr, RED " Broadcast %-2ld\n" RES, trade->arr[i]);

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

    while ( i < trade->num_of_messages )
    {
        pthread_mutex_lock(&mutex);

        sem_post(&semi); /* "++semaphore" */

        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock (&mutex);

        fprintf(stderr, GRE "Thread: %-2lu |"  RES, pthread_self()%100);
        fprintf(stderr, GRE " Recieved %-2ld \n" RES, trade->cbuffer);

        ++i;
        ++received; /* global verification variable */
    }

    return NULL;
}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main ()
{
    size_t i;

    pthread_t producer;
    pthread_t consumer[NUM_OF_CONSUMERS];

    long arr[N_BROADCAST];

    trade_t aux_struct;

    aux_struct.num_of_messages = N_BROADCAST;
    aux_struct.arr = arr;

    sem_init(&semi , 0, 0);
    pthread_cond_init(&cond, NULL);

    /* init source array */
    for ( i = 0 ; i < N_BROADCAST; ++i )
    {
        arr[i] = i;
    }

    /*============  create threads for consumers an producers  ============*/
    pthread_create(&producer, NULL, Produce, &aux_struct);


    for ( i = 0 ; i < NUM_OF_CONSUMERS ; ++i )
    {
        pthread_create(&consumer[i], NULL, Consume, &aux_struct);
    }

    /*=================  Release/deallocate the threads  =================*/
    pthread_join(producer, NULL);


    for ( i = 0 ; i < NUM_OF_CONSUMERS ; ++i )
    {
        pthread_join(consumer[i], NULL);
    }

    /*==================  Print statuses  ==================*/
    printf("\nNumber of consumers: %lu"    , (size_t)N_BROADCAST);
    printf("\nNumber of messages:  %lu"    , (size_t)NUM_OF_CONSUMERS);
    printf("\nTotal messages received %lu ", received);
    PrintOKorERR(received == N_BROADCAST * NUM_OF_CONSUMERS);

    printf("\n" RES);
    return 0;
}

