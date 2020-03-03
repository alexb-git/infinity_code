/***************************************************
  Filename: fixed_allocator.h
  Purpose:  Header file for Fixed Size Allocator
  Product:  Fixed Size Allocator
  Version:  2
 ***************************************************/
#ifndef __FIXED_ALLOCATOR_H__
#define __FIXED_ALLOCATOR_H__

#include <stddef.h> /* size_t */

typedef struct allocator fallocator_t; /* Fixed Allocator Handler. */

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
                               size_t block_size  );

/*****************************************************************************
** description:  allocate a new block.
** arguments:    handler to a Fixed Size Allocator.
** return value: pointer to the allocated  block.
******************************************************************************/
void* FAllocatorAlloc(fallocator_t* allocator);

/*****************************************************************************
** description: free the block pointed by block.
** arguments:   fallocator - handler to a Fixed Size Allocator.
**              block      - pointer to the block to free.
** return value: void
******************************************************************************/
void FAllocatorFree(fallocator_t* allocator, void *block);

/*****************************************************************************
** description:  counts size of free memory in fallocator in bytes.
** arguments:    handler to a Fixed Size Allocator.
** return value: number of free bytes in buffer.
******************************************************************************/
size_t FAllocatorCountFree(const fallocator_t* allocator);

/*****************************************************************************
** description:  return the minimum buffer size.
** arguments:    num_elem  - num of elements.
**               num_bytes - quantity of bytes of each element.
** return value: the minimum buffer size in bytes
******************************************************************************/
size_t FAllocatorGetMinSize(size_t num_elem, size_t num_bytes);

#endif /* __FIXED_ALLOCATOR_H__ */
