/*
** Author: Alex B
** Last update: 29.08.17 09:00
** Program:	Worksheet 5 Exercise 1 - Logger 
**			
*/

#include <stdio.h>		/* printf, fopen, fcolse, fgets */
#include <string.h>		/* strcmp */
#include <stdlib.h> 	/* exit */


#define BUFFER_SIZE 100
#define COMMAND_ARR_SIZE 4

typedef enum Error_Type 
{ 
	SUCCESS		 =   0,

	file_name_not_given_ERROR = -10,

	fopen_ERROR	 = -21,
	fputs_ERROR	 = -22,
	fclose_ERROR = -23,
	remove_ERROR = -24,
	fgets_ERROR	 = -25
	
} Error_Type;

enum { TRUTH_, FALSE_ };

typedef struct 
{
	char *command_as_string;
	long (*comparison)(char*, char*);
	Error_Type (*operation)(FILE *, const char*);

} command_type;


/*	uses strcmp from the string.h library */
long CompareCommand (char *command, char *user_input);

/*	counts '\n' instances. checks the file char by char. */
Error_Type CountLines(FILE *dest_file_ptr, const char *src_file_name);

/*	fclose 's the file pointer and removes\deletes the file */
Error_Type RemoveFile(FILE *dest_file_ptr, const char *src_file_name);

/*	fclose 's the file pointer and terminates the program */
Error_Type ExitProgram(FILE *dest_file_ptr, const char *src_file_name);

/* Simply Prints what the File contains */
Error_Type PrintFile(FILE *dest_file_ptr, const char *src_file_name);

/* 	if user string begins with "<" then the string should be added 
	to the beginning of the file  */
Error_Type AddToBeginning(const char *users_input, const char *src_file_name);

/* 	the primery function of this exercise */
Error_Type WorkSheet5E1 (int argc, const char **argv);

/* 	gets the file we wish to work on. creates pointer to the file.
	and operates on him */
Error_Type CreateFilePtrRunCommands(const char *dest_file_name);

/* 	If command is found execute it 
	else put the users input string into the file */
Error_Type RunUsersCommands(const char *dest_file_name,
							FILE *dest_file_ptr,
							char *buffer_string );


/*	will print relevant error messege. using switch case */
void ErrorMessenger(Error_Type error_num);

static command_type commands_array[COMMAND_ARR_SIZE]
				= { { "-remove\n", CompareCommand, RemoveFile  	},
					{ "-count\n",  CompareCommand, CountLines  	},
					{ "-exit\n",   CompareCommand, ExitProgram 	},
					{ "-print\n",  CompareCommand, PrintFile   	}	};


/*NOTES TO SELF. next time:
		1. one function in the main to run it all
		2. user enters the file name he wants to creat
		3. what if commnad -remove then -count => handle it !!
		4. dont print command into the file !
	5. 	"-remove\n" !!
	6.	advanced exersize	
	7.	if -remove then -exit => the file will still exist empty?
	8.	 */



int main(int argc, const char *argv[])
{
	Error_Type error_num = WorkSheet5E1(argc,argv);
	ErrorMessenger(error_num);

	return 0;
}


/*****************************************************************************
** ARGUMENTS: int argc, const char *argv
**
** RETURNS: Error_Type
** 			 
** NOTES: checks if the user specified the file he wishes to work on
**		  if didn't return error else give file name as an argument 
**		  to the program that will handles users' commands
******************************************************************************/
Error_Type WorkSheet5E1 (int argc, const char **argv)
{
	long error_handler = SUCCESS;

	const char *dest_file_name = NULL;

	/* 	check if the user wrote the file name he 
		wishes to work on retrun error if he didn't */
	if ( 1 == argc )
	{
		return file_name_not_given_ERROR;
	}

	dest_file_name = argv[1];


	printf("\nUser, you may enter strings. As much as you like.\n\n");

	error_handler = CreateFilePtrRunCommands( dest_file_name );

	return error_handler;
}


/*****************************************************************************
** ARGUMENTS: file name the user will work on
**
** RETURNS: Error_Type
** 			 
** NOTES: gets the file we wish to work on. creates pointer to the file.
**		  and operates on him
******************************************************************************/
Error_Type CreateFilePtrRunCommands(const char *dest_file_name)
{

	long error_handler = SUCCESS; 

	long IS_file_exist = FALSE_;

	char buffer_string[BUFFER_SIZE];

	FILE *dest_file_ptr = NULL;


	while(1)
	{

		/* 	if file doesnt exist he will be created with fopen.
			if created successfully set IS_file_exist = TRUTH (exists)
			else returns error (if fopen doesnt execute successfully)  */
		if ( FALSE_ == IS_file_exist )
		{

			if ( NULL == (dest_file_ptr = fopen(dest_file_name, "a+")) )
			{
				printf("Cannot open %s.\n", dest_file_name);
				return fopen_ERROR;
			}
			IS_file_exist = TRUTH_;
		}

		/* get string from the user. return error if fgets fails */
		if ( NULL == fgets(buffer_string, BUFFER_SIZE, stdin) )
		{
			return fgets_ERROR;
		}


		if ( '<' == *(buffer_string) )
		{
			error_handler = AddToBeginning(buffer_string, dest_file_name);
		}
		else
		{

			error_handler =  RunUsersCommands(dest_file_name, 
											  dest_file_ptr, 
											  buffer_string);
		}


		if ( error_handler != SUCCESS )
		{
			return error_handler;
		}


		/* if last command was "-remove" then update IS_file_exist = FALSE_ */
		if ( 0 == strcmp(buffer_string, "-remove\n"))
		{
			IS_file_exist = FALSE_;
		}

	}

	return error_handler;
}


/*****************************************************************************
** ARGUMENTS: destination file name, destination file pointer,
**			  string/input from the user (buffer_string)
**
** RETURNS: Error_Type
** 			 
** NOTES: Iterates over the possible commands
**		  If command is found execute it
**		  else put the users input string into the file
******************************************************************************/
Error_Type RunUsersCommands(const char *dest_file_name,
							FILE *dest_file_ptr,
							char *buffer_string )
{
	long i = 0; /* for the for loop */ 
		
	long error_handler = SUCCESS; 


	/* 	iterate over the commands array.
		if command matches user input -> update IS_last_input_command = TRUTH_ 
		and move on (break) */
	for ( i = 0 ; i < COMMAND_ARR_SIZE ; ++i )
	{
		if ( 0 == commands_array[i].comparison(
									commands_array[i].command_as_string
									, buffer_string) )
		{
			error_handler = commands_array[i].operation( dest_file_ptr 
														,dest_file_name );

			if ( error_handler != SUCCESS )
			{
				return error_handler;
			}

			return SUCCESS;
		}
	}


	/* 	if last user input was not a command then put users' string
		into the destination file */
	if ( EOF == fputs(buffer_string, dest_file_ptr) )
	{
		return fputs_ERROR;
	}

	return error_handler;
}


/*****************************************************************************
** ARGUMENTS: user_input and command as a string
**
** RETURNS: 0 - if the strings are the same
** 			other - the strings do not match 
** NOTES: uses strcmp from the string.h library
******************************************************************************/
long CompareCommand (char *command, char *user_input)
{
	return strcmp(command, user_input);
}


/*****************************************************************************
** ARGUMENTS: file system pointer, sorce file mane as a string
**
** RETURNS: the number new lines (lines count)
** 			 
** NOTES: counts '\n' instances. checks the file char by char
******************************************************************************/
Error_Type CountLines(FILE *src_file_ptr, const char *src_file_name)
{
	long lines_counter = 0;
	char c;

	if ( (src_file_ptr = fopen(src_file_name, "a+") ) == NULL)
	{
		printf("Cannot open %s.\n", src_file_name);
		return fopen_ERROR;
	} 

	while ( ( c = fgetc(src_file_ptr) ) != EOF)
	{
		if ( '\n' == c )
		{
			++lines_counter;
		}
	}

	printf("%ld\n", lines_counter);


	if ( EOF == fclose(src_file_ptr) )
	{	
		return fclose_ERROR;
	}

	return SUCCESS;
}


/*****************************************************************************
** ARGUMENTS: file system pointer, sorce file mane as a string
**
** RETURNS: Error_Type
** 			 
** NOTES: 
******************************************************************************/
Error_Type RemoveFile(FILE *dest_file_ptr, const char *src_file_name)
{

	if ( EOF == fclose(dest_file_ptr) )
	{
		return fclose_ERROR;
	}

	if ( -1 == remove(src_file_name) )
	{
		return remove_ERROR;
	}

	return SUCCESS;
}


/*****************************************************************************
** ARGUMENTS: file system pointer, sorce file mane as a string
**
** RETURNS: will not reach the return statement
** 			 
** NOTES: if called this function will not reach the return statement 
**		  b/c exit will terminate the program beforehand
******************************************************************************/
Error_Type ExitProgram(FILE *dest_file_ptr, const char *src_file_name)
{
	if ( EOF == fclose(dest_file_ptr) )
	{
		return fclose_ERROR;
	}

	exit(SUCCESS);
	return SUCCESS;
}


/*****************************************************************************
** ARGUMENTS: file system pointer, sorce file mane as a string
**
** RETURNS: Error_Type
** 			 
** NOTES: Simply Prints what the File contains
******************************************************************************/
Error_Type PrintFile(FILE *src_file_ptr, const char *src_file_name)
{
	char  c;
	
	if ( (src_file_ptr = fopen(src_file_name, "a+") ) == NULL)
	{
		printf("Cannot open %s.\n", src_file_name);
		return fopen_ERROR;
	} 

	printf("\n---The contant of the file you're working on is:---\n\n");

	while ( (c = fgetc(src_file_ptr) ) != EOF)
	{
		putchar(c);      /* put the character on the screen */
	}

	printf("\n---END OF contant of the file you're working on.---\n");


	if ( EOF == fclose(src_file_ptr) )
	{	
		return fclose_ERROR;
	}


	return SUCCESS;
}

/*****************************************************************************
** ARGUMENTS: users' input as a string, file name that we are working on
**
** RETURNS: Error_Type
** 			 
** NOTES: if user string begins with "<" then the string should be added 
**		  to the beginning of the file
******************************************************************************/
Error_Type AddToBeginning(const char *users_input, const char *src_file_name)
{
	int c;

	FILE *src_file_ptr = NULL;
	FILE *temp_file_ptr = NULL;

	const char *tmp_file_name = "temp_specific_file.txt";

	/* link dest_file_ptr to the temporary file */
	if ( (temp_file_ptr = fopen(tmp_file_name, "a+") ) == NULL)
	{
		printf("Cannot open %s.\n", tmp_file_name);
		return fopen_ERROR;
	} 

	/* link src_file_ptr to the file we are working on */
	if ( (src_file_ptr = fopen(src_file_name, "a+") ) == NULL)
	{
		printf("Cannot open %s.\n", src_file_name);
		return fopen_ERROR;
	} 

	rewind(src_file_ptr);
	rewind(temp_file_ptr);

	/* copy from the file that we are working on to the temp file */
	while ( (c = fgetc(src_file_ptr) ) != EOF)
	{
		fputc(c, temp_file_ptr);  /* write to a file */
	}


	/* 	first close the pointer to the file we are working on,
		then delete it,
		thirdly create it again => now we have a new empty file */
	if ( EOF == fclose(src_file_ptr) )
	{	
		return fclose_ERROR;
	}
	if ( -1 == remove(src_file_name) )
	{
		return remove_ERROR;
	}	
	if ( (src_file_ptr = fopen(src_file_name, "a+") ) == NULL)
	{
		printf("Cannot open %s.\n", src_file_name);
		return fopen_ERROR;
	} 


	/* 	put the buffer_string into the begginig of the file we
		are working on */
	if ( EOF == fputs(users_input + 1, src_file_ptr) )
	{
		return fputs_ERROR;
	}


	rewind(temp_file_ptr);

	/* 	copy the remaining of the file from temp_specific_file.txt
		to the file that we are working on now */
	while ( (c = fgetc(temp_file_ptr) ) != EOF)
	{
		fputc(c, src_file_ptr);  /* write to a file */
	}

	/* 	fclose the pointer to the temp file.
		then remove the temp file complitly */
	if ( EOF == fclose(temp_file_ptr) )
	{	
		return fclose_ERROR;
	}
	if ( -1 == remove(tmp_file_name) )
	{
		return remove_ERROR;
	}


	/* 	lastly close the pointer to the file that we
		are working on in this function */
	if ( EOF == fclose(src_file_ptr) )
	{	
		return fclose_ERROR;
	}


	return SUCCESS;
}


/*****************************************************************************
** ARGUMENTS: Error_Type
**
** RETURNS: void
** 			 
** NOTES: will print error messege. using switch case
******************************************************************************/
void ErrorMessenger(Error_Type error_num)
{
	switch(error_num)
	{
		case file_name_not_given_ERROR:
			printf("\nERROR: File name not given at program call.\n");
			break;
		case SUCCESS:
			printf("\nThe program was executed successfully.\n");
			break;
		case fopen_ERROR:
			printf("\nERROR: Could not open the file that you've specified.\n");
			break;
		case fputs_ERROR:
			printf("\nERROR: couldn't execute fputs command properly.\n");
			break;
		case fclose_ERROR:
			printf("\nERROR: couldn't execute fclose command properly.\n");
			break;
		case remove_ERROR:
			printf("\nERROR: couldn't execute remove command properly.\n");
			break;

		default:
			printf("\nERROR: Some kind of error IDK !\n");
	}
}