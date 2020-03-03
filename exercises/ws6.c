/* Author: Alex B
** Last update: 31.08.17 21:00
** Program:	Worksheet6 - Bitwise operations
*/

#include <stdio.h>	/* printf */
#include "bits.h"	/* my string library */

#define BITES_IN_BYTE 8 /* number of bits in one byte*/


#define PRINT_IN_GREEN 	"\x1b[32m"
#define PRINT_IN_RED 	"\x1b[31m"
#define PRINT_IN_YELLOW "\x1b[93m"
#define PRINT_CO_RESET 	"\x1b[0m"


/* tests functions declarations */
void Testpow2();
void TestIsPowerOfTwo();
void TestIsPowerOfTwoNoLoop();
void TestPrintIntsWith3OnesFromArr();
void TestByteMirror();
void TestIsBits2and6Set();
void TestIsBits2or6Set();
void TestSwapBit3and5();
void TestClosestDividerBy16();
void TestSwapBitwise();
void TestByteMirrorNoLoop();


/* auxiliary function for the tests functions */
void PrintBottomHeader(char *function_name);
void PrintHeader(char *function_name);


int main(int argc, char const *argv[])
{

	/* Tests functions */
	Testpow2();
	TestIsPowerOfTwo();
	TestIsPowerOfTwoNoLoop();
	TestPrintIntsWith3OnesFromArr();
	TestByteMirror();
	TestIsBits2and6Set();
	TestIsBits2or6Set();
	TestSwapBit3and5();
	TestClosestDividerBy16();
	TestSwapBitwise();
	TestByteMirrorNoLoop();


	printf("\n");
	return 0;
}



/******************************************************************************
	auxiliary function for the tests functions. simply prints colorful header 
	with function name that we test 
******************************************************************************/
void PrintHeader(char *function_name)
{
	printf (PRINT_IN_YELLOW
			"\n\t-----This is a test for %s function-----\n"
			PRINT_CO_RESET, function_name);
}

/******************************************************************************
	auxiliary function for the tests functions. simply prints colorful 
	bottom header with function name that we test 
******************************************************************************/
void PrintBottomHeader(char *function_name)
{
	printf (PRINT_IN_YELLOW
			"\n\n\t-----end of test for %s function-----\n"
			PRINT_CO_RESET, function_name);
}


/******************************************************************************
	Tests functions for My Bitwise functions
******************************************************************************/
void Testpow2()
{
	unsigned int multiplyer = 0;
	int power_of_two = 0;


	PrintHeader("pow2");

	multiplyer = 2;
	power_of_two = -4;
	printf("\n\tpow2(%d,%d) = %f"
		, multiplyer, power_of_two ,pow2(multiplyer, power_of_two));

	multiplyer = 2;
	power_of_two = 2;
	printf("\n\tpow2(%d,%d) = %f"
		, multiplyer, power_of_two ,pow2(multiplyer, power_of_two));

	multiplyer = 1;
	power_of_two = -7;
	printf("\n\tpow2(%d,%d) = %f"
		, multiplyer, power_of_two ,pow2(multiplyer, power_of_two));


	PrintBottomHeader("pow2");

}

/********************************TestIsPowerOfTwo******************************/
void TestIsPowerOfTwo()
{
	unsigned int var = 4;

	PrintHeader("IsPowerOfTwoNoLoop");

	var = 4;
	printf(	"\tIs %d power of two? - %s\n"
			, var, IsPowerOfTwo(var) ? "yes" : "no");

	var = 1234;
	printf(	"\tIs %d power of two? - %s\n", var
			, IsPowerOfTwo(var) ? "yes" : "no");

	var = 1024;
	printf(	"\tIs %d power of two? - %s\n"
			, var, IsPowerOfTwo(var) ? "yes" : "no");

	var = 1354312;
	printf(	"\tIs %d power of two? - %s\n"
			, var, IsPowerOfTwo(var) ? "yes" : "no");

	PrintBottomHeader("IsPowerOfTwo");
}

/********************************TestIsPowerOfTwoNoLoop************************/
void TestIsPowerOfTwoNoLoop()
{
	unsigned int var = 4;

	PrintHeader("IsPowerOfTwoNoLoop");

	var = 4;
	printf(	"\tIs %d power of two? - %s\n"
			, var, IsPowerOfTwoNoLoop(var) ? "yes" : "no");

	var = 1234;
	printf(	"\tIs %d power of two? - %s\n"
			, var, IsPowerOfTwoNoLoop(var) ? "yes" : "no");

	var = 1024;
	printf(	"\tIs %d power of two? - %s\n"
			, var, IsPowerOfTwoNoLoop(var) ? "yes" : "no");

	var = 1354312;
	printf(	"\tIs %d power of two? - %s\n"
			, var, IsPowerOfTwoNoLoop(var) ? "yes" : "no");


	PrintBottomHeader("IsPowerOfTwoNoLoop");
}

/********************************TestPrintIntsWith3OnesFromArr*****************/
void TestPrintIntsWith3OnesFromArr()
{
	unsigned int arr[] = { 3, 7, 11, 23, 15, 0x0111, 13 };

	PrintHeader("PrintIntsWith3OnesFromArr");

	PrintIntsWith3OnesFromArr(arr, sizeof(arr)/sizeof(unsigned int) );

	PrintBottomHeader("PrintIntsWith3OnesFromArr");
}

/********************************TestByteMirror********************************/
void TestByteMirror()
{
	unsigned int var = 0xf0f0f0f0;

	PrintHeader("ByteMirror");

	printf("\nBefore ByteMirror:");
	PrintBinary(var);

	var = ByteMirror(var);
	printf("\nAfter ByteMirror:");
	PrintBinary(var);

	printf("\n");


	var = 0x0000000a;
	printf("\nBefore ByteMirror:");
	PrintBinary(var);

	var = ByteMirror(var);
	printf("\nAfter ByteMirror:");
	PrintBinary(var);

	printf("\n");


	var = 0xaaaaaaaa;
	printf("\nBefore ByteMirror:");
	PrintBinary(var);

	var = ByteMirror(var);
	printf("\nAfter ByteMirror:");
	PrintBinary(var);

	PrintBottomHeader("ByteMirror");
}

/********************************ByteMirrorNoLoop******************************/
void TestByteMirrorNoLoop()
{
	unsigned int var = 0xf0f0f0f0;

	PrintHeader("ByteMirrorNoLoop");

	printf("\nBefore ByteMirrorNoLoop:");
	PrintBinary(var);

	var = ByteMirrorNoLoop(var);
	printf("\nAfter ByteMirrorNoLoop:");
	PrintBinary(var);

	printf("\n");

	var = 0x0000000a;
	printf("\nBefore ByteMirrorNoLoop:");
	PrintBinary(var);

	var = ByteMirrorNoLoop(var);
	printf("\nAfter ByteMirrorNoLoop:");
	PrintBinary(var);

	printf("\n");

	var = 0x0000000f;
	printf("\nBefore ByteMirrorNoLoop:");
	PrintBinary(var);

	var = ByteMirrorNoLoop(var);
	printf("\nAfter ByteMirrorNoLoop:");
	PrintBinary(var);

	PrintBottomHeader("ByteMirrorNoLoop");

}

/********************************TestCharFunction1*****************************/
void TestIsBits2and6Set()
{
	unsigned int var = '0';
	unsigned int res = 0;

	PrintHeader("IsBits2and6Set");

	var = 'a';
	PrintBinaryChar(var);
	res = IsBits2and6Set(var);
	if ( 1 == res  )
	{
		printf("\n\t\t- bits 2, 6 are both on");
	}
	else
	{
		printf("\n\t\t- bits 2, 6 are NOT both on");
	}

	printf("\n");
	var = 0x22;
	PrintBinaryChar(var);
	res = IsBits2and6Set(var);
	if ( 1 == res  )
	{
		printf("\n\t\t- bits 2, 6 are both on");
	}
	else
	{
		printf("\n\t\t- bits 2, 6 are NOT both on");
	}


	printf("\n");
	var = 0xdd;
	PrintBinaryChar(var);
	res = IsBits2and6Set(var);
	if ( 1 == res  )
	{
		printf("\n\t\t- bits 2, 6 are both on");
	}
	else
	{
		printf("\n\t\t- bits 2, 6 are NOT both on");
	}


	printf("\n");
	var = 0x3f;
	PrintBinaryChar(var);
	res = IsBits2and6Set(var);
	if ( 1 == res  )
	{
		printf("\n\t\t- bits 2, 6 are both on");
	}
	else
	{
		printf("\n\t\t- bits 2, 6 are NOT both on");
	}


	PrintBottomHeader("IsBits2and6Set");
}

/********************************TestCharFunction2*****************************/
void TestIsBits2or6Set()
{
	unsigned int var = '0';
	unsigned int res = 0;

	PrintHeader("IsBits2or6Set");

	var = 'a';
	PrintBinaryChar(var);
	res = IsBits2or6Set(var);
	if ( 1 == res  )
	{
		printf("\n\t\t- at least one of bits 2, 6 is on - TRUE");
	}
	else
	{
		printf("\n\t\t- at least one of bits 2, 6 is on - FALSE");
	}

	printf("\n");
	var = 0x22;
	PrintBinaryChar(var);
	res = IsBits2or6Set(var);
	if ( 1 == res  )
	{
		printf("\n\t\t- at least one of bits 2, 6 is on - TRUE");
	}
	else
	{
		printf("\n\t\t- at least one of bits 2, 6 is on - FALSE");
	}


	printf("\n");
	var = 0xdd;
	PrintBinaryChar(var);
	res = IsBits2or6Set(var);
	if ( 1 == res  )
	{
		printf("\n\t\t- at least one of bits 2, 6 is on - TRUE");
	}
	else
	{
		printf("\n\t\t- at least one of bits 2, 6 is on - FALSE");
	}


	printf("\n");
	var = 0x3f;
	PrintBinaryChar(var);
	res = IsBits2or6Set(var);
	if ( 1 == res  )
	{
		printf("\n\t\t- at least one of bits 2, 6 is on - TRUE");
	}
	else
	{
		printf("\n\t\t- at least one of bits 2, 6 is on - FALSE");
	}


	PrintBottomHeader("IsBits2or6Set");
}

/********************************TestCharFunction3*****************************/
void TestSwapBit3and5()
{
	unsigned int var = 0xe4;


	PrintHeader("SwapBit3and5");


	printf("\nBefore SwapBit3and5:");
	PrintBinaryChar(var);
	var = SwapBit3and5(var);
	printf("\nAfter SwapBit3and5:");
	PrintBinaryChar(var);

	printf("\n");
	var = 0x1b;
	printf("\nBefore SwapBit3and5:");
	PrintBinaryChar(var);
	var = SwapBit3and5(var);
	printf("\nAfter SwapBit3and5:");
	PrintBinaryChar(var);


	printf("\n");
	var = 'z';
	printf("\nBefore SwapBit3and5:");
	PrintBinaryChar(var);
	var = SwapBit3and5(var);
	printf("\nAfter SwapBit3and5:");
	PrintBinaryChar(var);


	PrintBottomHeader("SwapBit3and5");
}

/********************************TestClosestDividerBy16************************/
void TestClosestDividerBy16()
{
	unsigned int var = 0;
	PrintHeader("ClosestDividerBy16");

	var = 26;
	printf(	"\nThe closest divider by 16 to %u is %d."
			, var, ClosestDividerBy16(var) );

	var = 52;
	printf(	"\nThe closest divider by 16 to %u is %d."
			, var, ClosestDividerBy16(var) );

	var = 154;
	printf(	"\nThe closest divider by 16 to %u is %d."
			, var, ClosestDividerBy16(var) );

	var = 215464;
	printf(	"\nThe closest divider by 16 to %u is %d."
			, var, ClosestDividerBy16(var) );


	PrintBottomHeader("ClosestDividerBy16");
}

/********************************TestSwapBitwise*******************************/
void TestSwapBitwise()
{
	unsigned int var1 = 0xf0f0f0f0;
	unsigned int var2 = 0x0f0f0f0f;

	PrintHeader("SwapBitwise");



	printf("\nBefore SwapBitwise:");
	PrintBinary(var1);
	PrintBinary(var2);

	printf("\n");

	SwapBitwise(&var1, &var2);
	printf("\nAfter SwapBitwisvncose:");
	PrintBinary(var1);
	PrintBinary(var2);

	printf("\n\n");


	var1 = 0xaaaaaaaa;
	var2 = 0x00000666;

	printf("\nBefore SwapBitwise:");
	PrintBinary(var1);
	PrintBinary(var2);

	printf("\n");

	SwapBitwise(&var1, &var2);
	printf("\nAfter SwapBitwisvncose:");
	PrintBinary(var1);
	PrintBinary(var2);

	printf("\n\n");

	PrintBottomHeader("SwapBitwise");
}





