/**********************************************
Filename: dlist.h
Purpose: Header file for doubly list DS
Data Structure: Doubly Linked List
Version: 7
***********************************************/
#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h> /* size_t */

typedef struct dlist dlist_t;
typedef void* itr_t;

/*****************************************************************************
**  description:  boolean function that is provided by the user.
**  arguments:    param   - for the use of bool function,
**                element - the elemnet to invoke the bool function on.
**  return value: true or false / or an integer number.
**  notes:
******************************************************************************/
typedef int (*bool_function)(void* element, void *param);

/*****************************************************************************
** description:  compare function provided by the user in order to compare
** arguments:    data_1 - compare between data_1 and data_2
**               data_2 - compare between data_1 and data_2
** return value: 0 - data is equal, negative integer if 2 is bigger than 1,
**               positive integer if 1 is bigger than 2.
** notes:
******************************************************************************/
typedef int (*cmp_function)(const void *data_1, const void *data_2);

/*****************************************************************************
** description:  create a new doubly linked list handler.
** arguments:    void.
** return value: pointer to doubly linked list handler.
** notes:        must call DListDestroy at end of use.
******************************************************************************/
dlist_t* DlistCreate(void);

/*****************************************************************************
** description:  free the dlist.
** arguments:    dlist - pointer to the list to be free.
** return value: void.
** notes:        must call at end of use.
******************************************************************************/
void DlistDestroy(dlist_t *dlist);

/*****************************************************************************
** description:  counts number of elements in dlist.
** arguments:    dlist - pointer to dlist handler.
** return value: number of elements in dlist.
** notes:
******************************************************************************/
size_t DlistCount(const dlist_t *dlist);

/*****************************************************************************
** description:  check if dlist is empty.
** arguments:    dlist - pointer to dlist handler.
** return value: 1 - empty, 0 - else.
** notes:
******************************************************************************/
int DlistIsEmpty(const dlist_t *dlist);

/*****************************************************************************
** description:  returns iterator that points to first element of dlist.
** arguments:    dlist - pointer to dlist handler.
** return value: iterator that points to beginning of dlist,
**               in case of empty retrun pointer to stub element
** notes:
******************************************************************************/
itr_t DlistBegin(const dlist_t *dlist);

/*****************************************************************************
** description:  returns iterator that points to end of dlist.
**               (end of dlist is the stub element after the last element)
** arguments:    dlist - pointer to dlist handler.
** return value: iterator that points to end of dlist
** notes:
******************************************************************************/
itr_t DlistEnd(const dlist_t *dlist);

/*****************************************************************************
** description:  promote the iterator to the next element.
** arguments:    itr - iterator.
** return value: iterator to the next element.
** notes:        if itr points to end, the return value is unpredicted
******************************************************************************/
itr_t DlistNext(const itr_t itr);

/*****************************************************************************
** description:   returns iterator of the previous element.
** arguments:     iterator.
** return value:  iterator to the previous element.
** notes:         if itr points to begin, the return value is unpredicted
******************************************************************************/
itr_t DlistPrev(const itr_t itr);

/*****************************************************************************
** description:  insert a new element before specified itr
** arguments:    dlist - pointer to dlist handler
**               itr   - iterator to the specified element in dlist
**               data  - pointer to data
** return value: iterator to the inserted element that contains the data
** notes:        if insertion failed - return null
******************************************************************************/
itr_t DlistInsert(dlist_t *dlist, itr_t itr, const void *data);

/*****************************************************************************
** description:  insert a new element after specified iterator
** arguments:    dlist - pointer to dlist handler
**               itr  - iterator to the location
**               data - pointer to the data to insert
** return value: if itr points to end, the return value is unpredicted
** notes:        if insertion failed - return null
******************************************************************************/
itr_t DlistInsertAfter(dlist_t *dlist, itr_t itr, const void *data);

/*****************************************************************************
** description:  erase element pointed by itr
** arguments:    dlist - pointer to dlist handler
**               itr   -  iterator to the element to erase
** return value: iterator to next element (after the removed element)
** notes:        if itr points to end or if list is empty
**               no action occurs, and the return value is
**               itr that points to end.
******************************************************************************/
itr_t DlistErase(dlist_t *dlist, itr_t itr);

/*****************************************************************************
** description:  push data to the start of the data structure
** arguments:    dlist - pointer to dlist handler
** return value: itertaor to the new element.
** notes:        if push failed - return null
******************************************************************************/
itr_t DlistPushFront(dlist_t *dlist, const void *data);

/*****************************************************************************
** description:  push data to the back of the data structure
** arguments:    dlist   - doubly list handler
**               data  - pointer  to the data to push
** return value: itertaor to the new element.
** notes:        if push failed - return null
******************************************************************************/
itr_t DlistPushBack(dlist_t *dlist, const void *data);

/*****************************************************************************
** description:  remove first element in doubly list
** arguments:    dlist    - doubly list handler
** return value: iterator to next element to the one that was popped.
** notes:        if list is empty return value is itr that points to end.
******************************************************************************/
itr_t DlistPopFront(dlist_t *dlist);

/*****************************************************************************
** description:  remove last element in doubly list
** arguments:    dlist    - doubly list handler
** return value: iterator to previous element to the one that was popped
** notes:        if list is empty return value is itr that points to end.
******************************************************************************/
itr_t DlistPopBack(dlist_t *dlist);

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
itr_t DlistForEach(itr_t start, itr_t end, bool_function b_func, void *param);

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
itr_t DlistFind(itr_t start, itr_t end, cmp_function c_func, const void *data);

/*****************************************************************************
** description:  insert the linked list 'start'
**               between 'before' and 'before->next'.
** arguments:    before - iterator to element to inset before.
**               start  - splice from this iterator.
**               end    - splice up to this iterator.
** return value: void
** notes:
******************************************************************************/
void DlistSpliceBefore(itr_t before, itr_t start, itr_t end);

/*****************************************************************************
** description:  check if both iterators point to the same element.
** arguments:    itr1   - iterator
**               itr2   - iterator
** return value: 1 - same
**               0 - else
** notes:        both iterators must point to elements in the same dlist
******************************************************************************/
int DlistSameIterator(const itr_t itr1, const itr_t itr2);

/*****************************************************************************
** description:  get the data from the element that is pointed by itr
** arguments:    itr   - iterator
** return value: pointer to data
** notes:        if itr points to end, the return value is NULL
******************************************************************************/
void* DlistGetData(itr_t itr);

#endif /* __DLIST_H__ */
