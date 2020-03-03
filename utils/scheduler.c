/****************************************************************************
** Filename:    - scheduler.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementation of task scheduler
** Date:        - 11/10/2017
** Version:     - 1
*****************************************************************************/
#include <assert.h>     /* assert */
#include <stdlib.h>     /* malloc, free */
#include <pthread.h>    /* thread  ID */
#include <unistd.h>     /* sleep */

#include "task.h"       /* task structure and management */
#include "pqueue.h"     /* priority queue DS */
#include "scheduler.h"  /* task scheduler */

struct scheduler
{
    pqueue_t *pqueue;
};

/*****************************************************************************
** description:   create a new handler to a operation schedular
** arguments:     void.
** return value:  pointer to new scheduler handler,
**                or NULL if failed to create.
** notes:         must call SchedulerDestroy at end of use.
******************************************************************************/
scheduler_t* SchedulerCreate(void)
{
    scheduler_t *handler = (scheduler_t*) malloc( sizeof(scheduler_t) );
    if (NULL != handler)
    {
        handler->pqueue = PQueueCreate( GetCmpFunc() );
        if ( NULL == handler->pqueue )
        {
            /* case: PQueueCreate faild to allocate */
            free(handler);
            handler = NULL;
        }
    }

    return handler;
}

/*****************************************************************************
** description:  destroys the scheduler.
** arguments:    scheduler handler.
** return value: void.
** notes:        must be called at end of use.
******************************************************************************/
void SchedulerDestroy(scheduler_t *scheduler)
{
    assert( scheduler != NULL );

    /* pop pqueue till empty and destroy each remaining task */
    while ( !PQueueIsEmpty(scheduler->pqueue) )
    {
        TaskDestroy( (task_t*)PQueueDequeue(scheduler->pqueue) );
    }

    /* destroy the pqueue handler */
    PQueueDestroy(scheduler->pqueue);

    /* free the scheduler handler */
    free(scheduler);
    scheduler = NULL;
}

/*****************************************************************************
** description:  adds new task to the scheduler.
** arguments:    scheduler  - scheduler handler.
**               op_func    - the function to be preformed.
**               interval   - time interval for the task to be preformed.
**               param      - user's data.
** return value: if succeed - returns a unique identifier to the added task
**               otherwise  - returns g_bad_id.
******************************************************************************/
unique_id_t SchedulerAdd( scheduler_t    *scheduler,
                          operation_func  op_func,
                          size_t          interval,
                          void           *param      )
{
    task_t *new_task = NULL;

    assert( (scheduler != NULL) && (op_func != NULL) );

    new_task = TaskCreate(op_func, interval, param);

    if ( new_task != NULL ) /* TaskCreate succeeded */
    {
        if ( PQueueEnqueue( scheduler->pqueue, (void*)new_task) ) /* ==1 */
        {
            /* PQueueEnqueue succeeded */
            return TaskGetUID(new_task);
        }
        else /* PQueueEnqueue failed */
        {
            free(new_task);
            new_task = NULL;
        }
    }

    return g_bad_id; /* PQEnqueue OR TaskCreate failed */
}

/*****************************************************************************
**  description:  retuns 1 if UID match, 0 - otherwise.
**  arguments:    task - pointer to the task.
**                uid  - pointer to the uid.
**  return value: 1 - match, 0 - no match.
**  notes:
******************************************************************************/
static int MatchByUID(const void *task, void *uid)
{
    return UIDIsTheSame( TaskGetUID( (task_t*)task ) , *(unique_id_t*)uid );
}

/*****************************************************************************
** description:  removes task from the scheduler.
** arguments:    scheduler - scheduler handler.
**               uid       - unique identifier of the task.
** return value: void.
** notes:
******************************************************************************/
void SchedulerRemove(scheduler_t *scheduler, unique_id_t uid)
{
    assert( scheduler != NULL );

    TaskDestroy( (task_t*)PQueueErase( scheduler->pqueue, MatchByUID, &uid ) );
}

/*****************************************************************************
** description:  runs the scheduler.
** arguments:    scheduler - scheduler handler.
** return value: 1 - all tasks finished successfully,
                 0 - SchedulerRun failed at some point.
******************************************************************************/
int SchedulerRun(scheduler_t *scheduler)
{
    size_t prev_sleep_interval = 0;

    assert( scheduler != NULL );

    /* run while there are tasks to execute */
    while ( !SchedulerIsEmpty(scheduler) )
    {
        /* Dequeue task to perform */
        task_t *task = (task_t*)PQueueDequeue(scheduler->pqueue);

        /* extract the next_call_time of the function */
        size_t sleep_interval = TaskCalcNextTime( task );

        /* sleep till next_call_time */
        size_t interval = sleep_interval - prev_sleep_interval;
        while ((interval = sleep(interval)) > 0) {}

        prev_sleep_interval = sleep_interval;

        if ( TaskRun( task ) )  /* ==1 -> continue */
        {
            /* re-insert the task that ran */
            if ( PQueueEnqueue(scheduler->pqueue, task) == 0 )
            {
                /* case: PQueueEnqueue failed */
                TaskDestroy(task);
                return 0;
            }
        }
        else /* TaskRun( task ) == 0 -> don't continue task */
        {
            TaskDestroy(task);
        }
    }

    return 1; /* all tasks finished successfully */
}

/*****************************************************************************
** description:  stops the scheduler.
** arguments:    scheduler - scheduler handler.
** return value: void.
** notes:        releases the tasks from the scheduler.
******************************************************************************/
void SchedulerStop(scheduler_t *scheduler)
{
    assert( scheduler != NULL );

    /* release all the tasks from pqueue */
    while ( !PQueueIsEmpty(scheduler->pqueue) )
    {
        TaskDestroy( (task_t*)PQueueDequeue(scheduler->pqueue) );
    }
}

/*****************************************************************************
** description:  counts number of tasks in the scheduler.
** arguments:    scheduler - scheduler handler.
** return value: number of tasks in the scheduler.
******************************************************************************/
size_t SchedulerSize(scheduler_t *scheduler)
{
    assert( scheduler != NULL );
    return PQueueCount(scheduler->pqueue);
}

/*****************************************************************************
** description:  checks if the scheduler is empty.
** arguments:    scheduler - scheduler handler.
** return value: 1 - if scheduler is empty,
**               0 - otherwise.
******************************************************************************/
int SchedulerIsEmpty(scheduler_t *scheduler)
{
    assert( scheduler != NULL );
    return PQueueIsEmpty(scheduler->pqueue);
}
