
/* Author: Alex B
** Last update: 05.09.17 17:00
** Program:	- practising with structs
**			- read file into allocated array of structs
*/


#include <stdio.h> 	/* printf, fopen, fclose, fscanf */
#include <stdlib.h> /* malloc, free */
#include <assert.h>	/* assert */

#define MEMBERS_OFFSET(x,y) ((long)(x)-(long)(y))

#define FIRST_NAME_SIZE (20)
#define LAST_NAME_SIZE	(20)
#define CELLULAR_NUMBER_SIZE (20)


typedef enum Error_Type 
{ 
	SUCCESS		 =   1,
	fopen_ERROR	 = -21,
	fclose_ERROR = -23,
	InitializeArray_ERROR = -24,
	file_name_not_given_ERROR = -25

} Error_Type;


typedef struct
{
	char first_name[FIRST_NAME_SIZE];
	char last_name[LAST_NAME_SIZE];
	char cellular_number[CELLULAR_NUMBER_SIZE];
	unsigned int ID;
	char gender;

} student_t;


/*****************************************************************************
** ARGUMENTS: sorce file mane as a string
**
** RETURNS: the number of new lines (lines count)
** 			 
** NOTES: counts '\n' instances. checks the file char by char
******************************************************************************/
long CountFileLines( const char *src_file_name );


/*****************************************************************************
** ARGUMENTS: pointer to student struct instant
** 			 
** NOTES: prints first_name, last_name, cellular_number and gender
******************************************************************************/
void PrintStudent(student_t *student_instant);


/*****************************************************************************
** ARGUMENTS: pointer to student struct array, number of members in array
** 			 
** NOTES: print student information, for each element in the received array
******************************************************************************/
void PrintStudentList( student_t *student_t_arr_ptr, size_t num_of_members );


/*****************************************************************************
** ARGUMENTS: pointer to student struct instant
** 			 
** NOTES: Prints in one line the offset of each field in the struct,
**		  relative to the begining of the struct.
******************************************************************************/
void PrintFieldOffset(student_t *student_instant);


/*****************************************************************************
** ARGUMENTS: pointer to student struct array, number of members in array
** 			 
** NOTES: Prints in one line the offset of the beginning of each struct in
**		  the array, relative to the begining of the array.
******************************************************************************/
void PrintStructsOffset(student_t *student_instant, size_t num_of_students);


/*****************************************************************************
** ARGUMENTS: 1. num_of_members - number of students that were found in file
**			  2. file name that contains students info in the following format:
**			 	  first_name	last_name	cellular_number	ID	gender(F or M) 
**
** RETURNS: pointer to the allocated array of structs (type student_t).
**			each struct (student instant) is read from the file
** 			 
** NOTES: (!) memory was allocated. when finished working with the 
**			  returned pointer FREE IT (!) 
******************************************************************************/
student_t *InitializeArray( const char *src_file_name, size_t num_of_members );



/*****************************************************************************
** ARGUMENTS: sorce file mane as a string
**
** RETURNS: Error_Type
** 			 
** NOTES:  
**	 1. Reads the file (that contains students info) into allocated array of
**		student struct type (student_t).
**	 2. -prints list of students with their relevant information
**		-prints offset of each field in the struct, relative struct begining
**		-prints offset of the beginning of each struct, relative to arr[0] 
**	 3. frees the allcated memory
**
**	 !. this function manages errors
******************************************************************************/
Error_Type ReadFileIntoStructandPrint ( const char *src_file_name );





int main()
{
	char *file_name = "class_list.txt";

	ReadFileIntoStructandPrint(file_name);

	return 0;
}




/*****************************************************************************
	allocates memory to array of struct student (student_t) 
	each struct (student instant) is read from the file
	(!) when finished working with the returned pointer FREE IT (!)
******************************************************************************/
student_t *InitializeArray( const char *src_file_name, size_t num_of_students )
{
	size_t i = 0; /* for loop */
	FILE *src_file_ptr = NULL;

	student_t *student_t_arr_ptr 
					= (student_t *)malloc( sizeof(student_t)*(num_of_students));

	assert( src_file_name != NULL);

    if ( NULL == student_t_arr_ptr)
    {
    	printf("Memory allocation was not successful");
    	return NULL;
    }


	/* fopen and errror handling */
	if ( (src_file_ptr = fopen(src_file_name, "r") ) == NULL)
	{
		printf("Cannot open %s.\n", src_file_name);
		return NULL;
	} 

	/* read from the file into structs */
	for (i = 0 ; i < num_of_students ; ++i)
	{
		fscanf(src_file_ptr, "%s %s %s %u %c"
				, student_t_arr_ptr[i].first_name
				, student_t_arr_ptr[i].last_name
				, student_t_arr_ptr[i].cellular_number
				, &student_t_arr_ptr[i].ID
				, &student_t_arr_ptr[i].gender		);
	}


	/* fclose and errror handling */
	if ( EOF == fclose(src_file_ptr) )
	{	
		printf("fclose was not successfuly executed\n");
		return NULL;
	}

    return student_t_arr_ptr;
}



/*****************************************************************************
	print student information, for each element in the received array
******************************************************************************/
void PrintStudentList( student_t *student_t_arr_ptr, size_t num_of_students )
{
	long i = 0;
	assert( student_t_arr_ptr != NULL);

	for ( i = 0 ; i < num_of_students ; ++i )
	{
		PrintStudent( student_t_arr_ptr + i );
	}
}



/*****************************************************************************
	prints first_name, last_name, cellular_number and gender
******************************************************************************/
void PrintStudent(student_t *student_instant)
{
	assert( student_instant != NULL);

	printf("%-10s", student_instant->first_name );
	printf("%-15s", student_instant->last_name );
	printf("%-14s", student_instant->cellular_number );
	printf("%-2c\n", student_instant->gender );
}



/*****************************************************************************
	Prints in one line the offset of each field in the struct,
	relative to the begining of the struct.
******************************************************************************/
void PrintFieldOffset(student_t *student_instant)
{
	assert( student_instant != NULL);

	printf(	"\nOffset of each field in the struct, "
			"\nrelative to the begining of the struct.\n");

	printf("%ld "
		, MEMBERS_OFFSET(student_instant->first_name, student_instant) );
	printf("%ld "
		, MEMBERS_OFFSET(student_instant->last_name, student_instant) );
	printf("%ld "
		, MEMBERS_OFFSET(student_instant->cellular_number, student_instant) );
	printf("%ld "
		, MEMBERS_OFFSET(&student_instant->ID, student_instant) );
	printf("%ld "
		, MEMBERS_OFFSET(&student_instant->gender, student_instant) );

	printf("\n");
}



/*****************************************************************************
	Prints in one line the offset of the beginning of each struct in
	the array, relative to the begining of the array.
******************************************************************************/
void PrintStructsOffset(student_t *student_instant, size_t num_of_students)
{

	size_t i = 0;
	assert( student_instant != NULL);

	printf(	"\nOffset of the beginning of each struct in the array,"
			"\nrelative to the begining of the array.\n");

	for ( i = 0; i < num_of_students ; ++i)
	{
		printf("%ld "
		, MEMBERS_OFFSET(student_instant + i, student_instant) );
	}

	printf("\n");
}


/*****************************************************************************
	counts '\n' instances. checks the file char by char
******************************************************************************/
long CountFileLines( const char *src_file_name )
{
	FILE *src_file_ptr = NULL;
	long lines_counter = 0;
	char c = '0';

	assert( src_file_name != NULL);

	/* fopen and errror handling */
	if ( (src_file_ptr = fopen(src_file_name, "r") ) == NULL)
	{
		printf("Cannot open %s.\n", src_file_name);
		return fopen_ERROR;
	} 


	/* counts '\n instances in the files' */
	while ( ( c = fgetc(src_file_ptr) ) != EOF)
	{
		if ( '\n' == c )
		{
			++lines_counter;
		}
	}

	/* fclose and errror handling */
	if ( EOF == fclose(src_file_ptr) )
	{	
		return fclose_ERROR;
	}

	return lines_counter;
}


/*****************************************************************************
 1. Reads the file (that contains students info) into allocated array of
	student struct type (student_t).
 2. -prints list of students with their relevant information
	-prints offset of each field in the struct, relative struct begining
	-prints offset of the beginning of each struct, relative to arr beginning
 3. frees the allcated memory

 NOTE: this function manages errors
******************************************************************************/
Error_Type ReadFileIntoStructandPrint ( const char *file_name )
{
	student_t *class_info = NULL;
	size_t num_of_students = 0;

	assert( file_name != NULL);

	if ( NULL == file_name )
	{
		return file_name_not_given_ERROR;
	}

	num_of_students = CountFileLines(file_name);
	/* num_of_students might hold ERROR code returned by CountFileLines func. */
	if ( num_of_students < 0 )
	{
		return num_of_students;
	}


	class_info = InitializeArray(file_name, num_of_students);
	/* in case an ERROR occured in InitializeArray NULL will be returned */
	if ( NULL == class_info )
	{
		return InitializeArray_ERROR;
	}


	PrintStudentList(class_info, num_of_students);

	PrintFieldOffset(class_info);

	PrintStructsOffset(class_info, num_of_students);

	free(class_info);
	class_info = NULL;

	return SUCCESS;
}