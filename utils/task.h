/***************************************************
  Filename: task.h
  Purpose:  Header file for task/operation
  Product:  task manager
  Version:  1
 ***************************************************/
#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h>             /* size_t */
#include "uid.h"                /* Unique Identifier - unique_id_t */
#include "operation_func.h"     /* Header file for operation function */

typedef struct task task_t;

/*****************************************************************************
** description:  compares two tasks.
** arguments:    data_1 - task 1 object,
**               data_2 - task 2 object.
** return value: 0 - task_1 and task_2 priorities are equal,
**               positive number - task_1 priority > task_2 priority.
**               negative number - task_1 priority < task_2 priority.
** notes:
******************************************************************************/
typedef int (*cmp_tasks)(const void *data_1, const void *data_2);

/*****************************************************************************
** description:  Get the task comparsion function.
** arguments:    none.
** return value: pointer to the comparsion function between tasks.
******************************************************************************/
cmp_tasks GetCmpFunc(void);

/*****************************************************************************
** description:  create a new task.
** arguments:    op_func  - the carried function to preform.
**               interval - time interval between function operations.
** return value: pointer to task handler.
******************************************************************************/
task_t* TaskCreate(operation_func op_func, size_t interval, void *param);

/*****************************************************************************
** description:   destroys the task.
** arguments:     uid - unique identifier of the task.
** return value:  void.
******************************************************************************/
void TaskDestroy(task_t* task);

/*****************************************************************************
** description:  runs the task
** arguments:    task - pointer to a task handler.
** return value: 1 - task should continue, 0 - task should stop.
******************************************************************************/
int TaskRun(task_t* task);

/*****************************************************************************
** description:  return next execution time.
** arguments:    task - pointer to a task handler.
** return value: next execution time.
******************************************************************************/
size_t TaskCalcNextTime(task_t *task);

/*****************************************************************************
** description:  Get task's unique ID.
** arguments:    task - pointer to a task handler.
** return value: task's unique ID.
******************************************************************************/
unique_id_t TaskGetUID(task_t* task);

#endif /* __TASK_H__ */
