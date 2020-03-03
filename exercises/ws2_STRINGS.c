/* Made by Alex Budie 22.08.17 */

#include <stdio.h>		/* printf, scanf */
#include <string.h> 	/* strlen */
#include <strings.h> 	/* strcasecmp */
#include <ctype.h> 		/* tolower */
#include <assert.h>		/* asssert function */
#include <stdlib.h>		/* malloc */

#include "ws2_STRINGS.h" /* my string library */

#define PRINT_IN_GREEN 	"\x1b[32m"
#define PRINT_IN_RED 	"\x1b[31m"
#define PRINT_IN_YELLOW "\x1b[93m"
#define PRINT_CO_RESET 	"\x1b[0m"






/*********************************************************************************
	Function that recieves pointer to string and retuns the length of the string
**********************************************************************************/
size_t MyStrlen (const char *ptr)
{	

	size_t len = 0;
	assert ( NULL != ptr );

	while ( *ptr != '\0')
	{
		++ptr;
		++len;
	}

	return len;
}


/*********************************************************************************
	input two strings.

	output
	0			if both strings are identical (equal)
	negative	if the ASCII value of first unmatched character is less than second.
	positive 	if the ASCII value of first unmatched character is greater than second.
**********************************************************************************/
int MyStrcmp (const char* str1, const char* str2)
{
	if ( NULL == str1 && NULL == str2)
	{
		/* this is useful for my tests functions*/
		return 0;
	}

	while ( *(str1) == *(str2) && *(str1) != '\0' )
	{
		++str1;
		++str2;
	}

	return	*(str1) - *(str2);
}


/*******************************************************************************
	compares two strings irrespective of the case of characters
*******************************************************************************/
int MyStrCaseCmp(const char *str1, const char *str2)
{

	while (1)
	{
		if ( tolower( *(str1) ) == tolower( *(str2) ) && *(str1) != '\0')
		{
			++str1;
			++str2;
		}
		else
		{
			return	tolower( *(str1) ) - tolower( *(str2) );
		}
	}
}



/*********************************************************************************
  Copies the string pointed by source into the array pointed by destination,
  including the terminating null character (and stopping at that point).

  To avoid overflows, the size of the array pointed by destination shall be long 
  enough to contain the same C string as source (including the terminating null 
  character), and should not overlap in memory with source.
**********************************************************************************/
char* MyStrcpy(char* dest, const char* src)
{

	char *ptr = dest;
	assert ( NULL != dest || NULL != src );

	while( *(src) != '\0' )
	{
		*ptr = *src;
		++src;
		++ptr;
	}

	*(ptr) = '\0';

	return dest;

}


/*********************************************************************************
  copies up to n characters from the string pointed to, by src to dest. 
  In a case where the length of src is less than that of n, the remainder 
  of dest will be padded with null bytes.
**********************************************************************************/
char* MyStrNCpy(char *dest, const char *src, size_t n)
{

	char *ptr = dest;
	size_t i = 0;

	assert ( NULL != src );

	while( *(src) != '\0' && i < n)
	{
		*ptr = *src;
		++src;
		++ptr;
		++i;
	}


	if ( '\0' == *(src))
	{
		 /* here we imitate the behaviour of strncpy function */ 
		*(ptr) = '\0';
	}

	return dest;
	
}


/*********************************************************************************
  searches for the first occurrence of the character c (an unsigned char) in the 
  string pointed to by the argument str. returns a pointer to the first occurrence 
  of the character c in the string str, or NULL if the character is not found.
**********************************************************************************/
char *MyStrChr(const char *str, int c)
{

	char *prt = (char *)str;

	assert ( NULL != str );

	while ( *(prt) != c && *(prt) != '\0')
	{
		prt++;
	}

	if ( '\0' == *(prt) )
	{
		return NULL;
	}

	return prt;
	
}


/*********************************************************************************
  Duplicates the given string. allocates memory. retruns pointer to allocated memory
  NOTE: strdup is not ISO C function, It's part of POSIX.
  example: char *p1 = "Raja"; char *p2; p2 = strdup(p1);
**********************************************************************************/
char *MyStrDup(const char *str)
{

	char *arr = NULL;
	assert ( NULL != str );

	arr = (char *)calloc( MyStrlen(str) + 1, sizeof(char) );

	if ( NULL == arr ) 
	{
		/* No more memory ! couldn't allocate new memory */
		return NULL;	 
	}

	MyStrcpy(arr, str);

	return (char*)(arr);
}


/*********************************************************************************
  appends the string pointed to by src to the end of the string pointed to by dest
**********************************************************************************/
char *MyStrCat(char *dest, const char *src)
{

	char *ptr_dest = dest;
	char *ptr_src = (char *)src;

	size_t len = MyStrlen (dest);

	ptr_dest += len;

	while ( *(ptr_src) != '\0' )
	{
		*(ptr_dest) = *(ptr_src);
		++ptr_dest;
		++ptr_src;
	}
	*(ptr_dest) = '\0';

	return dest;
	
}


/*********************************************************************************
  appends the string pointed by src to the end of the string pointed 
  by dest up to n characters long
**********************************************************************************/
char *MyStrNCat(char *dest, const char *src, size_t n)
{
	
	size_t i = 0;
	char *ptr_dest = dest;
	char *ptr_src = (char *)src;

	size_t len = MyStrlen (dest);

	assert ( NULL != dest || NULL != src );

	ptr_dest += len;

	while ( *(ptr_src) != '\0' && i < n)
	{
		*(ptr_dest) = *(ptr_src);
		++ptr_dest;
		++ptr_src;
		++i;
	}
	*(ptr_dest) = '\0';

	return dest;
	
}


/*********************************************************************************
   This function finds the first occurrence of the substring needle in the string 
   haystack. The terminating '\0' characters are not compared.
**********************************************************************************/
char *MyStrStr(const char *haystack, const char *needle)
{

	char *ptr_hay 		= (char *)haystack;
	char *ptr_needle 	= (char *)needle;

	int counter = 0;
	int len_needle = MyStrlen(needle);

	assert ( NULL != haystack || NULL != needle );	

	while ( *(ptr_hay) != '\0' )
	{
	/* loop stop condition - we got to the end of the haystack */

		if ( *(ptr_hay) == *(ptr_needle) )
		{
			/* the characters match. we begin to count the matches */
			++ptr_needle;
			++counter;

			if ( '\0' == *(ptr_needle) && counter == len_needle )
			{
				/* in this case we've found the inside string fully */
				return (ptr_hay - len_needle + 1);
			}

		}

		else
		{
			/* the characters doesn't match. we nullify the counter */
			counter = 0;
		}

		++ptr_hay;

	}

	if ( 0 == len_needle)
	{
		/* in case we are looking for "" */
		return (char*)haystack;
	}

	return NULL;

}
