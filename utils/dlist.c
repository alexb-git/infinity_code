/****************************************************************************
** Filename:    - dlist.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.come
** Purpose:     - implementation of Doubly Linked List Data Structure
** Date:        - 02/10/2017
** Version:     - 20
*****************************************************************************/
#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */

#include "dlist.h"

#define first_in_list (dlist->head->next)

typedef struct node
{
    void        *data;
    struct node *next;
    struct node *prev;
} node_t;


struct dlist
{
    node_t *head; /* head->next points to the first element of the list  */
    node_t *tail; /* end of list, doesn't hold data, denotes end */
};

/*****************************************************************************
** description:  create a new node.
** arguments:    data - pointer to data
**               next - pointer to next node
**               prev - pointer to prev node
** return value: pointer to new node.
******************************************************************************/
static node_t* NodeCreate(const void *data, node_t *next, node_t *prev)
{
    node_t *new_node = (node_t*) malloc ( sizeof(node_t) );

    if (NULL != new_node)
    {
        new_node->data = (void*)data;

        /* connect 'new_node' and 'next' node  */
        new_node->next = next;
        next->prev     = new_node;

        /* connect 'new_node' and 'prev' node  */
        new_node->prev = prev;
        prev->next     = new_node;
    }

    return new_node;
}

/*****************************************************************************
** description:  create a new doubly linked list handler.
** arguments:    void.
** return value: pointer to doubly linked list handler.
** notes:        must call DListDestroy at end of use.
******************************************************************************/
dlist_t* DlistCreate(void)
{
    dlist_t *dlist_handler = (dlist_t*) malloc ( sizeof(dlist_t) );
    if (NULL == dlist_handler)
    {
        return NULL;
    }

    /* creation of head stub */
    dlist_handler->head = (node_t*) malloc ( sizeof(node_t) );
    if (NULL == dlist_handler->head)
    {
        /* case: malloc failed. release previous allocations and return NULL */
        free(dlist_handler);
        dlist_handler = NULL;
        return NULL;
    }

    dlist_handler->head->data = NULL;   /* init not necessary */
    dlist_handler->head->prev = NULL;   /* init not necessary */

    /* cretion and tail stub */
    dlist_handler->tail = (node_t*) malloc ( sizeof(node_t) );
    if (NULL == dlist_handler->tail)
    {
        /* case: malloc failed. release previous allocations and return NULL */
        free(dlist_handler);
        dlist_handler = NULL;

        free(dlist_handler->head);
        dlist_handler->head = NULL;

        return NULL;
    }

    dlist_handler->tail->data = NULL;   /* init not necessary */
    dlist_handler->tail->next = NULL;   /* init not necessary */

    /* bind the stabs - head and tail */
    dlist_handler->tail->prev = dlist_handler->head;
    dlist_handler->head->next = dlist_handler->tail;

    return dlist_handler;
}

/*****************************************************************************
** description:  free the dlist.
** arguments:    dlist - pointer to the list to be free.
** return value: void.
** notes:        must call at end of use.
******************************************************************************/
void DlistDestroy(dlist_t *dlist)
{
    node_t *ptr = NULL;

    assert( dlist != NULL );

    ptr = dlist->head;

    /* free all of the nodes */
    while ( ptr != NULL )
    {
        node_t *temp = ptr->next;

        free(ptr);
        ptr = NULL;

        ptr = temp;
    }

    /* free the handler */
    free(dlist);
    dlist = NULL;
}

/*****************************************************************************
** description:  counts number of elements in dlist.
** arguments:    dlist - pointer to dlist handler.
** return value: number of elements in dlist.
** notes:
******************************************************************************/
size_t DlistCount(const dlist_t *dlist)
{
    size_t  counter  = -1;  /* b/c tail stub is always counted */
    node_t *ptr      = first_in_list;

    while ( ptr != NULL )
    {
        ++counter;
        ptr = ptr->next;
    }

    return counter;
}

/*****************************************************************************
** description:  check if dlist is empty.
** arguments:    dlist - pointer to dlist handler.
** return value: 1 - empty, 0 - else.
** notes:
******************************************************************************/
int DlistIsEmpty(const dlist_t *dlist)
{
    assert( dlist != NULL );
    return (first_in_list == dlist->tail);
}

/*****************************************************************************
** description:  returns iterator that points to first element of dlist.
** arguments:    dlist - pointer to dlist handler.
** return value: iterator that points to beginning of dlist,
**               in case of empty retrun pointer to stub element
** notes:
******************************************************************************/
itr_t DlistBegin(const dlist_t *dlist)
{
    assert( dlist != NULL );
    return (void*)first_in_list;
}

/*****************************************************************************
** description:  returns iterator that points to end of dlist.
**               (end of dlist is the stub element after the last element)
** arguments:    dlist - pointer to dlist handler.
** return value: iterator that points to end of dlist
** notes:
******************************************************************************/
itr_t DlistEnd(const dlist_t *dlist)
{
    assert( dlist != NULL );
    return (void*)dlist->tail;
}

/*****************************************************************************
** description:  promote the iterator to the next element.
** arguments:    itr - iterator.
** return value: iterator to the next element.
** notes:        if itr points to end, the return value is unpredicted
******************************************************************************/
itr_t DlistNext(const itr_t itr)
{
    assert( itr != NULL );
    return (void*)((node_t*)itr)->next;
}

/*****************************************************************************
** description:   returns iterator of the previous element.
** arguments:     iterator.
** return value:  iterator to the previous element.
** notes:         if itr points to begin, the return value is unpredicted
******************************************************************************/
itr_t DlistPrev(const itr_t itr)
{
    assert( itr != NULL );
    return (void*)((node_t*)itr)->prev;
}

/*****************************************************************************
** description:  insert a new element before specified itr
** arguments:    dlist - pointer to dlist handler
**               itr   - iterator to the specified element in dlist
**               data  - pointer to data
** return value: iterator to the inserted element that contains the data
** notes:        if insertion failed - return null
******************************************************************************/
itr_t DlistInsert(dlist_t *dlist, itr_t itr, const void *data)
{
    assert( dlist != NULL && itr != NULL );

    /* create node and init (data, next,         prev ) */
    return (void*)NodeCreate(data, (node_t*)itr, (node_t*)DlistPrev(itr) );
}

/*****************************************************************************
** description:  insert a new element after specified iterator
** arguments:    dlist - pointer to dlist handler
**               itr  - iterator to the location
**               data - pointer to the data to insert
** return value: if itr points to end, the return value is unpredicted
** notes:        if insertion failed - return null
******************************************************************************/
itr_t DlistInsertAfter(dlist_t *dlist, itr_t itr, const void *data)
{
    assert( dlist != NULL && itr != NULL );

    /* create node and init (data, next,                    prev ) */
    return (void*)NodeCreate(data, (node_t*)DlistNext(itr), (node_t*)itr);
}

/*****************************************************************************
** description:  erase element pointed by itr
** arguments:    dlist - pointer to dlist handler
**               itr   -  iterator to the element to erase
** return value: iterator to next element (after the removed element)
** notes:        if itr points to end or if list is empty
**               no action occurs, and the return value is
**               itr that points to end.
******************************************************************************/
itr_t DlistErase(dlist_t *dlist, itr_t itr)
{
    node_t *ret_val  = DlistEnd(dlist);

    assert( dlist != NULL && itr != NULL );

    /*   ( list is not empty)    (itr doesn't point to end) */
    if ( !DlistIsEmpty(dlist) && (itr != ret_val) )
    {
        node_t *node_ptr = (node_t*)itr;
                ret_val  = node_ptr->next;

        /* prev field of next pointer points to node before the erased one */
        node_ptr->next->prev = node_ptr->prev;

        /* next field of previous pointer points to node after the erased one */
        node_ptr->prev->next = node_ptr->next;

        /* free the current node */
        free(node_ptr);
        node_ptr = NULL;
    }

    return ret_val;
}

/*****************************************************************************
** description:  push data to the start of the data structure
** arguments:    dlist - pointer to dlist handler
** return value: itertaor to the new element.
** notes:        if push failed - return null
******************************************************************************/
itr_t DlistPushFront(dlist_t *dlist, const void *data)
{
    assert( dlist != NULL );

    /* create node and init (data, next,          prev ) */
    return (void*)NodeCreate(data, first_in_list, dlist->head);
}

/*****************************************************************************
** description:  push data to the back of the data structure
** arguments:    dlist   - doubly list handler
**               data  - pointer  to the data to push
** return value: itertaor to the new element.
** notes:        if push failed - return null
******************************************************************************/
itr_t DlistPushBack(dlist_t *dlist, const void *data)
{
    assert( dlist != NULL );

    /* create node and init (data, next,        prev ) */
    return (void*)NodeCreate(data, dlist->tail, dlist->tail->prev);
}

/*****************************************************************************
** description:  remove first element in doubly list
** arguments:    dlist    - doubly list handler
** return value: iterator to next element to the one that was popped.
** notes:        if list is empty return value is itr that points to end.
******************************************************************************/
itr_t DlistPopFront(dlist_t *dlist)
{
    assert( dlist != NULL );

    if ( !DlistIsEmpty(dlist) )
    {
        return DlistErase(dlist, DlistBegin(dlist));
    }

    return DlistEnd(dlist);
}

/*****************************************************************************
** description:  remove last element in doubly list
** arguments:    dlist    - doubly list handler
** return value: iterator to previous element to the one that was popped
** notes:        if list is empty return value is itr that points to end.
******************************************************************************/
itr_t DlistPopBack(dlist_t *dlist)
{
    assert( dlist != NULL );

    if ( !DlistIsEmpty(dlist) )
    {
        return DlistPrev(DlistErase(dlist, DlistPrev(DlistEnd(dlist))));
    }

    return DlistEnd(dlist);
}

/*****************************************************************************
** description:  invoke `bool_function` on all data from 'start'
**               till 'end', return iterator to the first data
**               that failed the boolean function, or NULL if all succeeded
** arguments:    start - iterator, from where to invoke the function (inclusive)
**               end   - iterator, till where to invoke the function (exclusive)
**               b_func  - pointer to users' function .
**               param   - additional parameter for the function
** return value: pointer to the first node that failed the boolean
**               function, or NULL if all nodes succeeded.
******************************************************************************/
itr_t DlistForEach(itr_t start, itr_t end, bool_function b_func, void *param)
{
    assert( (start != NULL) && (end != NULL) && (b_func != NULL) );

    while ( start != end )
    {
        if ( b_func(DlistGetData(start), param) == 0 )
        {
            return start;
        }
        start = DlistNext(start);
    }

    return NULL;
}

/******************************************************************************
** description:  look for the specific element (first occurrence)
**               'data' in dlist.
** arguments:    start   - iterator, where to begin the search (inclusive)
**               end     - iterator, where to end the search (exclusive)
**               b_func  - user compare function.
**               data    - pointer to the data we seeked.
** return value: returns iterator that points to the data,
**               or NULL if data was not found.
******************************************************************************/
itr_t DlistFind(itr_t start, itr_t end, cmp_function c_func, const void *data)
{
    assert( (start != NULL) && (end != NULL) && (c_func != NULL) );

    while ( start != end )
    {
        if ( c_func(DlistGetData(start), data) == 0 )
        {
            return start;
        }
        start = DlistNext(start);
    }

    return NULL;
}

/*****************************************************************************
** description:  insert the linked list 'start'
**               between 'before' and 'before->next'.
** arguments:    before - iterator to element to inset before.
**               start  - splice from this iterator.
**               end    - splice up to this iterator.
** return value: void
** notes:
******************************************************************************/
void DlistSpliceBefore(itr_t before, itr_t start, itr_t end)
{
    assert( (before != NULL) && (start != NULL) && (end != NULL) );

    /* connect 'start->prev' node and 'end->next' node  */
    ((node_t*)start)->prev->next = ((node_t*)  end)->next;
    ((node_t*)  end)->next->prev = ((node_t*)start)->prev;

    /* connect 'before->next' node and 'end' node */
    ((node_t*)before)->next->prev = ((node_t*)end);
    ((node_t*)   end)->next       = ((node_t*)before)->next;

    /* connect 'before' node and 'start' node */
    ((node_t*)before)->next = ((node_t*)start);
    ((node_t*) start)->prev = ((node_t*)before);

}

/*****************************************************************************
** description:  check if both iterators point to the same element.
** arguments:    itr1   - iterator
**               itr2   - iterator
** return value: 1 - same
**               0 - else
** notes:        both iterators must point to elements in the same dlist
******************************************************************************/
int DlistSameIterator(const itr_t itr1, const itr_t itr2)
{
    return (itr1 == itr2);
}

/*****************************************************************************
** description:  get the data from the element that is pointed by itr
** arguments:    itr   - iterator
** return value: pointer to data
** notes:        if itr points to end, the return value is NULL
******************************************************************************/
void* DlistGetData(itr_t itr)
{
    assert( itr != NULL );

    return ((node_t*)itr)->data;
}
