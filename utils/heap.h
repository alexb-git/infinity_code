/**********************************************
  Filename: heap.h
  Purpose:  Header file for heap_t
  Version:  7
***********************************************/
#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */

typedef struct heap heap_t;

/*****************************************************************************
** description: compares two elements in a 'Max-heap_t', i.e.:
				in the case that cmp_func(element_1, element_2) >= 0,
				element_1 will heapify up, otherwise if <=0 then element_2
				will heapify up.
** arguments:
** return value:
******************************************************************************/
typedef int (*cmp_func_t)(const void *element1, const void *element2);

/*****************************************************************************
** description:  boolean function to identify the element/s to be removed.
** arguments:    element_1, element_2
** return value: 1 - elements are equal, 0 - elements differ
******************************************************************************/
typedef int (*rmv_bool_func_t)(const void *element1, const void *element2);

/*****************************************************************************
** description:  create a new heap_t handler.
** arguments:    number_of_elements - inital vector capacity
**                                    (must be greater than zero)
**               cmp_func           - user's function that compares two
**                                    elements
** return value: pointer to heap_t
** notes:        must call HeapDestroy at end of use.
******************************************************************************/
heap_t* HeapCreate(size_t element_size,
			       size_t number_of_elements,
                   cmp_func_t cmp_func);

/*****************************************************************************
** description:  free heap_t.
** arguments:    heap_t - Heap handler.
** return value: void
** notes:        must be called at end of use.
******************************************************************************/
void HeapDestroy(heap_t *heap);

/*****************************************************************************
** description:  Insert element to the heap_t.
** arguments:    heap_t - Heap handler.
**               element      - pointer to the element to insert
** return value: 1 - success, 0 - fail
** notes:
******************************************************************************/
int HeapPush(heap_t *heap, const void *element);

/*****************************************************************************
** description:  remove the Heap's root.
** arguments:    heap_t - handler for the heap_t.
** return value: pointer to the data of the heap_t's root or NULL if empty.
** notes:
******************************************************************************/
void* HeapPop(heap_t *heap);

/*****************************************************************************
** description:  returns pointer to heap_t's root data.
** arguments:    heap_t - handler for the heap_t.
** return value: pointer to the data of the heap_t's root or NULL if empty.
** notes:
******************************************************************************/
void *HeapPeek(const heap_t *heap);

/*****************************************************************************
** description:  counts the number of elements in the heap_t.
** arguments:    heap_t - pointer to heap_t.
** return value: size_t: number of elements in heap_t.
** notes:
******************************************************************************/
size_t HeapSize(const heap_t *heap);

/*****************************************************************************
** description:  check if the heap_t is empty.
** arguments:    heap_t -  handler to the heap_t.
** return value: int: 1 - empty, 0 - else.
** notes:
******************************************************************************/
int HeapIsEmpty(const heap_t *heap);

/*****************************************************************************
** description:  remove a certain element from heap_t.
** arguments:    heap_t -  handler to heap_t.
** return value: the pointer to the deleted element or NULL in case no element
				 that matches the rmv_cmp_func was found.
** notes:
******************************************************************************/
void* HeapRemove(heap_t *heap, rmv_bool_func_t rmv_cmp_func, void *param);

#endif /* __HEAP_H__ */
