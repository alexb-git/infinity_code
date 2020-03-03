/****************************************
  Filename: stack.h
  Purpose: Header file for stack
  Data Structure
  Version: 4
 ****************************************/
#ifndef __STACK__H__
#define __STACK__H__

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/*****************************************************************************
** description: allocates memory for the whole stack
** arguments:  element_size - size of single element in the stack
**                            (must be greater than zero)
**            stack_capacity - max number of elements in stack
**                            (must be greater than zero)
** return value: pointer to the stack handler, or NULL in case of failure
** notes:  must call StackDestroy at end of use
******************************************************************************/
stack_t* StackCreate(size_t element_size, size_t stack_capacity);

/*****************************************************************************
** description: destroyes a given stack, created by StackCreate
** arguments: pointer to the stack handler
** return value: void
** notes: call at end of use
******************************************************************************/
void StackDestroy(stack_t *stack);

/*****************************************************************************
** description: Pushes an item onto the top of the stack.
** arguments: pointer to the stack handler
**            pointer to the data to be pushed onto the stack
** return value: 1 - success, 0 - error.
** notes: the data is copied to the stack
******************************************************************************/
int StackPush(stack_t *stack, void *data);

/*****************************************************************************
** description: Pop out the item from the top of the stack.
** arguments: pointer to the stack handler
** return value: void
** notes: if stack is empty no action occurs.
******************************************************************************/
void StackPop(stack_t *stack);

/*****************************************************************************
** description: Peek at the item from the top of the stack.
** arguments: pointer to the stack handler
** return value: pointer to the value or NULL in case of empty stack
** notes:
******************************************************************************/
void* StackPeek(const stack_t *stack);

/*****************************************************************************
** description:  Get the number of elements in stack
** arguments: pointer to the stack handler
** return value:  size_t number of elements in stack
** notes:
******************************************************************************/
size_t StackCount(const stack_t *stack);

#endif /* __STACK_H__ */
