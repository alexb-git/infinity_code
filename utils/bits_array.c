/* Author: Alex B
** Last update: 12.09.17 03:00
** Program: Basic Data Structures - Bit Array
**			Screen 
*/
/****************************************
  Filename: bits_array.h                
  Purpose: Header file for bits array   
  Data Structure
  Version: 4                 
 ****************************************/

#include <stddef.h> /* size_t */
#include "bits_array.h"


#define BYTES_IN_WORD (8)
#define BITS_IN_WORD (64)
#define ASCII_INDEX (256)


static const unsigned char count_set_lut[ASCII_INDEX] = 
		{  	0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,
	        2,3,3,4,2,3,3,4,3,4,4,5,1,2,2,3,2,3,3,4,
	        2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,
	        4,5,5,6,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
	        2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,2,3,3,4,
	        3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,
	        4,5,5,6,5,6,6,7,1,2,2,3,2,3,3,4,2,3,3,4,
	        3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
	        2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,
	        4,5,5,6,4,5,5,6,5,6,6,7,2,3,3,4,3,4,4,5,
	        3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,
	        5,6,6,7,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
	        4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8			};

static const unsigned char mirror_lut[ASCII_INDEX] = 
		{	0, 128,64,192,32,160,96, 224,16,144,80,208,48,176,112,240,
			8, 136,72,200,40,168,104,232,24,152,88,216,56,184,120,248,
		 	4, 132,68,196,36,164,100,228,20,148,84,212,52,180,116,244,
			12,140,76,204,44,172,108,236,28,156,92,220,60,188,124,252,
			2, 130,66,194,34,162,98, 226,18,146,82,210,50,178,114,242,
			10,138,74,202,42,170,106,234,26,154,90,218,58,186,122,250,
			6, 134,70,198,38,166,102,230,22,150,86,214,54,182,118,246,
			14,142,78,206,46,174,110,238,30,158,94,222,62,190,126,254,
			1, 129,65,193,33,161,97, 225,17,145,81,209,49,177,113,241,
			9, 137,73,201,41,169,105,233,25,153,89,217,57,185,121,249,
			5, 133,69,197,37,165,101,229,21,149,85,213,53,181,117,245,
			13,141,77,205,45,173,109,237,29,157,93,221,61,189,125,253,
			3, 131,67,195,35,163,99, 227,19,147,83,211,51,179,115,243,
			11,139,75,203,43,171,107,235,27,155,91,219,59,187,123,251,
			7, 135,71,199,39,167,103,231,23,151,87,215,55,183,119,247,
			15,143,79,207,47,175,111,239,31,159,95,223,63,191,127,255	};


/*****************************************************************************
** DESCRIPTION: Setting all bits in the array to 1
** ARGUMENTS: word size bits array
** RETURN VALUE: bits array with all bits set
** NOTES: 
******************************************************************************/
size_t BitsArrayAllOn(size_t bits_array)
{
	return ~(size_t)0;
}

/*****************************************************************************
** DESCRIPTION: Setting all bits in the array to 0
** ARGUMENTS: word size bits array
** RETURN VALUE: bits array with all bits set to 0
** NOTES: 
******************************************************************************/
size_t BitsArrayAllOff(size_t bits_array)
{
	return 0;
}

/*****************************************************************************
** DESCRIPTION: Setting a single bit, indicated by an index, to 1
** ARGUMENTS: word size bits array, index ( from 0 to 63)
** RETURN VALUE: bits array with specified bit on
** NOTES: 
******************************************************************************/
size_t BitsArraySetBitOn(size_t bits_array, size_t index)
{
	return bits_array | ( (size_t)1 << (BITS_IN_WORD - 1 - index) );
}

/*****************************************************************************
** DESCRIPTION: Setting a single bit, indicated by an index, to 0
** ARGUMENTS: word size bits array, index (from 0 to  63)
** RETURN VALUE: bits array with specified bit off
** NOTES: 
******************************************************************************/
size_t BitsArraySetBitOff(size_t bits_array, size_t index)
{
	return bits_array & 
			( ~(size_t)0 - ( (size_t)1 << (BITS_IN_WORD - 1 - index) ));
}

/*****************************************************************************
** DESCRIPTION: Set bit, indicated by an index to the value
**              indicated by BitValue
** ARGUMENTS: word size bits array, index (from 0 to  63), BitValue ( 0 or 1)
**            - that'll be set at index
** RETURN VALUE: bits array with specified bit set to specified value
** NOTES: 
******************************************************************************/
size_t BitsArraySetBit(size_t bits_array, size_t index, int BitValue)
{
	/* nullyfy the bit */
	bits_array &= (~(size_t)0 - ((size_t)1 << (BITS_IN_WORD - 1 - index)));
	return bits_array | (size_t)BitValue << (BITS_IN_WORD - 1 - index);
}

/*****************************************************************************
** DESCRIPTION: Check if the bit, indicated by an index is set (1)
** ARGUMENTS: word size bits array, index (from 0 to  63)
** RETURN VALUE: 1 - bit is set,
                 0 - else.
** NOTES: boolean function
******************************************************************************/
int BitsArrayIsBitOn(size_t bits_array, size_t index)
{
	return ( ( bits_array >> (BITS_IN_WORD - 1 - index) ) & 1 );
}

/*****************************************************************************
** DESCRIPTION: Check if the bit, indicated by an index is off (0)
** ARGUMENTS: word size bits array, index (from 0 to 63)
** RETURN VALUE: 1 - bit is off,
                 0 - else
** NOTES: boolean function
******************************************************************************/
int BitsArrayIsBitOff(size_t bits_array, size_t index)
{
	size_t mask = 1 << (BITS_IN_WORD - 1 - index);
	return ( (bits_array & mask) != mask );
}

/*****************************************************************************
** DESCRIPTION: Inverting all bits values (~bits_array) 
** ARGUMENTS: word size bits array
** RETURN VALUE: updated bits array
** NOTES:
******************************************************************************/
size_t BitsArrayInvertBits(size_t bits_array)
{
	return ~bits_array;
}

/*****************************************************************************
** DESCRIPTION: Count num of On (1) bits
** ARGUMENTS: word size bits array
** RETURN VALUE: the number of set bits
** NOTES:
******************************************************************************/
size_t BitsArrayCountSetBits(size_t bits_array)
{
	size_t counter = 0;

	while(bits_array)
	{
		bits_array &= (bits_array - 1);
		++counter;

	}

	return counter;
}

/*****************************************************************************
** DESCRIPTION: count num of off bits 
** ARGUMENTS: word size bits array
** RETURN VALUE: updated bits array
** NOTES:
******************************************************************************/
size_t BitsArrayCountOffBits(size_t bits_array)
{
	return ( 64 - BitsArrayCountSetBits(bits_array) );
}

/*****************************************************************************
** DESCRIPTION: n - the number of bits to shift - left or right
** ARGUMENTS: word size bits array, n - number of shifts to perform
** RETURN VALUE: Rotated bits_array
** NOTES:
******************************************************************************/
size_t BitsArrayRotateRight(size_t bits_array, size_t n)
{
	return 	( bits_array >> (n % BITS_IN_WORD)) | 
			( bits_array << ( (BITS_IN_WORD - n) % BITS_IN_WORD ) );
}

/*****************************************************************************
** DESCRIPTION: shift all bits n times to the left. 
** ARGUMENTS: word size bits array, n - number of shifts to perform
** RETURN VALUE: Rotated bits_array
** NOTES:
******************************************************************************/
size_t BitsArrayRotateLeft(size_t bits_array, size_t n)
{
	return 	( bits_array << (n % BITS_IN_WORD)) | 
			( bits_array >> ( (BITS_IN_WORD - n) % BITS_IN_WORD ) );
}

/*****************************************************************************
** DESCRIPTION: Reverse array elements
** ARGUMENTS: word size bits array
** RETURN VALUE: Updated bits_array
** NOTES: 
******************************************************************************/
size_t BitsArrayMirror(size_t bits_64)
{

	bits_64 = 	((bits_64 & 0x5555555555555555) << 1 ) | 
				((bits_64 & 0xaaaaaaaaaaaaaaaa) >> 1 );

	bits_64 = 	((bits_64 & 0x3333333333333333) << 2 ) | 
				((bits_64 & 0xcccccccccccccccc) >> 2 );

	bits_64 = 	((bits_64 & 0x0f0f0f0f0f0f0f0f) << 4 ) | 
				((bits_64 & 0xf0f0f0f0f0f0f0f0) >> 4 );

	bits_64 = 	((bits_64 & 0x00ff00ff00ff00ff) << 8 ) | 
				((bits_64 & 0xff00ff00ff00ff00) >> 8 );

	bits_64 = 	((bits_64 & 0x0000ffff0000ffff) << 16 ) | 
				((bits_64 & 0xffff0000ffff0000) >> 16 );

	bits_64 = 	((bits_64 & 0x00000000ffffffff) << 32 ) | 
				((bits_64 & 0xffffffff00000000) >> 32 );

	return bits_64;
}

/*****************************************************************************
** DESCRIPTION: Count num of set ('1') bits
** ARGUMENTS: word size bits array
** RETURN VALUE: Updated bits_array
** NOTES: using Lool-Up Table methode
******************************************************************************/
size_t BitsArrayLutCountOn(size_t bits_array)
{
	int iterations = BYTES_IN_WORD;
	size_t counter = 0;
	unsigned char *byte_ptr = (unsigned char*)&bits_array;

	while(iterations--)
	{
		counter += count_set_lut[ (unsigned char)*byte_ptr ];
		++byte_ptr;
	}

	return counter;
}

/*****************************************************************************
** DESCRIPTION: Reverse array elements
** ARGUMENTS: word size bits array
** RETURN VALUE: Updated bits_array
** NOTES: using Lool-Up Table methode
******************************************************************************/
size_t BitsArrayLutMirror(size_t bits_array)
{
	int iterations = BYTES_IN_WORD;
	size_t result = 0;
	char *byte_ptr = (char*)&bits_array;

	while(iterations--)
	{
		result = ( result << 8 ) 
				 + mirror_lut[ (unsigned char)*byte_ptr ];
		++byte_ptr;
	}

	return result;
}