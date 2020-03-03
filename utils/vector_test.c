/* Author: Alex B
** Last update: 17.09.17 10:20
** Program: Testing Vector data structure
*/

#include <string.h> /* memcpy */
#include <stdio.h>  /* printf */
#include "vector.h" /* vector DS */

#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[93m"
#define RESET   "\x1b[0m"
#define BLUE    "\x1B[34m"
#define WHITE   "\x1B[37m"


#define YellowSysMessage(X) printf(YELLOW X RESET)
#define OKmessage			printf(GREEN "%-10s" RESET, "->OK")
#define ERRORmessage		printf(RED "%-10s" RESET, "->ERROR")


void PrintHeader(char *function_name);
void TestVectorWithINT();


int main(int argc, char const *argv[])
{
	TestVectorWithINT();

	return 0;
}



/****************************************************************************/
void TestVectorWithINT()
{
	int i = 0;
	int vec_get_res = 0;
	size_t vec_size_res = 0;
	size_t vec_cap_res  = 0;
	size_t expected_cap = 1;

	vector_t *my_vac = VectorCreate(sizeof(int), 1);

	PrintHeader("Testing vector with type ~int~");

	YellowSysMessage ("\nTest pushing:\n");

	printf(YELLOW "%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n" RESET
            , "|push|", "|Vector|", "|TEST|", "|Vector|", "|Size|"
            , "|Vector|", "|Capacity|");

	printf(YELLOW "%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n" RESET
            ,"|val|", "|GetItem|", "|RES|", "|Size|", "|RES|"
            , "|Capacity|", "|RES|");

	for (i = 0 ; i <= 40 ; ++i) /* must start with 0 or VectorGetItem failes*/
	{
		/* push val */
		printf("%-10d", i);

		VectorPush(my_vac, &i);

		/* VectorGetItem */
		vec_get_res = *(int*)VectorGetItem(my_vac, i);
		printf("%-10lu", (size_t)vec_get_res);

		/* TEST RES */
		(vec_get_res == (size_t)i)	? (OKmessage) : (ERRORmessage);

		/* VectorSize */
		vec_size_res = VectorSize(my_vac);
		printf("%-10lu", vec_size_res);

		/* Size RES */
		(vec_size_res == (size_t)(i + 1) ) ? (OKmessage) : (ERRORmessage);

		/* VectorCapacity */
		vec_cap_res = VectorCapacity(my_vac);
		printf("%-10lu", vec_cap_res);


		if ( expected_cap <= (size_t)i )
		{
			expected_cap *= 2;
		}

		/* Capacity RES */
		(vec_cap_res == expected_cap) ? (OKmessage) : (ERRORmessage);

		printf("\n");
	}

	YellowSysMessage("\nTest poping:\n");

	printf(YELLOW "%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n" RESET
        ,"|pop|", "|Vector|", "|TEST|", "|Vector|", "|Size|"
        , "|Vector|", "|Capacity|");

	printf(YELLOW "%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n" RESET
        ,"|val|", "|GetItem|", "|RES|", "|Size|", "|RES|"
        , "|Capacity|", "|RES|");

	--i;

	for ( ; i >= 0 ; --i)
	{
		/* push val */
		printf("%-10d", i);

		/* VectorGetItem */
		vec_get_res = *(int*)VectorGetItem(my_vac, i);

		VectorPop(my_vac);

		printf("%-10d", vec_get_res);

		/* TEST RES */
		(vec_get_res == (size_t)i) ? (OKmessage) : (ERRORmessage);

		/* VectorSize */
		vec_size_res = VectorSize(my_vac);
		printf("%-10lu", vec_size_res);

		/* Size RES */
		(vec_size_res == (size_t)i) ? (OKmessage) : (ERRORmessage);

		/* VectorCapacity */
		vec_cap_res = VectorCapacity(my_vac);
		printf("%-10lu", vec_cap_res);


		if (expected_cap <= (size_t)i)
		{
			expected_cap *= 2;
		}

		/* Capacity RES */
		(vec_cap_res == expected_cap) ? (OKmessage) : (ERRORmessage);

		printf("\n");
	}

	YellowSysMessage("\nTest poping an empty vector:\n");
	printf(GREEN "The program didn't crush" RESET);
	
	YellowSysMessage("\nTest VectorGetItem an empty vector:\n");
	printf("%s", (NULL == VectorGetItem(my_vac, 0))
				?(GREEN "NULL WAS RETURNED" RESET)
				:(RED "NULL WAS NOT RETURNED" RESET) );

	YellowSysMessage("\nTest VectorGetItem with out of range index:\n");
	printf("%s", (NULL == VectorGetItem(my_vac, 8))
                ?(GREEN "NULL WAS RETURNED" RESET)
                :(RED "NULL WAS NOT RETURNED" RESET) );

	printf("\n");
	VectorDestroy(my_vac);
}


/****************************************************************************/
void PrintHeader(char *function_name)
{
	printf(YELLOW "\n\t-------------------- %s ---------------------\n"
		RESET, function_name);
}
/****************************************************************************/