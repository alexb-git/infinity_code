
/****************************************
  Filename: bits_array.h                
  Purpose: Header file for bits array   
  Data Structure
  Version: 5                 
 ****************************************/
  
#ifndef __BITS_ARRAY_H__ 
#define __BITS_ARRAY_H__


/*****************************************************************************
** DESCRIPTION: Setting all bits in the array to 1
** ARGUMENTS: word size bits array
** RETURN VALUE: bits array with all bits set
** NOTES: 
******************************************************************************/
size_t BitsArrayAllOn(size_t bits_array);

/*****************************************************************************
** DESCRIPTION: Setting all bits in the array to 0
** ARGUMENTS: word size bits array
** RETURN VALUE: bits array with all bits set to 0
** NOTES: 
******************************************************************************/
size_t BitsArrayAllOff(size_t bits_array);

/*****************************************************************************
** DESCRIPTION: Setting a single bit, indicated by an index, to 1
** ARGUMENTS: word size bits array, index ( from 0 to 63)
** RETURN VALUE: bits array with specified bit on
** NOTES: 
******************************************************************************/
size_t BitsArraySetBitOn(size_t bits_array, size_t index);

/*****************************************************************************
** DESCRIPTION: Setting a single bit, indicated by an index, to 0
** ARGUMENTS: word size bits array, index (from 0 to  63)
** RETURN VALUE: bits array with specified bit off
** NOTES: 
******************************************************************************/
size_t BitsArraySetBitOff(size_t bits_array, size_t index);

/*****************************************************************************
** DESCRIPTION: Set bit, indicated by an index to the value
**              indicated by BitValue
** ARGUMENTS: word size bits array, index (from 0 to  63), BitValue ( 0 or 1)
**            - that'll be set at index
** RETURN VALUE: bits array with specified bit set to specified value
** NOTES: 
******************************************************************************/
size_t BitsArraySetBit(size_t bits_array, size_t index, int BitValue);

/*****************************************************************************
** DESCRIPTION: Check if the bit, indicated by an index is set (1)
** ARGUMENTS: word size bits array, index (from 0 to  63)
** RETURN VALUE: 1 - bit is set,
                 0 - else.
** NOTES: boolean function
******************************************************************************/
int BitsArrayIsBitOn(size_t bits_array, size_t index);

/*****************************************************************************
** DESCRIPTION: Check if the bit, indicated by an index is off (0)
** ARGUMENTS: word size bits array, index (from 0 to 63)
** RETURN VALUE: 1 - bit is off,
                 0 - else
** NOTES: boolean function
******************************************************************************/
int BitsArrayIsBitOff(size_t bits_array, size_t index);

/*****************************************************************************
** DESCRIPTION: Inverting all bits values (~bits_array) 
** ARGUMENTS: word size bits array
** RETURN VALUE: updated bits array
** NOTES:
******************************************************************************/
size_t BitsArrayInvertBits(size_t bits_array);

/*****************************************************************************
** DESCRIPTION: Count num of On (1) bits
** ARGUMENTS: word size bits array
** RETURN VALUE: the number of set bits
** NOTES:
******************************************************************************/
size_t BitsArrayCountSetBits(size_t bits_array);

/*****************************************************************************
** DESCRIPTION: count num of off bits 
** ARGUMENTS: word size bits array
** RETURN VALUE: updated bits array
** NOTES:
******************************************************************************/
size_t BitsArrayCountOffBits(size_t bits_array);

/*****************************************************************************
** DESCRIPTION: n - the number of bits to shift - left or right
** ARGUMENTS: word size bits array, n - number of shifts to perform
** RETURN VALUE: Rotated bits_array
** NOTES:
******************************************************************************/
size_t BitsArrayRotateRight(size_t bits_array, size_t n);

/*****************************************************************************
** DESCRIPTION: shift all bits n times to the left. 
** ARGUMENTS: word size bits array, n - number of shifts to perform
** RETURN VALUE: Rotated bits_array
** NOTES:
******************************************************************************/
size_t BitsArrayRotateLeft(size_t bits_array, size_t n);

/*****************************************************************************
** DESCRIPTION: Reverse array elements
** ARGUMENTS: word size bits array
** RETURN VALUE: Updated bits_array
** NOTES: 
******************************************************************************/
size_t BitsArrayMirror(size_t bits_array);

/*****************************************************************************
** DESCRIPTION: Count num of set ('1') bits
** ARGUMENTS: word size bits array
** RETURN VALUE: Updated bits_array
** NOTES: using Lool-Up Table methode
******************************************************************************/
size_t BitsArrayLutCountOn(size_t bits_array);

/*****************************************************************************
** DESCRIPTION: Reverse array elements
** ARGUMENTS: word size bits array
** RETURN VALUE: Updated bits_array
** NOTES: using Lool-Up Table methode
******************************************************************************/
size_t BitsArrayLutMirror(size_t bits_array);


#endif /* __BITS_ARRAY_H__ */
