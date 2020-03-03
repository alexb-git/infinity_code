/**********************************************
  Filename: bst.h
  Purpose: Header file for Binary Search Tree
  Version: 2
***********************************************/
#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct bst_handler bst_handler_t;
typedef void*  bst_itr_t;

/*****************************************************************************
** description:  compare function provided by the user in order to compare.
** arguments:    data_1, data_2 - compare between data_1 and data_2
                 param   - for the use of compatre function
** return value: =0  - data is equal,
**               >0  - if data_1 is bigger than data_2,
**               <0  - if data_1 is smaller than data_2.
** notes:
******************************************************************************/
typedef int (*cmp_func_t)( const void *data_1,
                           const void *data_2,
                           const void *param );

/*****************************************************************************
**  description:  boolean function that is provided by the user.
**  arguments:    param   - for the use of bool function,
**                element - the elemnet to invoke the bool function on.
**  return value: true or false / or an integer number.
**  notes:
******************************************************************************/
typedef int (*bool_function_t)(void* element, const void *param);

/*****************************************************************************
** description:  create a new Binary Search Tree handler.
** arguments:    func - defines the tree sorting order.
** return value: pointer to Binary Search Tree handler.
** notes:        must call BSTDestroy at end of use.
******************************************************************************/
bst_handler_t* BSTCreate(cmp_func_t func, void *func_param);

/*****************************************************************************
** description:  free the Binary Search Tree.
** arguments:    bst_handler - Binary Search Tree handler
** return value: void.
** notes:        must call at end of use.
******************************************************************************/
void BSTDestroy(bst_handler_t *bst_handler);

/*****************************************************************************
** description:  insert a new element to the Binary Search Tree
** arguments:    bst_handler - Binary Search Tree handler
**               element     - pointer to the element to insert
** return value: 1 - success,
**               0 - fail
******************************************************************************/
int BSTInsert(bst_handler_t *bst_handler, void* element);

/*****************************************************************************
** description:  get the data pointed by iterator
** arguments:    bst_handler - Binary Search Tree handler
**               itr         - iterator to the node containing the data.
** return value: pointer to the data.
** notes:
******************************************************************************/
void* BSTGetData(bst_itr_t itr);

/*****************************************************************************
** description:  check if Binary Search Tree is empty.
** arguments:    bst_handler - Binary Search Tree handler.
** return value: 1 - empty,
**               0 - else.
** notes:
******************************************************************************/
int BSTIsEmpty(const bst_handler_t *bst_handler);

/*****************************************************************************
** description:  counts number of elements (nodes) in Binary Search Tree.
** arguments:    bst_handler - Binary Search Tree handler.
** return value: number of elements in Binary Search Tree.
** notes:
******************************************************************************/
size_t BSTCount(const bst_handler_t *bst_handler);

/*****************************************************************************
** description:  returns iterator that points to the element
**               with the lowest key value
** arguments:    bst_handler - pointer to BST handler.
** return value: iterator that points to beginning of the BST
**               in case of empty - Undefined result.
** notes:
******************************************************************************/
bst_itr_t BSTBegin(const bst_handler_t *bst_handler);

/*****************************************************************************
** description:  returns iterator that points to the end of the BST.
** arguments:    bst_handler - pointer to BST handler.
** return value: iterator that points to end of BST
** notes:
******************************************************************************/
bst_itr_t BSTEnd(const bst_handler_t *bst_handler);

/*****************************************************************************
** description:  promote the iterator to the next element.
** arguments:    itr - binary search tree iterator.
** return value: iterator to the next element (according to compare function).
** notes:        if itr points to end, the return value is unpredicted
******************************************************************************/
bst_itr_t BSTNext(const bst_itr_t itr);

/*****************************************************************************
** description:   returns iterator of the previous element.
** arguments:     itr - binary search tree iterator.
** return value:  iterator to the previous element(according to compare function).
** notes:         if itr points to begin, the return value is unpredicted.
******************************************************************************/
bst_itr_t BSTPrev(const bst_itr_t itr);

/*****************************************************************************
** description:  removes the node pointed by itr
** arguments:    itr - binary search tree iterator.
** return value: iterator to the next element(according to compare function).
** notes:        if itr points to end, the return value is unpredicted
******************************************************************************/
bst_itr_t BSTRemove(const bst_itr_t itr);

/******************************************************************************
** description:  invoke `bool_function` on all data from 'start'
**               till 'end', return iterator to the first data
**               that failed the boolean function, or NULL if all succeeded
** arguments:    from - start iterator.
**               to   - end iterator.
**               b_func  - pointer to users' function.
**               param   - additional parameter for the function
** return value: pointer to the first node that failed the boolean
**               function, or itr to end  if all nodes succeeded.
******************************************************************************/
bst_itr_t BSTForEach(bst_itr_t from, bst_itr_t to,
                     bool_function_t b_func, void *param);

/*****************************************************************************
** description:  find the first occurrence of 'data' in binary search tree
**               pointed by bst_handler.
** arguments:    bst_handler - pointer to BST handler
**               data  - pointer to the data to search for.
** return value: returns iterator that points to the data,
**               or end  if data was not found.
** notes:
******************************************************************************/
bst_itr_t BSTFind(bst_handler_t *bst_handler, const void *data);

#endif /* __BST_H__ */
