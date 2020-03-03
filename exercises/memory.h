/* Author: Alex B
** Last update: 09.09.17 03:00
** Program:	- Worksheet 9 - word boundary optimization
**			- memset, memcpy, memmoce, MyItoa, StringToInt,
**			  IsLittleEndian, PrintExistIn2Not3rd
*/

#ifndef __MEMORY_H__
#define __MEMORY_H__


/*****************************************************************************
** DESCRIPTION: copies the character c (an unsigned char) to the first n
**				characters of the string pointed to, by the argument str.
**
** RETURNS: This function returns a pointer to the memory area str
**
** NOTES:
******************************************************************************/
void *Mymemset(void *ptr, int value, size_t num);


/*****************************************************************************
** DESCRIPTION: copies n characters from memory area source
**				to memory area destination.
**
** RETURNS: This function returns a pointer to destination
**
** NOTES:
******************************************************************************/
void *Mymemcpy(void *destination, const void *source, size_t num);


/*****************************************************************************
** DESCRIPTION: copies n characters from source to destination,
**				but for overlapping memory blocks, memmove()
**				is a safer approach than memcpy()
**
** RETURNS: This function returns a pointer to the destination
**
** NOTES:
******************************************************************************/
void *Mymemmove(void *destination, const void *source, size_t num);



#endif 	/* __MEMORY_H__ */