/***********************************************
  Filename: pqueue.h
  Purpose: Header file for Priority Queue DS
  Data Structure: Priority Queue
  Version: 4
 ***********************************************/
#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include <stddef.h> /* size_t */

typedef struct pqueue pqueue_t;

/*****************************************************************************
** description:  compare function provided by the user in order to compare.
** arguments:    data_1, data_2 - compare between data_1 and data_2.
** return value: 0 - data is equal, negative integer if 2 is bigger than 1,
**               positive integer - if 1 is bigger than 2.
** notes:
******************************************************************************/
typedef int (*cmp_function3)(const void *data_1, const void *data_2);

/*****************************************************************************
**  description:  match function that is provided by the user.
**  arguments:    data    - element to invoke the function on.
**                param   - for the use of match function.
**  return value: 1 - match, 0 - not a match.
**  notes:
******************************************************************************/
typedef int (*is_match_func)(const void *data, void *param);

/*****************************************************************************
** description:  create a new empty priority queue handler.
** arguments:    cmp_function3 - defines the queues sorting order.
** return value: pointer to new priority queue handler or NULL if failed to
**               create queue.
** notes:        must call PQueueDestroy at end of use.
******************************************************************************/
pqueue_t* PQueueCreate(cmp_function3 cmpfunc);

/*****************************************************************************
** description:  destroy priority queue.
** arguments:    pointer to queue handler.
** return value: void.
** notes:        must call at end of use.
******************************************************************************/
void PQueueDestroy(pqueue_t *pqueue);

/*****************************************************************************
** description:  insert a new data element to priority queue.
** arguments:    queue - pointer to priority queue handler.
**               data  - pointer to data to be inserted to priority queue.
** return value: 1 - PQEnqueue succeeded.
**               0 - failed.
** notes:
******************************************************************************/
int PQueueEnqueue(pqueue_t *pqueue, const void *data );

/*****************************************************************************
** description:  remove the first element in the priority queue.
** arguments:    pointer to priority queue handler.
** return value: pointer to data which dequeue.
** notes:        when the queue is empty - the return value is NULL.
******************************************************************************/
void* PQueueDequeue(pqueue_t *pqueue);

/*****************************************************************************
** description:  get a pointer to the element at the head of priority queue.
** arguments:    pointer to priority queue handler.
** return value: pointer to element at the head of priority queue.
** notes:        in case of empty queue retrun NULL.
******************************************************************************/
void* PQueuePeek(const pqueue_t *pqueue);

/*****************************************************************************3
** description:  count number of elements in the priority queue.
** arguments:    pointer to priority queue handler.
** return value: number of elements in queue.
******************************************************************************/
size_t PQueueCount(const pqueue_t *pqueue);

/*****************************************************************************
** description:  check if priority queue is empty.
** arguments:    pointer to priority queue handler.
** return value: 1 - is empty, 0 - otherwise.
******************************************************************************/
int PQueueIsEmpty(const pqueue_t *pqueue);

/*****************************************************************************
** description:  empty/clear the priority queue
** arguments:    pointer to priority queue handler.
** return value: void.
** notes:        handler remains functional, priority queue is emptied.
******************************************************************************/
void PQueueClear(pqueue_t *pqueue);

/*****************************************************************************
** description:  erase certain elements from priority queue.
** arguments:    pqueue     - pointer to priority queue handler.
**               im_func    - function that identify certain elements.
                 param      - parameter for im_func use.
** return value: void
******************************************************************************/
void* PQueueErase(pqueue_t *pqueue, is_match_func im_func, void *param);

#endif /* __PQUEUE_H__ */
