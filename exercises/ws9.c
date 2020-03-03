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

#define PRINT_IN_GREEN 	"\x1b[32m"
#define PRINT_IN_RED 	"\x1b[31m"
#define PRINT_IN_YELLOW "\x1b[93m"
#define PRINT_CO_RESET 	"\x1b[0m"

#define IS_LITTLE_ENDIAN (*(size_t*)"\0\x2" == 0x200)


/*****************************************************************************
** DESCRIPTION: checks wheather the system is Little Endian
**
** RETURNS: 1 - the system is Little Endian
**			0 - the system is Big Endian
**
** NOTES: acts like a boolean function
******************************************************************************/
int IsLittleEndian(void)
{
	int var = 0x90AB12CD;
	char *char_ptr = (char*)&var;

	if ( (char)0xcd == *char_ptr )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*****************************************************************************
** DESCRIPTION: Converts an integer value to a null-terminated string using
**				the specified base and stores the result in the array given
**				by str parameter.
**
** RETURNS: pointer to the resulting null-terminated string,
**			same as parameter str.
**
** NOTES: str should be an array long enough to contain any possible value
******************************************************************************/
char *MyItoa(int int_number, char * string_number, int base);


/*****************************************************************************
** DESCRIPTION: converts the string argument str to an integer (type int)
**
** RETURNS: the converted integral number as an int value.
**			0 - if no valid conversion could be performed
** NOTES:
******************************************************************************/
int StringToInt(const char *str_number);


/*****************************************************************************
** DESCRIPTION: prints the letters that appear in both 2 arrays,
**				but doesn't appear in third array.
** RETURNS:
**
** NOTES: doesn't print the same characters more than once.
**		  traverse each array exactly once
******************************************************************************/
void PrintExistIn2Not3rd(const char *arr1, const char *arr2, const char *arr3);


/* tests functions */
void TestMymemset();
void TestMymemcpy();
void TestIsLittleEndian();
void TestMyItoa();
void TesStringToInt();
void TestPrintExistIn2Not3rd();
void TestMymemmove();


/* aid functions */
void CompareAndPrint(int func_result, int ex_result);
void PrintHeader(char *function_name);
void PrintBottomHeader(char *function_name);
void PrintHexNibbles(void *ptr, size_t num);


int main(int argc, char const *argv[])
{

	TestIsLittleEndian();
	TesStringToInt();
	TestMyItoa();
	TestMymemset();
	TestMymemcpy();
	TestMymemmove();
	TestIsLittleEndian();
	TestPrintExistIn2Not3rd();

	return 0;
}




/*****************************************************************************
	TEST FUNCTION - tests Mymemset function
******************************************************************************/
void TestMymemset()
{
	int result = 0;

	char arr1[20] = { 0 };
	char arr2[20] = { 0 };

	int arr3[10] = { 0 };
	int arr4[10] = { 0 };

	long arr5[10] = { 0 };
	long arr6[10] = { 0 };

	PrintHeader("Mymemset");

	printf("Mymemset for char variables");
	Mymemset(arr1, 0x3b, 11);
	memset(arr2, 0x3b, 11);
	result = memcmp(arr1, arr2, 11);
	CompareAndPrint(result, 0);


	printf("Mymemset for int variables");
	Mymemset(arr3, 0xf5, 18);
	memset(arr4, 0xf5, 18);
	result = memcmp(arr3, arr4, 18);
	CompareAndPrint(result, 0);


	printf("Mymemset for long variables");
	Mymemset(arr5, 0xab, 25);
	memset(arr6, 0xab, 25);
	result = memcmp(arr5, arr6, 25);
	CompareAndPrint(result, 0);

	PrintBottomHeader("Mymemset");
	printf("\n");
}


/*****************************************************************************
	TEST FUNCTION - tests Mymemcpy function
******************************************************************************/
void TestMymemcpy()
{
	int result = 0;

	char  char_arr_src[35] = "0123456789 0123456789 0123456789";
	char  char_arr_des1[35] = { 0 };
	char  char_arr_des2[35] = { 0 };

	int  int_arr_src[20] = { 0xaabbccff, 0xaaffaaff, 0x11223344,
		0xff00ff00, 0xaabbaabb };
	int  int_arr_des1[20] = { 0 };
	int  int_arr_des2[20] = { 0 };

	long  long_arr_src[20] = { 0x1122334455667788, 0x99aabbccddff1100,
		0xcccccccccccccccc, 0x0f0f0f0f0f0f0f0f, 0xca };
	long  long_arr_des1[20] = { 0 };
	long  long_arr_des2[20] = { 0 };

	PrintHeader("Mymemcpy");

	printf("Mymemcpy for char variables:");
	Mymemcpy(char_arr_des1, char_arr_src, 17);
	memcpy(char_arr_des2, char_arr_src, 17);
	result = memcmp(char_arr_des2, char_arr_des1, 17);
	CompareAndPrint(result, 0);


	printf("Mymemcpy for int variables");
	Mymemcpy(int_arr_des1, int_arr_src, 17);
	memcpy(int_arr_des2, int_arr_src, 17);
	result = memcmp(int_arr_des1, int_arr_des2, 17);
	CompareAndPrint(result, 0);


	printf("Mymemcpy for long variables");
	Mymemcpy(long_arr_des1, long_arr_src, 17);
	memcpy(long_arr_des2, long_arr_src, 17);
	result = memcmp(long_arr_des1, long_arr_des2, 17);
	CompareAndPrint(result, 0);

	PrintBottomHeader("Mymemcpy");
	printf("\n");
}


/*****************************************************************************
	AID FUNCTION - aided in checking of Mymemset, Mymemcpy functions
******************************************************************************/
void PrintHexNibbles(void *ptr, size_t num)
{
	int *mask = (int*)ptr;

	size_t num_of_loops = 0;

	while (1)
	{
		if (num > 4)
		{
			num -= 4;
			++num_of_loops;
		}
		else
		{
			++num_of_loops;
			break;
		}
	}


	while (num_of_loops)
	{
		printf("%X ", *mask);
		--num_of_loops;
		++mask;
	}

	printf("\n");
}


/*******************************************************************************
	FUNCTION that compares between the two inputes and prints accordingly
*******************************************************************************/
void CompareAndPrint(int func_result, int ex_result)
{

	if (func_result == ex_result)
	{
		printf(PRINT_IN_GREEN "\t--> CORRECT" PRINT_CO_RESET "\n");
	}
	else
	{
		printf(PRINT_IN_RED "\t--> INCORRECT" PRINT_CO_RESET "\n");
	}
}


/******************************************************************************
	auxiliary function for the tests functions. simply prints colorful header
	with function name that we test
******************************************************************************/
void PrintHeader(char *function_name)
{
	printf(PRINT_IN_YELLOW
		"\n\t-----This is a test for %s function-----\n"
		PRINT_CO_RESET, function_name);
}


/******************************************************************************
	auxiliary function for the tests functions. simply prints colorful
	bottom header with function name that we test
******************************************************************************/
void PrintBottomHeader(char *function_name)
{
	printf(PRINT_IN_YELLOW
		"\n\t-----end of test for %s function-----\n"
		PRINT_CO_RESET, function_name);
}


/*****************************************************************************
	TEST FUNCTION - tests IsLittleEndian function
******************************************************************************/
void TestIsLittleEndian(void)
{
	int result = 0;

	PrintHeader("IsLittleEndian");

	result = IsLittleEndian();
	printf(	"Function result. The system %s", 
			result ? "Is Little Endian" : "Is BIG Endian");
	CompareAndPrint(result, 1);

	result = IS_LITTLE_ENDIAN;
	printf(	"MACRO result.    The system %s",
			result ? "Is Little Endian" : "Is BIG Endian");
	CompareAndPrint(result, 1);

	PrintBottomHeader("IsLittleEndian");
	printf("\n");
}


/*****************************************************************************
	TEST FUNCTION - tests MyItoa function
******************************************************************************/
void TestMyItoa()
{
	int  result = 0;
	int  int_number = 123456789;
	char str_number[20];

	PrintHeader("MyItoa");

	MyItoa(int_number, str_number, 10);
	printf("Int |%d|\t string |%s|", int_number, str_number);
	result = strcmp(str_number, "123456789");
	CompareAndPrint(result, 0);



	int_number = -123;
	MyItoa(int_number, str_number, 10);
	printf("Int |%d|\t string |%s|", int_number, str_number);
	result = strcmp(str_number, "-123");
	CompareAndPrint(result, 0);



	int_number = 2603;
	MyItoa(int_number, str_number, 10);
	printf("Int |%d|\t string |%s|", int_number, str_number);
	result = strcmp(str_number, "2603");
	CompareAndPrint(result, 0);


	int_number = 2603;
	MyItoa(int_number, str_number, 16);
	printf("Int |%d|\t string |%s|", int_number, str_number);
	result = strcmp(str_number, "a2b");
	CompareAndPrint(result, 0);


	int_number = 2603;
	MyItoa(int_number, str_number, 2);
	printf("Int |%d|\t string |%s|", int_number, str_number);
	result = strcmp(str_number, "101000101011");
	CompareAndPrint(result, 0);


	PrintBottomHeader("MyItoa");
	printf("\n");
}


/*****************************************************************************
	Converts an integer value to a null-terminated string using the
	specified base and stores the result in the array given by 
	string_number parameter.
******************************************************************************/
char *MyItoa(int int_number, char * string_number, int base)
{
	int positive_int_num = int_number;
	size_t num_of_digits = 0;
	size_t single_digit = 0;
	int sign = 0;	/* 0 - positive, 1 - Negative */


	/* if negative number unpdate sign and make number positive */
	if (int_number < 0)
	{
		sign = 1;
		int_number *= (-1);
		positive_int_num = int_number;
	}

 	/* count number of required digits according to base */
	while (int_number)
	{
		++num_of_digits;
		int_number /= base;
	}
	string_number[num_of_digits + sign] = '\0'; /* setting end of string */


	/* transfer the number to string of required base */
	while (num_of_digits)
	{
		single_digit = (positive_int_num % base);

		if (single_digit > 9) /* to handle base 16 */
		{
			single_digit += 'a' - '0' - 10;
		}

		string_number[num_of_digits + sign - 1] = single_digit + '0';

		positive_int_num /= base;
		--num_of_digits;
	}


	/* in case original int is negative */
	if (1 == sign) 
	{
		string_number[num_of_digits] = '-';
	}

	return string_number;
}


/******************************************************************************
	TEST FUNCTION - tests StringToInt function
******************************************************************************/
void TesStringToInt()
{
	char str_number[20];
	int  int_number = 0;


	PrintHeader("StringToInt");

	strcpy(str_number, "123");
	int_number = StringToInt(str_number);
	printf("string |%s|\t Int |%d|", str_number, int_number);
	CompareAndPrint(int_number, 123);


	strcpy(str_number, "-123");
	int_number = StringToInt(str_number);
	printf("string |%s|\t Int |%d|", str_number, int_number);
	CompareAndPrint(int_number, -123);


	strcpy(str_number, "+123456789");
	int_number = StringToInt(str_number);
	printf("string |%s|\t Int |%d|", str_number, int_number);
	CompareAndPrint(int_number, 123456789);

	PrintBottomHeader("StringToInt");
	printf("\n");
}


/******************************************************************************
	converts the string argument str_number to an integer (type int)
	returns 0 if no valid conversion could be performed
******************************************************************************/
int StringToInt(const char *str_number)
{
	int result_number = 0;
	char *current_str_place = (char*)str_number;

	char sign = 0; /* 0  - not given(assumed posotive),
				   'P' - positive, 'N' - Negative */

	assert(str_number != NULL);

	/* handles string that starts with '-' sign e.g "-123"*/
	if ('-' == *current_str_place)
	{
		sign = 'N';
		++current_str_place;
	}

	/* handles string that starts with '+' sign e.g "+123"*/
	if ('+' == *current_str_place)
	{
		sign = 'P';
		++current_str_place;
	}

	/* converts string to int */
	while (*current_str_place != '\0')
	{

		if (!isdigit(*current_str_place))
		{
			/* in case string contains non digit values */
			printf("Given string number contained non digits !\n");
			return 0;
		}

		result_number *= 10;

		result_number += *current_str_place - '0';

		++current_str_place;
	}


	/* if string started with '-' sign, make number negative*/
	if ('N' == sign)
	{
		result_number = (~result_number) + 1;
	}

	return result_number;
}


/******************************************************************************
	TEST FUNCTION - tests Mymemmove function
******************************************************************************/
void TestMymemmove()
{
	int result = 0;

	char str1[] = "memmove can be very useful......";
	char str2[] = "memmove can be very useful......";

	char str3[] = "00__88oo";
	char str4[] = "00__88oo";

	char str5[] = "00__88oo";
	char str6[] = "00__88oo";

	PrintHeader("Mymemmove");

	memmove(str1 + 20, str1 + 15, 11);
	Mymemmove(str2 + 20, str2 + 15, 11);
	printf("\n\n  memmove:  %s", str1);
	printf("\nMymemmove:  %s", str2);
	result = strcmp(str1, str2);
	CompareAndPrint(result, 0);

	/* testing the case 1 when source might overwrite destination */
	memmove(str3 + 3, str3 + 1, 3);
	Mymemmove(str4 + 3, str4 + 1, 3);
	printf("\n\n  memmove:  %s\n", str3);
	printf("Mymemmove:  %s", str4);
	result = strcmp(str3, str4);
	CompareAndPrint(result, 0);

	/* testing the case 2 when source might overwrite destination */
	memmove(str5 + 1, str5 + 3, 3);
	Mymemmove(str6 + 1, str6 + 3, 3);
	printf("\n\n  memmove:  %s\n", str5);
	printf("Mymemmove:  %s", str6);
	result = strcmp(str5, str6);
	CompareAndPrint(result, 0);

	PrintBottomHeader("Mymemmove");
}


/******************************************************************************
	TEST FUNCTION - tests PrintExistIn2Not3rd function
******************************************************************************/
void TestPrintExistIn2Not3rd()
{
	char arr1[] = "abcd1234";
	char arr2[] = "AbCd1034";
	char arr3[] = "000d0030";

	PrintExistIn2Not3rd(arr1, arr2, arr3);
}


/******************************************************************************
	AID FUNCTION - aided in checking of PrintExistIn2Not3rd function
******************************************************************************/
void PrintCharArr(char* arr, int members)
{
	int i = 0;

	printf("print starts here:\n");

	while( i < members )
	{
		printf("%d - %d\n", i, (int)arr[i]);
		++i;
	}
}


/******************************************************************************
	prints the letters that appear in both 2 arrays,
	but doesn't appear in third array.
******************************************************************************/
void PrintExistIn2Not3rd(const char *arr1, const char *arr2, const char *arr3)
{
	long i = 0;
	char arr_of_possible_values[256] = { 0 };

	/*  while traversing arr1 once,
		update arr_of_possible_values in index *arr1 to one */
	while (*arr1 != '\0')
	{
		arr_of_possible_values[(size_t)*arr1] = 1;
		++arr1;
	}

	/*  while traversing arr2 once,
		add one to arr_of_possible_values in index *arr2 */
	while (*arr2 != '\0')
	{
		arr_of_possible_values[(size_t)*arr2] += 1;
		++arr2;
	}

	/*  while traversing arr3 once,
		multiply by zero arr_of_possible_values in index *arr3 */
	while (*arr3 != '\0')
	{
		arr_of_possible_values[(size_t)*arr3] *= 0;
		++arr3;
	}

	/* go threw arr_of_possible_values */
	while (i < 256)
	{
		/* if value at index i greater than one the value will be printed */
		if (arr_of_possible_values[i] > 1)
		{
			printf("%c ", (char)i);
		}
		++i;
	}
	printf("\n");
}