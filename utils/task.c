/****************************************************************************
** Filename:    - task.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - management of task structure
** Date:        - 11/10/2017
** Version:     - 1
*****************************************************************************/
#include <assert.h>             /* assert */
#include <stdlib.h>             /* malloc, free */
#include <pthread.h>            /* thread  ID */

#include "task.h"               /* task structure and management */

struct task
{
    operation_func op_func;
    size_t         next_call_time;
    size_t         interval;
    void          *param;
    unique_id_t    uid;
};

/*****************************************************************************
** description:  compares next call time field of two tasks.
** arguments:    data_1 - task 1 object, data_2 - task 2 object.
** return value: 0 - task_1 and task_2 priorities are equal,
**               positive number - task_1 priority > task_2 priority.
**               negative number - task_1 priority < task_2 priority.
** notes:
******************************************************************************/
int CompareNextCallTime(const void *data_1, const void *data_2)
{
    assert( (data_1 != NULL) && (data_2 != NULL) );

    return    ((task_t*)data_1)->next_call_time\
            - ((task_t*)data_2)->next_call_time;
}

/*****************************************************************************
** description:  Get the task comparsion function.
** arguments:    none.
** return value: pointer to the comparsion function between tasks.
******************************************************************************/
cmp_tasks GetCmpFunc(void)
{
    return CompareNextCallTime;
}

/*****************************************************************************
** description:  create a new task.
** arguments:    op_func  - the carried function to preform.
**               interval - time interval between function operations.
** return value: pointer to task handler.
******************************************************************************/
task_t* TaskCreate(operation_func op_func, size_t interval, void *param)
{
    task_t *task = NULL;

    assert( op_func != NULL );

    task = (task_t*) malloc( sizeof(task_t) );

    if (NULL != task)
    {
        task->next_call_time = interval;
        task->interval       = interval;
        task->op_func        = op_func;
        task->param          = param;
        task->uid            = UIDCreate();
    }

    return task;
}

/*****************************************************************************
** description:   destroys the task.
** arguments:     uid - unique identifier of the task.
** return value:  void.
******************************************************************************/
void TaskDestroy(task_t* task)
{
    free(task);
    task = NULL;
}

/*****************************************************************************
** description:  runs the task
** arguments:    task - pointer to a task handler.
** return value: 1 - task should continue, 0 - task should stop.
******************************************************************************/
int TaskRun(task_t* task)
{
    assert( task != NULL );

    if ( task->op_func(task->param) ) /* ==1 -> continue */
    {
        task->next_call_time += task->interval;
        return 1;
    }

    return 0;
}

/*****************************************************************************
** description:  return next execution time.
** arguments:    task - pointer to a task handler.
** return value: next execution time.
******************************************************************************/
size_t TaskCalcNextTime(task_t *task)
{
    assert( task != NULL );
    return task->next_call_time;
}

/*****************************************************************************
** description:  Get task's unique ID.
** arguments:    task - pointer to a task handler.
** return value: task's unique ID.
******************************************************************************/
unique_id_t TaskGetUID(task_t* task)
{
    assert( task != NULL );
    return task->uid;
}
