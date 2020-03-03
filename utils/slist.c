/* Author: Alex B
** Last update: 24.09.17 09:30
** Program: Singly Linked List
*/

#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */
#include <stdio.h> 	/* printf */
#include <string.h>	/* memcpy */
#include <errno.h>	/* errno */
#include <stddef.h> /* size_t */

#include "slist.h"


/*****************************************************************************
** description:  create a new node.
** arguments:    data - pointer to data 
**               next - pointer to new_node next  pointer
** return value: pointer to new node.
******************************************************************************/      
node_t* SListCreateNode(node_t *next, const void *data )
{
	node_t *node_ptr = NULL;

	node_ptr = (node_t*)malloc( sizeof(node_t) );
	if ( NULL == node_ptr)
	{
		return NULL;
	}

	node_ptr->data = (void*)data;
 	node_ptr->next = next;

	return node_ptr;
}


/*****************************************************************************
** description:  free nodes from current node till the end of list.
** arguments:    pointer to the first node to be freed.
** return value: void.
** notes: 
******************************************************************************/
void SListFreeAll(node_t *node)
{

	while( node != NULL )
	{
		node_t *next_node = node->next;

		free(node);

		node = next_node;
	}

}



/*****************************************************************************
** description:  Insert a new node before a specified node.           
** arguments:    node  - pointer to specified node.
**               data  - pointer to data to be inserted before node.
** return value: a pointer to new node that contains the data
** notes:        
******************************************************************************/
node_t* SListInsert( node_t *node, const void *data )
{
	node_t *new_node = NULL;

	new_node = (node_t*)malloc( sizeof(node_t) );
	if ( NULL == new_node )
	{
		return NULL; /* case: malloc failed, return NULL */
	}

	/* the new node will contain the information of current node */
	new_node->next = node;
	new_node->data = (void*)data;

	return new_node;
}


/*****************************************************************************
** description:   Insert a new node after a specified node.
** arguments:     node - pointer to specified node.
**                data - pointer to the data to be entered after the given node.
** return value:  a pointer to the node that contains the data
** notes: 
******************************************************************************/
node_t* SListInsertAfter( node_t *node, const void *data )
{
	node_t *new_node = NULL;

	new_node = (node_t*)malloc( sizeof(node_t) );
	if ( NULL == new_node )
	{
		return NULL; /* case: malloc failed, return NULL */
	}

	/* new node points to the node that the previous node pointed to */
	new_node->next = node->next;
	new_node->data = (void*)data;

	/* current node points to new node */
	node->next = new_node;

	return new_node;
}


/*****************************************************************************
** description:  remove the specified node.
** arguments:    node - pointer to the node to be removed.
** return value: next node (after the node that was removed)
** notes: last node can not be removed
******************************************************************************/
node_t* SListRemove( node_t *node )
{	
	assert( node != NULL );

	if ( NULL != node->next )
	{
		/* temp points to node which the 'node to be removed' point to */
		node_t *temp = node->next;

		node->data = (node->next)->data;
		node->next = (node->next)->next;

		free(temp);
		temp = NULL;
	}
	else
	{
		node = NULL;
	}

	return node;
}


/*****************************************************************************
** description:  remove the node next to the specified node.
** arguments:    node - pointer to specified node.
** return value: current node
** notes: when node points to NULL nothing happens
******************************************************************************/
node_t* SListRemoveAfter( node_t *node )
{
	assert( node != NULL );

	if ( NULL != node->next )
	{
		/* temp points to node which the 'node to be removed' point to */
		node_t *temp = node->next;

		node->next = (node->next)->next;

		free(temp);
		temp = NULL;
	}

	return node;
}


/*****************************************************************************
** description:  count number of nodes starting from specified
**               node (including) till the end of list.
** arguments:    node - pointer to specified node to start counting from (incl.)
** return value: number of nodes
** notes:
******************************************************************************/
size_t SListCountNodes( const node_t *node )
{
	size_t counter = 0;

	while( node != NULL )
	{
		++counter;
		node = node->next;
	}

	return counter;
}


/*****************************************************************************
** description:  finds the node (first occurrence) 
**               that contains the specified data.
** arguments:    node - pointer to specified node,
**               comparing function - between 2 elements,
**               data - pointer to the data
** return value: the node that holds the data, or NULL if data is not found.
** notes: 
******************************************************************************/
node_t* SListFind( node_t *node, cmp_function input_func, const void *data)
{
	int func_result = input_func(node->data, (void*)data);

	assert( node != NULL );

	/* '0' - data equal, 'other' - data doesnt equal */
	while ( (func_result != 0) && (node->next != NULL) )
	{
		node = node->next;
		func_result = input_func(node->data, (void*)data);
	}

	return ( 0 == func_result )?(node):(NULL);
}


/*****************************************************************************
** description:  receives first node of linked list, and flips the nodes data
                 from the given node till the end of the list.
** arguments:    first node of linked list to start flipping the data from.
** return value: pointer to the begining of the flipped list.
** notes: 
******************************************************************************/
node_t* SListFlip( node_t *node )
{
	node_t *previous  = NULL;
	node_t *next_node = NULL;

	assert( node != NULL );

	while ( node != NULL )
	{
		/* store the address of next node */
		next_node = node->next;

		/*current node->next will point to previous node (of null at first)*/
		node->next = previous;

		/* previous will hold the current node  */
		previous = node;

		/* node will now point to the next node */
		node = next_node;

	}

	return previous;
}


/*****************************************************************************
** description:  find the node where the loop begins.
** arguments:    pointer to first node of linked list.
** return value: there is a loop - 1
**               else            - 0
** notes: 
******************************************************************************/
int SListHasLoop( const node_t *node )
{
	int result = 0; /* 1 - there is a loop, 0 - no loop*/

	const node_t *one_step = node;
	const node_t *two_step = node;

	assert( node != NULL );

	/* check if the next step is legal */
	while ( two_step && two_step->next ) 
	{
		one_step = one_step->next;
		two_step = two_step->next->next;

		if ( one_step == two_step )
		{
			/* if pointers meet then its a loop */
			result = 1;
			break;
		}
	}
	

	return result;
}


/*****************************************************************************
** description:  receives two lists and returns the first node that 
**               is mutual to both lists if there is one, or NULL if
**               there is no such node.
** arguments:    two pointers to different nodes 
** return value: a pointer to the node that points to the intersection
**               from the linked list that starts with node_1
******************************************************************************/
node_t* SListFindIntersection( const node_t *node_1, const node_t *node_2 )
{
	size_t length_1   = 0;
	size_t length_2   = 0;
	size_t difference = 0;
	const node_t *node2promote = NULL;
	const node_t *shorter_list = NULL;
	const node_t *result  	 = NULL;

	assert( (node_1 != NULL) && (node_2 != NULL) );

	length_1   = SListCountNodes(node_1);
	length_2   = SListCountNodes(node_2);

	/* figure out which list is shorter  */
	if ( length_1 < length_2 )
	{
		difference   = length_2 - length_1;
		node2promote = node_2; /* the longer liset will be promoted */
		shorter_list = node_1;
	}
	else /* length_2 <= length_1 */
	{
		difference   = length_1 - length_2;
		node2promote = node_1; /* the longer liset will be promoted */
		shorter_list = node_2;
	}


	/* align the two lists  same number of nodes till the end) */
	while ( difference )
	{
		node2promote = node2promote->next;
		--difference;
	}

	/* check if the two nodes share the same address at some point */
	while ( node2promote->next != NULL )
	{
		if ( shorter_list == node2promote )
		{
			result = shorter_list;
			break;
		}
		node2promote = node2promote->next;
		shorter_list = shorter_list->next;
	}

	return (node_t*)result;
}


/*****************************************************************************
** description:  invoke `bool_function` on all the nodes from
**               the node till end of list.
** arguments:    function_ptr - pointer to boolean function .
**               node - from where to start the iteration.
**               param - additional parameter for the function
** return value: pointer to the first node that failed the boolean
**               function, or NULL if all nodes succeeded.
******************************************************************************/
node_t* SListForEach(node_t *node, bool_function input_func, void *param)
{
	/* typedef int (*bool_function)(node_t* node, void *param); */

	int func_result = input_func(node, param);

	while ( func_result && node->next != NULL )
	{
		node = node->next;
		func_result = input_func(node, param);
	}

	return (0 == func_result)?(node):(NULL);
}