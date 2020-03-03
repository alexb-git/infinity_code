/* Author: Alex B
** Last update: 01.09.17 21:00
** Program:	Worksheet 7. LUT of functions.
*/

#include <stdio.h>	/*printf*/
#include <stdlib.h>	/*exit, system*/
#include <assert.h>	/*assert*/

#define ARRAY_SIZE (256)
#define ESC (27)		/* ASCII for Esc */

enum { EXIT, CONTINUE };

/*****************************************************************************
** ARGUMENTS: pointer to array of function pointers
**		 
** NOTES: Initialize every function pointer to NULL,
**		  then point to the functions that will be used
******************************************************************************/
void InitializeArr( long (*function_ptr[])(void *) );


/*****************************************************************************
** ARGUMENTS: character
**		 
** NOTES: printf("%c pressed\n", ch);
******************************************************************************/
long PrintPressed(void *);


/*****************************************************************************
** ARGUMENTS: character
**			 
** NOTES: stop terminal buffering and exit the program
******************************************************************************/
long ESCPressed(void *);


/*****************************************************************************
** ARGUMENTS: pointer to array of function pointers
**			 
** NOTES: get char from stdin, and execute the corresponding functionality
******************************************************************************/
void InteractWithUser( long (*function_ptr[])(void *) );



int main()
{
	long (*function_ptr[ARRAY_SIZE])(void *);

	InteractWithUser(function_ptr);

	return 0;
}



/*****************************************************************************
	Initialize every function pointer to NULL,
	then point to the functions that will be used
******************************************************************************/
void InitializeArr( long (*function_ptr[])(void *) )
{
	int i = 0;

	assert( function_ptr != NULL );

	for (i = 0 ; i < ARRAY_SIZE ; ++i)
	{
		function_ptr[i] = NULL;
	}

	function_ptr[(unsigned int)'A'] = PrintPressed;
	function_ptr[(unsigned int)'T'] = PrintPressed;
	function_ptr[ESC] = ESCPressed;
}


/*****************************************************************************
	
******************************************************************************/
long PrintPressed(void *ch)
{
	printf("%c pressed\n", *(char*)ch);
	return CONTINUE;
}


/*****************************************************************************
	return value of EXIT to the calling function
******************************************************************************/
long ESCPressed(void *ch)
{
	return EXIT;
}


/*****************************************************************************
	First initializes the the given array of function pointers to functions 
	that will be used and the rest to NULL. Then interact with user. 
******************************************************************************/
void InteractWithUser( long (*function_ptr[])(void *) )
{
	unsigned int c = '0';
	long exit_flag = CONTINUE;

	assert( function_ptr != NULL );
	InitializeArr(function_ptr);

	/* stop terminal buffering, and stop echoing keyboard pressing */
	system("stty -icanon -echo");

	
	while( exit_flag && c != EOF )
	{
		c = getchar();

		if ( function_ptr[c] != NULL )
		{
			exit_flag = function_ptr[c](&c);
		}
	}
/*
**	don't add anything here
**	the program neeeds to exit
*/
	/* return terminal to its default state */
	system("stty icanon echo");
	exit (0);
}