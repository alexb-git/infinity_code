/**********************************************
  Filename: search.h
  Purpose:  Header file for searching methods
  Version:  1
***********************************************/
#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stddef.h>

/*****************************************************************************
**  description:  compare function that compares two elements.
**  arguments:    elem_1       - pointer to the first element
**                elem_2       - pointer to the first element.
**  return value: an integer less than, equal to,  or greater  than.
**                zero  if  the first argument is considered to be respec‐
**                tively less than, equal to, or greater than the second.
**                If two members compare as equal, their order in the sorted
**                array is undefined.
**  notes:
******************************************************************************/
typedef  int (*cmp_func_t)(const void *, const void *);

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
                        cmp_func_t cmp_func, void* req_data  );

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
                       cmp_func_t cmp_func, void* req_data  );

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
                  cmp_func_t cmp_func, void* req_data  );


#endif
