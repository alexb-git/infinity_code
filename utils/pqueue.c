/****************************************************************************
** Filename:    - pqueue.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.come
** Purpose:     - implementation of Priority List
** Date:        - 08/10/2017
** Version:     - 6
*****************************************************************************/
#include <stdlib.h>	        /* malloc, free */
#include <assert.h>	        /* assert */

#include "sortedlist.h"     /* Sorted Linked List DS */
#include "pqueue.h"         /* Priority List DS */

struct pqueue
{
  sorted_list_t *sorted_list;
};

/*****************************************************************************
** description:  create a new empty priority queue handler.
** arguments:    cmp_function3 - defines the queues sorting order.
** return value: pointer to new priority queue handler or NULL if failed to
**               create queue.
** notes:        must call PQueueDestroy at end of use.
******************************************************************************/
pqueue_t* PQueueCreate(cmp_function3 cmpfunc)
{
  pqueue_t *handler = NULL;

  assert( cmpfunc != NULL );

  handler = (pqueue_t*) malloc ( sizeof(pqueue_t) );

  if (NULL != handler)
  {
      handler->sorted_list = SortedListCreate(cmpfunc);

      if ( NULL == handler->sorted_list )
      {
          /* SortedListCreate failed */
          free(handler);
          handler = NULL;
      }
  }

  return handler;
}

/*****************************************************************************
** description:  destroy priority queue.
** arguments:    pointer to queue handler.
** return value: void.
** notes:        must call at end of use.
******************************************************************************/
void PQueueDestroy(pqueue_t *pqueue)
{
  assert( pqueue != NULL );

  SortedListDestroy(pqueue->sorted_list);
  pqueue->sorted_list = NULL;

  free(pqueue);
  pqueue = NULL;
}

/*****************************************************************************
** description:  insert a new data element to priority queue.
** arguments:    queue - pointer to priority queue handler.
**               data  - pointer to data to be inserted to priority queue.
** return value: 1 - PQEnqueue succeeded.
**               0 - failed.
** notes:
******************************************************************************/
int PQueueEnqueue(pqueue_t *pqueue, const void *data )
{
  sorted_list_itr_t itr;

  assert( pqueue != NULL );

  itr = SortedListInsert(pqueue->sorted_list, data);

  /* 0 - SortedListInsert didn't succeeded, 1 - otherwise */
  return (itr.itr == NULL) ? (0) : (1);
}

/*****************************************************************************
** description:  remove the first element in the priority queue.
** arguments:    pointer to priority queue handler.
** return value: pointer to data which dequeue.
** notes:        when the queue is empty - the return value is NULL.
******************************************************************************/
void* PQueueDequeue(pqueue_t *pqueue)
{
  void *ret_data = NULL;

  assert( pqueue != NULL );

  ret_data = SortedListGetData(SortedListBegin(pqueue->sorted_list));

  SortedListPopFront(pqueue->sorted_list);;

  return ret_data;
}

/*****************************************************************************
** description:  get a pointer to the element at the head of priority queue.
** arguments:    pointer to priority queue handler.
** return value: pointer to element at the head of priority queue.
** notes:        in case of empty queue retrun NULL.
******************************************************************************/
void* PQueuePeek(const pqueue_t *pqueue)
{
  assert( pqueue != NULL );

  return SortedListGetData(SortedListBegin(pqueue->sorted_list));;
}

/*****************************************************************************3
** description:  count number of elements in the priority queue.
** arguments:    pointer to priority queue handler.
** return value: number of elements in queue.
******************************************************************************/
size_t PQueueCount(const pqueue_t *pqueue)
{
  assert( pqueue != NULL );

  return SortedListSize(pqueue->sorted_list);
}

/*****************************************************************************
** description:  check if priority queue is empty.
** arguments:    pointer to priority queue handler.
** return value: 1 - is empty, 0 - otherwise.
******************************************************************************/
int PQueueIsEmpty(const pqueue_t *pqueue)
{
  assert( pqueue != NULL );

  return SortedListIsEmpty(pqueue->sorted_list);
}

/*****************************************************************************
** description:  empty/clear the priority queue
** arguments:    pointer to priority queue handler.
** return value: void.
** notes:        handler remains functional, priority queue is emptied.
******************************************************************************/
void PQueueClear(pqueue_t *pqueue)
{
    assert( pqueue != NULL );

    while ( !PQueueIsEmpty(pqueue) )
    {
        /* pop till empty */
        SortedListPopFront(pqueue->sorted_list);
    }
}

/*****************************************************************************
** description:  find and erase the first element that
**               satisfies the function (function retuns 1),
**               if element is not found returns NULL.
** arguments:    pqueue     - pointer to priority queue handler.
**               im_func    - function that identify certain elements.
**               param      - parameter for im_func use.
** return value: pointer to the erased data, or NULL of no match was found.
******************************************************************************/
void* PQueueErase(pqueue_t *pqueue, is_match_func im_func, void *param)
{
    sorted_list_itr_t itr;
    sorted_list_itr_t end;

    assert( pqueue != NULL && im_func != NULL );

    itr = SortedListBegin(pqueue->sorted_list);
    end =   SortedListEnd(pqueue->sorted_list);

    while ( !SortedListSameIterator(itr, end) )
    {
        if ( im_func(SortedListGetData(itr) ,param) ) /* == 1 */
        {
            void *data = SortedListGetData(itr);

            /* if there is a match erase queue element */
            itr = SortedListErase(pqueue->sorted_list, itr);

            return data;
        }
        else
        {
            itr = SortedListNext(itr);
        }
    }

    return NULL;
}
