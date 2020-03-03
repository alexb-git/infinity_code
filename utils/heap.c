/****************************************************************************
** Filename:    - heap.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Heap implementation (based on Vector)
** Date:        - 23/11/2017
** Version:     - 1
*****************************************************************************/
#include <stdlib.h>    /* malloc, free */
#include <assert.h>    /* assert */
#include <string.h>    /* memcpy */

#include "vector.h"    /* vector DS */
#include "heap.h"      /* Heap DS */

/****************************************************************************
    Macros for this program
*****************************************************************************/
#define Left(X)     (2*(X) + 1)
#define Right(X)    (2*(X) + 2)
#define Even(X)     (((X)&0x1)?(X-1):(X-2) )
#define Parent(X)   (Even(X)/2)
#define NOT_FOUND   (-1)

#define GetItem(X,i) (*(void**)VectorGetItem(X, i))

/****************************************************************************
    Structs for this program
*****************************************************************************/
/* typedef struct heap heap_t; */
struct heap
{
    vector_t  *vector;
    cmp_func_t cmp_func;
};


/*============================  Static functions  ============================*/
static void HeapSwap( vector_t *vector, size_t index_1, size_t index_2);
static void HeapifyUp(heap_t *heap, size_t index);
static void HeapifyDown(heap_t *heap, size_t index);


/*****************************************************************************
** description:  create a new heap_t handler.
** arguments:    number_of_elements - inital vector capacity
**                                    (must be greater than zero)
**               cmp_func           - user's function that compares two
**                                    elements
** return value: pointer to heap_t
** notes:        must call HeapDestroy at end of use.
******************************************************************************/
heap_t* HeapCreate(size_t     element_size      ,
			       size_t     number_of_elements,
                   cmp_func_t cmp_func          )
{
    heap_t *heap = NULL;

    assert( cmp_func != NULL );

    heap = (heap_t*) malloc(sizeof(heap_t));
    if (NULL != heap)
    {
        heap->vector   = VectorCreate(element_size, number_of_elements);
        if ( NULL == heap->vector )
        {
            /* case: VectorCreate failed */
            free(heap);
			heap = NULL;

			return NULL;
        }

        heap->cmp_func = cmp_func;
    }

    return heap;
}

/*****************************************************************************
** description:  free heap.
** arguments:    heap - Heap handler.
** return value: void
** notes:        must be called at end of use.
******************************************************************************/
void HeapDestroy(heap_t *heap)
{
    assert( heap != NULL );

    VectorDestroy(heap->vector);

    /* free the handler and take care of dangling pointer */
    memset(heap, 0, sizeof(heap_t));
    free(heap);
    heap = NULL;
}


/****************************************************************************/
static void HeapSwap(vector_t *vector, size_t index_1, size_t index_2)
{
    /* addresses of index_1 and index_2 */
    void **var1 = NULL;
    void **var2 = NULL;

    assert( vector != NULL );

    var1 = (void**)VectorGetItem(vector, index_1);
    var2 = (void**)VectorGetItem(vector, index_2);

    if ( *(size_t*) var1 != *(size_t*) var2 )
    {
        *(size_t*) var1 ^= *(size_t*) var2;
        *(size_t*) var2 ^= *(size_t*) var1;
        *(size_t*) var1 ^= *(size_t*) var2;
    }
}

/****************************************************************************
** description:  Heapifys-Up elemet in index place to its' rightful place
** arguments:    vector   - representation of the heap
**               index    - element in index place to Heapify-Up
**               cmp_func - function that compares between two elements
**               element_size - size of element type
** return value: void
** notes:        recursive function
*****************************************************************************/
static void HeapifyUp( heap_t *heap, size_t index)
{
    assert( heap != NULL );

    /* base case 1: index of root */
    if ( 0 == index )
    {
        return;
    }
    else
    {
        /* continue to Heapify-Up if necessary */
        void *child  = GetItem(heap->vector, index);
        void *parent = GetItem(heap->vector, Parent(index));

        if ( heap->cmp_func(child, parent) > 0 )
        {
            /* need to swap */
            HeapSwap(heap->vector, index, Parent(index));

            /* recursive call */
            HeapifyUp(heap, Parent(index));
        }
    }
}

/*****************************************************************************
** description:  Insert element to the heap.
** arguments:    heap_t - Heap handler.
**               element      - pointer to the element to insert
** return value: 1 - success, 0 - fail
** notes:
******************************************************************************/
int HeapPush(heap_t *heap, const void *element)
{
    assert(heap != NULL);

    /* first: insert element to the end */
    if ( VectorPush(heap->vector, &element) )
    {
        /* Heapify-Up recursivly */
        HeapifyUp( heap, HeapSize(heap) - 1);

        return 1;
    }


    return 0; /* VectorPush failed */
}

/****************************************************************************
** description:  Heapifys-Up elemet in index place to its' rightful place
** arguments:    vector   - representation of the heap
**               index    - element in index place to Heapify-Up
**               cmp_func - function that compares between two elements
**               element_size - size of element type
** return value: void
** notes:        recursive function
*****************************************************************************/
static void HeapifyDown( heap_t *heap, size_t index)
{
    vector_t *vector    = NULL;
    size_t    heap_size = 0;

    assert( heap != NULL );

    vector    = heap->vector;
    heap_size = HeapSize(heap);

    /* base case 1: index of last leaf */
    if ( (heap_size - 1 == index) || (Left(index) >= heap_size) )
    {
        return;
    }
    else
    {
        size_t bigger_i = index;

        /* find if left child is bigger_i than current (parent) */
        void *curr = GetItem(vector, index);
        void *left = GetItem(vector, Left(index));

        if ( heap->cmp_func(left, curr) > 0 )
        {
            /* left bigger_i than current */
            bigger_i = Left(index);
        }

        /* find if 'bigger_i' is bigger_i than right */
        if ( Right(index) < heap_size )
        {
            void *right  = GetItem(vector, Right(index));

            if ( heap->cmp_func(right, GetItem(vector, bigger_i)) > 0 )
            {
                bigger_i = Right(index);
            }
        }

        if ( bigger_i != index )
        {
            /* need to swap */
            HeapSwap(vector, index, bigger_i);

            /* recursive call */
            HeapifyDown(heap, bigger_i);
        }
    }
}

/*****************************************************************************
** description:  remove the Heap's root.
** arguments:    heap_t - heap handler.
** return value: pointer to the data of the heap's root or NULL if empty.
** notes:
******************************************************************************/
void* HeapPop(heap_t *heap)
{
    void *ret_val = NULL;

    assert(heap != NULL);

    if ( !HeapIsEmpty(heap) )
    {
        /* save the data that the root holds for return */
        ret_val = GetItem(heap->vector, 0);

        /* first: swap root with last element */
        memcpy( VectorGetItem(heap->vector, 0),
                VectorGetItem(heap->vector, HeapSize(heap) - 1),
                sizeof(void*));

        /* pop out last element, previous root */
        VectorPop(heap->vector);

        /* Heapify-Down recursivly the new root */
        HeapifyDown(heap, 0);
    }

    return ret_val;
}

/*****************************************************************************
** description:  returns pointer to heap's root data.
** arguments:    heap_t - handler for the heap_t.
** return value: pointer to the data of the heap_t's root or NULL if empty.
** notes:
******************************************************************************/
void* HeapPeek(const heap_t *heap)
{
    assert( heap != NULL );

    if ( !HeapIsEmpty(heap) )
    {
        return GetItem(heap->vector, 0);
    }

    return NULL;
}

/*****************************************************************************
** description:  counts the number of elements in the heap.
** arguments:    heap_t - pointer to heap_t.
** return value: size_t: number of elements in heap_t.
** notes:
******************************************************************************/
size_t HeapSize(const heap_t *heap)
{
    assert( heap != NULL );

    return VectorSize(heap->vector);
}

/*****************************************************************************
** description:  check if the heap_t is empty.
** arguments:    heap_t -  handler to the heap.
** return value: int: 1 - empty, 0 - else.
** notes:
******************************************************************************/
int HeapIsEmpty(const heap_t *heap)
{
    assert( heap != NULL );

    return HeapSize(heap) == 0;
}

static long HeapFindIndexREC(  heap_t          *heap             ,
                               rmv_bool_func_t  rmv_cmp_func     ,
                               void *param, long index, long end )
{
    if ( index == end )
    {
        return NOT_FOUND; /* case: element to remove was not found  */
    }

    if ( rmv_cmp_func(GetItem(heap->vector, index), param) ) /* ==1 */
    {
        return index;
    }

    return HeapFindIndexREC( heap, rmv_cmp_func, param, ++index, end);
}

/*****************************************************************************
** description:  remove a certain element from heap.
** arguments:    heap_t -  handler to heap_t.
** return value: the pointer to the deleted element or NULL in case no element
				 that matches the rmv_cmp_func was found.
** notes:
******************************************************************************/
void* HeapRemove(heap_t *heap, rmv_bool_func_t rmv_cmp_func, void *param)
{
    long index = 0;
    long end   = 0;
    vector_t *vector;

    assert( (heap != NULL) && (rmv_cmp_func != NULL) );

    end    = HeapSize(heap);
    vector = heap->vector;

    index = HeapFindIndexREC( heap, rmv_cmp_func, param, index, end);
    if ( index != NOT_FOUND )
    {
        long last_index = HeapSize(heap) - 1;

        /* save the data that the cell holds for return */
        void *ret_val = GetItem(vector, index);

        /*  in case of removing last element Heapify-Up will try to
            Heapify NULL => core dump */
        if ( index != last_index )
        {
            /*  memcpy last element to the element to be deleted
                and remove the last element */
            memcpy( VectorGetItem(heap->vector, index),
                    VectorGetItem(heap->vector, HeapSize(heap) - 1),
                    sizeof(void*));
            VectorPop(heap->vector);

            /*  perform HeapifyUp and HeapifyDown sequentially
                if element in index place is balanced no action
                (Heapify) will be performed */
            HeapifyUp(heap, index);
            HeapifyDown(heap, index);
        }
        else
        {
            /* case: need to remove last element */
            VectorPop(heap->vector);
        }

        return ret_val;
    }

    return NULL;
}


/*******************************************************************
  Debug Functions
*******************************************************************/
#ifdef _DEBUG
#include <stdio.h>    /* printf */

#define GRE	 "\x1b[92m"
#define RED	 "\x1b[91m"
#define RES	 "\x1b[0m"

/*==========================  PrintHeap  ==========================*/
void PrintHeap(heap_t *heap)
{
    size_t end = VectorSize(heap->vector);
    size_t   i = 0;

    printf("\n");

    for ( i = 0 ; i < end ; ++i )
    {
        if ( !((i+1) & i) )
        {
            printf("\n");
        }

        printf("| %ld |", *(long*)*(void**)VectorGetItem(heap->vector, i));
    }
}

/*==========================  IsBalancedRec  ==========================*/
int IsBalancedRec(vector_t *vector, size_t index, cmp_func_t cmp_func)
{
    size_t heap_size = VectorSize(vector) - 1;

    /* base case 1: out of heap */
    if ( index >= heap_size )
    {
        return 1;
    }

    /* base case 2: right child is not balanced */
    if (    Right(index) <= heap_size
         && cmp_func(*(void**)VectorGetItem(vector, Right(index)),
                     *(void**)VectorGetItem(vector, index)       ) > 0 )
    {
        return 0;
    }

    /* base case 3: left child is not balanced */
    if (    Left(index) <= heap_size
         && cmp_func(*(void**)VectorGetItem(vector, Left(index)),
                     *(void**)VectorGetItem(vector, index)       ) > 0 )
    {
        return 0;
    }

    return    IsBalancedRec(vector, Right(index), cmp_func)
            & IsBalancedRec(vector,  Left(index), cmp_func);
}

/*==========================  IsBalanced  ==========================*/
void IsBalanced(heap_t *heap)
{
    if ( VectorSize(heap->vector) != 0 )
    {
        int is_balanced = IsBalancedRec(heap->vector, 0, heap->cmp_func);

        if ( is_balanced )
        {
            printf(GRE "\nHeap is balanced" RES);
        }
        else
        {
            printf(RED "\nHeap is NOT balanced" RES);
        }
    }
}
#else
    void PrintHeap(heap_t *heap){}
    void IsBalanced(heap_t *heap){}
#endif
