/****************************************************************************
** Filename:    - search.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementations of search algorithms
** Date:        - 29/11/2017
** Version:     - 7
*****************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memmove */
#include <assert.h> /* assert */
#include <math.h>   /* sqrt, ceil */

#include "search.h" /* Sorting Algorithms */

/****************************************************************************
    Macros for this program
*****************************************************************************/
#define GetElem(X,I)((char*)X + (I) * size)
#define Min(A,B)    ((A < B)?(A):(B))

/*****************************************************************************
** description: implementation of Itertative  Binary search
** arguments:   base    - pointer to the start of the array.
**              nmemb   - number of elements in the array.
**              size    - size of each element.
**              cmp_func- user defined compare func.
**              req_data - the element to search for
** return value:  req_data if found, NULL otherwise,
** notes:         - o(lgn)
******************************************************************************/
void* IterBinarySearch( void* base, size_t nmemb, size_t size,
                        cmp_func_t cmp_func, void* to_find  )
{
    size_t left = 0;
    size_t right = nmemb - 1;

    assert( (base != NULL) && (cmp_func != NULL) );

    while ( left <= right )
    {
        size_t middle = left + (right - left)/2;
        int    function_result;

        function_result = cmp_func( GetElem(base, middle), to_find);

        if ( function_result == 0 ) /* base[middle] == to_find */
        {
            /* case: elements are equal */
            return GetElem(base, middle);
        }

        if ( function_result < 0 )
        {
            left = middle + 1;
        }
        else/* to_find < start[middle] */
        {
            right = middle - 1;
        }
    }

    return NULL;
}

/****************************************************************************/
static void* RecBinSearchStep(void* base, size_t left, size_t right,
                              size_t size, cmp_func_t cmp_func, void* to_find)
{
    size_t middle = left + (right - left)/2;
    int    function_result;

    assert( (base != NULL) && (cmp_func != NULL) );

    /* base case 1: element was not found */
    if ( left > right )
    {
        return NULL;
    }

    function_result = cmp_func( GetElem(base, middle), to_find );

    /* base case 2: element found */
    if ( function_result == 0 )
    {
        return GetElem(base, middle);
    }

    /* recursive jmp */
    if ( function_result < 0 )
    {
        return RecBinSearchStep(base                   , /* array */
                                middle + 1             , /* left */
                                right                  , /* right */
                                size, cmp_func, to_find);
    }
    else/* to_find < start[middle] */
    {
        return RecBinSearchStep(base                   , /* array */
                                left                   , /* left */
                                middle - 1             , /* right */
                                size, cmp_func, to_find);
    }
}

/*****************************************************************************
** description: implementation of Recursive  Binary search
** arguments:   base    - pointer to the start of the array.
**              nmemb   - number of elements in the array.
**              size    - size of each element.
**              cmp_func- user defined compare func.
**              req_data - the element to search for
** return value:  req_data if found, NULL otherwise,
** notes:         - o(lgn)
******************************************************************************/
void* RecBinarySearch( void* base, size_t nmemb, size_t size,
                       cmp_func_t cmp_func, void* to_find   )
{
    return RecBinSearchStep(base                    , /* array */
                            0                       , /* left */
                            nmemb - 1               , /* right */
                            size, cmp_func, to_find );
}

/*****************************************************************************
** description:   implementation of Jump  Search search
** arguments:     base     - pointer to the start of the array.
**                nmemb    - number of elements in the array.
**                size     - size of each element.
**                cmp_func - user defined compare func.
**                req_data - the element to search for
** return value:  req_data if found, NULL otherwise,
** notes:         -
******************************************************************************/
void* JumpSearch( void* base, size_t nmemb, size_t size,
                  cmp_func_t cmp_func, void* to_find   )
{
    /* sqrt(nmemb); */
    size_t jump_size  = ceil( ((-1. + sqrt(1 + 8 * nmemb))/2.) ); /* calc the jump */
    size_t jump_index = jump_size;
    size_t prev_index = 0;          /* holds prev jump_index */

    assert( (base != NULL) && (cmp_func != NULL) );

    /* Search for the block that contains the element */
    while ( cmp_func(GetElem(base, Min(jump_index, nmemb) - 1), to_find) < 0 )
    {
        prev_index  = jump_index;
        jump_index += jump_size;
        --jump_size;

        if (prev_index >= nmemb)
        {
            /* case: overstepped the array, element was not found */
            return NULL;
        }
    }

    /* linearly search for the element in the block */
    while ( cmp_func( GetElem(base, prev_index), to_find ) < 0 )
    {
        ++prev_index;

        if ( prev_index == Min(jump_index, nmemb) )
        {
            /*  If we reached next block or end of array,
                element is not present */
            return NULL;
        }
    }

    if ( cmp_func( GetElem(base, prev_index), to_find ) == 0 )
    {
        /* Case: element was found */
        return GetElem(base, prev_index);
    }

    return NULL;
}
