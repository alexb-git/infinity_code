/****************************************************************************
** Filename:    - sorts.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementations of sorting algorithms
** Date:        - 21/11/2017
** Version:     - 6
*****************************************************************************/
#include <stdlib.h>     /* malloc, free */
#include <string.h>     /* memmove */
#include <assert.h>     /* assert */
#include <time.h>       /* time_t */

#include "sorts.h"      /* Sorting Algorithms */

/****************************************************************************
    Macros for this program
*****************************************************************************/
#define Next(X)     ( (char*)X + size )
#define Prev(X)     ( (char*)X - size )

/*===== for HeapSort =====*/
#define Left(X)     (2*(X) + 1)
#define Right(X)    (2*(X) + 2)
#define Even(X)     (((X)&0x1)?(X-1):(X-2) )
#define Parent(X)   (Even(X)/2)
#define GetElem(X,I)((char*)X + (I) * size)


/*******************************************************************
  Debug Functions
*******************************************************************/
#ifdef _DEBUG
#include <stdio.h>    /* printf */
void PrintLongArr(void *arr, size_t size)
{
    long *arr_long = (long*)arr;
    size_t i = 0;

    printf("{");
    for ( ; i < size ; ++i)
    {
        printf(" %ld,", arr_long[i]);

    }
    printf("}\n");
}
#else
    void PrintLongArr(void *arr, size_t size){}
#endif


/*==================  struct of radix weight calculation  ==================*/
typedef struct radix_weight
{
    weight user_func;
    size_t current_nibble;
} radix_weight_t;

/*=============================  InnerRadixComp  ============================*/
static size_t InnerRadixComp(void *input, void *param)
{
    radix_weight_t *radix_weight = (radix_weight_t*)param;

    size_t element = radix_weight->user_func(input, NULL);
    size_t shift   = radix_weight->current_nibble;

    return ( element >> (shift * 4) ) & 0x0F ;
}

/*==============================  MaxNibbles  ==============================*/
static size_t MaxNibbles(void *base, size_t nmemb, size_t size, weight func)
{
    void  *last_element    = (char*)base + nmemb * size;
    size_t  max_key        = func(base, NULL);
    size_t  num_of_nibbles = 0;

    for ( ;
          base < last_element ;
          base = Next(base)   )
    {
        size_t key = func(base, NULL);
        if( key > max_key )
        {
            max_key = key;
        }
    }

    while ( max_key )
    {
        ++num_of_nibbles;
        max_key >>= 4;
    }

    return num_of_nibbles;
}

/****************************************************************************
    SWAP FUNCTION
    Note: need to provide the swap area (temp) for the function to work
*****************************************************************************/
static void Swap ( void *cell_1, void *cell_2,
                   size_t elem_size, void *temp)
{
    memmove( temp  , cell_1, elem_size );
    memmove( cell_1, cell_2, elem_size );
    memmove( cell_2, temp  , elem_size );
}

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
void SortRadix( void *base  , size_t nmemb, size_t size,
                weight func, void *param )
{
    size_t max_nibbles;
    size_t nibble;

    radix_weight_t inner_comp;  /* = {func, 0};*/
    inner_comp.user_func      = func;
    inner_comp.current_nibble = 0;

    assert( (base != NULL) && (func != NULL) );

    max_nibbles = MaxNibbles(base, nmemb, size, func);

    for ( nibble = 0 ; nibble < max_nibbles ; ++nibble )
    {
        inner_comp.current_nibble = nibble;

        SortCounting(base, nmemb, size, 16, InnerRadixComp, &inner_comp );
    }
}

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
void SortCounting(void *base  , size_t nmemb, size_t size,
                  size_t range, weight func, void *param )
{
    size_t i = 0;

    void   *runner       = NULL;
    void   *dup_array    = malloc(nmemb * size);
    void   *last_element = (char*)dup_array + nmemb * size;

    size_t *histogram    = (size_t*)calloc(range, sizeof(size_t));

    memcpy(dup_array, base, nmemb * size);

    assert( (base != NULL) && (func != NULL) );

    /* create histogram of occurrences for the given array */
    for (   runner = dup_array      ;
            runner < last_element   ;
            runner = Next(runner)   )
    {
        ++histogram[func(runner, param)];
    }

    /* make the histogram cumulative */
    --histogram[0];
    for ( i = 1 ; i < range ; ++i )
    {
        histogram[i] += histogram[i - 1];
    }

    /* sort the array with histogram table */
    for (   runner  = Prev(last_element) ;
            runner >= dup_array          ;
            runner  = Prev(runner)       )
    {
        size_t weight = func(runner, param);

        memcpy((char*)base + histogram[weight] * size, runner, size);
      --histogram[weight];
    }


    free(dup_array);
    dup_array = NULL;

    free(histogram);
    histogram = NULL;
}

/****************************************************************************
    SORT FUNCTION - SELECTION_SORT
    - each iteration find the the smallest element and insert to sorted area
*****************************************************************************/
void SortSelection( void *base, size_t nmemb, size_t size,
                    int (*compar)(const void *, const void *) )
{
    void *last_element = (char*)base + nmemb * size;
    void *before_last  = (char*)last_element - size;
    void *swap_space   = malloc(size);

    assert( (base != NULL) && (compar != NULL) );

    for ( ; base < before_last ; base = Next(base) )
    {
        void *cur_min = base;
        void  *runner = Next(base);

        for ( ; runner < last_element ; runner = Next(runner) )
        {
            if ( compar( cur_min, runner ) > 0 )
            {
                cur_min = runner;
            }
        }

        Swap( base, cur_min, size, swap_space );
    }

    free(swap_space);
    swap_space = NULL;
}

/****************************************************************************
    SORT FUNCTION - INSERTION_SORT
    - each iteration insert new element to soted area
*****************************************************************************/
void SortInsertion( void *base, size_t nmemb, size_t size,
                    int (*compar)(const void *, const void *) )
{
    void  *start        = base;
    void  *last_element = (char*)base + nmemb * size;
    void  *to_insert    = malloc(size);

    assert( (base != NULL) && (compar != NULL) );

    for ( base = Next(base) ; base < last_element ; base = Next(base) )
    {
        size_t elem_2_shift = 0;
        void  *runner       = base;

        memmove(to_insert, base, size);

        for ( ; runner > start ; runner = Prev(runner) )
        {
            if ( compar( to_insert, Prev(runner)) > 0 )
            {
                /* position for insertion found */
                break;
            }
            ++elem_2_shift;
        }

        /* shift the sorted part to right */
        memmove(Next(runner), runner, size * elem_2_shift);

        /* insert element to its' sutable place */
        memcpy(runner, to_insert, size);
    }

    free(to_insert);
    to_insert = NULL;
}

/****************************************************************************
    SORT FUNCTION - BUBBLE_SORT
    - compare each pair and bubble bigger
*****************************************************************************/
void SortBubble ( void *runner, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *) )
{
    int   is_sorted     = 0;
    void *start         = runner;
    void *last_unsorted = (char*)runner + ( nmemb - 1 ) * size;
    void *swap_space    = malloc(size);

    assert( (runner != NULL) && (compar != NULL) );

    while ( !is_sorted )
    {
        is_sorted = 1; /* if swap will not be performed the arrays is sorted */

        /* bubble up */
        for (   runner = start          ;
                runner < last_unsorted  ;
                runner = Next(runner)   )
        {
            if ( compar( runner, Next(runner)) > 0 )
            {
                Swap(runner, Next(runner), size, swap_space );
                is_sorted = 0;
            }
        }

        last_unsorted = Prev(last_unsorted);
    }

    free(swap_space);
    swap_space = NULL;
}

/****************************************************************************
    AID FUNCTIONS FOR MergeSort and MergeSort itself
*****************************************************************************/
static void MergeStep(  void *arr1,  size_t nmemb1,
                        void *arr2,  size_t nmemb2,
                        size_t size, void *buffer,
                        int (*compar)(const void *, const void *))
{
    void  *arr_start = arr1;
    void  *buf_start = buffer;

    void  *arr1_lim = (char*)arr1 + nmemb1 * size;
    void  *arr2_lim = (char*)arr2 + nmemb2 * size;

    while ( (arr1 < arr1_lim) && (arr2 < arr2_lim) )
    {
        if ( compar(arr1, arr2) < 0 )
        {
            /*  arr1 element is smaller than arr2 element,
                put arr1 element into destination */
            memcpy(buffer, arr1, size);
            arr1 = Next(arr1);
        }
        else
        {
            /*  arr2 element is smaller than arr1 element,
                put arr2 element into destination */
            memcpy(buffer, arr2, size);
            arr2 = Next(arr2);
        }

        buffer = Next(buffer);
    }

    /* case: already copied the whole arr1, copy the rest of arr2 */
    memcpy(buffer, arr2, ((char*)arr2_lim - (char*)arr2) );

    /* case: already copied the whole arr2, copy the rest of arr1 */
    memcpy(buffer, arr1, ((char*)arr1_lim - (char*)arr1) );

    /* copy the buffer (sorted array) into the passed array */
    memcpy(arr_start, buf_start, (nmemb1 + nmemb2) * size);
}

/****************************************************************************/
static void MergeSortRec( void *base, size_t nmemb, size_t size, void *buffer,
                          int (*compar)(const void *, const void *) )
{
    size_t middle = nmemb / 2;

    if ( nmemb > 1 )
    {

    /* Sort first halve of sub-array */
    MergeSortRec( base,                         /* left array */
                  middle,                       /* left array size */
                  size, buffer, compar);

    /* Sort second halve of sub-array */
    MergeSortRec( (char*)base + middle * size,  /* right array */
                  nmemb - middle,               /* right array size */
                  size, buffer, compar);

    /* Merge the two arrays */
    MergeStep( base,                            /* left  array */
               middle,                          /* left  array size */
               (char*)base + middle * size,     /* right array */
               nmemb - middle,                  /* right array size */
               size, buffer, compar);
    }
}

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
                int (*compar)(const void *, const void *) )
{
    void *buffer = NULL;

    assert( (base != NULL) && (compar != NULL) );

    /* buffer array for the use of MergeSort */
    buffer = (void*) malloc(nmemb * size);
    if (NULL != buffer)
    {
        MergeSortRec(base, nmemb, size, buffer, compar);

        free(buffer);
        buffer = NULL;
    }
}

/****************************************************************************
    AID FUNCTIONS FOR HeapSort and HeapSort itself
*****************************************************************************/
/****************************************************************************
** description:  Heapifys-Up elemet in index place to its' rightful place
** return value: void
** notes:        recursive function
*****************************************************************************/
static void MaxHeapify( void *base, size_t index, size_t nmemb, size_t size,
                        int (*compar)(const void*, const void*), void *buffer )
{
    size_t left  = 2 * index + 1;

   /* base case 1: left doesn't exist */
   if ( left >= nmemb )
   {
       return;
   }
   else
   {
       size_t bigger_i = index;
       size_t right    = 2 * index + 2;

       /* find if left child is bigger_i than current (parent) */
       if ( compar( GetElem(base, left), GetElem(base, index)) > 0 )
       {
           /* left bigger_i than current */
           bigger_i = left;
       }

       /* find if 'bigger_i' is bigger_i than right */
       if (    right < nmemb
            && compar( GetElem(base, right), GetElem(base, bigger_i)) > 0 )
       {
           bigger_i = right;
       }

       if ( bigger_i != index )
       {
           /* need to swap */
           Swap( GetElem(base, index)   , /* element 1 */
                 GetElem(base, bigger_i), /* element 2 */
                 size, buffer           ); /* elem_size and swap space */

           /* recursive call */
           MaxHeapify(base, bigger_i, nmemb, size, compar, buffer);
       }
   }
}

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
               int (*compar)(const void *, const void *) )
{
    void  *swap_buffer = NULL;
    size_t index;

    assert( (base != NULL) && (compar != NULL) );

    /* buffer array for the use of HeapSort */
    swap_buffer = (void*) malloc(size);

    if (NULL != swap_buffer)
    {
        /* BuildMaxHeap */
        for ( (index = nmemb / 2 + 2) ; index > 0 ; --index )
        {
            /* when index == 1, MaxHeapify will be called with index == 0 */
            MaxHeapify(base, index - 1, nmemb, size, compar, swap_buffer);
        }

        for ( index = nmemb - 1 ; index >= 1 ; --index )
        {
            Swap( base                ,  /* element 1 */
                  GetElem(base, index),  /* element 2 */
                  size, swap_buffer   ); /* elem_size and swap space */

            MaxHeapify(base, 0 /*Root*/, index, size, compar, swap_buffer);
        }

        free(swap_buffer);
        swap_buffer = NULL;
    }
}

/****************************************************************************
    AID FUNCTIONS FOR QuickSort and QuickSort itself
*****************************************************************************/
static long ChoosePivot(size_t l, size_t r)
{
	size_t pivot = 0;
	static time_t t;

	/* Intializes random number generator */
    srand((unsigned) time(&t));

	pivot = l + rand() % (r-l);

	return pivot;
}

/*==============================  Partition  ===============================*/
static size_t Partition( void *base,
                         long l,
                         long r,
                         size_t size,
                         int (*compar)(const void *, const void *),void *buffer)
{
    long pivot = ChoosePivot(l, r);

    /* moving the pivot to the end of the sub-array (temporarily) */
    Swap( GetElem(base, pivot),  /* pivot        */
          GetElem(base, r)    ,  /* last element */
          size, buffer        ); /* elem_size and swap space */


    pivot = r; /* update pivot index (was swaped with last element) */
    --r;       /* update right index, now points to element before the pivot */

    while( l < r )
    {
        /* if 'l' and 'r' were not moved swap will be performed */
        int was_moved = 0;

        /*  If base[r] >= base[pivot] promote 'r' */
        if ( compar(GetElem(base, r), GetElem(base, pivot)) >= 0 )
        {
            --r;
            was_moved = 1;
        }

        /*  If base[l] <= base[pivot] promote 'l' */
        if ( compar(GetElem(base, l), GetElem(base, pivot)) <= 0 )
        {
            ++l;
            was_moved = 1;
        }

        if ( !was_moved ) /* if 'l' and 'r' were not moved then swap */
        {
            Swap( GetElem(base, r), /* right - smaller then pivot */
                  GetElem(base, l), /* left  - bigger */
                  size, buffer   );

            /* update the indexes to the next candidates */
            --r;
            ++l;
        }
    }

    /* special case:
        - if 'l' points to element greater than pivot
            then swap 'l' with pivot
        - else
            then swap one element after 'l' with pivot */
    if ( compar(GetElem(base, l), GetElem(base, pivot)) > 0 )
    {
        Swap( GetElem(base, l)    ,
              GetElem(base, pivot),
              size, buffer        );
        pivot = l;
    }
    else
    {
        Swap( GetElem(base, l + 1),
              GetElem(base, pivot),
              size, buffer        );
        pivot = l + 1;
    }

    return pivot; /* the pivot index */
}

/****************************************************************************/
static void QuickSortRec( void *base, long l, long r, size_t size,
                          int (*compar)(const void *, const void *),
                          void *buffer )
{
    if (l < r)
    {
        /* arrange according to  */
        long pivot_index = Partition( base  ,   /* array address */
                                      l     ,   /* left */
                                      r     ,   /* right */
                                      size, compar, buffer);

        /*  Separately sort elements before partition and after partition */
        QuickSortRec( base              ,   /* array address */
                      l                 ,   /* left */
                      pivot_index - 1   ,   /* right */
                      size, compar, buffer);


        QuickSortRec( base            ,     /* array address */
                      pivot_index + 1 ,     /* left */
                      r               ,     /* right */
                      size, compar, buffer);
    }
}

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
                int (*compar)(const void *, const void *) )
{
    void *buffer = NULL;

    assert( (base != NULL) && (compar != NULL) );

    /* buffer array for the use of QuickSort */
    buffer = (void*) malloc(size);
    if (NULL != buffer)
    {
        QuickSortRec( base      , /* array address */
                      0         , /* left */
                      nmemb - 1 , /* right */
                      size, compar, buffer);

        free(buffer);
        buffer = NULL;
    }
}
