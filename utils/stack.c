/* Author: Alex B
** Last update: 13.09.17 20:00
** Program: Stack data structure
*/

#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */
#include <string.h>	/* memcpy */

#include "stack.h"

struct stack
{
	void *start;
	void *end;
	void *current;
	size_t element_size;

};



/*****************************************************************************
** description: allocates memory for the whole stack
** arguments:  element_size - size of single element in the stack
**                            (must be greater than zero)
**            stack_capacity - max number of elements in stack
**                            (must be greater than zero)
** return value: pointer to the stack handler, or NULL in case of failure
** notes:  must call StackDestroy at end of use
******************************************************************************/
stack_t* StackCreate(size_t element_size, size_t stack_capacity)
{
	size_t stack_size_in_bytes = element_size * stack_capacity;

	stack_t *pstack =
			(stack_t*)malloc(sizeof(stack_t) + stack_size_in_bytes);

	if ( NULL == pstack )
	{
		/* memory allocation was not successful */
		return pstack;
	}

	/* init struct */
	pstack->start   	   = (stack_t*)pstack + 1;
	pstack->current 	   = pstack->start;
	pstack->end     	   = (char*)(pstack->start)
						   + stack_size_in_bytes;
	pstack->element_size   = element_size;

	return pstack;
}

/*****************************************************************************
** description: destroyes a given stack, created by StackCreate
** arguments: pointer to the stack handler
** return value: void
** notes: call at end of use
******************************************************************************/
void StackDestroy(stack_t *stack)
{
	assert(stack != NULL);

	/* free the allocated stack */
	free(stack);
	stack = NULL;
}

/*****************************************************************************
** description: Pushes an item onto the top of the stack.
** arguments: pointer to the stack handler
**            pointer to the data to be pushed onto the stack
** return value: 1 - success, 0 - error.
** notes: the data is copied to the stack
******************************************************************************/
int StackPush(stack_t *stack, void *data)
{
	assert(stack != NULL && data != NULL);

	/* case: end of stack */
	if ( (stack->current) == (stack->end) )
	{
		return 0;
	}

	memcpy ( stack->current, data, (stack->element_size) );

	stack->current = (char*)(stack->current)
				   + (stack->element_size);

	return 1;
}

/*****************************************************************************
** description: Pop out the item from the top of the stack.
** arguments: pointer to the stack handler
** return value: void
** notes: if stack is empty no action occurs.
******************************************************************************/
void StackPop(stack_t *stack)
{
	assert(stack != NULL);

	/* case: empty stack */
	if ( stack->current != stack->start )
	{
		(stack->current) = (char*)(stack->current)
						 - (stack->element_size);
	}
}

/*****************************************************************************
** description: Peek at the item from the top of the stack.
** arguments: pointer to the stack handler
** return value: pointer to the value or NULL in case of empty stack
** notes:
******************************************************************************/
void *StackPeek(const stack_t *stack)
{
	assert(stack != NULL);

	/* case: empty stack */
	if ( (stack->current) == (stack->start) )
	{
		return NULL;
	}

	return (char*)(stack->current) - (stack->element_size);
}

/*****************************************************************************
** description:  Get the number of elements in stack
** arguments: pointer to the stack handler
** return value:  size_t number of elements in stack
** notes:
******************************************************************************/
size_t StackCount(const stack_t *stack)
{
	assert(stack != NULL);

	return ( ((char*)(stack-> current) -
			  (char*)(stack-> start))  /
			  (stack->element_size)    );
}
