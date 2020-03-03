/****************************************************************************
** Filename:    - scheduler_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - testing the task scheduler
** Date:        - 11/10/2017
** Version:     - 1
*****************************************************************************/
#include <stdio.h>      /* printf */
#include <time.h>       /* time */
#include <pthread.h>    /* thread  ID */

#include "scheduler.h"  /* task scheduler */

/* gc scheduler_test.c scheduler.c pqueue.c uid.c sortedlist.c dlist.c task.c
 */

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

#define PrintExecutionStatus(X)\
        printf("\tCall_time: %ld"       , call_time         );\
        printf("\tCalls_left: %ld "     , X                 );\
        printf("\tSec_count: %ld" RESET , since_beginning   );\
        PrintOKorERR(since_beginning == call_time);\
        fflush(stdout);

/****************************************************************************
    My functions to run
*****************************************************************************/
static time_t rel_time; /* used to count seconds since the beginning of run */
long number_of_calls1 = 10;
long number_of_calls2 = 6;
long number_of_calls3 = 4;


/*==============================  PrintParam1  ==============================*/
int PrintParam1(void *param)
{
    size_t since_beginning      = time(NULL) - rel_time;
    size_t call_time            = *(long*)param*(11 - number_of_calls1);

    printf(YELLOWS "\nPrintParam1" );

    PrintExecutionStatus(number_of_calls1);

    return --number_of_calls1;
    printf("\n");
}

/*==============================  PrintParam2  ==============================*/
int PrintParam2(void *param)
{
    size_t since_beginning      = time(NULL) - rel_time;
    size_t call_time            = *(long*)param*(7 - number_of_calls2);

    printf(BLUE "\nPrintParam2" );

    PrintExecutionStatus(number_of_calls2);

    return --number_of_calls2;
    printf("\n");
}

/*==============================  PrintParam3  ==============================*/
int PrintParam3(void *param)
{
    size_t since_beginning      = time(NULL) - rel_time;
    size_t call_time            = *(long*)param*(5 - number_of_calls3);

    printf(CYAN "\nPrintParam3" );

    PrintExecutionStatus(number_of_calls3);

    return --number_of_calls3;
    printf("\n");
}

/****************************************************************************/
void PrintCheckSizeEmpty( scheduler_t *scheduler, size_t ex_size)
{
    size_t calc_size  = SchedulerSize(scheduler);
    int    calc_empty = SchedulerIsEmpty(scheduler);

    printf("SchedulerSize: %ld" , calc_size );
    PrintOKorERR( calc_size == ex_size );

    printf("\tSchedulerIsEmpty: %d", calc_empty );
    PrintOKorERR( calc_empty == !ex_size );

    printf("\n");
}


/****************************************************************************/
void TestSchedulerRunAll(void)
{
    long param1 = 2;
    long param2 = 6;
    long param3 = 10;

    scheduler_t *scheduler = SchedulerCreate();

    number_of_calls1 = 10;
    number_of_calls2 = 6;
    number_of_calls3 = 4;

    PrintHeader("Run All tasks");

    PrintInYellow("\n--> create scheduler\n");
    PrintCheckSizeEmpty(scheduler, 0);


    PrintInYellow("\n--> insert three tasks into the scheduler\n");
    SchedulerAdd(scheduler, PrintParam1, 2, (void*)&param1 );
    SchedulerAdd(scheduler, PrintParam2, 6, (void*)&param2 );
    SchedulerAdd(scheduler, PrintParam3, 10, (void*)&param3 );
    PrintCheckSizeEmpty(scheduler, 3);


    PrintInYellow("\n--> run the scheduler\n");
    rel_time = time(NULL);
    SchedulerRun(scheduler);

    SchedulerDestroy(scheduler);
    printf("\n");
}

/****************************************************************************/
void TestSchedulerRemove(void)
{
    long param1 = 2;
    long param2 = 6;
    long param3 = 10;

    scheduler_t *scheduler = SchedulerCreate();
    unique_id_t uid2, uid3;

    number_of_calls1 = 10;
    number_of_calls2 = 6;
    number_of_calls3 = 4;

    PrintHeader("Remove Tasks");

    PrintInYellow("\n--> create scheduler\n");
    PrintCheckSizeEmpty(scheduler, 0);

    PrintInYellow("\n--> insert three tasks into the scheduler\n");
           SchedulerAdd(scheduler, PrintParam1, 2 , (void*)&param1 );
    uid2 = SchedulerAdd(scheduler, PrintParam2, 6 , (void*)&param2 );
    uid3 = SchedulerAdd(scheduler, PrintParam3, 10, (void*)&param3 );
    PrintCheckSizeEmpty(scheduler, 3);


    PrintInYellow("\n--> remove PrintParam2 function (middle) \n");
    SchedulerRemove(scheduler, uid2);
    PrintCheckSizeEmpty(scheduler, 2);


    PrintInYellow("\n--> remove PrintParam3 function (end) \n");
    SchedulerRemove(scheduler, uid3);
    PrintCheckSizeEmpty(scheduler, 1);


    PrintInYellow("\n--> run the scheduler\n");
    rel_time = time(NULL);
    SchedulerRun(scheduler);

    SchedulerDestroy(scheduler);
    printf("\n");
}

/****************************************************************************/
void TestSchedulerStop(void)
{
    long param1 = 2;
    long param2 = 6;
    long param3 = 10;

    scheduler_t *scheduler = SchedulerCreate();

    number_of_calls1 = 10;
    number_of_calls2 = 6;
    number_of_calls3 = 4;

    PrintHeader("Remove Tasks");

    PrintInYellow("\n--> create scheduler\n");
    PrintCheckSizeEmpty(scheduler, 0);


    PrintInYellow("\n--> insert three tasks into the scheduler\n");
    SchedulerAdd(scheduler, PrintParam1, 2, (void*)&param1 );
    SchedulerAdd(scheduler, PrintParam2, 6, (void*)&param2 );
    SchedulerAdd(scheduler, PrintParam3, 10, (void*)&param3 );
    PrintCheckSizeEmpty(scheduler, 3);


    PrintInYellow("\n--> Stop the scheduler \n");
    SchedulerStop(scheduler);
    PrintCheckSizeEmpty(scheduler, 0);


    PrintInYellow("\n--> run the scheduler\n");
    rel_time = time(NULL);
    SchedulerRun(scheduler);

    SchedulerDestroy(scheduler);
    printf("\n");
}


/*==============================  TestScheduler  ============================*/
void TestScheduler()
{
    TestSchedulerRunAll();
    TestSchedulerRemove();
    TestSchedulerStop();
}

/*===========================  THE MAIN FUNCTION  ===========================*/
int main()
{
    TestScheduler();

    printf("\n");
    return 0;
}
