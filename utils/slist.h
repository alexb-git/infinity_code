/***********************************************
  Filename: slist.h                          
  Purpose: Header file for Singly Linked List  
  Data Structure: Singly Linked List           
  Version: 9
 ***********************************************/
#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h> /* size_t */

typedef struct node
{
    void        *data;
    struct node *next;
} node_t;

/*  boolean function that is provided by the user.
    receives a `node` and paramaters(`param`), then execute a statments
    and return true or false / or an integer number. */
typedef int (*bool_function)(node_t* node, void *param);

/* description: compare function provided by the user in order to compare  
                the data in the linked list with the data from the user.
   return value: 0 - data is equal,  negative integer if 2 is bigger than 1,
                 positive integer if 1 is bigger than 2  */
typedef int (*cmp_function)(const void *data_1, const void *data_2); 

/*****************************************************************************
** description:  create a new node.
** arguments:    data - pointer to data 
**               next - pointer to new_node next  pointer
** return value: pointer to new node.
******************************************************************************/      
node_t* SListCreateNode(node_t *next, const void *data );

/*****************************************************************************
** description:  free nodes from current node till the end of list.
** arguments:    pointer to the first node to be freed.
** return value: void.
** notes: will fail (core dump) if list is loopy
******************************************************************************/
void SListFreeAll(node_t *node);

/*****************************************************************************
** description:  Insert a new node before a specified node.           
** arguments:    node  - pointer to specified node.
**               data  - pointer to data to be inserted before node.
** return value: a pointer to node that contains the data
** notes:        
******************************************************************************/
node_t* SListInsert(node_t *node, const void *data );

/*****************************************************************************
** description:   Insert a new node after a specified node.
** arguments:     node - pointer to specified node.
**                data - pointer to the data to be entered after the given node.
** return value:  a pointer to the new node that contains the data
** notes: 
******************************************************************************/
node_t* SListInsertAfter(node_t *node, const void *data );

/*****************************************************************************
** description:  remove the specified node.
** arguments:    node - pointer to the node to be removed.
** return value: next node (after the first node was removed)
** notes: last node can not be removed
******************************************************************************/
node_t* SListRemove(node_t *node );

/*****************************************************************************
** description:  remove the node next to the specified node.
** arguments:    node - pointer to specified node.
** return value: current node
** notes: when node points to NULL nothing happens
******************************************************************************/
node_t* SListRemoveAfter(node_t *node );

/*****************************************************************************
** description:  count number of nodes starting from specified
**               node (including) till the end of list.
** arguments:    node - pointer to specified node to start counting from (incl.)
** return value: number of nodes
** notes: before using this function check that the list is not loopy,
**        otherwise the program will fail (endless loop)
******************************************************************************/
size_t SListCountNodes(const node_t *node );

/*****************************************************************************
** description:  finds the node (first occurrence) 
**               that contains the specified data.
** arguments:    node - pointer to specified node,
**               comparing function - between 2 elements,
**               data - pointer to the data
** return value: the node that holds the data, or NULL if data is not found.
**               (!) will fail (endless loop) if list is loopy 
**                   and the data is not found
******************************************************************************/
node_t* SListFind(node_t *node, cmp_function, const void *data);

/*****************************************************************************
** description:  receives first node of linked list, and flips the nodes data
                 from the given node till the end of the list.
** arguments:    first node of linked list to start flipping the data from.
** return value: pointer to the begining of the flipped list.
** notes:        (!) will fail (endless loop) if list is loopy 
******************************************************************************/
node_t* SListFlip(node_t *node );

/*****************************************************************************
** description:  check if there is a loop in the singly linked list
** arguments:    pointer to first node of linked list.
** return value: there is a loop - 1
**               else            - 0
** notes: 
******************************************************************************/
int SListHasLoop(const node_t *node );

/*****************************************************************************
** description:  receives two lists and returns the first node that 
**               is mutual to both lists if there is one, or NULL if
**               there is no such node.
** arguments:    two pointers to different nodes 
** return value: a pointer to the node that points to the intersection
**               from the linked list that starts with node_1
**               (!) will fail (endless loop) if one of the lists is loopy
******************************************************************************/
node_t* SListFindIntersection(const node_t *node_1, const node_t *node_2 );

/*****************************************************************************
** description:  invoke `bool_function` on all the nodes from
**               the node till end of list.
** arguments:    function_ptr - pointer to boolean function .
**               node - from where to start the iteration.
**               param - additional parameter for the function
** return value: pointer to the first node that failed the boolean
**               function, or NULL if all nodes succeeded.
**               (!) will fail (endless loop) if list is loopy 
**                   and all nodes succeed
******************************************************************************/
node_t* SListForEach(node_t *node, bool_function, void *param);

#endif /* __SLIST_H__ */
