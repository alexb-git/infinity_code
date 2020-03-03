/***************************************************
  Filename: sorts.h
  Purpose:  Header file for Sorting Algorithms
  Product:  Sorting Algorithms
  Version:  1
 ***************************************************/
#ifndef __SORTS_H__
#define __SORTS_H__

#include <stddef.h> /* size_t */

/****************************************************************************
    SORT FUNCTION - SELECTION_SORT
    - each iteration find the the smallest element and insert to sorted area
*****************************************************************************/
void SortSelection( void *base, size_t nmemb, size_t size,
                    int (*compar)(const void *, const void *) );

/****************************************************************************
    SORT FUNCTION - INSERTION_SORT
    - each iteration insert new element to soted area
*****************************************************************************/
void SortInsertion( void *base, size_t nmemb, size_t size,
                    int (*compar)(const void *, const void *) );

/****************************************************************************
    SORT FUNCTION - BUBBLE_SORT
    - compare each pair and bubble bigger
*****************************************************************************/
void SortBubble ( void *base, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *) );

/*****************************************************************************
**  description: the weight function, is a user define function that return
**               the weight of the inputed element in [0, range]
**  arguments: element - that we need to weight.
**             param   - the user given input.
**  return: weight of the inputed element.
**  notes:  used in radix.
******************************************************************************/
typedef size_t (*weight)(void *element, void *param);

/*****************************************************************************
**  description:  sort an array of elements.
**  arguments:    base   - Pointer to the first object of the array
**                         to be sorted, converted to a void*.
**                nmem   - Number of elements in the array pointed to by base
**                size   - Size in bytes of each element in the array.
**                range  - the number of possible values for an element.
**                weight - a function that return the weight of the element.
**  return value: void
**  notes:        Can, and should, be use in radix sort.
******************************************************************************/
void SortCounting(void *base  , size_t nmem, size_t size ,
                  size_t range, weight func, void *param );

/*****************************************************************************
**  description:  sort an array of elements.
**  arguments:    base   - Pointer to the first object of the array to be
**                        sorted, converted to a void*.
**                nmem   - Number of elements in the array pointed to by base
**                size   - Size in bytes of each element in the array.
**                range  - the number of possible values for an element.
**                weight - function that return the weight of the element.
**  return value: void
**  notes:        Can, and should, be use in radix sort.
******************************************************************************/
void SortRadix(void *base  , size_t nmem, size_t size ,
               weight func, void *param );

/*****************************************************************************
**  description:  sort an array of elements.
**  arguments:    base   - Pointer to the first object of the array to be
**                        sorted, converted to a void*.
**                nmem   - Number of elements in the array pointed to by base
**                size   - Size in bytes of each element in the array.
**                range  - the number of possible values for an element.
**                compar - comparison function given by the user.
**  return value: void
**  notes:        time complexity O(n*log(n)). space O(n)
******************************************************************************/
void MergeSort( void *base, size_t nmemb, size_t size,
                int (*compar)(const void *, const void *) );

/*****************************************************************************
**  description:  sort an array of elements.
**  arguments:    base   - Pointer to the first object of the array to be
**                        sorted, converted to a void*.
**                nmem   - Number of elements in the array pointed to by base
**                size   - Size in bytes of each element in the array.
**                range  - the number of possible values for an element.
**                compar - comparison function given by the user.
**  return value: void
**  notes:        time complexity O(n*log(n)). space O(1)
******************************************************************************/
void HeapSort( void *base, size_t nmemb, size_t size,
               int (*compar)(const void *, const void *) );

/*****************************************************************************
**  description:  sort an array of elements.
**  arguments:    base   - Pointer to the first object of the array to be
**                        sorted, converted to a void*.
**                nmem   - Number of elements in the array pointed to by base
**                size   - Size in bytes of each element in the array.
**                range  - the number of possible values for an element.
**                compar - comparison function given by the user.
**  return value: void
**  notes:        time complexity O(n*log(n)) - O(n^2)
******************************************************************************/
void QuickSort( void *base, size_t nmemb, size_t size,
                int (*compar)(const void *, const void *) );

#endif /* __SORTS_H__ */
