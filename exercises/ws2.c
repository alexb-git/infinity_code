/* Made by Alex Budie 22.08.17 */

#include <stdio.h>		/* printf, scanf */
#include <string.h> 	/* strlen */
#include <strings.h> 	/* strcasecmp */
#include <ctype.h> 		/* tolower */
#include <assert.h>		/* asssert function */
#include <stdlib.h>		/* malloc */

#include "ws2_STRINGS.h" /* my string library */



/* function that checks if a string is a polindrome */
int IsPalindrome(const char *str);

/* recieves a range. prints all numbers in the range exept numbers that 
   have "7" or devided by "7" with no remainder, instead print "BOOM" */
void SevenBOOM (unsigned int beginning, unsigned int end);

/* 	cleans white spaces from the string, and cleans up white spaces when there 
	is more than one white space in the middle of the string */
void RmSpaces(char *str);

/* 	function that swaps two (int) pointers  */
void SwapIntPtrs (int **a, int **b);

/* 	returns result of addition operation on a very big positive numbers */
char* AddLargeNumbers (const char *num1, const char *num2);



/* MY TEST FUNCTIONS */
void TestIsPalindrome();
void TestRmSpaces();
void TestSwapIntPtrs ();
void TestAddLargNumbers();


/* MY TEST FUNCTIONS FOR STRINGS */
void TestMyStrlen();
void TestMyStrcmp();
void TestMyStrCaseCmp();
void TestMyStrcpy();
void TestMyStrNCpy();
void TestMyStrChr();
void TestMyStrDup();
void TestMyStrCat();
void TestMyStrNCat();
void TestMyStrStr();


/* sidekick functions - Prints CORRECT or INCORRECT in color*/
void CompareAndPrint (int func_result, int ex_result);


#define PRINT_IN_GREEN 	"\x1b[32m"
#define PRINT_IN_RED 	"\x1b[31m"
#define PRINT_IN_YELLOW "\x1b[93m"
#define PRINT_CO_RESET 	"\x1b[0m"


/*______________________________________________________________________________
	START OF MAIN FUNCTION
  ______________________________________________________________________________*/
int main()
{
	
	TestAddLargNumbers();
	

	
	/*------READY TESTS_------*/
	/*
	TestMyStrlen();
	TestMyStrcmp();
	TestMyStrCaseCmp();
	TestMyStrcpy();
	TestMyStrChr();
	TestMyStrStr();
	TestMyStrCat();
	TestIsPalindrome();
	SevenBOOM(1, 100);
	TestMyStrNCpy();
	TestMyStrNCat();
	TestMyStrDup();
	TestRmSpaces();
	TestSwapIntPtrs();
	TestSwapIntPtrs();
	*/
	/*------END OF TESTS_------*/
	

	return 0;
}




/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  ++++++++++++++++++++++++START TESTS FUNCTIONS FOR STRINGS++++++++++++++++++++++++
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*******************************************************************************
	FUNCTION that compares between the two inputes and prints accordingly
*******************************************************************************/
void CompareAndPrint (int func_result, int ex_result)
{

	if (func_result == ex_result)
	{	
		printf(PRINT_IN_GREEN "\t--> CORRECT" PRINT_CO_RESET "\n\n");				
	}
	else
	{
		printf(PRINT_IN_RED "\t--> INCORRECT" PRINT_CO_RESET "\n\n");
	}
}


/*********************************************************************************
	This FUNCTION will compare between MyStrlen and strlen in string.h library
**********************************************************************************/
void TestMyStrlen()
{
	int i;	

	char *string2test[] = {	"Hello", "World", "Hi", "1231hi", 
							"long ago in a galaxy far far away", "" };

	int n_array = (sizeof (string2test) / sizeof (char *));
	

	printf (PRINT_IN_YELLOW
			"\nThis test will compare between MyStrlen and strlen in string.h library\n\n"
			PRINT_CO_RESET);

	for ( i = 0 ; i < n_array ; i++)
	{
		size_t 	MyStrlen_output = MyStrlen(string2test[i]); 
		size_t 	strlen_output = strlen(string2test[i]);

		printf("Iput:\t\"%s\" \nMyStrlen output: %d \nstrlen output:\t %d",
						string2test[i],	(int)MyStrlen_output,(int)strlen_output);

		CompareAndPrint (MyStrlen_output, strlen_output);

	}

	printf(PRINT_IN_YELLOW
		"------------------------ end of MyStrlen test ------------------------\n"
		PRINT_CO_RESET);

}


/*********************************************************************************
	This FUNCTION will compare between MyStrcmp and strcmp in string.h library
**********************************************************************************/
void TestMyStrcmp()
{
	int i;	

	char *string2test1[] = {	"Helloa", "World", "Hi", "1231h", 
								"long ago in a galaxy far far away", "" };

	char *string2test2[] = {	"Hello", "World", "Hi", "1231hi", 
								"long ago in a galaxy  far far away", "" };

	int n_array = (sizeof (string2test1) / sizeof (char *));
	

	printf (PRINT_IN_YELLOW
			"\nThis test will compare between MyStrcmp and strcmp in string.h library\n\n"
			PRINT_CO_RESET);

	for ( i = 0 ; i < n_array ; i++)
	{
		int 	my_func_output = MyStrcmp(string2test1[i], string2test2[i]); 
		int 	library_output = strcmp(string2test1[i], string2test2[i]);

		printf("Iput:\t{\"%s\", \"%s\"} \nTestMyStrcmp output: %d \nstrcmp output:\t %d",
					string2test1[i], string2test2[i], (int)my_func_output,(int)library_output);

		CompareAndPrint (my_func_output, library_output);

	}

	printf(	PRINT_IN_YELLOW
			"------------------------ end of MyStrcmp test ------------------------\n"
			PRINT_CO_RESET);
}


/*************************************************************************************
	This FUNCTION will compare between MyStrcasecmp and strcasecmp in string.h library
**************************************************************************************/
void TestMyStrCaseCmp()
{
	int i;	

	char *string2test1[] = {	"Helloa", "World", "", "01a", "A", "A",
								"long ago in a galaxy far far away" };

	char *string2test2[] = {	"Hello", "WORLD", "", "012", "a", "b",
								"LONG AGO IN A GALAXY FAR FAR AWAY" };

	int n_array = (sizeof (string2test1) / sizeof (char *));
	

	printf (PRINT_IN_YELLOW
			"\nThis test will compare between MyStrcasecmp and strcasecmp in string.h library\n\n"
			PRINT_CO_RESET);

	for ( i = 0 ; i < n_array ; i++)
	{
		int 	my_func_output = MyStrCaseCmp(string2test1[i], string2test2[i]); 
		int 	library_output = strcasecmp(string2test1[i], string2test2[i]);

		printf("Iput:\t{\"%s\", \"%s\"} \nMyStrlen output: %d \nstrlen output:\t %d",
					string2test1[i], string2test2[i], (int)my_func_output,(int)library_output);

		CompareAndPrint (my_func_output, library_output);

	}

	printf(	PRINT_IN_YELLOW
			"------------------------ end of MyStrCaseCmp test ------------------------\n"
			PRINT_CO_RESET);
}


/*************************************************************************************
	This FUNCTION will compare between MyStrcpy and strcpy in string.h library
**************************************************************************************/
void TestMyStrcpy ()
{
	char str1[40];
	char str2[40];
	char str3[40];
	char str4[40];

	printf (PRINT_IN_YELLOW
			"\nThis test will compare between MyStrcpy and strcpy in string.h library\n\n"
			PRINT_CO_RESET);



	/* INPUT "string in str1 char array." */
	MyStrcpy(str1, "some kind of string");
	MyStrcpy(str2, str1);
	strcpy(str3, "some kind of string");
	strcpy (str4, str3);

	printf("MyStrcpy output:   \"%s\"\n", str2);
	printf("strcpy output:     \"%s\"",   str3);
	CompareAndPrint (MyStrcmp(str2, str3), 0);



	/* INPUT "" */
	MyStrcpy(str1, "");
	MyStrcpy(str2, str1);
	strcpy(str3, "");
	strcpy (str4, str3);

	printf("MyStrcpy output:   \"%s\"\n", str2);
	printf("strcpy output:     \"%s\"",   str3);
	CompareAndPrint (MyStrcmp(str2, str3), 0);



	/* INPUT "12345679" */
	MyStrcpy(str1, "12345679");
	MyStrcpy(str2, str1);
	strcpy(str3, "12345679");
	strcpy (str4, str3);

	printf("MyStrcpy output:   \"%s\"\n", str2);
	printf("strcpy output:     \"%s\"",   str3);
	CompareAndPrint (MyStrcmp(str2, str3), 0);



	/* INPUT "12345679" */
	MyStrcpy(str3, str3);
	strcpy(str3, str3);

	printf("MyStrcpy output:   \"%s\"\n", str2);
	printf("strcpy output:     \"%s\"",   str3);
	CompareAndPrint (MyStrcmp(str2, str3), 0);



	printf(	PRINT_IN_YELLOW
			"------------------------ end of TestMyStrcpy test ------------------------\n"
			PRINT_CO_RESET);
}


/*************************************************************************************
	This FUNCTION will compare between MyStrNCpy and strncpy in string.h library
**************************************************************************************/
void TestMyStrNCpy ()
{
	char str1[40] = "some kind of string";
	char str2[40] = {0};
	char str3[40] = {0};

	printf (PRINT_IN_YELLOW
			"\nThis test will compare between MyStrNCpy and strncpy in string.h library\n\n"
			PRINT_CO_RESET);


	/* first test */
	MyStrNCpy(str2, str1, 6);
	strncpy(str3, str1, 6);

	printf("MyStrNCpy output:   \"%s\"\n", str2);
	printf("strncpy output:     \"%s\"",   str3);
	CompareAndPrint (MyStrcmp(str2, str3), 0);



	/* second test */
	MyStrNCpy(str2, str1, 0);
	strncpy(str3, str1, 0);

	printf("MyStrNCpy output:   \"%s\"\n", str2);
	printf("strncpy output:     \"%s\"",   str3);
	CompareAndPrint (MyStrcmp(str2, str3), 0);



	/* thired test" */
	MyStrNCpy(str2, str1, 20);
	strncpy(str3, str1, 20);

	printf("MyStrNCpy output:   \"%s\"\n", str2);
	printf("strncpy output:     \"%s\"",   str3);
	
	CompareAndPrint (MyStrcmp(str2, str3), 0);



	/*forth test*/
	MyStrNCpy(str2, str1, 1);
	strncpy(str3, str1, 1);

	printf("MyStrNCpy output:   \"%s\"\n", str2);
	printf("strncpy output:     \"%s\"",   str3);
	
	CompareAndPrint (MyStrcmp(str2, str3), 0);



	printf(	PRINT_IN_YELLOW
			"------------------------ end of MyStrNCpy test ------------------------\n"
			PRINT_CO_RESET);
}


/*************************************************************************************
	This FUNCTION will compare between MyStrChr and strchr in string.h library
**************************************************************************************/
void TestMyStrChr ()
{
	char *my_result = NULL;
	char *library_result = NULL;

	/* first test variables */
	char ch1 = '.';
	char str1[] = "http://www.tutorialspoint.com";
	
	/* second test variables */
	char ch2 = 'B';
	char str2[] = "http://www.youtube.com";;
	

	printf (PRINT_IN_YELLOW
			"\nThis test will compare between MyStrChr and strchr in string.h library\n\n"
			PRINT_CO_RESET);


	/* first test comparison */
	printf("\nlook for \"%c\" in \"%s\"\n\n", ch1, str1);

	my_result = MyStrChr(str1, ch1);
	library_result = strchr(str1, ch1);

	printf("MyStrChr output:   \"%s\"\n", my_result);
	printf("strchr output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);


	/* second test comparison */
	printf("\nlook for \"%c\" in \"%s\"\n\n", ch2, str2);

	my_result = MyStrChr(str2, ch2);
	library_result = strchr(str2, ch2);


	printf("MyStrChr output:   \"%s\"\n", my_result);
	printf("strchr output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);



	printf(	PRINT_IN_YELLOW
			"------------------------ end of MyStrChr test ------------------------\n"
			PRINT_CO_RESET);
}


/*************************************************************************************
	This FUNCTION runs a couple of tests on the MyStrDup function.
	NOTE: strdup is not ISO C function, It's part of POSIX.
**************************************************************************************/
void TestMyStrDup ()
{

	char *p1 = NULL;
    char *p2 = NULL;
    
 

	printf (PRINT_IN_YELLOW
			"\nThis will runs a couple of tests on the MyStrDup function.\nNOTE: strdup is not included in c99. There is no function to compare to :(\n\n"
			PRINT_CO_RESET);


	p1 = "Hey what's going on ?";
	p2 = MyStrDup(p1);

	printf("Duplicated string is : %s\n", p2);
    free(p2);


    p1 = "It's not what it looks like !!!";
	p2 = MyStrDup(p1);
	
	printf("Duplicated string is : %s\n", p2);
    free(p2);

    p1 = "Nothing to see here... moving on !";
	p2 = MyStrDup(p1);
	
	printf("Duplicated string is : %s\n", p2);
    free(p2);

    printf("\n---I remembered to free the allocated memory :)!---\n\n");

	printf(	PRINT_IN_YELLOW
			"------------------------ end of MyStrDup test ------------------------\n"
			PRINT_CO_RESET);
}


/*************************************************************************************
	This FUNCTION will compare between MyStrCat and strcat in string.h library
**************************************************************************************/
void TestMyStrCat ()
{
	char *my_result = NULL;
	char *library_result = NULL;

	/* first test variables */
	
	char str1[40] = "one two three";
	char str2[40] = "one two three";

	/* second test variables */
	char str3[40] = "infinity is my";
	char str4[40] = "infinity is my";


	printf (PRINT_IN_YELLOW
			"\nThis test will compare between MyStrCat and strcat in string.h library\n\n"
			PRINT_CO_RESET);


	/* first test comparison */
	printf("\nappends \"%s\" to \"%s\"\n\n", " four", str1);

	my_result = MyStrCat(str1, " four");
	library_result = strcat(str2, " four");

	printf("MyStrCat output:   \"%s\"\n", my_result);
	printf("strcat output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);


	/* second test comparison */
	printf("\nappends \"%s\" to \"%s\"\n\n", " second home", str3);

	my_result = MyStrCat(str3, " second home");
	library_result = strcat(str4, " second home");


	printf("MyStrCat output:   \"%s\"\n", my_result);
	printf("strcat output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);


	/* third test comparison */
	printf("\nappends \"%s\" to \"%s\"\n\n", "", str3);

	my_result = MyStrCat(str3, "");
	library_result = strcat(str4, "");


	printf("MyStrCat output:   \"%s\"\n", my_result);
	printf("strcat output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);


	printf(	PRINT_IN_YELLOW
			"------------------------ end of MyStrCat test ------------------------\n"
			PRINT_CO_RESET);
}


/*************************************************************************************
	This FUNCTION will compare between MyStrNCat and strncat in string.h library
**************************************************************************************/
void TestMyStrNCat ()
{
	char *my_result = NULL;
	char *library_result = NULL;

	/* first test variables */
	
	char str1[40] = "one two three";
	char str2[40] = "one two three";

	/* second test variables */
	char str3[40] = "infinity is my";
	char str4[40] = "infinity is my";


	printf (PRINT_IN_YELLOW
			"\nThis test will compare between MyStrNCat and strncat in string.h library\n\n"
			PRINT_CO_RESET);


	/* first test comparison */
	printf("\nappends \"%s\" (n=%d) to \"%s\"\n\n", " four", 2, str1);

	my_result = MyStrNCat(str1, " four", 2);
	library_result = strncat(str2, " four", 2);

	printf("MyStrChr output:   \"%s\"\n", my_result);
	printf("strchr output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);


	/* second test comparison */
	printf("\nappends \"%s\" (n=%d) to \"%s\"\n\n", " helloa", 5, str1);

	my_result = MyStrNCat(str1, " helloa", 5);
	library_result = strncat(str2, " helloa", 5);

	printf("MyStrChr output:   \"%s\"\n", my_result);
	printf("strchr output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);


	/* thired test comparison */
	printf("\nappends \"%s\" (n=%d) to \"%s\"\n\n", " second home", 20, str3);

	my_result = MyStrNCat(str3, " second home", 20);
	library_result = strncat(str4, " second home", 20);


	printf("MyStrChr output:   \"%s\"\n", my_result);
	printf("strchr output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);


	/* forth test comparison */
	printf("\nappends \"%s\" (n=%d) to \"%s\"\n\n", " second home", 4, str3);

	my_result = MyStrNCat(str3, " second home", 4);
	library_result = strncat(str4, " second home", 4);


	printf("MyStrChr output:   \"%s\"\n", my_result);
	printf("strchr output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);


	printf(	PRINT_IN_YELLOW
			"------------------------ end of MyStrNCat test ------------------------\n"
			PRINT_CO_RESET);
}


/*************************************************************************************
	This FUNCTION will compare between MyStrStr and strstr in string.h library
**************************************************************************************/
void TestMyStrStr ()
{
	char *my_result = NULL;
	char *library_result = NULL;

	/* first test variables */
	
	const char str1[] = "one two three two one";
	const char str2[] = "two";

	/* second test variables */
	const char str3[] = "http://www.youtube.com";
	const char str4[] = "It's not in here";

	const char *str5 = "";

	printf (PRINT_IN_YELLOW
			"\nThis test will compare between MyStrStr and strstr in string.h library\n\n"
			PRINT_CO_RESET);


	/* first test comparison */
	printf("\nlook for \"%s\" in \"%s\"\n\n", str2, str1);

	my_result = MyStrStr(str1, str2);
	library_result = strstr(str1, str2);

	printf("MyStrStr output:   \"%s\"\n", my_result);
	printf("strstr output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);


	/* second test comparison */
	printf("\nlook for \"%s\" in \"%s\"\n\n", str4, str3);

	my_result = MyStrStr(str3, str4);
	library_result = strstr(str3, str4);


	printf("MyStrStr output:   \"%s\"\n", my_result);
	printf("strstr output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);


	/* third test comparison */
	printf("\nlook for \"%s\" in \"%s\"\n\n", "", str3);

	my_result = MyStrStr(str3, str5);
	library_result = strstr(str3, str5);


	printf("MyStrStr output:   \"%s\"\n", my_result);
	printf("strstr output:     \"%s\"",   library_result);

	CompareAndPrint (MyStrcmp(my_result, library_result), 0);


	printf(	PRINT_IN_YELLOW
			"------------------------ end of MyStrStr test ------------------------\n"
			PRINT_CO_RESET);
}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  ++++++++++++++++++++++++END OF TESTS FUNCTIONS FOR STRINGS+++++++++++++++++++++++
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*************************************************************************************
	function that checks if a string is a polindrome
**************************************************************************************/
int IsPalindrome(const char *str)
{
	size_t len_str = MyStrlen(str);

	char *left = (char *)str;
	char *right = left + len_str - 1;

	assert ( NULL != str );

	while( left < right )
	{

		if ( *(left) != *(right) )
		{
			return 0;
		}

		++left;
		--right;

	}

	return 1;
}


/*************************************************************************************
	TEST FUNCTION for IsPalindrome 
**************************************************************************************/
void TestIsPalindrome ()
{
	printf(	"\nIs \"%s\" a polindrome? ...%d (1 for yes, 0 for no)"
	,"aa", IsPalindrome("aa"));
	CompareAndPrint(IsPalindrome("aa") ,1);

	printf(	"\nIs \"%s\" a polindrome? ...%d (1 for yes, 0 for no)"
	,"abba", IsPalindrome("abba"));
	CompareAndPrint(IsPalindrome("abba") ,1);

	printf(	"\nIs \"%s\" a polindrome? ...%d (1 for yes, 0 for no)"
	,"ababa", IsPalindrome("ababa"));
	CompareAndPrint(IsPalindrome("ababa") ,1);

	printf(	"\nIs \"%s\" a polindrome? ...%d (1 for yes, 0 for no)"
	,"abxoba", IsPalindrome("abxoba"));
	CompareAndPrint(IsPalindrome("abxoba") ,0);

	printf(	"\nIs \"%s\" a polindrome? ...%d (1 for yes, 0 for no)"
	,"", IsPalindrome(""));
	CompareAndPrint(IsPalindrome("") ,1);
}


/*************************************************************************************
	function that checks there is "7" in the number ( main test 7 == number % 10 )
**************************************************************************************/
int IsThereSeven (int number)
{
	while( number > 0)
	{
		if ( 7 == number % 10  )
		{
			return 1;
		}
		number /= 10;
	}
	return 0;
}


/*************************************************************************************
	FUNCTION that recieves a range and prints all numbers in the range exept for the
	numbers that have "7" or devided by "7" with no remainder instead of those
	numbers print "BOOM"
**************************************************************************************/
void SevenBOOM (const unsigned int beginning, const unsigned int end)
{
	int counter = beginning;

	while( counter <= end)
	{

		if ( 0 == counter % 7 || IsThereSeven(counter) )
		{
			printf(PRINT_IN_RED"BOOM\t "PRINT_CO_RESET);
		}
		else
		{
			printf("%d\t ", counter);

		}

		++counter;
	}

	printf("\n");
}


/*************************************************************************************
	cleans white spaces ("tab" and "space") from the beginning and the end of the
	string, and cleans up white spaces when there is more than one white space in the
	middle of the string
**************************************************************************************/
void RmSpaces (char *str)
{
	/* dealing with the beginning of the string */
	char *start = str;
	char *end = NULL;
	int flag_space = 0; /* if precvious char in string is white space then flag_space = 1 */

	assert ( NULL != str );

	while( ' ' == *(start) || '\t' == *(start) )
	{
		++start;
	}


	/* dealing with the end of the string */
	end = start + MyStrlen(start) - 1;

	while( ' ' == *(end) || '\t' == *(end) )
	{
		--end;
	}
	*(end + 1) = '\0';  /* shorten the string ignoring white spaces */


	/* dealing with the middle of the string */
	MyStrcpy(str, start);

	while( *(start) != '\0')
	{

		if ( isspace(*start) )
		{
			if ( 1 == flag_space)
			{
				MyStrcpy( start, start + 1 );
			}
			flag_space = 1;
		}
		else
		{
			flag_space = 0;
		}

		++start;

	}
}


/*************************************************************************************
	TEST FUNCTION for RmSpaces (Remove white spaces) function 
**************************************************************************************/
void TestRmSpaces()
{
	char str[40] = "		test  number		one		";

	printf(PRINT_IN_YELLOW"\n\t--- Testing for RmSpaces function ---\t\n\n"PRINT_CO_RESET);

	/* first test */
	printf("\nBefore:		\"%s\"\n", str);
	RmSpaces (str);
	printf("After RmSpaces:	\"%s\"\n", str);

	/* second test */
	MyStrcpy(str, "		 test\t\tnumber   two  		");
	printf("\nBefore:		\"%s\"\n\n", str);
	RmSpaces (str);
	printf("After RmSpaces:	\"%s\"\n", str);


	/* third test */
	MyStrcpy(str, "		 test 		number  	 three  		");
	printf("\nBefore:		\"%s\"\n", str);
	RmSpaces (str);
	printf("After RmSpaces:	\"%s\"\n", str);


	/* forth test */
	MyStrcpy(str, "dudu");
	printf("\nBefore:		\"%s\"\n", str);
	RmSpaces (str);
	printf("After RmSpaces:	\"%s\"\n", str);


	/* sixth test */
	MyStrcpy(str, "	 dudu");
	printf("\nBefore:		\"%s\"\n", str);
	RmSpaces (str);
	printf("After RmSpaces:	\"%s\"\n", str);


	/* seventh test */
	MyStrcpy(str, "dudu  ");
	printf("\nBefore:		\"%s\"\n", str);
	RmSpaces (str);
	printf("After RmSpaces:	\"%s\"\n", str);

	printf(PRINT_IN_YELLOW"\n\t---END OF Testing for RmSpaces function ---\t\n\n"PRINT_CO_RESET);
}	


/*************************************************************************************
	function that swaps two (int) pointers  
**************************************************************************************/
void SwapIntPtrs (int **a, int **b)
{
	int *tmp = *a;
	*a = *b;
	*b = tmp;
}


/*************************************************************************************
	TEST FUNCTION for the SwapIntPtrs function
**************************************************************************************/
void TestSwapIntPtrs()
{
	int var1 = 314, var2 = 111;
	int *ptr1 = &var1, *ptr2 = &var2;

	printf(PRINT_IN_YELLOW"\n\t--- Testing for SwapIntPtrs function ---\t\n\n"PRINT_CO_RESET);


	printf("Befor SwapIntPtrs: var1 = %d, var2 = %d\n", *ptr1, *ptr2);
	SwapIntPtrs(&ptr1, &ptr2);
	printf("After SwapIntPtrs: var1 = %d, var2 = %d\n", *ptr1, *ptr2);


	printf(PRINT_IN_YELLOW"\n\t--- END OF Testing for SwapIntPtrs function ---\t\n\n"PRINT_CO_RESET);
}



/*************************************************************************************
	function that returns a result of an addition operation on a very big positive
	numbers represented as strings. 
**************************************************************************************/
char* AddLargeNumbers (const char *num1, const char *num2)
{
	int carry = 0;

	char *digit_ptr_num_1 = NULL; /* will point to single digit at a time */
	char *digit_ptr_num_2 = NULL;
	char *digit_ptr_result = NULL;

	int len_num1 = MyStrlen(num1);
	int len_num2 = MyStrlen(num2);
	int len_result = ( ( (len_num1 > len_num2) ? (len_num1): (len_num2)) );
										/*  +1 b/c need space for '\0' */
	char *result = (char*)malloc( sizeof(char)*(len_result + 2) );

	if ( NULL == result)
	{
		printf(PRINT_IN_RED"\nNo space allocation was possible !\n"PRINT_CO_RESET);
		return 0;
	}

	assert ( NULL != num1 || NULL != num2 );


	/* point the pointers to the last digit respectivly */
	digit_ptr_num_1 = (char*)num1 + len_num1 - 1;
	digit_ptr_num_2 = (char*)num2 + len_num2 - 1;
	digit_ptr_result = result + len_result;

	*(digit_ptr_result + 1) = '\0'; /* for the end of result string */


	/* the body of the algoritm. exit loop when at the begining of result array*/
	while( digit_ptr_result > result || digit_ptr_result == result)
	{
		*digit_ptr_result = 0;
		/* are we finished adding the first number fully ? */
		if ( digit_ptr_num_1 > num1 || digit_ptr_num_1 == num1)
		{
			*digit_ptr_result += *digit_ptr_num_1 - '0';
			--digit_ptr_num_1;
		}

		/* are we finished adding the first number fully ? */
		if ( digit_ptr_num_2 > num2 || digit_ptr_num_2 == num2)
		{
			*digit_ptr_result += *digit_ptr_num_2 - '0';
			--digit_ptr_num_2;
		}


		*digit_ptr_result += carry;
		carry = 0;	/* carry was added befor. now nullify it*/

		/* handaling the carrier case - ex 5+6 =1 and carrier = 1*/
		if ( *digit_ptr_result >= 10 )
		{
			*digit_ptr_result -= 10;
			++carry;
		}


		*digit_ptr_result += '0';
		--digit_ptr_result;

	}


	if ( '0' == *result )
	{
		MyStrcpy( result, result + 1 );
	}


	return result;
}


/*************************************************************************************
	TEST FUNCTION for the AddLargNumbers function
**************************************************************************************/
void TestAddLargNumbers()
{
	
	char num1[40] = "9999";
	char num2[40] = "25";
	char *result = NULL;

	printf(PRINT_IN_YELLOW"\n\t--- Testing for SwapIntPtrs function ---\t\n"PRINT_CO_RESET);

	/* First test */
	result = AddLargeNumbers(num1, num2);
	printf("\n%s + %s = %s\n", num1, num2, result);
	free(result);
	result = NULL;

	/* Second test */
	MyStrcpy( num1, "123" );
	MyStrcpy( num2, "321" );
	result = AddLargeNumbers(num1, num2);
	printf("\n%s + %s = %s\n", num1, num2, result);
	free(result);
	result = NULL;

	/* Thired test */
	MyStrcpy( num1, "1234" );
	MyStrcpy( num2, "4321" );
	result = AddLargeNumbers(num1, num2);
	printf("\n%s + %s = %s\n", num1, num2, result);
	free(result);
	result = NULL;

	/* Forth test */
	MyStrcpy( num1, "123456789" );
	MyStrcpy( num2, "987654321" );
	result = AddLargeNumbers(num1, num2);
	printf("\n%s + %s = %s\n", num1, num2, result);
	free(result);
	result = NULL;

	printf(PRINT_IN_YELLOW"\n\t--- END OF Testing for SwapIntPtrs function ---\t\n\n"PRINT_CO_RESET);


}


