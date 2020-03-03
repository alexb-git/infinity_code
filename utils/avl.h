/**********************************************
  Filename: avl.h
  Purpose: Header file for AVL tree
  Version: 1
***********************************************/
#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

typedef struct avl_handler avl_handler_t;
typedef struct avl_node    avl_node_t;

/*****************************************************************************
** description:  compare function provided by the user in order to compare.
 ** arguments:    data_1, data_2 - compare between data_1 and data_2
** return value: =0  - data is equal,
**               >0  - if data_1 is bigger than data_2,
**               <0  - if data_1 is smaller than data_2.
** notes:
******************************************************************************/
typedef int (*cmp_func_t)( const void *data_1,
                           const void *data_2);

/*****************************************************************************
**  description:  boolean function that is provided by the user.
**  arguments:    param   - for the use of bool function,
**                element - the elemnet to invoke the bool function on.
**  return value: true or false / or an integer number.
**  notes:
******************************************************************************/
typedef int (*bool_function_t)(void* element, const void *param);

/*****************************************************************************
** description:  create a new AVL Tree handler.
** arguments:    func - defines the tree sorting order.
** return value: pointer to AVL Tree handler.
** notes:        must call AVLDestroy at end of use.
******************************************************************************/
avl_handler_t* AVLCreate(cmp_func_t func);

/*****************************************************************************
** description:  free the AVL Tree.
** arguments:    avl_handler - AVL Tree handler
** return value: void.
** notes:        must call at end of use.
**               recursive function, post order
******************************************************************************/
void AVLDestroy(avl_handler_t *avl_handler);

/*****************************************************************************
** description:  Insert a new element to the AVL Tree
** arguments:    avl_handler - AVL Tree handler
**               element     - pointer to the element to insert
** return value: 1 - success,
**               0 - fail
** notes:        recursive function
******************************************************************************/
int AVLInsert(avl_handler_t *avl_handler, void* element);

/*****************************************************************************
** description:  check if AVL Tree is empty.
** arguments:    avl_handler - AVL Tree handler.
** return value: 1 - empty,
**               0 - else.
** notes:
******************************************************************************/
int AVLIsEmpty(const avl_handler_t *avl_handler);

/*****************************************************************************
** description:  counts number of elements (nodes) in The AVL Tree.
** arguments:    avl_handler - AVL Tree handler.
** return value: number of elements in AVL Tree.
** notes:        recursive function
******************************************************************************/
size_t AVLSize(const avl_handler_t *avl_handler);

/*****************************************************************************
** description:  returns the height of the AVL tree.
** arguments:    avl_handler - AVL Tree handler.
** return value: height of the AVL Tree.
** notes:        recursive function
******************************************************************************/
size_t AVLHeight(const avl_handler_t *avl_handler);

/*****************************************************************************
** description:  removes an element from an AVL Tree
** arguments:    avl_handler - pointer to a AVL Tree handler
                 element     - the element to be removed
** return value: void
** notes:        recursive function
******************************************************************************/
void AVLRemove(avl_handler_t *avl_handler, void *element);

/******************************************************************************
** description:  iterate over all nodes in tree untill bool function fails
** arguments:    b_func - user define function.
**               param  - additional parameter for the function
** return value: the first key that failed the bool function,
**               or null if all elements succeed
** notes:        recursive function, in order.
******************************************************************************/
void* AVLForEach( avl_handler_t *avl_handler,
                  bool_function_t b_func    ,
                  void *param               );

/*****************************************************************************
** description:  find the first occurrence of 'key' in AVL tree
** arguments:    avl_handler - AVL tree handler
**               key  - pointer to the data to search for.
** return value: returns the element that corresponds to the key.
** notes:        recursive function, in order.
******************************************************************************/
void* AVLFind(avl_handler_t *avl_handler, const void *key);

#endif /* __AVL_H__ */
