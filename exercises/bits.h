/* Author: Alex B
** Last update: 31.08.17 21:00
** Program:	Worksheet6 - Bitwise operations
*/

#ifndef __BITWISE_H__
#define __BITWISE_H__



/*****************************************************************************
** ARGUMENTS: unsigned int multiplyer, int power_of_two
**
** RETURNS: given x and y as an input solves/returns the result
**			for x<<y == x*2^y
** 			 
** NOTES: can calculate result if power_of_two is negative
**
******************************************************************************/
double pow2(unsigned int multiplyer, int power_of_two);


/*****************************************************************************
** ARGUMENTS: int input
**
** RETURNS:  prints "(input) Is the power of two !" if input power of 2
**			 prints "(input) Is NOT the power of two !" if not
** 			 
** NOTES: the input will be power of two only if there is -only one-
**		  bit that is equals to '1' (other bits should be '0')
**
******************************************************************************/
int IsPowerOfTwo(unsigned int input);


/*****************************************************************************
** ARGUMENTS: unsigned int input
**
** RETURNS:  prints "(input) Is the power of two !" if input power of 2
**			 prints "(input) Is NOT the power of two !" if not
** 			 
** NOTES: - using NOT BITWISE operation -1 (minus one) for this function
**		  - exploiting the fact that power of two number minus one AND
**			(logic gate) the number itself always equals 0 !
**			for example (0100-1)&(0100)=0 for any power of two number
**
******************************************************************************/
int IsPowerOfTwoNoLoop (unsigned int input);


/*****************************************************************************
** ARGUMENTS: unsigned int input
**
** RETURNS: input + 1
** 			 
** NOTES: the given input plus 1 implemented with bitwise operations
**
******************************************************************************/
unsigned int AddOne(unsigned int input);



/*****************************************************************************
** ARGUMENTS: array of unsigned ints, number of rays in array
**
** RETURNS: prints only the ints that have exactly 3 bits on ('1')
** 			 
** NOTES: this function is using CountOnes function
**		  CountOnes - counts ('1') ones in a given unsigned int 
**
******************************************************************************/
void PrintIntsWith3OnesFromArr(unsigned int *arr, unsigned int arr_length);



/*****************************************************************************
** ARGUMENTS: unsigned int input
**
** RETURNS: mirrors/swaps the bits of input and return the result 
** 			 
** NOTES: 
**
******************************************************************************/
unsigned int ByteMirror(unsigned int input);



/*****************************************************************************
** ARGUMENTS: unsigned int input
**
** RETURNS: mirrors/swaps the bits of input and return the result 
** 			 
** NOTES: this ByteMirror function is implemented without any loop
**
******************************************************************************/
unsigned int ByteMirrorNoLoop(unsigned int res);



/*****************************************************************************
** ARGUMENTS: unsigned char input
**
** RETURNS: checks the bits 2, 6 if they are both on,
**			it returns 1 ("true")
** 			 
** NOTES: 
**
******************************************************************************/
unsigned int IsBits2and6Set (unsigned char input);



/*****************************************************************************
** ARGUMENTS: unsigned char input
**
** RETURNS: checks the bits 2, 6 if at least one of them is on,
**			it returns 1 ("true")	 
** NOTES: 
**
******************************************************************************/
unsigned int IsBits2or6Set (unsigned char input);



/*****************************************************************************
** ARGUMENTS: unsigned char input
**
** RETURNS: swaps between bit 3 and bit 5 and returns the new number
** 			 
** NOTES: 
**
******************************************************************************/
unsigned int SwapBit3and5 (unsigned char input);



/*****************************************************************************
** ARGUMENTS: unsigned int intput
**
** RETURNS: returns the closest (smaller) number that is devided by 16 
**			without remainder.
** 			 
** NOTES: exploiting the notion that every (input)AND(0xfffffff0) will give
**		  us the closest number that is divided by 16.
**
******************************************************************************/
unsigned int ClosestDividerBy16 (unsigned int intput);




/*****************************************************************************
** ARGUMENTS: unsigned int *num1, unsigned int *num2
**
** RETURNS: void
** 			 
** NOTES: function that swaps 2 variables without using a third variable
**
******************************************************************************/
void SwapBitwise( unsigned int *num1, unsigned int *num2 );



/*****************************************************************************
** ARGUMENTS: unsigned int intput
**
** RETURNS: number of turned on bits '1' (ones) in input
** 			 
** NOTES: 
**
******************************************************************************/
unsigned int CountOnes(unsigned int input);



/*****************************************************************************
** ARGUMENTS: unsigned int intput
**
** RETURNS: number of turned on bits '1' (ones) in input
** 			 
** NOTES: count number of set bits in a 32-bit integer withough loop. 
**		  from the book "Hacker's Delight", p. 66, Figure 5-2	
**
******************************************************************************/
unsigned int TurnedBitsInInt(unsigned int x);



/*****************************************************************************
** ARGUMENTS: number of float type
**
** RETURNS: 
** 			 
** NOTES: receives a float and prints its bits
**
******************************************************************************/
void PrintFloat(float num);



/* used throughout the program to print out the binary value of unsigned int */
void PrintBinary(unsigned int input);


/* used throughout the program to print out the binary value of unsigned char */
void PrintBinaryChar(unsigned char input);


#endif 	/* __BITWISE_H__ */