
/****************************************
  Filename: cbuffer.h
  Purpose: Header file for circular_buffer
  Data Structure: circular_buffer
  Version: 3
 ****************************************/
#ifndef __CBUFFER_H__
#define __CBUFFER_H__

#include <stddef.h> /* size_t */

typedef struct cbuffer cbuffer_t;

/*****************************************************************************
** description: init the circular buffer
** arguments:  buffer_size - the buffer size in bytes
**             (must be greater than zero)
** return value: pointer to the circular buffer handler,
**               or NULL in case of failure
** notes:  - must call CircBufferDestroy at end of use
******************************************************************************/
cbuffer_t* CBufferCreate( size_t buffer_size );

/*****************************************************************************
** description: destroys a given circular buffer, created by CircBufferCreate
** arguments: cbuffer - pointer to the circular buffer handler
** return value: void
** notes: call at end of use
******************************************************************************/
void CBufferDestroy( cbuffer_t *cbuffer );

/*****************************************************************************
** description: returns the capacity of the circular buffer.
** arguments: cbuffer - pointer to the circular buffer handler
** return value: capacity, in bytes, of the circular buffer
** notes:
******************************************************************************/
size_t CBufferCapacity( const cbuffer_t *cbuffer );

/*****************************************************************************
** description: returns the current free space of the circular buffer
** arguments: cbuffer - pointer to the circular buffer handler
** return value: free space, in bytes, of the circular buffer
** notes:
******************************************************************************/
size_t CBufferFreeSpace( const cbuffer_t *cbuffer );

/*****************************************************************************
** description: read 'n_bytes' from the CircBuffer to destination
** arguments: cbuffer - pointer to the circular buffer handler
**            dest - the data destination pointer
**            n_bytes - number of bytes to read
** return value: Returns the number of bytes that were actually read 
** notes: the `dest` buffer needs to be larger or equal to `n_bytes`
**        when there is no more data to be read errno
**        is assigned to ENODATA
******************************************************************************/
size_t CBufferRead( cbuffer_t *cbuffer, void* dest, size_t n_bytes );
                      
/*****************************************************************************
** description: write 'n_bytes' from the src to c_buffer handler
** arguments: cbuffer - pointer to the circular buffer handler
**            src - the data source pointer
**            n_bytes - number of bytes to be writen 
** return value: Returns the number of bytes that were actually writen
** notes: - `src` array need to be larger or equal to `n_bytes`
**        -  when there is not enough free space errno is assigned to OVERFLOW  
******************************************************************************/
size_t CBufferWrite( cbuffer_t *cbuffer ,
                     const void *src, size_t n_bytes );

/*****************************************************************************
** description: checks if the current circular buffer is empty
** arguments: cbuffer - pointer to the circular buffer handler
** return value:  1 if buffer is empty, 0 otherwise
** notes: boolean function
******************************************************************************/
int CBufferIsEmpty( const cbuffer_t *cbuffer );


#endif /* __CBUFFER_H__ */