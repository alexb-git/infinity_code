/**********************************************
  Filename: sortedlist.h
  Purpose: Header file for Sorted list
  Data Structure: Sorted Linked List
  Version: 4
***********************************************/
#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include <stddef.h> /* size_t */

typedef struct sorted_list sorted_list_t; /* sorted list handler */

/* do not use this struct, this is an internal design */
typedef struct iterator
{
    void          *itr;
    sorted_list_t *list;
    long           magic_number;
} sorted_list_itr_t;


/*****************************************************************************
**  description:  boolean function that is provided by the user.
**  arguments:    param   - for the use of bool function,
**                element - the elemnet to invoke the bool function on.
**  return value: true or false / or an integer number.
**  notes:
******************************************************************************/
typedef int (*bool_function2)(void *element, void *param);

/*****************************************************************************
** description:  compare function provided by the user in order to compare
** arguments:    data_1 - compare between data_1 and data_2
**               data_2 - compare between data_1 and data_2
** return value: 0 - data is equal, negative integer if 2 is bigger than 1,
**               positive integer if 1 is bigger than 2.
** notes:
******************************************************************************/
typedef int (*cmp_function2)(const void *data_1, const void *data_2);

/*****************************************************************************
** description:  create a new sorted list handler.
** arguments:    c_func - compare function, define the sorting order.
** return value: pointer to sorted_list handler.
** notes:        must call SortedListDestroy at end of use.
******************************************************************************/
sorted_list_t* SortedListCreate(const cmp_function2 c_func);

/*****************************************************************************
** description:  destroy sorted list.
** arguments:    sorted_list - pointer to the list to destroy.
** return value: void.
** notes:        must be called at the end of use.
******************************************************************************/
void SortedListDestroy(sorted_list_t *sorted_list);

/*****************************************************************************
** description:  counts number of elements in sorted list.
** arguments:    sorted_list - pointer to sorted list handler.
** return value: number of elements in sorted list.
** notes:
******************************************************************************/
size_t SortedListSize(const sorted_list_t *sorted_list);

/*****************************************************************************
** description:  check if sorted list is empty.
** arguments:    sorted_list - pointer to the sorted list handler.
** return value: 1 - empty, 0 - else.
** notes:
******************************************************************************/
int SortedListIsEmpty(const sorted_list_t *sorted_list);

/*****************************************************************************
** description:  returns iterator that points to first element of sorted list.
** arguments:    sorted_list - pointer to sorted list handler.
** return value: iterator that points to beginning of the sorted list,
**               in case of empty list return pointer to end of sorted list.
**               (end of sorted list is the stub element after the last element).
** notes:
******************************************************************************/
sorted_list_itr_t SortedListBegin(const sorted_list_t *sorted_list);

/*****************************************************************************
** description:  returns iterator that points to end of sorted list.
**               (end of sorted list is the stub element after the last element).
** arguments:    sorted_list - pointer to sorted list handler.
** return value: iterator that points to end of the sorted list.
** notes:
******************************************************************************/
sorted_list_itr_t SortedListEnd(const sorted_list_t *sorted_list);

/*****************************************************************************
** description:  promote the iterator to the next element.
** arguments:    itr - iterator.
** return value: iterator to the next element.
** notes:        if itr points to end, the return value is unpredicted
******************************************************************************/
sorted_list_itr_t SortedListNext(const sorted_list_itr_t itr);

/*****************************************************************************
** description:   returns iterator of the previous element.
** arguments:     itr - iterator.
** return value:  iterator to the previous element.
** notes:         if itr points to begin, the return value is unpredicted
******************************************************************************/
sorted_list_itr_t SortedListPrev(const sorted_list_itr_t itr);

/*****************************************************************************
** description:  remove first element in sorted list.
** arguments:    sorted_list - sorted list handler.
** return value: iterator to next element of the one that was popped.
** notes:        if list is empty return value is itr that points to end.
******************************************************************************/
sorted_list_itr_t SortedListPopFront(sorted_list_t *sorted_list);

/*****************************************************************************
** description:  remove last element in sorted list.
** arguments:    sorted_list - sorted list handler.
** return value: iterator to previous element to the one that was popped.
** notes:        if list is empty return value is itr that points to end.
******************************************************************************/
sorted_list_itr_t SortedListPopBack(sorted_list_t *sorted_list);

/*****************************************************************************
** description:  insert a new element according to the list order
**               (defined by the compare function (cmp_function)).
** arguments:    sorted_list - pointer to sorted_list handler.
**               data  - pointer to data.
** return value: iterator to the inserted element that contains the data.
** notes:        if insertion failed - return null.
******************************************************************************/
sorted_list_itr_t SortedListInsert(sorted_list_t *sorted_list,
                                   const void *data);

/*****************************************************************************
** description:  erase element pointed by itr.
** arguments:    sorted_list - pointer to sorted list handler.
**               itr -  iterator to the element to erase.
** return value: iterator to next element (after the removed element).
** notes:        if itr points to end or if list is empty
**               no action occurs, and the return value is
**               itr that points to end.
******************************************************************************/
sorted_list_itr_t SortedListErase(sorted_list_t *sorted_list,
                                  sorted_list_itr_t itr);

/******************************************************************************
** description:  the function search for an element with the given data.
** arguments:    data - pointer to the data we seek.
**               sorted_list - pointer to sorted list handler.
** return value: returns iterator that points to the first instance of data,
**               or NULL if data was not found.
******************************************************************************/
sorted_list_itr_t SortedListFind(sorted_list_t *sorted_list, const void *data);

/*****************************************************************************
** description:  invoke `bool_function` on all data from 'start'
**               till 'end', return iterator to the first data
**               that failed the boolean function, or NULL if all succeeded.
** arguments:    start - iterator, from where to invoke the function (inclusive).
**               end   - iterator, till where to invoke the function (exclusive).
**               b_func - pointer to users' function.
**               param  - additional parameter for the function.
** return value: pointer to the first node that failed the boolean
**               function, or NULL if all nodes succeeded.
******************************************************************************/
sorted_list_itr_t SortedListForEach(const sorted_list_itr_t start,
                                    const sorted_list_itr_t end,
                                    bool_function2 b_func,
                                    const void *param);

/*****************************************************************************
** description:  merge two sorted lists.
** arguments:    sorted_list_1 - pointer to first sorted list's handler.
**               sorted_list_2 - pointer to second sorted list's handler.
** notes :       sorted_list_2 will be emptied.
** return value: void
******************************************************************************/
void SortedListMerge(sorted_list_t *sorted_list_1,
                     sorted_list_t *sorted_list_2);

/*****************************************************************************
** description:  get the data from the element that is pointed to by the itr.
** arguments:    itr - iterator.
** return value: pointer to data.
** notes:        if itr points to end, the return value is NULL.
******************************************************************************/
void* SortedListGetData(const sorted_list_itr_t itr);

/*****************************************************************************
** description:  check if both iterators point to the same element.
** arguments:    itr1 - iterator, itr2 - iterator.
** return value: 1 - same, 0 - else.
** notes:        when NULL is inserted instead of iterators,
**               you will get unexpected behavior.
******************************************************************************/
int SortedListSameIterator(const sorted_list_itr_t itr1,
                           const sorted_list_itr_t itr2);

#endif /* __SORTED_LIST_H__ */
