/****************************************************************************
** Filename:    - wdduncs.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - watch dog implementation
** Date:        - 26/12/2017
** Version:     - 52
*****************************************************************************/
#include <sys/types.h>  /* getppid */
#include <unistd.h>     /* getppid */
#include <signal.h>     /* sig_atomic_t */
#include <string.h>     /* memset */
#include <pthread.h>    /* threads */
#include <sys/wait.h>   /* wait */

#include <sys/ipc.h>    /* semctl */
#include <sys/sem.h>    /* semctl */

#include <stdio.h>      /* prints */

#include "semV.h"       /* system 5 semaphore wrapper */
#include "../utils/scheduler.h" /* tasks scheduler */

/* gd watch_dog.c semV.c wdfuncs.c lib.a -D_GNU_SOURCE -pthread -o watch_dog.out */
/* gd wd_test.c semV.c wdfuncs.c lib.a -D_GNU_SOURCE -pthread */
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

/*========================  Helpful defines  ========================*/
#define DONT_CONT_TASK  (0)      /* do NOT continue task in scheduler */
#define      CONT_TASK  (1)      /* continue task in scheduler */
#define MAX_TRIES       (1000)   /* how many tries will be in Sync function */

#define SEND_SUSR1      (1)     /* used with sig_mode variable */
#define SEND_SUSR2      (0)     /* used with sig_mode variable */

#define CHILD           (0)      /* used after fork function */

/*========================  FOR ERROR HANDLING  ========================*/
#define ERROR           (-1)     /* used with semaphore function */
#define SCHED_RUN_ERR   (0)      /* 0 - SchedulerRun failed at some point */

typedef enum error
{
    SEM_NO_WAIT = -100,   /* SemNoWait */
    SEM_CREATE, /* -99 */ /* SemCreate */
    SEM_POST,   /* -98 */ /* SemPost */
    SEM_WAIT,   /* -97 */ /* SemWait */
    SEM_CTL,    /* -96 */ /* semctl */

    FORK_ERR = -80,       /* fork */
    EXCECV,     /* -79 */ /* execvp */
    TH_CREAT,   /* -78 */ /* pthread_create */
    TH_DETCH,   /* -77 */ /* pthread_detach */
    SIG_ACT,    /* -76 */ /* sigaction */

    KILL_ERR    = -60,     /* kill */
    SCHDE_ERR   = -59,     /* SchedulerCreate, SchedulerAdd */
    MAIN_OP_ERR = -58,     /* MainOp failed */
    SUCCESS = 0

} error_t;

#define     CheckIfError(func, error, ret_val)\
{ if (func == error) return ret_val; }

#define CheckIfNotSuccess(func, succ, ret_val)\
{ if (func != succ)  return ret_val; }


/*==========================  Global variables  ==========================*/
sig_atomic_t is_alive  = 1; /* 1 - opposite app runs,
                               0 - otherwise */
sig_atomic_t is_needed = 1; /* 1 - opposite app marked as needed,
                               0 - otherwise */
sig_atomic_t sig_mode  = 1; /* 1 - Task_1 sends SIGUSR1
                               0 - Task_1 sends SIGUSR2 */

scheduler_t *scheduler;     /* pointer to the scheduler */
pid_t        pid;           /* process id of the opposite application */

int semi_a;                 /* semaphore that indicate if WD was created once */
int is_wd = 0;              /* flag that indicates if current process is WD */

const char *wd_path = "./watch_dog.out";

/*=======================  functions declarations  ========================*/
static void* MainOp(void *arg);
static void* CatchZombie(void *arg);

static error_t Sync(void);
static error_t InitScheduler();
static error_t InitSignalHandlers();
static error_t RestartApp(char* const *argv);

static void SignalHandler1(int arg);
static void SignalHandler2(int arg);

static int Task_1(void *ignored);
static int Task_2(void *ignored);

/****************************************************************************
    Function that catches zombie - design for thread use
    NOTES: designd for pthread ( void *(*start_routine) (void *) )
*****************************************************************************/
static void* CatchZombie(void *arg)
{
    int status;
    wait( &status );

    return NULL;
}

/*****************************************************************************
**  description: set current app as the watch dog side, USED ONLY BY WD
**  arguments:    none
**  return value: none
******************************************************************************/
void SetIsWD()
{
    is_wd = 1;
}

/****************************************************************************
    performes acknowledgment between two process that use this same func
*****************************************************************************/
static error_t Sync(void) /* return if sync succeeded or failed */
{
    int semi_b = SemCreate(wd_path, 'b', 0);
    int semi_c = SemCreate(wd_path, 'c', 0);

    if ( (ERROR == semi_b) || (ERROR == semi_c) )
    {
        return SEM_CREATE;
    }

    #ifdef _DEBUG
        fprintf(stderr, "%s" "| is_wd = %d | getpid %6d | pid %6d |"\
        "sync about to performe\n" RES,
        (is_wd)?(RED):(GRE),  is_wd, getpid(), pid);
    #endif

    if (is_wd) /* is WD */
    {
        CheckIfError( SemPost(semi_b, 1), ERROR, SEM_POST);

        if ( SemNoWait(semi_c, 1, MAX_TRIES) == ERROR )
        {
            return SEM_NO_WAIT;
        }
    }
    else /* is APP */
    {
        if ( SemNoWait(semi_b, 1, MAX_TRIES) == ERROR )
        {
            return SEM_NO_WAIT;
        }

        CheckIfError( SemPost(semi_c, 1), ERROR, SEM_POST);
    }

    #ifdef _DEBUG
        fprintf(stderr, "%s" "| is_wd = %d | getpid %6d | pid %6d |"\
        "sync was performed\n" RES,
        (is_wd)?(RED):(GRE),  is_wd, getpid(), pid);
    #endif

  return SUCCESS;
}

/****************************************************************************
    restarts the opposite application (current process forks and execvp)
*****************************************************************************/
static error_t RestartApp(char* const *argv)
{
    int thread_creat_ret;
    pthread_t thread_zombie_catch;

    #ifdef _DEBUG
        fprintf(stderr, "%s" "| is_wd = %d | getpid %6d | pid %6d |"\
        "in RestartApp b4fork\n" RES,
        (is_wd)?(RED):(GRE),  is_wd, getpid(), pid);
    #endif

    pid = fork();

    if ( ERROR == pid )
    {
        return FORK_ERR;
    }

    #ifdef _DEBUG
        fprintf(stderr, "%s" "| is_wd = %d | getpid %6d | pid %6d |"\
        " in RestartApp after fork\n" RES,
        (is_wd)?(RED):(GRE),  is_wd, getpid(), pid);
    #endif

    if ( CHILD == pid ) /* child process becomes the opposite application */
    {
        /* the opposite application will be loaded */
        const char* to_load = (is_wd) ? (argv[0]) : (wd_path);

        /* make sure semi_a val in opposite process is also init to 1 */
        CheckIfError( SemPost(semi_a, 1), ERROR, SEM_POST);

        CheckIfError(execvp(to_load, argv), ERROR, EXCECV);
    }

    /* create thread fo handle zombie processes */
    thread_creat_ret = pthread_create( &thread_zombie_catch,
                                       NULL, CatchZombie, NULL);

    CheckIfNotSuccess( thread_creat_ret, SUCCESS, TH_CREAT);

    CheckIfNotSuccess(pthread_detach(thread_zombie_catch), SUCCESS, TH_DETCH);

    return SUCCESS;
}

/****************************************************************************
    the main function for this application.
    runs the scheduler, restarts opposite app and scheduler if necessary
    NOTES: designd for pthread ( void *(*start_routine) (void *) )
*****************************************************************************/
static void* MainOp(void *arg)
{
    char* const *argv = (char* const *) arg;

    do{
        CheckIfError(SchedulerRun(scheduler), SCHED_RUN_ERR, (void*)0xDEADBEEF)

        #ifdef _DEBUG
            fprintf(stderr, "%s" "| is_wd = %d | getpid %6d | pid %6d | is_alive = %d |"\
            "exited SchedulerRun\n" RES,
            (is_wd)?(RED):(GRE), is_wd, getpid(), pid, is_alive);
        #endif

        if (is_needed)
        {
            /* restart opposite application */
            CheckIfError( RestartApp(argv), ERROR, (void*)0xDEADBEEF);

            /* allocate scheduler and load tasks into the scheduler */
            CheckIfError(InitScheduler(), ERROR, (void*)0xDEADBEEF);

            /* sync between the two apps */
            CheckIfError(Sync(), ERROR, (void*)0xDEADBEEF);
        }

    } while(is_needed);

    #ifdef _DEBUG
        fprintf(stderr, "%s" "| is_wd = %d | getpid %6d | pid %6d | is_alive = %d |"\
        "after while(is_needed)\n" RES,
        (is_wd)?(RED):(GRE), is_wd, getpid(), pid, is_alive);
    #endif

    SchedulerDestroy(scheduler);

    return NULL; /* successfull return */
}

/*****************************************************************************
**  description: Start wd service, will restart current app on crush after
**               this method was invoked.
**  arguments:   argv - the app argv array.
**  return value: SUCCSESS on succsess, on failure return error num.
**  notes: creates another thread for wd communicaion, uses SIGUSR1 SIGUSR2
**         and SIGCHLD. to end this service call StopWd(). may take some time
**         depending on system load.
******************************************************************************/
int StartWD(char* const *argv)
{
    int sem_crl = 0;

    semi_a = SemCreate(wd_path, 'a', 0);
    if ( ERROR == semi_a )
    {
        return SEM_CREATE;
    }

    sem_crl = semctl(semi_a, 0, GETVAL);
    if ( ERROR == sem_crl )
    {
        return SEM_CTL;
    }

    #ifdef _DEBUG
        fprintf(stderr, "%s" "| semi_a %6d | semi_a val %2d | is_wd = %d |"\
        " getpid %6d | pid %6d | first StartWD entrance\n" RES,
        (is_wd)?(RED):(GRE),  semi_a, semctl(semi_a, 0, GETVAL), is_wd, getpid(), pid);
    #endif

    if ( 0 == sem_crl )
    {
        pid = fork();
        if ( ERROR == pid )
        {
            return FORK_ERR;
        }

        if ( CHILD == pid ) /* if child => become a watch dog */
        {
            /*  on the first call parent will become the dog
                and semi_a will be increased to indicate that app called WD */
            CheckIfError(   SemPost(semi_a, 1), ERROR, SEM_POST);
            CheckIfError(execvp(wd_path, argv), ERROR, EXCECV);
        }
    }
    else /* semaphore indicating WD existence already exists */
    {
        int thread_creat_ret;
        pthread_t thread_zombie_catch;

        thread_creat_ret = pthread_create( &thread_zombie_catch ,
                                           NULL, CatchZombie, NULL);

        CheckIfNotSuccess( thread_creat_ret, SUCCESS, ERROR);

        CheckIfNotSuccess(pthread_detach(thread_zombie_catch), SUCCESS, ERROR);

        /* semaphore exists => I am watch dog => my parent is APP */
        pid = getppid();
    }
#ifdef _DEBUG
    fprintf(stderr, "%s" "| semi_a %6d | semi_a val %2d | is_wd = %d |"\
    " getpid %6d | pid %6d | b4 InitSignalHandlers\n" RES,
    (is_wd)?(RED):(GRE),  semi_a, semctl(semi_a, 0, GETVAL), is_wd, getpid(), pid);
#endif
    CheckIfError( InitSignalHandlers(), ERROR, ERROR);
    CheckIfError( InitScheduler(), ERROR, ERROR);
    CheckIfError( Sync(), ERROR, ERROR);

    #ifdef _DEBUG
        fprintf(stderr, "%s" "| semi_a %6d | is_wd = %d | getpid %6d | pid %6d |"\
        " Just after Sync in MainOp \n" RES,
        (is_wd)?(RED):(GRE),  semi_a, is_wd, getpid(), pid);
    #endif

    if ( !is_wd ) /* if APP (not WD) create thread to manage Communication */
    {
        /* thread for the APP communicator */
        pthread_t thread;

        /* will hold the return value of pthread_create */
        int thread_creat_ret;

        #ifdef _DEBUG
            fprintf(stderr, "%s" "| semi_a %6d | is_wd = %d | getpid %6d | pid %6d |"\
            " App is about to create thread for MainOp\n" RES,
            (is_wd)?(RED):(GRE),  semi_a, is_wd, getpid(), pid);
        #endif


        thread_creat_ret = pthread_create( &thread, NULL, MainOp, (void*)argv);

        CheckIfNotSuccess( thread_creat_ret, SUCCESS, TH_CREAT);

        CheckIfNotSuccess(pthread_detach(thread), SUCCESS, TH_DETCH);
    }
    else /* if Watch Dog */
    {
        #ifdef _DEBUG
            fprintf(stderr, "%s" "| semi_a %6d | is_wd = %d | getpid %6d | pid %6d |"\
            " WD is about to run MainOp\n" RES,
            (is_wd)?(RED):(GRE),  semi_a, is_wd, getpid(), pid);
        #endif

        CheckIfNotSuccess(MainOp((void*)argv), (void*) NULL, MAIN_OP_ERR);
    }

    return SUCCESS;
}

/*****************************************************************************
**  description: end Watch Dog service.
**  arguments:
**  return value: SUCCSESS on succsess, on failure return error num.
**  notes:  stopes the additional thread.
******************************************************************************/
int StopWD()
{
    int semi_b = SemCreate(wd_path, 'b', 0);
    int semi_c = SemCreate(wd_path, 'c', 0);

    /* turn on mode in Task_1 that sends SIGUSR2 alongside SIGUSR1 */
    sig_mode = SEND_SUSR2;

    if ( SemNoWait(semi_a, 0, MAX_TRIES) == ERROR )
    {
        /*  didn't get acknowledgment
            (when WD exits SEM_UNDO flag should make semi_a == 0),
            violently kill WD */
        CheckIfError( kill(pid, SIGKILL), ERROR, KILL_ERR);
    }

    if ( is_needed )
    {
        /*  make sure APPs communicaion thread is closed
            scheduler will be stoped and deallocated,
            thread will be closed shortly */
        is_needed = 0;
    }

    /* only one application (APP) will release the semaphores */
    CheckIfNotSuccess(SemDestroy(semi_a), SUCCESS, ERROR);
    CheckIfNotSuccess(SemDestroy(semi_b), SUCCESS, ERROR);
    CheckIfNotSuccess(SemDestroy(semi_c), SUCCESS, ERROR);

    return SUCCESS;
}


/****************************************************************************
    set global flag is_alive to 1 (alive)
    NOTES: designd for sigaction function (  void (*sa_handler)(int)  )
*****************************************************************************/
static void SignalHandler1(int arg)
{
  /* marking the opposite process as alive */
  is_alive = 1;
}

/****************************************************************************
    set global flag is_needed to 0 (NOT NEEDED)
    and send SIGUSR2 to opposite application
    NOTES: designd for sigaction function (  void (*sa_handler)(int)  )
*****************************************************************************/
static void SignalHandler2(int arg)
{
    is_needed = 0; /* update is_needed of opposite process to not needed */

    /*  if in SEND_SUSR2 mode then
        send SIGUSR2 to enable bursts (every 1 [sec]) of SIGUSR2 signals
        from Task_1 */
    sig_mode  = SEND_SUSR2;
}

/****************************************************************************
    init sigaction function to handle SIGUSR1 and SIGUSR2 signals
*****************************************************************************/
static error_t InitSignalHandlers()
{
    struct sigaction sig_h_1;
    struct sigaction sig_h_2;

    memset (&sig_h_1, 0 /* set to zero */, sizeof (sig_h_1));
    memset (&sig_h_2, 0 /* set to zero */, sizeof (sig_h_2));

    sig_h_1.sa_handler = &SignalHandler1;
    sig_h_2.sa_handler = &SignalHandler2;

    /*  if SIGUSR1 recieved call SignalHandler1 function
        if SIGUSR2 recieved call SignalHandler2 function */
    CheckIfError( sigaction(SIGUSR1, &sig_h_1, NULL), ERROR, SIG_ACT);
    CheckIfError( sigaction(SIGUSR2, &sig_h_2, NULL), ERROR, SIG_ACT);

    return SUCCESS;
}

/****************************************************************************
    sig_mode == SEND_SUSR1 - send SIGUSR1 to the opposite process every second
    sig_mode == SEND_SUSR2 - send SIGUSR2 to the opposite process every second
    NOTES: designd for the uses of scheduler - int (*op_func)(void *param)
*****************************************************************************/
static int Task_1(void *ignored)
{
    /*  if in SEND_SUSR1 mode (default mode)
        then send SIGUSR1 to indicate that current process is alive */
    kill(pid, SIGUSR1);

    if ( SEND_SUSR2 == sig_mode ) /* also signal SIGUSR2 to opposite process */
    {
        /*  if in SEND_SUSR2 mode then
            send SIGUSR2 to enable bursts (every 1 [sec]) of SIGUSR2 signals */
        kill(pid, SIGUSR2);
    }

    #ifdef _DEBUG
        fprintf(stderr, "%s" "| is_wd = %d | getpid %6d | pid %6d | is_alive = %d | "
        CYA BLD UDL"Task_1\n" RES,
        (is_wd)?(RED):(GRE),  is_wd, getpid(), pid, is_alive);
    #endif

    return (CONT_TASK); /* continue task in scheduler */
}

/****************************************************************************
    if flag (is_alive == 0) OR (is_needed == 0) stops the scheduler and exits
    else sets is_alive flag to zero (0)
    NOTES: designd for the uses of scheduler - int (*op_func)(void *param)
*****************************************************************************/
static int Task_2(void *ignored)
{
  /*  stop scheduler if:
             (1) signal from opposite app was not received (for the last 5 sec)
         OR  (2) recieved no need signal
      then: stop the scheduler and act upon in MainOp function */
  if ( !is_alive || !is_needed )
  {

    #ifdef _DEBUG
        fprintf(stderr, "%s" "| is_wd = %d | getpid %6d | pid %6d | is_alive = %d |"\
        "is_needed = %d | "BLU BLD UDL"Task_2\n" RES,
        (is_wd)?(RED):(GRE),  is_wd, getpid(), pid, is_alive, is_needed);
    #endif

    SchedulerStop(scheduler);

    return (DONT_CONT_TASK); /* do NOT continue task in scheduler */
  }
  else
  {
    is_alive = 0; /* marking the opposite process as NOT alive */

    return (CONT_TASK); /* continue task in scheduler */
  }
}

/****************************************************************************
    allocate scheduler handler and add Task_1 and Task_2 to it
*****************************************************************************/
static error_t InitScheduler()
{
    unique_id_t uid;
    scheduler = SchedulerCreate();

    if ( NULL == scheduler )
    {
        return SCHDE_ERR;
    }

    uid = SchedulerAdd(scheduler, Task_1, 1 /*[sec]*/, NULL);
    if ( UIDIsTheSame(uid, g_bad_id) )
    {
        return SCHDE_ERR;
    }

    uid = SchedulerAdd(scheduler, Task_2, 5 /*[sec]*/, NULL);
    if ( UIDIsTheSame(uid, g_bad_id) )
    {
        return SCHDE_ERR;
    }

    return SUCCESS;
}
