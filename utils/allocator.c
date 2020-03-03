/****************************************************************************
** Filename:    - allocator.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementation of Allocator
** Date:        - 26/10/2017
** Version:     - 4597
*****************************************************************************/
#include <assert.h>       /* assert */
#include "allocator.h"    /* Fixed Size Allocator */

#define WORDSIZE ( sizeof(void*) )

#define AlignElement(num_bytes)  (( num_bytes % WORDSIZE )\
                                ?( WORDSIZE * ( num_bytes / WORDSIZE + 1 ) )\
                                :( num_bytes ))

/* assumption:
**    negative long = occupied segment,
**    positive long = free segment
*/

#define Abs(X)              ( ( (X) < 0) ? ( (-1)*(X) ) : (X) )
#define Occupy(X)           ( (-1)*(X) )
#define SegmentIsFree(X)    ( X->seg_size > 0 )
#define SizeOfHeader        ( sizeof(seg_header_t) )
#define NextHeader(X)       ((seg_header_t*)((char*)X + Abs(X->seg_size)))
#define SetBlockFree(X)     ( X->seg_size = Abs(X->seg_size) )
#define OccupyBlock(X,Z)    ( X->seg_size = Occupy(Z) )


/* ========== segment header structure ========== */
typedef struct seg_header
{
    long  seg_size; /*  negative - segment is occupied,
                        else     - segment is free      */
} seg_header_t;

/* ========== allocator handler ========== */
struct allocator
{
    void         *buffer_limit; /* points to the first out of buffer address */
    seg_header_t  first_header;
};

/*****************************************************************************
** description:   create a new handler to an Allocator.
** arguments:     buffer      - pointer to the allocated memory area.
**                buffer_size - allocated memory (buffer) size.
** return value:  pointer to new allocator handler.
** notes:         buffer size should be sufficient,
**                the allocation is aligned
******************************************************************************/
allocator_t* AllocatorCreate(void *buffer, size_t buffer_size )
{
    allocator_t *handler = NULL;

    assert( (buffer != NULL) && (buffer_size != 0) );

    /* ========== init allocator handler ========== */
    handler = (allocator_t*)buffer;

    handler->first_header.seg_size = buffer_size
                                   - ( AlignElement(sizeof(allocator_t))
                                     - AlignElement(sizeof(seg_header_t)) );

    handler->buffer_limit = (char*)buffer + buffer_size;

    return handler;
}

/*****************************************************************************
** description:  allocate a new block.
** arguments:    allocator    - handler of the Allocator.
**               req_bytes - number of bytes to allocate
** return value: pointer to the allocated block,
**               or null if there is not enough space to allocate.
******************************************************************************/
void* AllocatorAlloc(allocator_t *allocator, size_t req_bytes)
{
    seg_header_t *header = NULL;

    assert(allocator != NULL);

    header    = &allocator->first_header;
    req_bytes =  AlignElement(req_bytes);

    /*  find the first segment that can contain the 'req_bytes' + SizeOfHeader,
        or return 'NULL' if there is no such segment */
    while (1)
    {
     /*============  segment for allocation could not be found  =============*/
        if ( (void*)header ==  allocator->buffer_limit )
        {
            return NULL;  /* allocation cannot be performed */
        }

        if ( SegmentIsFree(header) )
        {
         /*===============  unites the freed adjusted segments  =============*/
            seg_header_t *next_header =  NextHeader(header);

            /* find the next non free block or end of buffer */
            while ( (next_header != allocator->buffer_limit)
                    && SegmentIsFree(next_header) )
            {
                next_header = NextHeader(next_header);
            }

            /*  update the current segment size to be the number of bytes
                from current free block till the next non free block */
            header->seg_size = (char*)next_header - (char*)header;

         /*==================  block to allocate was found  =================*/
            if ( req_bytes + SizeOfHeader <= header->seg_size )
            {
                break;
            }
        }

        header = NextHeader(header);
    }

    /*************************************************************************
        split free space into 2 legal segments OR one whole segment
    **************************************************************************/
    if (  (SizeOfHeader + req_bytes)  /*      header + user required bytes  */
         +(SizeOfHeader + WORDSIZE)   /* next header + minimal segment size */
         <= (header->seg_size)      )
    {
        /*  General case: able to create next segment */
        seg_header_t *next_header   = NULL;
        long          prev_seg_size = header->seg_size;

        /* allocate segment and update size */
        OccupyBlock(header, req_bytes + SizeOfHeader);

        /* updae the size of the second half of the segment */
        next_header           = NextHeader(header);
        next_header->seg_size = prev_seg_size - Abs(header->seg_size);
    }
    else
    {
        /*  give the whole segment (to avoid dead segments) */
        OccupyBlock(header, header->seg_size);
    }

    return ((char*)header + SizeOfHeader);
}

/*****************************************************************************
** description:  deallocates the memory previously allocated
**               by a call to AllocatorAlloc.
** arguments:    allocator - pointer to the Allocator handler.
**               block     - pointer to a memory block previously
**                           allocated with AllocatorAlloc.
** return value: void
******************************************************************************/
void AllocatorFree(allocator_t* allocator, void *block)
{
    seg_header_t *block_header = NULL;

    assert( (allocator != NULL) && (block != NULL) );

    block_header = (seg_header_t*)((char*)block - sizeof(seg_header_t));

    SetBlockFree(block_header);
}
