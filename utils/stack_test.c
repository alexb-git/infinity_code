/* Author: Alex B
** Last update: 13.09.17 20:00
** Program: Stack data structure
*/
#include <string.h>	/* memcpy */
#include <stdio.h>  /* printf */
#include "stack.h"


#define GREEN	"\x1b[32m"
#define RED		"\x1b[31m"
#define YELLOW	"\x1b[93m"
#define RESET	"\x1b[0m"
#define BLUE	"\x1B[34m"
#define WHITE	"\x1B[37m"


/* tests aid functions */
void PrintHeader(char *function_name);
void CompareAndPrint(size_t func_result, size_t ex_result);

/* test function */
void TestStackWithINT();
/* sub test functions */
void pushTest(stack_t * stack, void *item, size_t size);
void PopTest(stack_t *stack);

void TestStackWithLONG();
void TestStackWithSHORT();
void TestStackWithLONGDOUBLE();

int main(int argc, char const *argv[])
{
	TestStackWithINT();
	TestStackWithLONG();
    TestStackWithSHORT();
    TestStackWithLONGDOUBLE();


	return 0;
}


/*******************************************************************************
  FUNCTION that compares between the two inputes and prints accordingly
*******************************************************************************/
void CompareAndPrint(size_t func_result, size_t ex_result)
{
        if (func_result == ex_result)
        {
                printf(GREEN " [== CORRECT ==] " RESET "\n");
        }
        else
        {
                printf(RED " [== INCORRECT ==] " RESET "\n");
        }
}


/******************************************************************************
  auxiliary function for the tests functions. simply prints colorful header
  with function name that we test
******************************************************************************/
void PrintHeader(char *function_name)
{
	printf(	YELLOW "\n\t-------------------- %s ---------------------\n" 
			RESET, function_name);
}



/*
**	test the push operation push and chekck count
*/
void pushTest(stack_t * stack, void *item, size_t size)
{
    size_t stack_count = StackCount(stack);

    StackPush(stack , item);

    if( StackCount(stack) == stack_count + 1)
    {
        printf(GREEN "Count OK - from %-2ld to %-2ld" RESET,
        		stack_count,StackCount(stack));
    }
    else
    {
        printf(RED "Count FALIED - from %-2ld to %-2ld" RESET,
        		stack_count,StackCount(stack));

    }

    if( !memcmp(StackPeek(stack), item ,size) )
    {
        printf(GREEN "   - Push OK\n" RESET);
    }
    else
    {
        printf(RED "   - Push FAILED \n" RESET);
    }
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
		StackPop(stack);
		--i;
        printf("After one POP count is: %-2ld  ",StackCount(stack));
        CompareAndPrint((size_t)i, (size_t)StackCount(stack));
	}


    printf(YELLOW"\nTrying POP on empty stack\n"RESET);
    StackPop(stack);
    printf("StackCount after POP on an empty stack: %ld",StackCount(stack));
    CompareAndPrint(0, (size_t)StackCount(stack));


    printf(YELLOW"\nTrying StackPeek on empty stack\n"RESET);

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

    int c[] ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
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
  

    printf( YELLOW "\nTesting poping stack capacity:\n" RESET);
    PopTest(stack);
    StackDestroy(stack);
}

/******************************************************************************
  Testing the stack with type long
******************************************************************************/
void TestStackWithLONG()
{

    stack_t *stack = StackCreate( sizeof(long),20);

    long c[] ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int i= 0;

    PrintHeader("Test type ~long~ with Stack");
    printf(YELLOW "\nTesting push and StackPeek:\n" RESET);

    for(i=0; i < 20 ; i++)
    {
        pushTest(stack, &c[i], sizeof(c[1]) );
    }

    printf(	YELLOW"\nTesting pushing beyond stack capacity:\n" RESET);
    printf("%s\n", 	(StackPush(stack,&c))?
    				(RED "StackPush was performed" RESET):
    				(GREEN "StackPush was not performed" RESET) );
  

    printf(	YELLOW "\nTesting poping stack capacity:\n" RESET);
    PopTest(stack);
    StackDestroy(stack);
}

/******************************************************************************
  Testing the stack with type short
******************************************************************************/
void TestStackWithSHORT()
{

    stack_t *stack = StackCreate( sizeof(long),20);

    long c[] ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int i= 0;

    PrintHeader("Test type ~short~ with Stack");
    printf(YELLOW "\nTesting push and StackPeek:\n" RESET);

    for(i=0; i < 20 ; i++)
    {
        pushTest(stack, &c[i], sizeof(c[1]) );
    }

    printf( YELLOW"\nTesting pushing beyond stack capacity:\n" RESET);
    printf("%s\n",  (StackPush(stack,&c))?
                    (RED "StackPush was performed" RESET):
                    (GREEN "StackPush was not performed" RESET) );
  

    printf( YELLOW "\nTesting poping stack capacity:\n" RESET);
    PopTest(stack);
    StackDestroy(stack);
}


/******************************************************************************
  Testing the stack with type long double
******************************************************************************/
void TestStackWithLONGDOUBLE()
{

    stack_t *stack = StackCreate( sizeof(long double),20);

    long double c[] ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int i= 0;

    PrintHeader("Test type ~long double~ with Stack");
    printf(YELLOW "\nTesting push and StackPeek:\n" RESET);

    for(i=0; i < 20 ; i++)
    {
        pushTest(stack, &c[i], sizeof(c[1]) );
    }

    printf( YELLOW"\nTesting pushing beyond stack capacity:\n" RESET);
    printf("%s\n",  (StackPush(stack,&c))?
                    (RED "StackPush was performed" RESET):
                    (GREEN "StackPush was not performed" RESET) );
  

    printf( YELLOW "\nTesting poping stack capacity:\n" RESET);
    PopTest(stack);
    StackDestroy(stack);
}