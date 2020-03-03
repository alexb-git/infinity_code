/* Author: Alex B
** Last update: 09.09.17 03:00
** Program:	- Worksheet 9 - word boundary optimization
**			- memset, memcpy, memmoce, MyItoa, StringToInt,
**			  IsLittleEndian, PrintExistIn2Not3rd
*/

#include <stdio.h> 	/* printf, fopen, fclose, fscanf */
#include <stdlib.h> /* malloc, free */
#include <assert.h>	/* assert */
#include <string.h> /* memcpy, memcmp, memset */
#include <ctype.h>	/* Isdigit */

#include "memory.h"

#define WORD_SIZE (8) /* word size 8 byte */


/******************************************************************************
	copies the character c (an unsigned char) to the first n
	characters of the string pointed to, by the argument str.
******************************************************************************/
void *Mymemset(void *ptr, int value, size_t num)
{
	size_t i = 0; 					/* for while loop */

	char byte_chunk = (char)value; 	/* to copy one byte */
	size_t word_chunk = 0;			/* to copy one word */

	char   *current_place_ptr_byte = NULL;
	size_t *current_place_ptr_word = NULL;

	assert(ptr != NULL);

	/*	if need to copy more than word size construct word */
	if (num >= WORD_SIZE)
	{
		current_place_ptr_byte = (char*)&word_chunk;

		while (i < WORD_SIZE)
		{
			 *current_place_ptr_byte = byte_chunk;
			++current_place_ptr_byte;
			++i;
		}
	}

	/*	point to the given adress */
	current_place_ptr_byte = (char*)ptr;


	/*	while address is not divisible by word size
		and there are still bytes to copy, copy byte by byte */
	while (	( (size_t)current_place_ptr_byte % WORD_SIZE ) != 0
			&& num > 0 )
	{
		*current_place_ptr_byte = byte_chunk;
		 current_place_ptr_byte += 1;
		 num -= 1;
	}


	/*	while there are word sizes to be coppied,
		copy word by word */
	current_place_ptr_word = (size_t*)current_place_ptr_byte;
	while ( num >= WORD_SIZE )
	{
		/* use pointer of type (long*) to copy the whole word*/
		*current_place_ptr_word = word_chunk;
		 current_place_ptr_word += 1;
		 num -= WORD_SIZE;
	}
	current_place_ptr_byte = (char*)current_place_ptr_word;


	/* copy the rest of the bytes */
	while (num > 0)
	{
		*current_place_ptr_byte = byte_chunk;
		 current_place_ptr_byte += 1;
		 num -= 1;
	}

	return ptr;
}


/******************************************************************************
	copies n characters from memory area source to memory area destination
******************************************************************************/
void *Mymemcpy(void *destination, const void *source, size_t num)
{
	void *begining = destination;
	assert(destination != NULL && source != NULL);

	/*	while address is not divisible by word size
		and there are still bytes to copy, copy byte by byte */
	while (	((size_t)destination % WORD_SIZE) != 0
			&& num > 0)
	{
		*(char*)destination = *(char*)source;
		 destination = (char*)destination + 1;
		 source = (char*)source + 1;
		 num -= 1;
	}


	/*	while there are word sizes to be coppied,
		copy word by word */
	while (num >= WORD_SIZE)
	{
		*(size_t*)destination = *(size_t*)source;
		 destination = (size_t*)destination + 1;
		 source = (size_t*)source + 1;
		 num -= WORD_SIZE;
	}


	/* copy the rest of the bytes */
	while (num > 0)
	{
		*(char*)destination = *(char*)source;
		destination = (char*)destination + 1;
		source = (char*)source + 1;
		num -= 1;
	}

	return begining;
}


/******************************************************************************
	copies n characters from source to destination, but for overlapping
	memory blocks, memmove() is a safer approach than memcpy()
******************************************************************************/
void *Mymemmove(void *destination, const void *source, size_t num)
{
	void *begining = destination;
	void *des_limit = (char*)destination + num ;
	void *src_limit = (char*)source      + num ;
	char is_src_left_of_des = (source < destination) ? (1) : (0);

	assert(destination != NULL && source != NULL);

	/*	this function assumes that the source and destination
		addresses are 8-bytes aligned as the assignments states */

	/*	in case that source is LEFT of destination.
		to avoid overwrites the data will be copied from the
		left to right (pointers address increase each iteration) */
	if (is_src_left_of_des)
	{
		/*	while there are word sizes to be coppied,
		copy word by word */
		while (num > WORD_SIZE)
		{
			des_limit = (size_t*)des_limit - 1;
			src_limit = (size_t*)src_limit - 1;
			*(size_t*)des_limit = *(size_t*)src_limit;
			num -= WORD_SIZE;
		}

		/* copy the rest of the bytes */
		while (num > 0)
		{
			des_limit = (char*)des_limit - 1;
			src_limit = (char*)src_limit - 1;
			*(char*)des_limit = *(char*)src_limit;
			num -= 1;
		}
	}

	/*	in case that source is RIGHT of destination.
		to avoid overwrites the data will be copied from the
		right to left (pointers address decrease each iteration) */
	else
	{
		/*	while there are word sizes to be coppied,
			copy word by word */
		while (num > WORD_SIZE)
		{
			*(size_t*)destination = *(size_t*)source;
			destination = (size_t*)destination + 1;
			source = (size_t*)source + 1;
			num -= WORD_SIZE;
		}

		/* copy the rest of the bytes */
		while (num > 0)
		{
			*(char*)destination = *(char*)source;
			destination = (char*)destination + 1;
			source = (char*)source + 1;
			num -= 1;
		}
	}

	return begining;
}



