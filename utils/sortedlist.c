/****************************************************************************
** Filename:    - sortedlist.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.come
** Purpose:     - implementation of Sorted Linked List
** Date:        - 03/10/2017
** Version:     - 3
*****************************************************************************/
#include <stdlib.h>	        /* malloc, free */
#include <assert.h>	        /* assert */

#include "dlist.h"          /* Doubly Linked List DS */
#include "sortedlist.h"     /* Sorted Linked List DS */

struct sorted_list
{
    dlist_t *dlist;
    cmp_function2 c_func;

};

#define IsItrAtList(sorted_list,itr) (sorted_list == itr.list)

#define CreateAndReturnItrStruct(itr_, list_, magic_number_)\
                            sorted_list_itr_t itr_struct;\
                            itr_struct.itr          = itr_;\
                            itr_struct.list         = list_;\
                            itr_struct.magic_number = magic_number_;\
                            return itr_struct

/*****************************************************************************
** description:  create a new sorted list handler.
** arguments:    c_func - compare function, define the sorting order.
** return value: pointer to sorted_list handler.
** notes:        must call SortedListDestroy at end of use.
******************************************************************************/
sorted_list_t* SortedListCreate(const cmp_function2 c_func)
{
    sorted_list_t *sorted_list_h =
                  (sorted_list_t*)malloc ( sizeof(sorted_list_t) );

    if (NULL != sorted_list_h)
    {
        sorted_list_h->dlist  = DlistCreate();

        if ( sorted_list_h->dlist != NULL )
        {
            sorted_list_h->c_func = c_func;
        }
        else
        {
            free(sorted_list_h);
            sorted_list_h = NULL;
            return NULL;
        }

    }

    return sorted_list_h;
}

/*****************************************************************************
** description:  destroy sorted list.
** arguments:    sorted_list - pointer to the list to destroy.
** return value: void.
** notes:        must be called at the end of use.
******************************************************************************/
void SortedListDestroy(sorted_list_t *sorted_list)
{
    assert( sorted_list != NULL );

    /* free the list */
    DlistDestroy(sorted_list->dlist);
    sorted_list->dlist  = NULL;

    /* free the handler */
    free(sorted_list);
    sorted_list = NULL;
}

/*****************************************************************************
** description:  counts number of elements in sorted list.
** arguments:    sorted_list - pointer to sorted list handler.
** return value: number of elements in sorted list.
** notes:
******************************************************************************/
size_t SortedListSize(const sorted_list_t *sorted_list)
{
    assert( sorted_list != NULL );
    return DlistCount(sorted_list->dlist);
}

/*****************************************************************************
** description:  check if sorted list is empty.
** arguments:    sorted_list - pointer to the sorted list handler.
** return value: 1 - empty, 0 - else.
** notes:
******************************************************************************/
int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
    assert( sorted_list != NULL );
    return DlistIsEmpty(sorted_list->dlist);
}

/*****************************************************************************
** description:  returns iterator that points to first element of sorted list.
** arguments:    sorted_list - pointer to sorted list handler.
** return value: iterator that points to beginning of the sorted list,
**               in case of empty list return pointer to end of sorted list.
**               (end of sorted list is the stub element after the last element).
** notes:
******************************************************************************/
sorted_list_itr_t SortedListBegin(const sorted_list_t *sorted_list)
{
    assert( sorted_list != NULL );

    {CreateAndReturnItrStruct( DlistBegin(sorted_list->dlist),
                              (sorted_list_t*)sorted_list, 666 );}
}

/*****************************************************************************
** description:  returns iterator that points to end of sorted list.
**               (end of sorted list is the stub element after the last element).
** arguments:    sorted_list - pointer to sorted list handler.
** return value: iterator that points to end of the sorted list.
** notes:
******************************************************************************/
sorted_list_itr_t SortedListEnd(const sorted_list_t *sorted_list)
{
    assert( sorted_list != NULL );

    {CreateAndReturnItrStruct( DlistEnd(sorted_list->dlist),
                              (sorted_list_t*)sorted_list, 666 );}
}

/*****************************************************************************
** description:  promote the iterator to the next element.
** arguments:    itr - iterator.
** return value: iterator to the next element.
** notes:        if itr points to end, the return value is unpredicted
******************************************************************************/
sorted_list_itr_t SortedListNext(const sorted_list_itr_t itr)
{
    CreateAndReturnItrStruct( DlistNext(itr.itr), itr.list, 666 );
}

/*****************************************************************************
** description:   returns iterator of the previous element.
** arguments:     itr - iterator.
** return value:  iterator to the previous element.
** notes:         if itr points to begin, the return value is unpredicted
******************************************************************************/
sorted_list_itr_t SortedListPrev(const sorted_list_itr_t itr)
{
    CreateAndReturnItrStruct( DlistPrev(itr.itr), itr.list, 666 );
}

/*****************************************************************************
** description:  remove first element in sorted list.
** arguments:    sorted_list - sorted list handler.
** return value: iterator to next element of the one that was popped.
** notes:        if list is empty return value is itr that points to end.
******************************************************************************/
sorted_list_itr_t SortedListPopFront(sorted_list_t *sorted_list)
{
    assert( sorted_list != NULL );

    {CreateAndReturnItrStruct( DlistPopFront(sorted_list->dlist),
                              (sorted_list_t*)sorted_list, 666 );}
}

/*****************************************************************************
** description:  remove last element in sorted list.
** arguments:    sorted_list - sorted list handler.
** return value: iterator to previous element to the one that was popped.
** notes:        if list is empty return value is itr that points to end.
******************************************************************************/
sorted_list_itr_t SortedListPopBack(sorted_list_t *sorted_list)
{
    assert( sorted_list != NULL );

    {CreateAndReturnItrStruct( DlistPopBack(sorted_list->dlist),
                              (sorted_list_t*)sorted_list, 666 );}
}

/*****************************************************************************
** description:  insert a new element according to the list order
**               (defined by the compare function (cmp_function)).
** arguments:    sorted_list - pointer to sorted_list handler.
**               data  - pointer to data.
** return value: iterator to the inserted element that contains the data.
** notes:        if insertion failed - return null.
******************************************************************************/
sorted_list_itr_t SortedListInsert(sorted_list_t *sorted_list,
                                   const void *data)
{
    itr_t start = NULL;
    itr_t end   = NULL;

    assert( sorted_list != NULL );

    start = DlistBegin(sorted_list->dlist);
    end   =   DlistEnd(sorted_list->dlist);

    while ( start != end )
    {
        if ( sorted_list->c_func(DlistGetData(start), data) > 0 )
        {
            /*  find the first element in the list
                that is bigger than the inserted one */
            break;
        }
        start = DlistNext(start);
    }

    start = DlistInsert( sorted_list->dlist, start, (void*)data );

    {CreateAndReturnItrStruct( start, (sorted_list_t*)sorted_list, 666 );}

}

/*****************************************************************************
** description:  erase element pointed by itr.
** arguments:    sorted_list - pointer to sorted list handler.
**               itr -  iterator to the element to erase.
** return value: iterator to next element (after the removed element).
** notes:        if itr points to end or if list is empty
**               no action occurs, and the return value is
**               itr that points to end.
******************************************************************************/
sorted_list_itr_t SortedListErase(sorted_list_t    *sorted_list,
                                  sorted_list_itr_t itr)
{
    assert( sorted_list != NULL );

    if ( IsItrAtList(sorted_list, itr) )
    {
        itr.itr = DlistErase(sorted_list->dlist, itr.itr);
    }
    else
    {
        itr.itr = DlistEnd(sorted_list->dlist);
    }

    return itr;
}

/******************************************************************************
** description:  the function search for an element with the given data.
** arguments:    data - pointer to the data we seek.
**               sorted_list - pointer to sorted list handler.
** return value: returns iterator that points to the first instance of data,
**               or NULL if data was not found.
******************************************************************************/
sorted_list_itr_t SortedListFind(sorted_list_t *sorted_list, const void *data)
{
    assert( sorted_list != NULL );

    {CreateAndReturnItrStruct(  DlistFind(DlistBegin(sorted_list->dlist),
                                          DlistEnd(sorted_list->dlist)  ,
                                          sorted_list->c_func           ,
                                          data                          ),
                                sorted_list, 666                        );}
}

/*****************************************************************************
** description:  invoke `bool_function` on all data from 'start'
**               till 'end', return iterator to the first data
**               that failed the boolean function, or NULL if all succeeded.
** arguments:    start - iterator, from where to invoke the function (inclusive).
**               end   - iterator, till where to invoke the function (exclusive).
**               b_func - pointer to users' function.
**               param  - additional parameter for the function.
** return value: pointer to the first node that failed the boolean
**               function, or NULL if all nodes succeeded.
******************************************************************************/
sorted_list_itr_t SortedListForEach(const sorted_list_itr_t start,
                                    const sorted_list_itr_t end,
                                    bool_function2 b_func,
                                    const void *param)
{
    assert( param != NULL );

    {CreateAndReturnItrStruct(   DlistForEach(start.itr , end.itr         ,
                                              b_func    , (void*)param    ),
                                 start.list, 666                          );}
}

/*****************************************************************************
** description:  merge two sorted lists.
** arguments:    sorted_list_1 - pointer to first sorted list's handler.
**               sorted_list_2 - pointer to second sorted list's handler.
** notes :       sorted_list_2 will be emptied.
** return value: void
******************************************************************************/
void SortedListMerge(sorted_list_t *sorted_list_1,
                     sorted_list_t *sorted_list_2)
{
    assert( (sorted_list_1 != NULL) && (sorted_list_2 != NULL) );

    while ( !SortedListIsEmpty(sorted_list_2) )
    {
        SortedListInsert( sorted_list_1,
                          DlistGetData(DlistBegin(sorted_list_2->dlist)));

        SortedListPopFront(sorted_list_2);
    }
}

/*****************************************************************************
** description:  get the data from the element that is pointed to by the itr.
** arguments:    itr - iterator.
** return value: pointer to data.
** notes:        if itr points to end, the return value is NULL.
******************************************************************************/
void* SortedListGetData(const sorted_list_itr_t itr)
{
    return DlistGetData(itr.itr);
}

/*****************************************************************************
** description:  check if both iterators point to the same element.
** arguments:    itr1 - iterator, itr2 - iterator.
** return value: 1 - same, 0 - else.
** notes:        when NULL is inserted instead of iterators,
**               you will get unexpected behavior.
******************************************************************************/
int SortedListSameIterator(const sorted_list_itr_t itr1,
                           const sorted_list_itr_t itr2)
{
    return DlistSameIterator(itr1.itr, itr2.itr);
}
