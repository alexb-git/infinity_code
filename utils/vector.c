/* Author: Alex B
** Last update: 17.09.17 10:20
** Program: Vector data structure
*/

#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */
#include <string.h>	/* memcpy */

#include "vector.h"

#define is_vector_empty (vector->current == vector->start)
#define is_vector_full  (vector->current == vector->end)

struct vector
{
	void *start;
	void *end;
	void *current;			/* where the next element will be placed */
	size_t element_size;	/* in bytes */

};


/*****************************************************************************
** description: init the whole vector
** arguments:  element_size - size of single element in the vector
**                            (must be greater than zero)
**            number_of_elements - inital vector capacity
**                            (must be greater than zero)
** return value: pointer to the vector handler, or NULL in case of failure
** notes:  must call VectorDestroy at end of use
******************************************************************************/
vector_t* VectorCreate(size_t element_size, size_t number_of_elements)
{
	vector_t *vector_handler = NULL;
	size_t size_of_vector = element_size * number_of_elements; /* in bytes */

	if (0 == size_of_vector)
	{
		return NULL;
	}

	/* create vector handler - vector_t */
	vector_handler = (vector_t*)malloc( sizeof(vector_t) );

	if (NULL == vector_handler)
	{
		/* case: allocation for vector handler failed */
		return NULL;
	}

	/* init vector handler */
	vector_handler->start = (void*)malloc( size_of_vector );

	if (NULL == vector_handler->start)
	{
		/* case: allocation for vector stack failed */
		free(vector_handler);
		vector_handler = NULL;
		return NULL;
	}

	vector_handler->element_size = element_size;

	vector_handler->end 	= (char*)vector_handler->start 
							+ size_of_vector;

	vector_handler->current = vector_handler->start;
	
	return vector_handler;
}

/*****************************************************************************
** description: destroys a given vector, created by VectorCreate
** arguments: vector - pointer to the vector handler
** return value: void
** notes: call at end of use
******************************************************************************/
void VectorDestroy(vector_t *vector)
{
	assert(vector != NULL);

	free(vector->start);
	vector->start = NULL;

	free(vector);
	vector = NULL;
}

/*****************************************************************************
** description: Pushes an item into the end of the vector
** arguments: vector - pointer to the vector handler
**            data   - pointer to the data to be pushed into the vector
** return value: 1 - success
**               0 - error
** notes: pushing into a full vector will increase the capacity of the
**        vector by 2, this action might take additional time.
******************************************************************************/
int VectorPush(vector_t *vector, const void *data)
{
	assert(vector != NULL && data != NULL);

	if ( is_vector_full )
	{
		/* increase the capacity of the vector by the factor of 2 */
		if (!VectorReserve(vector, VectorCapacity(vector) * 2))
		{
			/* case: VectorPush failed */
			return 0;
		}
	}

	memcpy( vector->current,
			data,
			vector->element_size );

	vector->current = (char*)vector->current 
					+ vector->element_size;

	return 1;
}

/*****************************************************************************
** description: Pop out the item from the end of the vector
** arguments: pointer to the vector handler
** return value: void
** notes: if vector is empty no action occurs.
******************************************************************************/
void VectorPop(vector_t *vector)
{
	assert(vector != NULL);

	if (!is_vector_empty)
	{
		vector->current = (char*)vector->current
						- vector->element_size;
	}
}

/*****************************************************************************
** description: return pointer to the required (by index) element
** arguments: vector - pointer to the vector handler
**            index  - cell number of required element in vector
** return value: pointer to the required element, or NULL in case of failure
** notes:
******************************************************************************/
void* VectorGetItem(vector_t *vector, size_t index)
{
	size_t index_limit = VectorSize(vector) - 1;

	assert(vector != NULL);

	if (index > index_limit || is_vector_empty )
	{
		return NULL;
	}

	return (char*)vector->start + index * (vector->element_size);

}

/*****************************************************************************
** description: returns the size of the vector (number of elements)
** arguments: vector - pointer to the vector handler
** return value: number of elements in vector
** notes:
******************************************************************************/
size_t VectorSize(const vector_t *vector)
{
	assert(vector != NULL);

	return  ( (char*)vector->current
			- (char*)vector->start   )
			/ vector->element_size   ;
}

/*****************************************************************************
** description: returns the current capacity of the vector
** 				i.e. total capacity of vector: empty places + taken places
** arguments: vector - pointer to the vector handler
** return value: capacity of the vector
** notes:
******************************************************************************/
size_t VectorCapacity(const vector_t *vector)
{
	assert(vector != NULL);

	return  ( (char*)vector->end
			- (char*)vector->start )
			/ vector->element_size ;
}


/*****************************************************************************
** description: changes the vector capacity to the new size required
** arguments: vector - pointer to the vector handler
**            required_num_of_elements - new number of elements required
**                                       in the vector
** return value: 1 - success.
**               0 - error.
** notes:
******************************************************************************/
int VectorReserve(vector_t *vector, size_t required_num_of_elements)
{
	void  *alloc_ptr = NULL;

	size_t req_bytes_capacity 	= required_num_of_elements
								* vector->element_size;

	size_t cur_bytes_capacity 	= VectorSize(vector)
								* vector->element_size;

	size_t bytes_to_copy 		= (req_bytes_capacity < cur_bytes_capacity)
								? (req_bytes_capacity)
								: (cur_bytes_capacity);

	assert(vector != NULL);


	alloc_ptr = malloc(req_bytes_capacity);
	if (NULL == alloc_ptr)
	{
		/* case: allocation for vector stack failed */
		return 0;
	}

	/* copy data from current vector to the newly allocated memory */
	memcpy( alloc_ptr, 
			vector->start, 
			bytes_to_copy  );

	/* release the previous vector stack */
	free(vector->start);

	/* update the vector handler */
	vector->start = alloc_ptr;

	vector->end 	= (char*)(vector->start)
					+ req_bytes_capacity;

	vector->current = (char*)(vector->start)
					+ bytes_to_copy;

	return 1;
}
