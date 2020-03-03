/* Author: Alex B
** Last update: 31.08.17 21:00
** Program:	Worksheet6 - Bitwise operations
*/

#include <stdio.h>	/* printf */
#include "bits.h" 	/* my bits manipulation functions */

#define BITES_IN_BYTE 8


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	this function is an auxiliary function for the ByteMirror function.
	IsBitSet = 1 if (num & bit_location != 0) 
	- meaning that the bit that we are checking in num is '1' (turned on) 
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static unsigned int IsBitSet (unsigned int num, unsigned int bit_location)
{
	return ( num & bit_location ) ? (1) : (0);
}


/******************************************************************************
	given x (multiplyer) and y (power_of_two) as an num solves/returns 
	the result for x<<y == x*2^y
*******************************************************************************/
double pow2(unsigned int multiplyer, int power_of_two)
{
	/* checks if power_of_two is negative */
	if ( 1 == ( ( power_of_two >> 
				( sizeof(power_of_two)*BITES_IN_BYTE - 1 )) & 1) )
	{
		/* make power_of_two positive for further calculation */
		power_of_two = AddOne(~power_of_two); 
		return ( (double)multiplyer / (1 << power_of_two) );
	}

	/* power_of_two is positive. we do everything regularly */
	return multiplyer << power_of_two;
}


/******************************************************************************
	num if power of two if and only if it contains only one set bit
******************************************************************************/
int IsPowerOfTwo(unsigned int num)
{
	unsigned int couter = 0;

	while(num)
	{	
		if ( num & 1 )
		{
			++couter;

			if ( couter > 1 )
			{
				return 0;
			}
		}

		num >>= 1;
	}

	return 0;
}


/******************************************************************************
	exploiting the fact that power of two number minus one AND
	(logic gate) the number itself always equals 0 !
******************************************************************************/
int IsPowerOfTwoNoLoop (unsigned int num)
{
	return ( (num - 1) & num ) ? 0 : 1 ;
}



/******************************************************************************
	the given num plus 1 implemented with bitwise operations
******************************************************************************/
unsigned int AddOne(unsigned int num)
{
	/* carry == 0000 0000 0000 0000 0000 0000 0000 0001 */
	unsigned int carry = 1;

	/* we iterate till there is no more carry to handle */
	while( num & carry )
	{
		/* 	if we are here then there is a carry
			XOR gate acts like a plus if there is a carry */
		num = num ^ carry;

		carry = carry << 1;
	}

	num = num | carry;

	return num;
}



/******************************************************************************
	given an array of unsigned ints and number of array cells
	prints only the ints that have exactly 3 bits on ('1')
******************************************************************************/
void PrintIntsWith3OnesFromArr(unsigned int *arr, unsigned int arr_length)
{
	unsigned int i = 0;
	unsigned int num = 0;
	unsigned int counter = 0;

	for ( i = 0 ; i < arr_length ; ++i )
	{
		num = arr[i];
		counter = 0;

		while( num )
		{
			if ( num & 1)
			{
				++counter;
				if ( counter > 3)
				{
					break;
				}
			}
			num >>= 1;
		}

		if ( 3 == counter )
		{
			PrintBinary(arr[i]);
		}
	}
}



/******************************************************************************
	mirrors/swaps the bits of num and return the result
******************************************************************************/
unsigned int ByteMirror(unsigned int num)
{
	unsigned int right_bit = 1;
	unsigned int left_bit = 1;

	left_bit <<= ( sizeof(num) * BITES_IN_BYTE - 1 );

	/* run till both right_bit "pointer" and left_bit "pointer" meet */
	while( left_bit > right_bit )
	{
		/* 	we only care to swap two bits if they differ */
		if ( IsBitSet(num, right_bit) ^ (IsBitSet(num, left_bit) == 1) )
		{
			/* swap/change 1 to 0 and vice versa */
			num ^= right_bit; /* num_digit^1 = ~num_digit */
			num ^= left_bit;
		}

		right_bit <<= 1;
		left_bit >>= 1;
	}

	return num;
}


/******************************************************************************
	mirrors/swaps the bits of num and return the result without loop
******************************************************************************/
unsigned int ByteMirrorNoLoop(unsigned int res)
{
	/* 	swap between every pair of two neighboring bits  
		0101 0110 => 1010 1001 */
	res = ((res & 0x55555555) << 1 ) | ((res & 0xaaaaaaaa) >> 1 );

	/* 	swap between every two pairs of two neighboring pair of bits  
		1010 1001 => 1010 0110 */
	res = ((res & 0x33333333) << 2 ) | ((res & 0xcccccccc) >> 2 );

	/* 	swap between every 4 neighboring bits  
		1010 0110 => 01100 1010*/
	res = ((res & 0x0f0f0f0f) << 4 ) | ((res & 0xf0f0f0f0) >> 4 );


	res = ((res & 0x00ff00ff) << 8 ) | ((res & 0xff00ff00) >> 8 );

	/* 	swap between every 16 neighboring bits */
	res = ((res & 0x0000ffff) << 16 ) | ((res & 0xffff0000) >> 16 );


	return res;
}


/******************************************************************************
	checks the bits 2, 6 if they are both on, it returns 1 ("true")
	(0010 0010 both of them)
******************************************************************************/
unsigned int IsBits2and6Set (unsigned char ch)
{
	return (((ch & 0x02) >> 1) & ((ch & 0x20) >> 5));
}



/******************************************************************************
	checks the bits 2, 6 if at least one of them is on, it returns 1 ("true")
	(0010 0010 at least one of them)
******************************************************************************/
unsigned int IsBits2or6Set (unsigned char ch)
{
	
	unsigned int second_bit = 1 << 1;
	unsigned int sixth_bit = 1 << 5;

	second_bit = second_bit & ch;
	sixth_bit = sixth_bit & ch;

	second_bit >>= 1;
	sixth_bit >>= 5;

	return (second_bit | sixth_bit);
}



/******************************************************************************
	swaps between bit 3 and bit 5 and returns the new number
******************************************************************************/
unsigned int SwapBit3and5 (unsigned char ch)
{
	return ( (ch & 0x04)<<2 |(ch & 0x10)>>2 | (ch & 0xeb) );
}



/******************************************************************************
	returns the closest (smaller) number that is devided by 16 
	without remainder.
******************************************************************************/
unsigned int ClosestDividerBy16 (unsigned int intput)
{
	return (intput & 0xfffffff0);
}



/******************************************************************************
	function that swaps 2 variables without using a third variable
******************************************************************************/
void SwapBitwise( unsigned int *num1, unsigned int *num2 )
{
	
	if ( num1 != num2 )
	{
		*num1 ^= *num2;
		*num2 ^= *num1;
		*num1 ^= *num2;
	}
}



/******************************************************************************
	returned the number of set bits in an integer
******************************************************************************/
unsigned int CountOnes(unsigned int num)
{

	unsigned int couter = 0;

	while( num )
	{
		if ( num & 1 )
		{
			++couter;
		}
		num >>= 1;

	}

	return couter;
}



/******************************************************************************
	count number of set bits in a 32-bit integer withough loop. 
	from the book "Hacker's Delight", p. 66, Figure 5-2	
******************************************************************************/
unsigned int TurnedBitsInInt(unsigned int x)
{
	x = x - ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x + (x >> 4)) & 0x0F0F0F0F;
	x = x + (x >> 8);
	x = x + (x >> 16);
	return x & 0x0000003F;
}



/******************************************************************************
	receives a float and prints its bits
******************************************************************************/
void PrintFloat(float num)
{
	unsigned int *int_ptr_to_float;
	unsigned int mask = 1 << (sizeof(float) * BITS_IN_BYTE - 1);

	/* seperate every 4 bits (nibble) by space */
	unsigned int print_spacing = 4;

	/* seperate the first bit (sign bit) by space */
	unsigned int first_digit_print_flag = 1;	
 
 
	int_ptr_to_float = (unsigned int *) &num;

	while ( mask )
	{
		if (*int_ptr_to_float & mask )
		{
			printf("1");
		}
		else
		{
			printf("0");
		}

		if ( first_digit_print_flag )
		{
			printf(" ");
			--first_digit_print_flag;
		}

		if ( 0 == print_spacing )
		{
			printf(" ");
			print_spacing = 4;
		}
		--print_spacing;

		mask >>= 1;
	}

}



/* used throughout the program to print out the binary value of unsigned int */
void PrintBinary(unsigned int num)
{
	unsigned int shift = 1;
	unsigned int spacing = 4;

	/* shift == 1000 0000 0000 0000 0000 0000 0000 0000 */
	shift <<= ( sizeof(num) * BITES_IN_BYTE - 1 );

	printf("\n%11u (DEC): ", num);

	while( shift )
	{

		if( num & shift )
		{
			printf("1");
		}
		else
		{
			printf("0");
		}

		--spacing;
		if ( 0 == spacing )
		{
			printf(" ");
			spacing = 4;
		}
		

		shift = shift >> 1;
	}

	printf(" (Binary)");
}


/* used throughout the program to print out the binary value of unsigned char */
void PrintBinaryChar(unsigned char ch)
{
	/* shift == 1000 0000  */
	unsigned int shift = 1;
	unsigned int spacing = 4;

	shift <<= ( sizeof(ch) * BITES_IN_BYTE - 1 );

	printf("\n%11u (DEC): %3c (Char): ", ch, ch);

	while( shift )
	{

		if( ch & shift )
		{
			printf("1");
		}
		else
		{
			printf("0");
		}

		--spacing;
		if ( 0 == spacing )
		{
			printf(" ");
			spacing = 4;
		}
		

		shift = shift >> 1;
	}

	printf(" (Binary)");
}


