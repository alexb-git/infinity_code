#include <stdio.h> 	/* printf*/
#include <stdlib.h> /* calloc, free*/
#include <ctype.h>	/* tolower */
#include <assert.h> /* assert(expression)*/
#include <string.h>	/* strlen */


/* 	given destination string pointer and source string pointer
	copies all of the sorce string in lower case into destination */
static char* DuplicateStringToLower(const char *src);

/*	Counts the length (number of lines) of sorce input and allocates memory
	of the same length. returns pointer to the allocated memory. */
static char** AllocateAutomatically(const char **src);

/*	given two dimentional (src) array copies in lower case the sorce of src
	array into the newly allocated dest array.	*/
char** CopyEnvp (const char **src);

/*	free two dimentional array */
void FreeStrings (char **pointer);

/*	print two dimentional char array line by line */
void PrintStrings (char **pointer);



int main(int args, char *argv[], const char *envp[])
{
	
	char **buffer = CopyEnvp(envp);

	/* CopyEnvp allocates mamory that needs to be freed later */
	PrintStrings(buffer);


	/* Free memory that CopyEnvp function allocated before */
	FreeStrings(buffer);


	return 0;

}



/******************************************************************************
	given destination string pointer and source string pointer
	copies all of the sorce string in lower case into destination
	NOTE: Need to FREE the memory after using this function 
 ******************************************************************************/
char* DuplicateStringToLower (const char *src)
{
	char *start = NULL;
	char *dest = NULL;

	assert( NULL != src );

	start = (char*)malloc( sizeof(char)*(strlen(src) + 1) );
	dest = start;

	while( *src != '\0' )
	{
		*dest = tolower(*src);
		++dest;
		++src;
	}
	*dest= '\0';

	return start;
}


/******************************************************************************
	given two dimentional (src) array copies in lower case the sorce of src
	array into the newly allocated dest array
 ******************************************************************************/
char** CopyEnvp (const char **src)
{
	char **dest = AllocateAutomatically(src);
	char **start = dest;

	while( *src != NULL )
	{
		*dest = DuplicateStringToLower(*src);
		++dest;
		++src;
	}
	*dest = NULL;

	return start;
}


/******************************************************************************
	Counts the length (number of lines) of sorce input and allocates memory
	of the same length. returns pointer to the allocated memory.
	NOTE: Need to FREE the memory after using this function
 ******************************************************************************/
char** AllocateAutomatically(const char **src)
{

	int counter = 0;
	char **buffer = NULL;

	while( *src != '\0')
	{
		++counter;
		++src;
	}
	buffer = (char**)malloc( sizeof(char*)*(counter + 1) );

	return buffer;
}



/******************************************************************************
	free two dimentional array
 ******************************************************************************/
void FreeStrings (char **pointer)
{
	char **begining = pointer;

	while( *pointer != NULL )
	{
		free(*pointer );
		*pointer = NULL; /*handling dangling pointers*/
		++pointer;
	}

	free(begining);
	begining = NULL; /*handling dangling pointers*/
}


/******************************************************************************
	print two dimentional char array line by line
 ******************************************************************************/
void PrintStrings (char **pointer)
{

	while( *pointer != NULL )
	{
		printf( "%s\n", *pointer );
		++pointer;
	}
}