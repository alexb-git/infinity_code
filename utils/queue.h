 /***********************************************
  Filename: queue.h
  Purpose: Header file for Queue DS
  Data Structure: Queue
  Version: 3
 ***********************************************/
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct queue queue_t;

/*****************************************************************************
** description:  create a new empty queue handler.
** arguments:    void
** return value: pointer to new queue handler or NULL if failed to create queue.
** notes:        must call QDestroy at end of use
******************************************************************************/
queue_t* QueueCreate(void);

/*****************************************************************************
** description:  frees queue
** arguments:    pointer to queue handler
** return value: void
** notes:        must call at end of use
******************************************************************************/
void QueueDestroy(queue_t *queue);

/*****************************************************************************
** description:  insert a new data element to queue.
** arguments:    queue  - pointer to queue handler.
**               data  - pointer to data to be inserted to queue.
** return value: 1 - QEnqueue succeeded
**               0 - failed
** notes:
******************************************************************************/
int QueueEnqueue(queue_t *queue, const void *data );

/*****************************************************************************
** description:  get and remove the oldest entry from queue
** arguments:    pointer to queue from which to remove the element
** return value: returns a pointer to the element value
**               in case of empty queue retrun NULL
** notes:
******************************************************************************/
void* QueueDequeue(queue_t *queue);

/*****************************************************************************
** description:  get a pointer to the element at the head of queue.
** arguments:    pointer to queue handler.
** return value: pointer to element at the head of queue.
**               in case of empty queue retrun NULL
** notes:
******************************************************************************/
void* QueuePeek(const queue_t *queue);

/*****************************************************************************
** description:  count number of elements in queue
** arguments:    pointer to queue handler.
** return value: number of elements in queue
******************************************************************************/
size_t QueueSize(const queue_t *queue);

/*****************************************************************************
** description:  check if queue is empty
** arguments:    pointer to queue handler.
** return value: 1 - is empty
**               0 - otherwise
******************************************************************************/
int QueueIsEmpty(const queue_t *queue);

/*****************************************************************************
** description:  move elements from 'from' queue to 'to' queue
** arguments:    to   - pointer of the queue to append to
**               from - pointer of queue to be appended
** notes:       'from' queue will be emptyed
** return value: void
******************************************************************************/
void QueueAppend(queue_t *to, queue_t *from);

#endif /* __QUEUE_H__ */
