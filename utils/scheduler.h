/***************************************************
  Filename: scheduler.h
  Purpose:  Header file for scheduler
  Product:  operation scheduler
  Version:  2
 ***************************************************/
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h> /* size_t */

#include "uid.h"             /* Unique Identifier - unique_id_t */
#include "operation_func.h"  /* Header file for operation function */

typedef struct scheduler scheduler_t; /* scheduler handler */

/*****************************************************************************
** description:   create a new handler to a operation schedular
** arguments:     void.
** return value:  pointer to new scheduler handler,
**                or NULL if failed to create.
** notes:         must call SchedulerDestroy at end of use.
******************************************************************************/
scheduler_t* SchedulerCreate(void);

/*****************************************************************************
** description:  destroys the scheduler.
** arguments:    scheduler handler.
** return value: void.
** notes:        must be called at end of use.
******************************************************************************/
void SchedulerDestroy(scheduler_t *scheduler);

/*****************************************************************************
** description:  adds new task to the scheduler.
** arguments:    scheduler  - scheduler handler.
**               op_func    - the function to be preformed.
**               interval   - time interval for the task to be preformed.
**               param      - user's data.
** return value: if succeed - returns a unique identifier to the added task
**               otherwise  - returns g_bad_id.
******************************************************************************/
unique_id_t SchedulerAdd(scheduler_t *scheduler,
                         operation_func op_func,
                         size_t interval,
                         void *param);

/*****************************************************************************
** description:  removes task from the scheduler.
** arguments:    scheduler - scheduler handler.
**               uid       - unique identifier of the task.
** return value: void.
** notes:
******************************************************************************/
void SchedulerRemove(scheduler_t *scheduler, unique_id_t uid);

/*****************************************************************************
** description:  runs the scheduler.
** arguments:    scheduler - scheduler handler.
** return value: 1 - all tasks finished successfully,
                 0 - SchedulerRun failed at some point.
******************************************************************************/
int SchedulerRun(scheduler_t *scheduler);

/*****************************************************************************
** description:  stops the scheduler.
** arguments:    scheduler - scheduler handler.
** return value: void.
** notes:        releases the tasks from the scheduler.
******************************************************************************/
void SchedulerStop(scheduler_t *scheduler);

/*****************************************************************************
** description:  counts number of tasks in the scheduler.
** arguments:    scheduler - scheduler handler.
** return value: number of tasks in the scheduler.
******************************************************************************/
size_t SchedulerSize(scheduler_t *scheduler);

/*****************************************************************************
** description:  checks if the scheduler is empty.
** arguments:    scheduler - scheduler handler.
** return value: 1 - if scheduler is empty,
**               0 - otherwise.
******************************************************************************/
int SchedulerIsEmpty(scheduler_t *scheduler);

#endif /* __SCHEDULER_H__ */
