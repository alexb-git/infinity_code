
/* Author: Alex B
** Last update: 27.08.17 14:10
** Program:	100 Soldiers in circle riddle
**			includes modularity for any number of soldiers
*/

#include <stdio.h> 	/* printf */
#include <stdlib.h>	/* malloc */

#define PRINTF_IN_RED	"\x1b[31m"
#define PRINTF_RESET	"\x1b[0m"


/* prints the arrays of chars '1'=Alive '0'=Killed */
void PrintArrOfSoldiers(char *arr_of_soldiers, char  *end_of_arr);


/* Initialize array of soldiers - Make everyone alive, '1'=Alive */
void InitializeSoldiers(char *arr_of_soldiers, char *end_of_arr);

/* 	finds the next soldier alive (char '1') from the current location.
	We treat the array as a closed loop: 
	(end of array + 1) = begining of array */
char *FindNextAlive(char *current_location, 
					char *arr_of_soldiers, 
					char  *end_of_arr );


/* 	this function takes two steps (1). find next soldier alive (char '1') 
	and kill him (char '0').  (2). find next soldier alive and give him
	the sword (simply point to him with a pointer) */
char *KillAndMoveSword(	char *current_location, 
						char *arr_of_soldiers, 
						char  *end_of_arr );


/* 	given the number of soldiers to begin with (num_of_soldiers) whis function 
	returns the position/place of the last soldier that 
	will be alive (last_alive_place) */
long SolveSoldierRiddle(long num_of_soldiers);



int main()
{
	long i;

	for ( i = 90 ; i <= 110 ; ++i )
	{
		long num_of_soldiers = i;

		printf(	"\nOut of " PRINTF_IN_RED "%lu" PRINTF_RESET" soldiers, "
				"soldier number "
				PRINTF_IN_RED "%ld" PRINTF_RESET" remaind alive."

		, num_of_soldiers, SolveSoldierRiddle(num_of_soldiers));
	}
	printf("\n");

	
	return 0;
}


/******************************************************************************
	prints the arrays of chars '1'=Alive '0'=Killed
******************************************************************************/
void PrintArrOfSoldiers(char *arr_of_soldiers, char  *end_of_arr)
{
	/* iterate over the char array and print each soldier status */
	while ( arr_of_soldiers <= end_of_arr )
	{
		printf("%c", *arr_of_soldiers);
		++arr_of_soldiers;
	}
	printf("\n");
}


/******************************************************************************
	Initialize array of soldiers - Make everyone alive, '1'=Alive
******************************************************************************/
void InitializeSoldiers(char *arr_of_soldiers, char *end_of_arr)
{
	while ( arr_of_soldiers <= end_of_arr )
	{
		*arr_of_soldiers = '1';
		++arr_of_soldiers;
	}
}


/******************************************************************************
 	finds the next soldier alive (char '1') from the current location.
	We treat the array as a closed loop: 
	(end of array + 1) = begining of array 
******************************************************************************/
char *FindNextAlive(char *current_location,
					char *arr_of_soldiers,
					char  *end_of_arr)
{
	/* 	fist increas current_location by one.
		if we are at the end of the array => 
		(end of array + 1) = begining of array */
	if (current_location < end_of_arr)
	{
		++current_location;
	}
	else
	{
		current_location = arr_of_soldiers;
	}

	/* 	go over the array till we find a soldier alive (char '1')
		=> iterate if the soldier is killed (char '0') */
	while ( '0' == *current_location )
	{
		/* 	We treat the array as a closed loop: 
			(end of array + 1) = begining of array */
		if (current_location == end_of_arr)
		{
			current_location = arr_of_soldiers;
		}
		else
		{
			++current_location;
		}

	}
	return current_location;
}


/******************************************************************************
	this function takes two steps (1). find next soldier alive (char '1') 
	and kill him (char '0').  (2). find next soldier alive and give him
	the sword (simply point to him with a pointer)
******************************************************************************/
char *KillAndMoveSword(	char *current_location, 
						char *arr_of_soldiers,
						char  *end_of_arr)
{
	char *pass_sword_to = NULL;
	char *kill = NULL;

	kill = FindNextAlive(current_location, arr_of_soldiers, end_of_arr);
	*kill = '0';

	pass_sword_to = FindNextAlive(kill, arr_of_soldiers, end_of_arr);

	return pass_sword_to;
}


/******************************************************************************
	given the number of soldiers to begin with (num_of_soldiers) whis function 
	returns the position/place of the last soldier that 
	will be alive (last_alive_place)
******************************************************************************/
long SolveSoldierRiddle(long num_of_soldiers)
{
	long last_alive_place = 1;
	char *current_location = NULL;
	char *end_of_arr = NULL;
	char *arr_of_soldiers = (char*)malloc(num_of_soldiers *sizeof(char));

	/* check if the memory allocation was successful  */
	if ( NULL == arr_of_soldiers )
	{
		printf("\nNo memory allocation was possible at this point\n");
		return 666;
	}

	current_location = arr_of_soldiers;
	end_of_arr = arr_of_soldiers + num_of_soldiers - 1;

	/* Initialize every soldier to be alive (char '1') */
	InitializeSoldiers(arr_of_soldiers, end_of_arr);

	/* 	we iterate over the soldiers array till there's one last 
		soldier standing */
	while (num_of_soldiers > 1)
	{
		/*PrintArrOfSoldiers(arr_of_soldiers, end_of_arr);*/
		current_location = KillAndMoveSword( current_location, 
											 arr_of_soldiers,
											 end_of_arr );
		--num_of_soldiers;
	}

	/*  we iterate over the soldiers array to find the exect position of the
		last soldier alive . Begining of the array = position 1 */
	current_location = arr_of_soldiers;
	while ( *current_location != '1' )
	{
		++current_location;
		++last_alive_place;
	}

	/*PrintArrOfSoldiers(arr_of_soldiers, end_of_arr);*/
	free(arr_of_soldiers);
	arr_of_soldiers = NULL;
	return last_alive_place;
}