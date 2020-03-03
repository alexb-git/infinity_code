/****************************************************************************
** Filename:    - recexer_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Recursion functions testing
** Date:        - 14/11/2017
** Version:     - 1
***************************************************/
#include <stdlib.h> /* calloc */
#include <stdio.h>	/* printf */
#include <time.h>   /* time   */
#include <string.h> /* strlen, strcmp, strncmp */

#include "stack.h"   /* Stack data structure */
#include "slist.h"   /* Singly Linked List */
#include "recexer.h" /* Header file for recursive functions */

/****************************************************************************
    Helpful colors
*****************************************************************************/
#define GREEN	"\x1b[92m"
#define RED		"\x1b[91m"
#define YELLOW	"\x1b[93m"
#define YELLOWS	"\x1b[33m"
#define RESET	"\x1b[0m"
#define BLUE	"\x1B[34m"
#define CYAN	"\x1B[36m"
#define WHITE	"\x1B[37m"

/****************************************************************************
    Helpful defines
*****************************************************************************/
#define PrintHeader(X)      printf( BLUE "\n\t------------"\
                                    "  This is a test for: "\
                                    X" ------------\n" RESET)

#define PrintInYellow(X)  ( printf(YELLOWS X RESET) )
#define PrintInGreen(X)   ( printf(GREEN   X RESET) )
#define PrintInRed(X)     ( printf(RED     X RESET) )
#define PrintOK           ( printf(GREEN "%s" RESET, "-OK") )
#define PrintERR          ( printf(RED "%s" RESET, "-ERR") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************
    Macros for this program
*****************************************************************************/
#define TimeDiff(X)     ( (double)(clock() - X)/CLOCKS_PER_SEC )
#define PrintTimeDiff(X) printf("%f [seconds]", TimeDiff(X))

/*=========================  FUNCTION DECLARATION  =========================*/
/* MY TEST FUNCTIONS FOR STRINGS */
void TestMyStrlen();
void TestMyStrcmp();
void TestMyStrcpy();
void TestMyStrCat();
void TestMyStrStr();

void TestSListFlip();

void TestStackWithINT();

/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
    clock_t befor;
    size_t  result;
    size_t  place = 40;

    befor = clock();
    result = FibonacciRec(place);
    printf( "\nRecursion: %ld-th element of fibonacci is: %ld  - ",
            place, result);
    PrintTimeDiff(befor);

    befor = clock();
    result = FibonacciItr(place);
    printf( "\nIterative: %ld-th element of fibonacci is: %ld  - ",
            place, result);
    PrintTimeDiff(befor);

    printf("\n\n");
    PrintHeader("string functions");
    TestMyStrlen();
    TestMyStrcmp();
    TestMyStrcpy();
    TestMyStrCat();
    TestMyStrStr();

    printf("\n\n");
    PrintHeader("Flip singly linked list");
    TestSListFlip();

    PrintHeader("StackSort");
    TestStackWithINT();

    printf("\n");
    return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  ++++ BEGINNING OF STRING FUNCTIONS AND TESTS FUNCTIONS FOR STRINGS ++++++++
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/******************************************************************************
This FUNCTION will compare between MyStrlen and strlen in string.h library
*******************************************************************************/
void TestMyStrlen()
{
	size_t i;

	const char *string2test[] = {	"Hello", "World", "Hi", "1231hi",
							"long ago in a galaxy far far away"};

    PrintInYellow("\nThis test will compare between MyStrlen ");
    PrintInYellow("and strlen in string.h library\n");

	for ( i = 0 ; i < SizeArr(string2test) ; i++)
	{
		size_t 	MyStrlen_output = MyStrlen(string2test[i]);
		size_t 	strlen_output = strlen(string2test[i]);

		printf("\n\nIput:\t\"%s\" \nMyStrlen output: %d \nstrlen output:\t %d",
						string2test[i],	(int)MyStrlen_output,(int)strlen_output);

        PrintOKorERR(MyStrlen_output == strlen_output);
	}
}


/******************************************************************************
This FUNCTION will compare between MyStrcmp and strcmp in string.h library
*******************************************************************************/
void TestMyStrcmp()
{
	size_t i;

	const char *string2test1[] = {	"Helloa", "World", "Hi", "1231h",
								"long ago in a galaxy far far away"};

	const char *string2test2[] = {	"Hello", "World", "Hi", "1231hi",
								"long ago in a galaxy  far far away", "" };

    PrintInYellow("\nThis test will compare between MyStrcmp ");
    PrintInYellow("and strcmp in string.h library\n");

	for ( i = 0 ; i < SizeArr(string2test1) ; i++)
	{
		int 	my_func_output = MyStrcmp(string2test1[i], string2test2[i]);
		int 	library_output = strcmp(string2test1[i], string2test2[i]);

		printf("\n\nIput:\t{\"%s\", \"%s\"} \nTestMyStrcmp output: %d \nstrcmp output:\t %d",
					string2test1[i], string2test2[i], (int)my_func_output,(int)library_output);

        PrintOKorERR( my_func_output == library_output );
	}
}

/******************************************************************************
This FUNCTION will compare between MyStrcpy and strcpy in string.h library
*******************************************************************************/
void TestMyStrcpy ()
{
	char str1[40];
	char str2[40];
	char str3[40];
	char str4[40];

    PrintInYellow("\n\nThis test will compare between MyStrcpy ");
    PrintInYellow("and strcpy in string.h library\n");


	/* INPUT "string in str1 char array." */
	MyStrcpy(str1, "some kind of string");
	MyStrcpy(str2, str1);
	strcpy(str3, "some kind of string");
	strcpy (str4, str3);

	printf("\n\nMyStrcpy output:   \"%s\"\n", str2);
	printf("strcpy output:     \"%s\"",   str3);
    PrintOKorERR( MyStrcmp(str2, str3) == 0);


	/* INPUT "" */
	MyStrcpy(str1, "");
	MyStrcpy(str2, str1);
	strcpy(str3, "");
	strcpy (str4, str3);

	printf("\n\nMyStrcpy output:   \"%s\"\n", str2);
	printf("strcpy output:     \"%s\"",   str3);
    PrintOKorERR( MyStrcmp(str2, str3) == 0);



	/* INPUT "12345679" */
	MyStrcpy(str1, "12345679");
	MyStrcpy(str2, str1);
	strcpy(str3, "12345679");
	strcpy (str4, str3);

	printf("\n\nMyStrcpy output:   \"%s\"\n", str2);
	printf("strcpy output:     \"%s\"",   str3);
    PrintOKorERR( MyStrcmp(str2, str3) == 0);



	/* INPUT "12345679" */
	MyStrcpy(str3, str3);
	strcpy(str3, str3);

	printf("\n\nMyStrcpy output:   \"%s\"\n", str2);
	printf("strcpy output:     \"%s\"",   str3);
    PrintOKorERR( MyStrcmp(str2, str3) == 0);
}

/******************************************************************************
This FUNCTION will compare between MyStrCat and strcat in string.h library
*******************************************************************************/
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

    PrintInYellow("\nThis test will compare between MyStrCat ");
    PrintInYellow("and strcat in string.h library\n");

	/* first test comparison */
	printf("\n\nappends \"%s\" to \"%s\"\n\n", " four", str1);

	my_result      = MyStrCat(str1, " four");
	library_result = strcat(str2, " four");

	printf("MyStrCat output:   \"%s\"\n", my_result);
	printf("strcat output:     \"%s\"",   library_result);

	PrintOKorERR( MyStrcmp(my_result, library_result) == 0);


	/* second test comparison */
	printf("\n\nappends \"%s\" to \"%s\"\n\n", " second home", str3);

	my_result      = MyStrCat(str3, " second home");
	library_result = strcat(str4, " second home");


	printf("MyStrCat output:   \"%s\"\n", my_result);
	printf("strcat output:     \"%s\"",   library_result);

	PrintOKorERR( MyStrcmp(my_result, library_result) == 0);


	/* third test comparison */
	printf("\n\nappends \"%s\" to \"%s\"\n\n", "", str3);

	my_result      = MyStrCat(str3, "");
	library_result = strcat(str4, "");


	printf("MyStrCat output:   \"%s\"\n", my_result);
	printf("strcat output:     \"%s\"",   library_result);

	PrintOKorERR( MyStrcmp(my_result, library_result) == 0);
}

/******************************************************************************
This FUNCTION will compare between MyStrStr and strstr in string.h library
*******************************************************************************/
void TestMyStrStr ()
{
	char *my_result = NULL;
	char *library_result = NULL;

	/* first test variables */
	char str1[] = "one two three two one";
	char str2[] = "two";

	/* second test variables */
	char str3[] = "http://www.youtube.com";
	char str4[] = "It's not in here";

	const char *str5 = "";

    PrintInYellow("\nThis test will compare between MyStrStr ");
    PrintInYellow("and strstr in string.h library\n");

	/* first test comparison */
	printf("\n\nlook for \"%s\" in \"%s\"\n\n", str2, str1);

	my_result = MyStrStr(str1, str2);
	library_result = strstr(str1, str2);

	printf("MyStrStr output:   \"%s\"\n", my_result);
	printf("strstr output:     \"%s\"",   library_result);

    PrintOKorERR( strcmp(my_result, library_result) == 0);


	/* second test comparison */
	printf("\n\nlook for \"%s\" in \"%s\"\n\n", str4, str3);

	my_result = MyStrStr(str3, str4);
	library_result = strstr(str3, str4);

	printf("MyStrStr output:   \"%s\"\n", my_result);
	printf("strstr output:     \"%s\"", library_result);
	PrintOKorERR( my_result == library_result );


	/* third test comparison */
	printf("\n\nlook for \"%s\" in \"%s\"\n\n", "", str3);

	my_result = MyStrStr(str3, str5);
	library_result = strstr(str3, str5);

	printf("MyStrStr output:   \"%s\"\n", my_result);
	printf("strstr output:     \"%s\"", library_result);
	PrintOKorERR( my_result == library_result );
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +++++++++++++++++++++ END OF TESTS FUNCTIONS FOR STRINGS +++++++++++++++++++
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/***************************************************************************/
void PrintList(node_t *head)
{
    node_t *temp = head;

    while(temp!=NULL)
    {
      printf("| %ld |->", *((long *)temp->data) );
      temp = temp->next;
    }
    printf("%s\n", (temp==NULL)?("NULL"):("ERROR") );
}

/***************************************************************************/
void TestSListFlip()
{
    long arr[] = {1,2,3,4,5,6,7,8,9};
    /*long arr2[] = {9,8,7,6,5,4,3,2,1};*/
    node_t *node =  SListCreateNode(NULL, &arr[0] );
    node_t *head = node;
    size_t i = 0;

    PrintHeader("~SListFlip~");

    for ( i = 1 ; i < sizeof(arr) / sizeof(arr[0]) ; ++i)
    {
        node = SListInsertAfter(node, &arr[i]);
    }

    PrintInYellow("Before flip: (print head)\n");
    PrintList(head);

    head = SListFlipRecursively(head);

    PrintInYellow("\nAfter flip: (print head)\n");
    PrintList(head);
    PrintInYellow("Number of elements present as required: ");
    PrintOKorERR(SListCountNodes(head) == 9);
    PrintInYellow("\nElements flip algoritm behaves as reqired: ");
    PrintOKorERR((size_t)head->data == (size_t)&arr[8]); /*arr[8] == 9*/

    SListFreeAll(head);
}

/****************************************************************************
    StackSort implementation and testing
*****************************************************************************/
/*
**	test the push operation push and chekck count
*/
void pushTest(stack_t * stack, void *item, size_t size)
{
    size_t stack_count = StackCount(stack);

    StackPush(stack , item);

    if( StackCount(stack) == stack_count + 1)
    {
        printf(GREEN "StackCount %-3ld to %-3ld" RESET,
        		stack_count, StackCount(stack));
    }
    else
    {
        printf(RED "Count FALIED - from %ld to %ld" RESET,
        		stack_count, StackCount(stack));

    }

    if( !memcmp(StackPeek(stack), item ,size) )
    {
        printf("   %-3d was pushed  ", *(int*)StackPeek(stack));
        PrintOK;
    }
    else
    {
        printf(RED "   - Push FAILED \n" RESET);
    }
    printf("\n");
}

/*
**	testing pop and peek on empty  stack
*/
void PopTest(stack_t *stack)
{
	int i = StackCount(stack);

	printf("Before POP count is: %-2d\n", i);

	while( i )
	{
        printf("StackPeek(stack) : %-2d  ", *(int*)StackPeek(stack) );
        PrintOKorERR( i == *(int*)StackPeek(stack) );

		StackPop(stack);
		--i;
        printf("  After one POP count is: %-2ld  ",StackCount(stack));
        PrintOKorERR( i == (int)StackCount(stack));
        printf("\n");
	}

    printf(YELLOW"\nTrying POP on empty stack\n"RESET);
    StackPop(stack);
    printf("StackCount after POP on an empty stack: %ld",StackCount(stack));
    PrintOKorERR( 0 == StackCount(stack) );

    printf(YELLOW"\n\nTrying StackPeek on empty stack\n"RESET);

    if( StackPeek(stack) == NULL )
    {
        printf(GREEN "StackPeek on empty stack , got NULL !\n"RESET);
    }
    else
    {
        printf(RED "StackPeek on empty stack ,ERROR\n"RESET);
    }

    printf(BLUE"\nif you see this like than it didnt crush\n"RESET);
}

/******************************************************************************
  Testing the stack with type int
******************************************************************************/
void TestStackWithINT()
{

    stack_t *stack = StackCreate( sizeof(int),20);

    int c[] ={18,13,14,11,19,20,9,15,7,3,4,1,2,10,8,16,17,12,5,6};
    int i= 0;

    PrintHeader("Test type ~int~ with Stack");
    printf(YELLOW "\nTesting push and StackPeek:\n" RESET);

    for(i=0; i < 20 ; i++)
    {
        pushTest(stack,&c[i], sizeof(c[1]));
    }

    printf( YELLOW"\nTesting pushing beyond stack capacity:\n" RESET);
    printf("%s\n",  (StackPush(stack,&c))?
                    (RED "StackPush was performed" RESET):
                    (GREEN "StackPush was not performed" RESET) );

    StackSort(stack);

    printf( YELLOW "\nTesting poping stack capacity:\n" RESET);
    PopTest(stack);
    StackDestroy(stack);
}
