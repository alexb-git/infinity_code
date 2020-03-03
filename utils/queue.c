/****************************************************************************
** Filename:    - queue.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.come
** Purpose:     - Implementation of Queue Data Structure
** Date:        - 27/09/2017
** Version:     - 4
*****************************************************************************/

#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */

#include "slist.h"  /* singly list DS */
#include "queue.h"

#define first_in_q  (queue->stub->next)

struct queue
{
    node_t *tail;   /* points to the last element in the queue */
    node_t *stub;   /* stub->next is the head (first element) of queue */
};

/*
typedef struct node
{
    void        *data;
    struct node *next;
} node_t;
*/

/*****************************************************************************
** description:  create a new empty queue handler.
** arguments:    void
** return value: pointer to new queue handler or NULL if failed to create queue.
** notes:        must call QDestroy at end of use
******************************************************************************/
queue_t* QueueCreate(void)
{
    queue_t *handler = (queue_t*)malloc( sizeof(queue_t) );
    if ( NULL == handler )
    {
        return NULL;
    }

    handler->stub = SListCreateNode(NULL, NULL);
    if ( NULL == handler->stub )
    {
        free(handler);
        handler = NULL;
        return NULL;
    }

    handler->tail = handler->stub;

    return handler;
}

/*****************************************************************************
** description:  frees queue
** arguments:    pointer to queue handler
** return value: void
** notes:        must call at end of use
******************************************************************************/
void QueueDestroy(queue_t *queue)
{
    assert( queue != NULL );

    SListFreeAll(queue->stub);

    free(queue);
    queue = NULL;
}

/*****************************************************************************
** description:  insert a new data element to queue.
** arguments:    queue  - pointer to queue handler.
**               data  - pointer to data to be inserted to queue.
** return value: 1 - QEnqueue succeeded
**               0 - failed
** notes:
******************************************************************************/
int QueueEnqueue(queue_t *queue, const void *data )
{
    node_t *insert_location  = NULL;

    assert( queue != NULL );

    insert_location  = SListInsertAfter(queue->tail, data);
    if ( NULL == insert_location )
    {
        /* case: malloc in SListInsertAfter failed,
                 do not update the tail to NULL */
        return 0;
    }

    queue->tail = insert_location;
    return 1;
}

/*****************************************************************************
** description:  get and remove the oldest entry from queue
** arguments:    pointer to queue from which to remove the element
** return value: returns a pointer to the element value
**               in case of empty queue retrun NULL
** notes:
******************************************************************************/
void* QueueDequeue(queue_t *queue)
{
    assert( queue != NULL );

    if ( !QueueIsEmpty(queue) )
    {
        /* save the data that the head contained */
        void *ret_val = first_in_q->data;

        /* remove from the head of the queue */
        queue->stub = SListRemoveAfter(queue->stub);

        /* case: last entry removed, re-point the tail */
        if ( QueueIsEmpty(queue) )
        {
            queue->tail = queue->stub;
        }

        return ret_val;
    }

    return NULL;
}

/*****************************************************************************
** description:  get a pointer to the element at the head of queue.
** arguments:    pointer to queue handler.
** return value: pointer to element at the head of queue.
**               in case of empty queue retrun NULL
** notes:
******************************************************************************/
void* QueuePeek(const queue_t *queue)
{
    assert( queue != NULL );

    if ( !QueueIsEmpty(queue) )
    {
        return first_in_q->data;
    }

    return NULL;
}

/*****************************************************************************
** description:  count number of elements in queue
** arguments:    pointer to queue handler.
** return value: number of elements in queue
******************************************************************************/
size_t QueueSize(const queue_t *queue)
{
    assert( queue != NULL );
    return SListCountNodes(queue->stub) - 1;
}

/*****************************************************************************
** description:  check if queue is empty
** arguments:    pointer to queue handler.
** return value: 1 - is empty
**               0 - otherwise
******************************************************************************/
int QueueIsEmpty(const queue_t *queue)
{
    assert( queue != NULL );
    return ( NULL == first_in_q );
}

/*****************************************************************************
** description:  move elements from 'from' queue to 'to' queue
** arguments:    to   - pointer of the queue to append to
**               from - pointer of queue to be appended
** notes:       'from' queue will be emptyed
** return value: void
******************************************************************************/
void QueueAppend(queue_t *to, queue_t *from)
{
    assert( to != NULL && from != NULL);

    if ( !QueueIsEmpty(from) )
    {
        /* append from 'from' queue to 'to' queue */
        to->tail->next = from->stub->next;

        /* update the tail of 'to' queue */
        to->tail = from->tail;

        /* update the 'from' queue stub->next (head) */
        from->stub->next = NULL;

        /* update the tail of 'from' queue */
        from->tail = from->stub;
    }
}
