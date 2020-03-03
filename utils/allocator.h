/***************************************************
  Filename: allocator.h
  Purpose:  Header file for Allocator
  Product:  Memory Allocator
  Version:  2
 ***************************************************/
#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include <stddef.h> /* size_t */

typedef struct allocator allocator_t; /* Allocator Handler */

/*****************************************************************************
** description:   create a new handler to an Allocator.
** arguments:     buffer      - pointer to the allocated memory area.
**                buffer_size - allocated memory (buffer) size.
** return value:  pointer to new allocator handler.
** notes:         buffer size should be sufficient,
**                the allocation is aligned
******************************************************************************/
allocator_t* AllocatorCreate(void *buffer, size_t buffer_size );

/*****************************************************************************
** description:  allocate a new block.
** arguments:    allocator    - handler of the Allocator.
**               num_of_bytes - number of bytes to allocate
** return value: pointer to the allocated block,
**               or null if there is not enough space to allocate.
******************************************************************************/
void* AllocatorAlloc(allocator_t* allocator, size_t num_of_bytes);

/*****************************************************************************
** description:  deallocates the memory previously allocated
**               by a call to AllocatorAlloc.
** arguments:    allocator - pointer to the Allocator handler.
**               block     - pointer to a memory block previously
**                           allocated with AllocatorAlloc.
** return value: void
******************************************************************************/
void AllocatorFree(allocator_t* allocator, void *block);

#endif /* __ALLOCATOR_H__ */
