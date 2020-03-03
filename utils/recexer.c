/****************************************************************************
** Filename:    - recexer.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - recursive functions implementations
** Date:        - 15/11/2017
** Version:     - 3
*****************************************************************************/
#include <assert.h> /* assert */
#include <string.h> /* strlen, strcmp, strncmp */

#include "recexer.h" /* Header file for recursive functions */

/****************************************************************************
returns the value of n-th member in the fibonacci sequence - using recursion
*****************************************************************************/
size_t FibonacciRec(size_t n)
{
    /* assumption: series begins with 0,1,... */
    if (n <= 2)
    {
        return n;
    }

    return (FibonacciRec (n - 1) + FibonacciRec (n - 2));
}

/****************************************************************************
returns the value of n-th member in the fibonacci sequence - using iteration
*****************************************************************************/
size_t FibonacciItr(size_t n)
{
    /* assumption: series begins with 0,1,... */
    size_t curr = 1;
    size_t next = 2;

    if ( n < 2 )
    {
        return n;
    }

    for ( ; n > 2 ; --n )
    {
        next = next + curr;
        curr = next - curr;
    }

    return next;
}

/******************************************************************************
Function that recieves pointer to string and retuns the length of the string
******************************************************************************/
size_t MyStrlen (const char *ptr)
{
    assert( ptr != NULL );

    if ( *ptr == '\0' )
    {
        return 0;
    }

    return 1 + MyStrlen(++ptr);
}

/*********************************************************************************
	<0 - *str1 >  *str2
    >0 - *str1 <  *str2
    =0 - *str1 == *str2 (strings are equal)
**********************************************************************************/
int MyStrcmp (const char* str1, const char* str2)
{
    assert( (str1 != NULL) && (str2 != NULL) );

    if ( (*str1 != *str2) || *str1 == '\0' )
    {
        return	*(str1) - *(str2);
    }

    return MyStrcmp (++str1, ++str2);
}

/*********************************************************************************
Copies the string pointed by source into the array pointed by destination,
including the terminating null character (and stopping at that point).
**********************************************************************************/
char* MyStrcpy(char* dest, const char* src)
{
    assert( (dest != NULL) && (src != NULL) );

    *dest = *src;

    if ( *src != '\0' )
    {
        MyStrcpy(dest + 1, ++src);
    }

	return dest;
}

/*********************************************************************************
appends the string pointed to by src to the end of the string pointed to by dest
**********************************************************************************/
char* MyStrCat(char *dest, const char *src)
{
    assert( (dest != NULL) && (src != NULL) );

    if ( *dest != '\0' )
    {
        /* find end of 'dest' string */
        MyStrCat(++dest, src);
    }
    else /* *dest == '\0' */
    {
        if ( *src != '\0' )
        {
            /* copy 'src' to 'dest' char by char */
            *dest = *src;
            *(++dest) = '\0';

            MyStrCat(dest, ++src);
        }
    }

	return --dest;
}

/*********************************************************************************
This function finds the first occurrence of the substring needle in the string
haystack. The terminating '\0' characters are not compared.
**********************************************************************************/
char* MyStrStr(const char *haystack, const char *needle)
{
    assert( (haystack != NULL) && (needle != NULL) );

    if ( *haystack == '\0' )
    {
        /* case: needle not fount in haystack */
        return NULL;
    }

    if ( *needle == '\0' )
    {
        /* case: found the needle */
        return (char*)haystack;
    }

    if (    *haystack == *needle
         &&  MyStrStr(haystack + 1, ++needle) == haystack + 1 )
    {
        /* case: needle fount in haystack. return where it begins */
        return (char*)haystack;
    }
    else
    {
        /* next iteration */
        return MyStrStr(haystack + 1, needle);
    }
}

/*****************************************************************************
** description:   receives first node of linked list, and flips the nodes data
                  from the given node till the end of the list.
** arguments:     first node of linked list to start flipping the data from.
** return value:  pointer to the begining of the flipped list.
** notes:         recursive function
******************************************************************************/
node_t* SListFlipRecursively( node_t *node )
{
    /* exit point: (1) empty tree (vacuous truth)
                OR (2) list with a single node */
    if (node == NULL || node->next == NULL)
    {
        return node;
    }
    else /* list with more than one node */
    {
        /* get to the end of the list, find the head */
        node_t *new_head = SListFlipRecursively(node->next);

        /* step: connect "next node" (node->next) to 'current node' (node) */
        node->next->next = node;
        node->next = NULL;

        return new_head;
    }
}

/****************************************************************************
** description:  inserts new data element in order to ordered stack
** arguments:    stack - stack handler
**               data  - data to insert
** return value: void
** notes:        recursive function !
**               works only with int type
*****************************************************************************/
static void StackInsert(stack_t *stack, int insert)
{
    assert( stack != NULL );

    /* push data to insert if (1) stack is empty
                           OR (2) found the rightful place for the given data */
    if ( StackPeek(stack) == NULL || insert > *(int*)StackPeek(stack) )
    {
        StackPush(stack, &insert);
    }
    else /* case: place to insert data not found - pop out one more element */
    {
        int poped_data = *(int*)StackPeek(stack);
        StackPop(stack);

        /* find where to insert the data and insert it, recursive call */
        StackInsert(stack, insert);

        /* push the 'poped_data' back to the stack */
        StackPush(stack, &poped_data);
    }
}

/****************************************************************************
** description:  sort the stack in decreasing order
** arguments:    stack - stack handler
** return value: void
** notes:        recursive function !
**               works only with int type
*****************************************************************************/
void StackSort(stack_t *stack)
{
    assert( stack != NULL );

    /* if stack is not empty keep popping out elements, till empty */
    if ( StackPeek(stack) != NULL )
    {
        /* step: pop out one elements */
        int poped_data = *(int*)StackPeek(stack);
        StackPop(stack);
        StackSort(stack); /* recursive call */

        /* push the 'poped_data' back to the stack. the inserion is in order */
        StackInsert(stack, poped_data);
    }
}
