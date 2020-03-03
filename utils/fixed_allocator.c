/****************************************************************************
** Filename:    - fixed_allocator.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementation of Fixed Size Allocator
** Date:        - 25/10/2017
** Version:     - 5
*****************************************************************************/
#include <assert.h>             /* assert */
#include "fixed_allocator.h"    /* Fixed Size Allocator */

#define WORDSIZE ( sizeof(void*) )

#define AlignElement(num_bytes)  (( num_bytes % WORDSIZE )\
                                ?( WORDSIZE * ( num_bytes / WORDSIZE + 1 ) )\
                                :( num_bytes ))

struct allocator
{
    size_t  free_elements;
    void   *next_free;
};

/*****************************************************************************
** description:  return the minimum buffer size.
** arguments:    num_elem  - num of elements.
**               num_bytes - quantity of bytes of each element.
** return value: the minimum buffer size in bytes
******************************************************************************/
size_t FAllocatorGetMinSize(size_t num_elem, size_t num_bytes)
{
    return  ( num_elem * AlignElement(num_bytes) )
            + AlignElement(sizeof(fallocator_t));
}

/*****************************************************************************
** description:   create a new handler to a Fixed Size Allocator.
** arguments:     buffer      - pointer to the allocated memory area.
**                buffer_size - allocated memory (buffer) size.
**                block_size  - block size in bytes.
** return value:  pointer to new fallocator handler.
** notes:         buffer size should be sufficient,
**                at least FAllocatorGetMinSize().
**                buffer is aligned
******************************************************************************/
fallocator_t* FAllocatorCreate(void  *buffer      ,
                               size_t buffer_size ,
                               size_t block_size  )
{
    fallocator_t *handler = NULL;
    size_t *cur = NULL;
    size_t *end = NULL;

    assert( (buffer != NULL) && (buffer_size != 0) && (block_size != 0) );

    /* ========== init allocator handler ========== */
    handler = (fallocator_t*)buffer;

    handler->next_free     = (char*)buffer + AlignElement(sizeof(fallocator_t));

    block_size = AlignElement(block_size);

    handler->free_elements = (buffer_size - AlignElement(sizeof(fallocator_t)))
                           /  block_size;


    /* ========== init the buffer ========== */
    cur = handler->next_free;
    end = (size_t*)((char*)cur + ( (handler->free_elements - 1) * block_size ));

    while ( cur < end )
    {
        /* current r-value holds the address of the next block */
        *cur =  (size_t)( (char*)cur + block_size );

        /* promot current pointer to the next block */
         cur = (size_t*)( (char*)cur + block_size );
    }
    *cur = 0; /* last block point to NULL */

    return handler;
}

/*****************************************************************************
** description:  allocate a new block.
** arguments:    handler to a Fixed Size Allocator.
** return value: pointer to the allocated block.
******************************************************************************/
void* FAllocatorAlloc(fallocator_t* allocator)
{
    void *ptr = NULL;

    assert( allocator != NULL );

    if ( allocator->free_elements ) /* != 0 */
    {
        /* save the address of the block that will be allocated */
        ptr = allocator->next_free;

        /* update the handler. 'next_free' will point to the next free block */
        allocator->next_free = (void*)(*(size_t*)ptr);

        /* update number of free elements */
        --allocator->free_elements;
    }

    return ptr;
}

/*****************************************************************************
** description:  free the block pointed by block.
** arguments:    fallocator - handler to a Fixed Size Allocator.
**               block      - pointer to the block to free.
** return value: void
******************************************************************************/
void FAllocatorFree(fallocator_t* allocator, void *block)
{
    assert( allocator != NULL && block != NULL );

    /* the freed 'block' will point to the 'next_free' block */
    *(size_t*)block = (size_t)allocator->next_free;

    /* the handler will point to the newly freed block */
    allocator->next_free = block;

    /* update number of free elements */
    ++allocator->free_elements;
}

/*****************************************************************************
** description:  counts size of free memory in fallocator in bytes.
** arguments:    handler to a Fixed Size Allocator.
** return value: number of free bytes in buffer.
******************************************************************************/
size_t FAllocatorCountFree(const fallocator_t* allocator)
{
    assert( allocator != NULL );
    return allocator->free_elements;
}
