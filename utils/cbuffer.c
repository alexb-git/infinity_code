/* Author: Alex B
** Last update: 18.09.17 21:20
** Program: Circular Buffer data structure
*/

#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */
#include <stdio.h> 	/* printf */
#include <string.h>	/* memcpy */
#include <errno.h>	/* errno */

#include "cbuffer.h"

#define MIN(a,b) ( (a < b) ? (a) : (b) )
#define AddressDiff(a,b) ( (char*)a - (char*)b )

extern int errno;

struct cbuffer
{
	void *start;
	void *end;		/* points to the limit of the buffer, illegal address */
	void *read;		/* place where the data will be read from */
	void *write;	/* next place to write data to */

	int is_full;	/* bollean variable */
};


/* promote the ptr by n bytes in a cyclical way */
static void* PromotePtr(cbuffer_t *cbuffer, void *ptr, size_t n_bytes );


/*****************************************************************************
** description: init the circular buffer
** arguments:  buffer_size - the buffer size in bytes
**             (must be greater than zero)
** return value: pointer to the circular buffer handler,
**               or NULL in case of failure
** notes:  - must call CircBufferDestroy at end of use
******************************************************************************/
cbuffer_t* CBufferCreate( size_t buffer_size )
{
	cbuffer_t *handler = NULL;

	if ( 0 == buffer_size ) /* case: zero passed as buffer size */
	{
		return NULL;
	}

	handler = (cbuffer_t*)malloc( sizeof(cbuffer_t) );

	if ( NULL == handler ) /* case: memory allocation failed */
	{
		return NULL;
	}

	handler->start = malloc( buffer_size );

	if ( NULL == handler->start ) /* case: memory allocation failed */
	{
		free(handler);
		handler = NULL;
		return NULL;
	}

	handler->end 		= (char*)handler->start 
						+ buffer_size;

	handler->read 		= handler->start;
	handler->write 		= handler->start;
	handler->is_full 	= 0;

	return handler;
}


/*****************************************************************************
** description: destroys a given circular buffer, created by CircBufferCreate
** arguments: cbuffer - pointer to the circular buffer handler
** return value: void
** notes: call at end of use
******************************************************************************/
void CBufferDestroy( cbuffer_t *cbuffer )
{
	assert( cbuffer != NULL );

	free(cbuffer->start);	/* free the buffer */
	cbuffer->start = NULL;

	free(cbuffer);	/* free the handler */
	cbuffer = NULL;
}


/*****************************************************************************
** description: returns the capacity of the circular buffer.
** arguments: cbuffer - pointer to the circular buffer handler
** return value: capacity, in bytes, of the circular buffer
** notes:
******************************************************************************/
size_t CBufferCapacity( const cbuffer_t *cbuffer )
{
	assert( cbuffer != NULL );

	return AddressDiff(cbuffer->end, cbuffer->start);
}


/*****************************************************************************
** description: returns the current free space of the circular buffer
** arguments: cbuffer - pointer to the circular buffer handler
** return value: free space, in bytes, of the circular buffer
** notes:
******************************************************************************/
size_t CBufferFreeSpace( const cbuffer_t *cbuffer )
{
	assert( cbuffer != NULL );
	
	if ( (cbuffer->read) < (cbuffer->write) ) /* normal case */
	{
		return AddressDiff(cbuffer->write ,cbuffer->read) + 1;
	}
	else if ( (cbuffer->write) < (cbuffer->read) )
	{

		return  AddressDiff(cbuffer->read, cbuffer->write);
	}
	else /* cbuffer->read == cbuffer->write */
	{
		return 	  ( cbuffer->is_full ) 
				? ( 0 ) 
				: ( CBufferCapacity(cbuffer) );
	}
}


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
size_t CBufferRead( cbuffer_t *cbuffer, 
                    void* dest, size_t n_bytes )
{
	size_t actually_read = 0;
	char *des_ptr = dest;

	assert( cbuffer != NULL && dest != NULL );

	/* loopy behaviour of read pointer */
	while( n_bytes && !CBufferIsEmpty(cbuffer) )
	{

		*(des_ptr) = *(char*)cbuffer->read;
		++des_ptr;
		++actually_read;
		--n_bytes;

		if ( (char*)cbuffer->read + 1 == cbuffer->end )
		{
			/* promote pointer in a loopy manner */
			cbuffer->read = cbuffer->start;
		}
		else /* (char*)cbuffer->read + 1 != cbuffer->end */
		{
			/* promote pointer regularry */
			cbuffer->read = (char*)cbuffer->read + 1;
		}

		if ( cbuffer->read == cbuffer->write )
		{
			/* case: there is no more data to read */
			cbuffer->is_full = 0;
			break;
		}
	}

	if ( actually_read < n_bytes )
	{
		errno = ENODATA;
	}
	
	return actually_read;
}


/*****************************************************************************
** description: write 'n_bytes' from the src to c_buffer handler
** arguments: cbuffer - pointer to the circular buffer handler
**            src - the data source pointer
**            n_bytes - number of bytes to be writen 
** return value: Returns the number of bytes that were actually writen
** notes: - `src` array need to be larger or equal to `n_bytes`
**        -  when there is not enough free space errno is assigned to EOVERFLOW  
******************************************************************************/
size_t CBufferWrite( cbuffer_t *cbuffer,
                     const void *src, size_t n_bytes )
{
	size_t free_space 		= CBufferFreeSpace(cbuffer);
	size_t bytes2copy 		= MIN(free_space, n_bytes);
	size_t bytes_till_end   = MIN( AddressDiff(cbuffer->end, cbuffer->write),
								   bytes2copy );
	size_t bytes_from_start = bytes2copy - bytes_till_end ;

	assert( cbuffer != NULL && src != NULL );

	memcpy(	cbuffer->write,
			src,
			bytes_till_end  );

	memcpy(	cbuffer->start, 
			(char*)src + bytes_till_end , 
			bytes_from_start );

	cbuffer->write = PromotePtr(cbuffer, cbuffer->write, bytes2copy );

	if ( cbuffer->write == cbuffer->end )
	{
		cbuffer->write = cbuffer->start;
	}

	if ( cbuffer->read == cbuffer->write )
	{
		cbuffer->is_full = 1;
	}

	if ( bytes2copy < n_bytes )
	{
		errno = EOVERFLOW;
	}

	return bytes2copy;
}


/*****************************************************************************
	promote the ptr by n bytes in a cyclical way
******************************************************************************/
static void* PromotePtr(cbuffer_t *cbuffer, void *ptr, size_t n_bytes )
{
	assert( cbuffer != NULL && ptr != NULL );

	return    (  (char*)ptr + n_bytes  > (char*)(cbuffer->end) ) 
			? (  (char*)ptr + n_bytes - (char*)cbuffer->end 
				+(char*)cbuffer->start ) 
			: (  (char*)ptr + n_bytes );
}


/*****************************************************************************
** description: checks if the current circular buffer is empty
** arguments: cbuffer - pointer to the circular buffer handler
** return value:  1 if buffer is empty, 0 otherwise
** notes: boolean function
******************************************************************************/
int CBufferIsEmpty( const cbuffer_t *cbuffer )
{
	assert( cbuffer != NULL );

	if ( (cbuffer->read == cbuffer->write) && (0 == cbuffer->is_full) )
	{
		return 1;
	}
	return 0;	
}

/* hide from the user */
void PrintAddresses(const cbuffer_t *cbuffer)
{
	printf("%-7lu", (size_t)cbuffer->read %100);
	printf("%-7lu", (size_t)cbuffer->write%100);
}
