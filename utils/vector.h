/****************************************
Filename: vector.h
Purpose: Header file for vector
Data Structure: Vector
Version: 3
****************************************/

#ifndef __VECTOR_H__ 
#define __VECTOR_H__

#include <stddef.h> /* size_t */

typedef struct vector vector_t;

/*****************************************************************************
** description: init the whole vector
** arguments:  element_size - size of single element in the vector
**                            (must be greater than zero)
**            number_of_elements - inital vector capacity
**                            (must be greater than zero)
** return value: pointer to the vector handler, or NULL in case of failure
** notes:  must call VectorDestroy at end of use
******************************************************************************/
vector_t* VectorCreate(size_t element_size, size_t number_of_elements);

/*****************************************************************************
** description: destroys a given vector, created by VectorCreate
** arguments: vector - pointer to the vector handler
** return value: void
** notes: call at end of use
******************************************************************************/
void VectorDestroy(vector_t *vector);

/*****************************************************************************
** description: Pushes an item into the end of the vector
** arguments: vector - pointer to the vector handler
**            data   - pointer to the data to be pushed into the vector
** return value: 1 - success
**               0 - error
** notes: pushing into a full vector will increase the capacity of the
**        vector by 2, this action might take additional time.
******************************************************************************/
int VectorPush(vector_t *vector, const void *data);

/*****************************************************************************
** description: Pop out the item from the end of the vector
** arguments: pointer to the vector handler
** return value: void
** notes: if vector is empty no action occurs.
******************************************************************************/
void VectorPop(vector_t *vector);

/*****************************************************************************
** description: return pointer to the required (by index) element
** arguments: vector - pointer to the vector handler
**            index  - cell number of required element in vector
** return value: pointer to the required element, or NULL in case of failure
** notes:
******************************************************************************/
void* VectorGetItem(vector_t *vector, size_t index);

/*****************************************************************************
** description: returns the size of the vector (number of elements)
** arguments: vector - pointer to the vector handler
** return value: number of elements in vector
** notes:
******************************************************************************/
size_t VectorSize(const vector_t *vector);

/*****************************************************************************
** description: returns the current capacity of the vector
** i.e. total capacity of vector: empty places + taken places
** arguments: vector - pointer to the vector handler
** return value: capacity of the vector
** notes:
******************************************************************************/
size_t VectorCapacity(const vector_t *vector);

/*****************************************************************************
** description: changes the vector capacity to required capacity
** arguments: vector - pointer to the vector handler.
required_capacity   -  required capacity.
** return value: 1 - success.
**               0 - error.
** notes:
******************************************************************************/
int VectorReserve(vector_t *vector, size_t required_capacity);


#endif /* __VECTOR_H__ */
