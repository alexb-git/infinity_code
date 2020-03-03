/***************************************************
  Filename: recexer.h
  Purpose: Header file for recursive functions
  Version: 1
***************************************************/
#ifndef __RECSTR_H__
#define __RECSTR_H__

#include <stddef.h> /* size_t */

#include "stack.h"   /* Stack data structure */
#include "slist.h"   /* Singly Linked List */

/******************************************************************************
1. returns the value of n-th member in the fibonacci sequence - using recursion
2. returns the value of n-th member in the fibonacci sequence - using iteration
*******************************************************************************/
size_t FibonacciRec(size_t n);
size_t FibonacciItr(size_t n);

/******************************************************************************
Function that recieves pointer to string and retuns the length of the string
******************************************************************************/
size_t MyStrlen (const char *ptr);

/*********************************************************************************
<0 - *str1 >  *str2
>0 - *str1 <  *str2
=0 - *str1 == *str2 (strings are equal)
**********************************************************************************/
int MyStrcmp (const char* str1, const char* str2);

/*********************************************************************************
  Copies the string pointed by source into the array pointed by destination,
  including the terminating null character (and stopping at that point).

  To avoid overflows, the size of the array pointed by destination shall be long
  enough to contain the same C string as source (including the terminating null
  character), and should not overlap in memory with source.
**********************************************************************************/
char* MyStrcpy(char* dest, const char* src);

/******************************************************************************
  Appends a copy of the source string to the destination string.
  The terminating null character in destination is overwritten by the
  first character of source, and a null-character is included at the end of
  the new string formed by the concatenation of both in destination.

  destination and source shall not overlap.
******************************************************************************/
char* MyStrCat(char *dest, const char *src);

/******************************************************************************
 Returns a pointer to the first occurrence of str2 in str1, or a null pointer
 if str2 is not part of str1.The matching process does not include the
 terminating null-characters, but it stops there.
******************************************************************************/
char* MyStrStr(const char *haystack, const char *needle);

/*****************************************************************************
** description:   receives first node of linked list, and flips the nodes data
                  from the given node till the end of the list.
** arguments:     first node of linked list to start flipping the data from.
** return value:  pointer to the begining of the flipped list.
** notes:         recursive function
******************************************************************************/
node_t* SListFlipRecursively( node_t *node );

/****************************************************************************
** description:  sort the stack in decreasing order
** arguments:    stack - stack handler
** return value: void
** notes:        recursive function !
**               works only with int type
*****************************************************************************/
void StackSort(stack_t *stack);


#endif /* __RECSTR_H__ */
