/* Author: Alex B
** Last update: 24.09.17 09:30
** Program: Tests for Singly Linked List
*/

#include <stdio.h>	/* printf */
#include "slist.h"

#define GREEN	"\x1b[32m"
#define RED		"\x1b[31m"
#define YELLOW	"\x1b[93m"
#define RESET	"\x1b[0m"
#define BLUE	"\x1B[34m"
#define WHITE	"\x1B[37m"

#define PrintInYellow(X)  ( printf(YELLOW X RESET) )
#define PrintInGreen(X)   ( printf(GREEN  X RESET) )
#define PrintInRed(X)     ( printf(RED    X RESET) )

/*
1. test SlistInsert
	- insert from array, check count and order
2. test SListInsertAfter
	- insert from array, check count and order
3. test TestSListRemove
	- remove elements from head, check count and behaviour (order of data)
4. test TestSListRemoveAfter
	- remove elements from head, check count and behaviour (order of data)
5. test TestSListCountNodes
	- create list, count nodes, remove some, count again
6. test TestSListFind
	- try to find elements that doesn't exist,
	  try to find elements that exist,
	  try to find the last element
7. test TestSListFlip
	- create list, flip it, count it, verify flipped order of data
8. test TestSListForEach
	- create list, call function with argument that effects half of the list,
	  call function with argument that effects till last node,
	  call function with argument that effects all of the list (till NULL)
9. test SListFindIntersection
	- create 3 lists, manually intersect two of them and call this function,
	  call this function with two lists that has no intersections
10. test TestSListHasLoop
	- create list, manually make a loop, call this function and
	  verify expected behaviour (correct function output)
*/

void TestSListInsert();
void TestSListInsertAfter();
void TestSListRemove();
void TestSListRemoveAfter();
void TestSListCountNodes();
void TestSListFind();
void TestSListFlip();
void TestSListForEach();
void TestSListFindIntersection();
void TestSListHasLoop();

/* prints the list. visual aid for the test functions */
void PrintList(node_t *head);

/* 	Created to test the SListFind function. This function converts the
	two args into long type and compares them.
	return value: 0 - equal, 1 - not equal */
int myLongCmp( const void *data_1, const  void *data_2);

/* 	Created to test the SListForEach function. This function checks
	if arg is divisible by param(eter) without remainder */
int MultIfNotDivisibleByParam(node_t *head, void *param);

/******************************************************************************
    auxiliary function for the tests functions. simply prints colorful header
    with function name that we test
******************************************************************************/
static void PrintHeader(char *function_name)
{
    printf(	BLUE
			"\n\t-----This is a test for %s function-----\n"
			RESET, function_name);
}


/******************************************************************************
    auxiliary function for the tests functions. simply prints colorful
    bottom header with function name that we test
******************************************************************************/
static void PrintBottomHeader(char *function_name)
{
    printf(	BLUE
			"\n\t-----end of test for %s function-----\n"
			RESET, function_name);
}


/*******************************************************************************
        FUNCTION that compares between the two inputes and prints accordingly
*******************************************************************************/
void CompareAndPrint(size_t func_result, size_t ex_result)
{
    if (func_result == ex_result)
    {
		PrintInGreen(GREEN" [== SUCCESS ==] \n"RESET);
    }
    else
    {
		PrintInRed(RED" [== FAIL ==] \n"RESET);
    }
}


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

/*******************************************************************************
	Created to test the SListFind function. This function converts the
	two args into long type and compares them.
	return value: 0 - equal, 1 - not equal
******************************************************************************/
int myLongCmp( const void *data_1, const void *data_2)
{
    return !( (long*)data_1 == (long*)data_2 );
}


/***************************************************************************/
void TestSListInsert()
{
	long arr[] = {1,2,3,4,5,6,7,8,9};
	node_t *node =  SListCreateNode(NULL, &arr[0] );
    int i = 0;

    PrintHeader("~SListInsert Before~");

    PrintInYellow("Inserting 9 elements\n");

    for( i = 1 ; i < sizeof(arr)/sizeof(arr[0]) ; ++i )
    {
        node = SListInsert(node, &arr[i]);
        PrintList(node);
    }
	PrintInYellow("\nElements insurtion algoritm behaves as reqired: ");
	CompareAndPrint((size_t)node->data, (size_t)&arr[8]);
	PrintInYellow("Number of elements inserted  as required: ");
	CompareAndPrint(SListCountNodes(node), 9);

	SListFreeAll(node);

	PrintBottomHeader("~SListInsert Before~");
}


/***************************************************************************/
void TestSListInsertAfter()
{

	long arr[] = {1,2,3,4,5,6,7,8,9};
	node_t *node =  SListCreateNode(NULL, &arr[0] );
    node_t *head = node;
    int i = 0;

    PrintHeader("~SListInsertAfter~");

    PrintInYellow("Inserting 9 elements\n");

    for( i = 1 ; i < sizeof(arr)/sizeof(arr[0]) ; ++i )
    {
        node = SListInsertAfter(node, &arr[i]);
        PrintList(head);
    }
	PrintInYellow("\nElements insurtion algoritm behaves as reqired: ");
	CompareAndPrint((size_t)node->data, (size_t)&arr[8]);
	PrintInYellow("Number of elements inserted  as required: ");
	CompareAndPrint(SListCountNodes(head), 9);

	SListFreeAll(head);

	PrintBottomHeader("~SListInsertAfter~");
}


/***************************************************************************/
void TestSListRemove()
{
	long arr[] = {1,2,3,4,5,6,7,8,9};
    node_t *node =  SListCreateNode(NULL, &arr[0] );
    node_t *head = node;
    int i = 0;

    PrintHeader("~SListRemove~");

    for( i = 1 ; i < sizeof(arr)/sizeof(arr[0]) ; ++i )
    {
        node = SListInsertAfter(node, &arr[i]);
    }

    PrintInYellow("Before ~SListRemove~ two elements:\n");
    PrintList(head);

	PrintInYellow("\nAfter ~SListRemove~ two elements:\n");
    head = SListRemove(head);
    head = SListRemove(head);
    PrintList(head);
	CompareAndPrint((size_t)head->data, (size_t)&arr[2]); /* arr[2] == 3 */

    PrintInYellow("Removing last (should not change):\n");
    SListRemove(node);
    PrintList(head);
	CompareAndPrint((size_t)head->data, (size_t)&arr[2]); /* arr[2] == 3 */

    SListFreeAll(head);

    PrintBottomHeader("~SListRemove~");
}


/***************************************************************************/
void TestSListRemoveAfter()
{
	long arr[] = {1,2,3,4,5,6,7,8,9};
    node_t *node =  SListCreateNode(NULL, &arr[0] );
    node_t *head = node;
    int i = 0;

    PrintHeader("~SListRemoveAfter~");

    for( i = 1 ; i < sizeof(arr)/sizeof(arr[0]) ; ++i )
    {
        node = SListInsertAfter(node, &arr[i]);
    }

    PrintInYellow("Before ~SListRemoveAfter~ first two elements:\n");
    PrintList(head);

    head = SListRemoveAfter(head);
    head = SListRemoveAfter(head);

    PrintInYellow("\nAfter ~SListRemoveAfter~");
    PrintInYellow(" first two elements after head:\n");

    PrintList(head);
	CompareAndPrint((size_t)head->next->data, (size_t)&arr[3]); /*arr[3]==4*/

    PrintInYellow("Removing last (should not change):\n");

    SListRemoveAfter(node);
    PrintList(head);
	CompareAndPrint((size_t)head->next->data, (size_t)&arr[3]); /*arr[3]==4*/

    SListFreeAll(head);
    PrintBottomHeader("~SListRemoveAfter~");
}


/***************************************************************************/
void TestSListCountNodes()
{
	long arr[] = {1,2,3,4,5,6,7,8,9};
	node_t *node =  SListCreateNode(NULL, &arr[0] );
    node_t *head = node;
    int i = 0;

    PrintHeader("~SListCountNodes~");
    PrintInYellow("Creating list of 9 nodes...\n");

    for( i = 1 ; i < sizeof(arr)/sizeof(arr[0]) ; ++i )
    {
        node = SListInsertAfter(node, &arr[i]);
    }

    printf("SListCountNodes: %lu", SListCountNodes( head ));
    CompareAndPrint(SListCountNodes( head ), 9);

    head = SListRemoveAfter(head);
    head = SListRemoveAfter(head);
    head = SListRemoveAfter(head);

    PrintInYellow("After removing 3 nodes...\n");
    printf("SListCountNodes: %lu", SListCountNodes( head ));
	CompareAndPrint(SListCountNodes( head ), 6);

	SListFreeAll(head);
	PrintBottomHeader("~SListCountNodes~");
}


/***************************************************************************/
void TestSListFind()
{
	long arr[] = {1,2,3,4,5,6,7,8,9,10};
    node_t *node =  SListCreateNode(NULL, &arr[0] );
    node_t *head = node;
    node_t *find_node = NULL;
    int i = 0;

    PrintHeader("~SListFind~");

    for( i = 1 ; i < 9 ; ++i )
    {
        node = SListInsertAfter(node, &arr[i]);
    }

    PrintList(head);

    printf("\nTrying to find "YELLOW"10"RESET" (doesn't exist) - ");
    find_node = SListFind(head, myLongCmp, &arr[9]);
	printf("%s", (find_node != NULL) ? ("Found  ") : ("Not found  "));
    CompareAndPrint(find_node != NULL, 0); /* '!=NULL' => found, 1 */


    printf("\nTrying to find "YELLOW"9"RESET"  (last element) - ");
    find_node = SListFind(head, myLongCmp, &arr[8]);
	printf("%s", (find_node != NULL) ? ("Found  ") : ("Not found  "));
	CompareAndPrint(find_node != NULL, 1); /* '!=NULL' => found, 1 */


	printf("\nTrying to find "YELLOW"1"RESET"  (first element) - ");
	find_node = SListFind(head, myLongCmp, &arr[0]);
	printf("%s", (find_node != NULL) ? ("Found  ") : ("Not found  "));
	CompareAndPrint(find_node != NULL, 1); /* '!=NULL' => found, 1 */


    SListFreeAll(head);
    PrintBottomHeader("~SListFind~");
}


/***************************************************************************/
void TestSListFlip()
{
	long arr[] = {1,2,3,4,5,6,7,8,9};
	/*long arr2[] = {9,8,7,6,5,4,3,2,1};*/
    node_t *node =  SListCreateNode(NULL, &arr[0] );
    node_t *head = node;
    int i = 0;

    PrintHeader("~SListFlip~");

	for ( i = 1 ; i < sizeof(arr) / sizeof(arr[0]) ; ++i)
    {
        node = SListInsertAfter(node, &arr[i]);
    }

	PrintInYellow("Before flip: (print head)\n");
    PrintList(head);

    head = SListFlip(head);

	PrintInYellow("\nAfter flip: (print head)\n");
    PrintList(head);
	PrintInYellow("Number of elements present as required: ");
	CompareAndPrint(SListCountNodes(head), 9);
	PrintInYellow("Elements flip algoritm behaves as reqired: ");
	CompareAndPrint((size_t)head->data, (size_t)&arr[8]); /* arr[8] == 9 */

    SListFreeAll(head);
    PrintBottomHeader("~SListFlip~");
}


/***************************************************************************
	Created to test the SListForEach function. This function checks
	if arg is divisible by param(eter) without remainder
***************************************************************************/
int MultIfNotDivisibleByParam(node_t *head, void *param)
{
	int result = 0;

	if (*(long*)head->data % *(long*)param != 0)
	{
		*(long*)head->data *= 2;
		result = 1;
	}

	return result;
}


/***************************************************************************/
void TestSListForEach()
{
	long arr[] = { 1,2,3,4,5,6,7,20 };
	long modulu  = 0;

	node_t *node = SListCreateNode(NULL, &arr[0]);
	node_t *head = node;
	node_t *for_each_result = NULL;
	int i = 0;

	PrintHeader("~SListForEach~");

	for ( i = 1 ; i < sizeof(arr) / sizeof(arr[0]) ; ++i)
	{
		node = SListInsertAfter(node, &arr[i]);
	}

	PrintList(head);

	modulu = 5;
	PrintInYellow("\nMultiply by two if number is not divisible by 5 ");
	PrintInYellow("(stop in the middle):\n");
	for_each_result = SListForEach(head, MultIfNotDivisibleByParam, &modulu);
	PrintList(head);
	CompareAndPrint( *(long*)for_each_result->data, 5);

	modulu = 20;
	PrintInYellow("\nMultiply by two if number is not divisible by 20 ");
	PrintInYellow("(last element)\n");
	for_each_result = SListForEach(head, MultIfNotDivisibleByParam, &modulu);
	PrintList(head);
	CompareAndPrint(*(long*)for_each_result->data, 20);

	modulu = 21;
	PrintInYellow("\nMultiply by two if number is not divisible by 21 ");
	PrintInYellow("(end of the list)\n");
	for_each_result = SListForEach(head, MultIfNotDivisibleByParam, &modulu);
	PrintList(head);
	/* made it to the end of the list */
	CompareAndPrint(for_each_result == NULL, 1);

	SListFreeAll(head);
	PrintBottomHeader("~SListForEach~");
}


/***************************************************************************/
void TestSListFindIntersection()
{
	long arr_1[] = { 1,2,3,4,5,6,7,8 };
	long arr_2[] = { 21,22,23,24,25 };
	long arr_3[] = { 31,32,33,34,35 };
	int i = 0;
	node_t *intersection = NULL;

	node_t *node1 = SListCreateNode(NULL, &arr_1[0]);
	node_t *head1 = node1;

	node_t *node2 = SListCreateNode(NULL, &arr_2[0]);
	node_t *head2 = node2;

	node_t *node3 = SListCreateNode(NULL, &arr_3[0]);
	node_t *head3 = node3;

	PrintHeader("~SListFindIntersection~");

	for ( i = 1 ; i < sizeof(arr_1) / sizeof(arr_1[0]) ; ++i)
	{
		node1 = SListInsertAfter(node1, &arr_1[i]);
	}

	for ( i = 1 ; i < sizeof(arr_2) / sizeof(arr_2[0]) ; ++i)
	{
		node2 = SListInsertAfter(node2, &arr_2[i]);
	}

	/* Creating intersection with list 1 and list 2 */
	node2->next = head1->next->next->next;

	for ( i = 1 ; i < sizeof(arr_3) / sizeof(arr_3[0]) ; ++i)
	{
		node3 = SListInsertAfter(node3, &arr_3[i]);
	}

	PrintInYellow("List #1:\n");
	PrintList(head1);

	PrintInYellow("\nList #2 (has intersection with list 1 at");
	PrintInYellow(" data value | 4 |):\n");
	PrintList(head2);

	PrintInYellow("\nList #3 (doesn't have any intersection");
	PrintInYellow(" with other lists):\n");
	PrintList(head3);


	PrintInYellow("\nFunction result (SListFindIntersection");
	PrintInYellow(" with list 1 and list 2): ");
	if ((intersection = SListFindIntersection(head1, head2)) != NULL)
	{
		printf(	GREEN  "\nThere is intersection at data value | %lu |  "
				RESET  ,*(long*)intersection->data);
	}
	else
	{
		printf(RED "There is NO intersection  " RESET);
	}
	CompareAndPrint( *(long*)intersection->data, 4);


	PrintInYellow("\nFunction result (SListFindIntersection");
	PrintInYellow(" with list 1 and list 3): ");

	if (SListFindIntersection(head1, head3) != NULL)
	{
		printf(RED"\nThere is intersection  "RESET);
	}
	else
	{
		printf(GREEN"\nThere is NO intersection  "RESET);
	}
	CompareAndPrint(SListFindIntersection(head1, head3) == NULL, 1);


	node2->next = NULL; /* manually break the intersection */
	SListFreeAll(head1);
	SListFreeAll(head2);
	SListFreeAll(head3);

	PrintBottomHeader("~SListFindIntersection~");

}


/***************************************************************************/
void TestSListHasLoop()
{
	long arr[] = { 1,2,3,4,5,6,7,8,9 };

	node_t *tail = SListCreateNode(NULL, &arr[0]);
	node_t *head = tail;
	int result_hasloop = 0;
	int i = 0;

	PrintHeader("~SListHasLoop~");

	for (i = 1; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		tail = SListInsertAfter(tail, &arr[i]);
	}

	PrintInYellow("Before creating a loop:\n");
	PrintList(head);
	result_hasloop = SListHasLoop(head);
	printf(YELLOW "Function result: %s" RESET,
		(result_hasloop) ? ("1 - there is a loop") : ("0 - there is no loop"));
	CompareAndPrint(result_hasloop, 0);


	PrintInYellow("\n\nManually create a loop...\n");
	PrintInYellow("tail (last list node) connected to node with data ");
	printf(YELLOW "value | %lu |...\n" RESET, *(long*)head->next->next->data);

	/* manually create a loop */
	tail->next = head->next->next;
	result_hasloop = SListHasLoop(head);

	printf(	YELLOW "\nFunction result: %s" RESET,
			(result_hasloop)?("1 - there is a loop"):("0 - there is no loop"));
	CompareAndPrint(result_hasloop, 1);

	/* manually disconnected the loop and free it */
	tail->next = NULL;
	SListFreeAll(head);

	PrintBottomHeader("~SListHasLoop~");
}


/***************************************************************************/
void TestSlist()
{
    TestSListInsert();
    TestSListInsertAfter();
    TestSListRemove();
    TestSListRemoveAfter();
    TestSListCountNodes();
    TestSListFind();
    TestSListFlip();
	TestSListForEach();
	TestSListFindIntersection();
	TestSListHasLoop();
}


int main()
{
	TestSlist();

    return 0;
}
