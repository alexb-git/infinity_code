/****************************************************************************
** Filename:    - sortesorted_list_test.c
** Code Author: - all right reserved Alex, Adam, Ran, Ronen, Eyal
** Purpose:     - testing the Sorted Linked List
** Date:        - 03/10/2017
** Version:     - 234
** Standard quality: The highest rank - Alex convention
*****************************************************************************/
#include <stdio.h>          /* printf */
#include "sortedlist.h"     /* Sorted Linked List DS */

#define GREEN	"\x1b[92m"
#define RED		"\x1b[91m"
#define YELLOW	"\x1b[93m"
#define YELLOWS	"\x1b[33m"
#define RESET	"\x1b[0m"
#define BLUE	"\x1B[94m"
#define WHITE	"\x1B[37m"

/****************************************************************************
    Helpful defines
*****************************************************************************/
#define PrintHeader(X)      printf(BLUE "\n\t--------- This is a test for: ~"\
                                    X" ---------\n" RESET)

#define PrintInYellow(X)  ( printf(YELLOW X RESET) )
#define PrintInGreen(X)   ( printf(GREEN  X RESET) )
#define PrintInRed(X)     ( printf(RED    X RESET) )
#define PrintOK           ( printf(GREEN "%s" RESET, "-OK") )
#define PrintERR          ( printf(RED "%s" RESET, "-ERR") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )

#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/*******************************************************************************
	Created to test the SListFind function. This function converts the
	two args into long type and compares them.
    return value: 0 - data is equal, negative integer if 2 is bigger than 1,
                  positive integer if 1 is bigger than 2.
******************************************************************************/
int myLongCmp( const void *data_1, const void *data_2)
{
    return ( *(long*)data_1 - *(long*)data_2 );
}

/***************************************************************************
	Created to test the SListForEach function. This function checks
	if arg is divisible by param(eter) without remainder
***************************************************************************/
int SmallerThanParam(void *node_data, void *param)
{
    return ( *(long*)node_data < *(long*)param );
}

/****************************************************************************
    Aux functions for the test functions
*****************************************************************************/
void ListInfoAndComp(sorted_list_t *list, int ex_is_em, size_t ex_size)
{
    printf(YELLOWS "|IsEmpty|: " RESET);
    printf("%d  ", SortedListIsEmpty(list));                  /* |IsEmpty|    */
    (SortedListIsEmpty(list)==ex_is_em)?(PrintOK):(PrintERR); /* |T IsEmpty|  */

    printf(YELLOWS "  |Size|: " RESET);
    printf("%ld  ", SortedListSize(list));                    /* |Size|       */
    (SortedListSize(list)==ex_size)?(PrintOK):(PrintERR);     /* |T Size|     */

    printf("\n");

    /*ListInfoAndComp(queue_1, 0, 10);*/  /*|IsEmpty||T IsEmpty||Size||T Size|*/
}

/****************************************************************************/
void Printlist(sorted_list_t *list)
{
    sorted_list_itr_t itr = SortedListBegin(list);
    sorted_list_itr_t end =   SortedListEnd(list);

    printf("\x1b[90m" "NULL<->" RESET);

    for ( ; !SortedListSameIterator(itr, end) ; itr = SortedListNext(itr) )
    {
        printf("| %ld |<->", *(long*)SortedListGetData(itr));
    }
    printf("\x1b[90m" "NULL  " RESET);
}

/****************************************************************************/
void VerifySumOfElements(sorted_list_t *list, long ex_sum)
{
    sorted_list_itr_t itr = SortedListBegin(list);
    sorted_list_itr_t end =   SortedListEnd(list);
    long sum = 0;

    for ( ; !SortedListSameIterator(itr, end) ; itr = SortedListNext(itr) )
    {
        sum += *(long*)SortedListGetData(itr);
    }

    printf(YELLOWS "\nVerify Sum Of Elements: " RESET);
    ( sum == ex_sum )?(PrintOK):(PrintERR);
}

/****************************************************************************/
void VerifyOrderOfElements(sorted_list_t *list, long *arr, int flag)
{
    /* flag = 0 - increase each loop,  flag = 1 - decrease each loop,*/
    sorted_list_itr_t itr = SortedListBegin(list);
    sorted_list_itr_t end =   SortedListEnd(list);

    PrintInYellow("\n\n--> Verify order of elements\n");

    for ( ; !SortedListSameIterator(itr, end) ; itr = SortedListNext(itr) )
    {
        if ( arr == (long*)SortedListGetData(itr) )
        {
            PrintOK; printf(" ");
        }
        else
        {
            PrintERR; printf(" ");
        }
        (flag)?(--arr):(++arr);
    }
}

/****************************************************************************/
void SimRandomInsertion(sorted_list_t *list, long insert_arr[])
{
    sorted_list_itr_t itr;
    long order_arr[] = {1,8,9,7,5,0,4,6,2,3,10};    /* 11 elements */
                     /*{0,1,2,3,4,5,6,7,8,9,10};*/
    long i = 0;

    PrintInYellow("Insertion order");
    while ( i < SizeArr(order_arr) )
    {
        itr = SortedListInsert(list, &insert_arr[order_arr[i]]);
        printf(" -> %ld", *(long*)SortedListGetData(itr));
        ++i;
    }

    printf("\n\n");
}

/****************************************************************************/
void InsertFindErasePop()
{
    sorted_list_t          *list = SortedListCreate(myLongCmp);
    sorted_list_itr_t       itr  = SortedListEnd(list);
    sorted_list_itr_t  NULL_itr  = SortedListEnd(list);

	long arr[] = {1,2,2,3,4,5,6,7,8,9,9}; /* 11 elements */
    long sixsix = 66;
    NULL_itr.itr = NULL;

    PrintHeader("Insert Pop back/front Find Erase");

    PrintInYellow("\n--> Create Sorted List\n");
    ListInfoAndComp(list, 1, 0);  /*|IsEmpty||T IsEmpty||Size||T Size|*/

    PrintInYellow("\n--> Insert 11 values randomly\n");
    SimRandomInsertion(list,arr);
    ListInfoAndComp(list, 0, 11); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    Printlist(list);

    VerifyOrderOfElements(list, arr, 0);
    VerifySumOfElements(list, 56);

    PrintInYellow("\n\n--> Pop front\n");
    itr = SortedListPopFront(list);
    ListInfoAndComp(list, 0, 10); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    Printlist(list);
    printf("\nElement after poped | %ld | ", *(long*)SortedListGetData(itr));
    PrintOKorERR((long*)SortedListGetData(itr)==&arr[1]);
    VerifySumOfElements(list, 55);

    PrintInYellow("\n\n--> Pop back:\n");
    itr = SortedListPopBack(list);
    ListInfoAndComp(list, 0, 9); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    Printlist(list);
    printf("\nElement before poped | %ld | ", *(long*)SortedListGetData(itr));
    PrintOKorERR((long*)SortedListGetData(itr)==&arr[9]);
    VerifySumOfElements(list, 46);

    PrintInYellow("\n\n--> Find element | 9 | and erase it (last element)\n");
    itr = SortedListFind(list, &arr[9]); /* arr[9]==9 */
    SortedListErase(list, itr);
    ListInfoAndComp(list, 0, 8); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    Printlist(list);
    VerifySumOfElements(list, 37);

    PrintInYellow("\n\n--> Find element | 3 | and erase it (regular case)\n");
    itr = SortedListFind(list, &arr[3]); /* arr[3]==3 */
    SortedListErase(list, itr);
    ListInfoAndComp(list, 0, 7); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    Printlist(list);
    VerifySumOfElements(list, 34);

    PrintInYellow("\n\n--> Find element | 2 | and erase it (first element)\n");
    itr = SortedListFind(list, &arr[1]); /* arr[1]==2 */
    SortedListErase(list, itr);
    ListInfoAndComp(list, 0, 6); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    Printlist(list);
    VerifySumOfElements(list, 32);

    PrintInYellow("\n\n--> Find element | 66 | (desn't exist)\n");
    itr = SortedListFind(list, &sixsix); /* arr[1]==2 */
    (SortedListSameIterator(NULL_itr,itr))
    ?( printf(GREEN "iterator that holds NULL was returned" RESET) )
    :( printf(RED "iterator that DOESN'T hold NULL was returned" RESET) );
    VerifySumOfElements(list, 32);


    PrintInYellow("\n\n--> PopBack till empty\n");
    while ( !SortedListIsEmpty(list) )
    {
        SortedListPopBack(list);
        Printlist(list);
        printf("\n");
    }

    PrintInYellow("\n\n--> PopFront on an empty list\n");
     (SortedListSameIterator(SortedListPopFront(list), SortedListEnd(list)))
    ?( printf(GREEN "List end was returned" RESET)     )
    :( printf(RED "List end was NOT returned" RESET)   );

    PrintInYellow("\n\n--> PopBack on an empty list\n");
     (SortedListSameIterator(SortedListPopFront(list), SortedListEnd(list)))
    ?( printf(GREEN "List end was returned" RESET)     )
    :( printf(RED "List end was NOT returned" RESET)   );


    printf("\n");
    SortedListDestroy(list);
}


/****************************************************************************
    Compare function between function result and expected result
*****************************************************************************/
static void CompareValues(long func_result, long exp_result,
                   char *name)
{
	if ((func_result) == (exp_result))
	{
		printf(GREEN "\n%s ---->>> SUCCESS\n" RESET, name);
		printf("Result is:%ld\n\n",  func_result);
	}
	else
	{
		printf(RED "\n%s ---->>> FAILURE\n" RESET, name);
		printf("Func result: :%ld\n", ( func_result));
		printf("Func exp_result: :%ld\n\n", ( exp_result));
	}
}

/*  boolean function that is provided by the user.
    receives a `node` and paramaters(`param`), then execute a statments
    and return true or false / or an integer number. */
 int IsDataDifferFromParam(void *data, void *param)
 {

 	return ((*(long*)(data)) != (*(long*) param));

 }


static void TestSortedListForEach(void)
{
	size_t   i = 0;
	long arr[] = {0, 1, 2, -3, 4, 5, -6, 7, 8, 9, -1, -4, 12};

	sorted_list_t *list = SortedListCreate(myLongCmp);
    long func_result = 0;
    long exp_result  = 0;
    sorted_list_itr_t itr;
    sorted_list_itr_t itr_end;

    sorted_list_itr_t  NULL_itr  = SortedListEnd(list);
    NULL_itr.itr = NULL;

	itr_end = SortedListEnd(list);

	for (i = 0; i < 10; ++i)
	{
		 SortedListInsert(list, &arr[i]);

	}

    PrintHeader("Test ForEach");

	/* bool failue in the 1th node */
	itr = SortedListForEach(SortedListBegin(list), itr_end,
                            IsDataDifferFromParam, &arr[6] );

	/* "check DlistForEach - bool failue in the 1th node") */
    PrintInYellow("\n-->Searching for an element differ from 0\n");
	PrintInYellow("(The bool func should fail in the first element)\n");
	func_result = *(long*) SortedListGetData(itr);
	exp_result = -6;
	Printlist(list);
	CompareValues(func_result, exp_result, "check DlistForEach");


	/* bool failue in the middle node of the dlist */
	itr = SortedListForEach(SortedListBegin(list), itr_end,
                            IsDataDifferFromParam, &arr[4]);

	/* "check DlistForEach - bool failue in the 1th node") */
    PrintInYellow("\n-->Searching for an element differ from 4\n");
    PrintInYellow("(The bool func should failed in middle of list)\n");
	func_result = *(long*) SortedListGetData(itr);
	exp_result = 4;
	Printlist(list);
	CompareValues(func_result, exp_result, "check DlistForEach");


	/* bool failue in the middle node of the dlist */
	itr = SortedListForEach(SortedListBegin(list), itr_end,
                            IsDataDifferFromParam, &arr[9]);

	/* "check DlistForEach - bool failue in the end node") */
    PrintInYellow("\n-->Searching for an element differ from  9\n");
    PrintInYellow("(The bool func should failed with the last element)\n");
	func_result = *(long*) SortedListGetData(itr);
	exp_result = 9;
	Printlist(list);
	CompareValues(func_result, exp_result, "check DlistForEach");


      /* check  DlistForEach - bool func didnt fail")
         bool func didnt fail */
    PrintInYellow("\n-->Searching for an element differ from  -1\n");
    PrintInYellow("(Element doesn't exist - return NULL)\n");
	itr = SortedListForEach(SortedListBegin(list),
                            itr_end, IsDataDifferFromParam,&arr[10]);

    (SortedListSameIterator(NULL_itr, itr))
    ?( printf(GREEN "iterator that holds NULL was returned\n" RESET) )
    :( printf(RED "iterator that DOESN'T hold NULL was returned\n" RESET) );

	itr     = SortedListNext(SortedListNext(SortedListBegin(list)));
	itr_end = SortedListPrev(SortedListPrev(  SortedListEnd(list)));

	/* Get sub dlist and check operate bool func */
	itr = SortedListForEach(itr, itr_end,
                            IsDataDifferFromParam, &arr[7]);


	/* "check DlistForEach - bool failue in the middle node") */
    PrintInYellow("\n-->Searching for element differ 7 in sub dlist");
    PrintInYellow("\n(without 2 nodes in each edge)\n");
	func_result = *(long*) SortedListGetData(itr);
	exp_result = 7;
	Printlist(list);
	CompareValues(func_result, exp_result, "check DlistForEach");

    /* Get sub dlist and check operate bool func */
    itr = SortedListForEach(itr, itr_end,
                            IsDataDifferFromParam, &arr[8]);

    /* "check DlistForEach - bool failue in the middle node") */
    PrintInYellow("\n-->Searching for element differ 9 in sub dlist");
    PrintInYellow("\n(Element doesn't exist in boundaries - return NULL)\n");
    (SortedListSameIterator(NULL_itr, itr))
    ?( printf(GREEN "\niterator that holds NULL was returned\n" RESET) )
    :( printf(RED "\niterator that DOESN'T hold NULL was returned\n" RESET) );

	SortedListDestroy(list);
}


/****************************************************************************/

#define PrintHeaderAdam(X)      printf(BLUE "\n---------"\
                                    X"---------\n" RESET)
void MergeTest_1()
{
    size_t i = 0;
    sorted_list_t          *list_1 = SortedListCreate(myLongCmp);
    sorted_list_t          *list_2 = SortedListCreate(myLongCmp);
    long arr[] = {1,1,3,4,5,5}; /* 6 elements */
    long *ptr = arr;

    PrintHeaderAdam("\n\nMergeTest 1"\
                    "add a list to the end\n");

    PrintInYellow("\n--> Create two Sorted List\n");

    while ( i < 3)
    {
        ++i;
        SortedListInsert(list_1, ptr++);
    }
    while ( i > 0)
    {
        --i;
        SortedListInsert(list_2, ptr++);
    }

    printf("list 1\n");
    ListInfoAndComp(list_1, 0, 3);
    Printlist(list_1);

    printf("list 2\n");
    ListInfoAndComp(list_2, 0, 3);
    Printlist(list_2);

    SortedListMerge(list_1, list_2);
    PrintInYellow("\n\n--> SortedListMerge(list_1, list_2)\n");

    printf("list 1\n");
    ListInfoAndComp(list_1, 0, 6);
    Printlist(list_1);
    VerifyOrderOfElements(list_1, arr, 0);

    printf("\n\nlist 2\n");
    ListInfoAndComp(list_2, 1, 0);
    Printlist(list_2);

    SortedListDestroy(list_1);
    SortedListDestroy(list_2);
}
void MergeTest_2()
{
    size_t i = 0;
    sorted_list_t          *list_1 = SortedListCreate(myLongCmp);
    sorted_list_t          *list_2 = SortedListCreate(myLongCmp);
    long arr[] = {1,1,3,4,5,5}; /* 6 elements */
    long *ptr = arr;
    PrintHeaderAdam("\n\nMergeTest 2:"\
                    "add a list to the start.\n");

    PrintInYellow("\n--> Create two Sorted List\n");
    while ( i < 3)
    {
        ++i;
        SortedListInsert(list_2, ptr++);
    }
    while ( i > 0)
    {
        --i;
        SortedListInsert(list_1, ptr++);
    }

    printf("list 1\n");
    ListInfoAndComp(list_1, 0, 3);
    Printlist(list_1);

    printf("list 2\n");
    ListInfoAndComp(list_2, 0, 3);
    Printlist(list_2);

    SortedListMerge(list_1, list_2);
    PrintInYellow("\n\n--> SortedListMerge(list_1, list_2)\n");

    printf("list 1\n");
    ListInfoAndComp(list_1, 0, 6);
    Printlist(list_1);
    VerifyOrderOfElements(list_1, arr, 0);

    printf("\n\nlist 2\n");
    ListInfoAndComp(list_2, 1, 0);
    Printlist(list_2);

    SortedListDestroy(list_1);
    SortedListDestroy(list_2);
}
void MergeTest_3()
{
    size_t i = 0;
    sorted_list_t          *list_1 = SortedListCreate(myLongCmp);
    sorted_list_t          *list_2 = SortedListCreate(myLongCmp);
    long arr[] = {1,1,3,4,5,5}; /* 6 elements */
    long *ptr = arr;

    PrintHeaderAdam("\n\nMergeTest 3:"\
                    "add a list to the start.\n");

    PrintInYellow("\n--> Create two Sorted List\n");

    while ( i < 6)
    {
        i+=2;
        SortedListInsert(list_1, ptr);
        ptr = ptr + 2;
    }

    i = 1;
    ptr = arr +1;
    while ( i < 6)
    {
        i+=2;
        SortedListInsert(list_2, ptr);
        ptr = ptr + 2;
    }

    printf("list 1\n");
    ListInfoAndComp(list_1, 0, 3);
    Printlist(list_1);

    printf("list 2\n");
    ListInfoAndComp(list_2, 0, 3);
    Printlist(list_2);

    SortedListMerge(list_1, list_2);
    PrintInYellow("\n\n--> SortedListMerge(list_1, list_2)\n");

    printf("list 1\n");
    ListInfoAndComp(list_1, 0, 6);
    Printlist(list_1);
    VerifyOrderOfElements(list_1, arr, 0);

    printf("\n\nlist 2\n");
    ListInfoAndComp(list_2, 1, 0);
    Printlist(list_2);

    SortedListDestroy(list_1);
    SortedListDestroy(list_2);

}
void MergeTest_4()
{
    size_t i = 0;
    sorted_list_t          *list_1 = SortedListCreate(myLongCmp);
    sorted_list_t          *list_2 = SortedListCreate(myLongCmp);
    long arr[] = {1,1,3,4,5,5}; /* 6 elements */
    long *ptr = arr;

    PrintHeaderAdam( "\n\nMergeTest 4:"\
                     "add to empty list.\n");

    PrintInYellow("\n--> Create two Sorted List\n");

    while ( i < 3)
    {
        ++i;
        SortedListInsert(list_2, ptr++);
    }

    printf("list 1\n");
    ListInfoAndComp(list_1, 1, 0);
    Printlist(list_1);

    printf("list 2\n");
    ListInfoAndComp(list_2, 0, 3);
    Printlist(list_2);

    SortedListMerge(list_1, list_2);
    PrintInYellow("\n\n--> SortedListMerge(list_1, list_2)\n");

    printf("list 1\n");
    ListInfoAndComp(list_1, 0, 3);
    Printlist(list_1);
    VerifyOrderOfElements(list_1, arr, 0);

    printf("\n\nlist 2\n");
    ListInfoAndComp(list_2, 1, 0);
    Printlist(list_2);

    SortedListDestroy(list_1);
    SortedListDestroy(list_2);

}
void MergeTest_5()
{
    size_t i = 0;
    sorted_list_t          *list_1 = SortedListCreate(myLongCmp);
    sorted_list_t          *list_2 = SortedListCreate(myLongCmp);
    long arr[] = {1,1,3,4,5,5}; /* 6 elements */
    long *ptr = arr;

    PrintHeaderAdam("\n\nMergeTest 5:"\
                    "add empty list to a list.\n");

    PrintInYellow("\n--> Create two Sorted List\n");
    while ( i < 3)
    {
        ++i;
        SortedListInsert(list_1, ptr++);
    }

    printf("list 1\n");
    ListInfoAndComp(list_1, 0, 3);
    Printlist(list_1);

    printf("\nlist 2\n");
    ListInfoAndComp(list_2, 1, 0);
    Printlist(list_2);
    printf("\n");
    SortedListMerge(list_1, list_2);

    PrintInYellow("\n--> SortedListMerge(list_1, list_2)\n");
    printf("list 1\n");
    ListInfoAndComp(list_1, 0, 3);
    Printlist(list_1);
    VerifyOrderOfElements(list_1, arr, 0);

    printf("\n\nlist 2\n");
    ListInfoAndComp(list_2, 1, 0);
    Printlist(list_2);

    ptr = arr;



    printf("\n");

    SortedListDestroy(list_1);
    SortedListDestroy(list_2);

}
void MergeTest_6()
{
    sorted_list_t  *list_1 = SortedListCreate(myLongCmp);
    sorted_list_t  *list_2 = SortedListCreate(myLongCmp);

    PrintHeaderAdam("\n\nMergeTest 6:"\
                    "add empty list to a list.\n");

    PrintInYellow("\n--> Create two Sorted List\n");

    printf("list 1\n");
    ListInfoAndComp(list_1, 1, 0);
    Printlist(list_1);

    printf("\nlist 2\n");
    ListInfoAndComp(list_1, 1, 0);
    Printlist(list_2);

    SortedListMerge(list_1, list_2);

    PrintInYellow("\n\n--> SortedListMerge(list_1, list_2)\n");
    printf("list 1\n");
    ListInfoAndComp(list_1, 1, 0);
    Printlist(list_1);

    printf("list 2\n");
    ListInfoAndComp(list_2, 1, 0);
    Printlist(list_2);

    printf("\n");
    SortedListDestroy(list_1);
    SortedListDestroy(list_2);

}

void MergeTest_7()
{
    size_t i = 0;
    sorted_list_t          *list_1 = SortedListCreate(myLongCmp);
    sorted_list_t          *list_2 = SortedListCreate(myLongCmp);
    long arr[] = {1,1,3,4,5,5}; /* 6 elements */
    long *ptr = arr;

    PrintHeaderAdam( "\n\nMergeTest 7:"\
                     "add to an empty list after merge.\n");

    PrintInYellow("\n--> Create two Sorted List\n");
    printf("\nlist 1\n");
    ListInfoAndComp(list_1, 1, 0);
    Printlist(list_1);

    printf("\nlist 2\n");
    ListInfoAndComp(list_2, 1, 0);
    Printlist(list_2);
    printf("\n");

    SortedListMerge(list_1, list_2);
    PrintInYellow("\n--> SortedListMerge(list_1, list_2)");

    while ( i < 3)
    {
        ++i;
        SortedListInsert(list_1, ptr++);
    }

    while ( i < 6)
    {
        ++i;
        SortedListInsert(list_2, ptr++);
    }

    printf("\nlist 1\n");
    ListInfoAndComp(list_1, 0, 3);
    Printlist(list_1);

    printf("\nlist 2\n");
    ListInfoAndComp(list_2, 0, 3);
    Printlist(list_2);
    printf("\n");

    SortedListDestroy(list_1);
    SortedListDestroy(list_2);
}

void MergeTest()
{
    MergeTest_1();
    MergeTest_2();
    MergeTest_3();
    MergeTest_4();
    MergeTest_5();
    MergeTest_6();
    MergeTest_7();
}


/****************************************************************************/
int main()
{
    InsertFindErasePop();
    TestSortedListForEach();
    MergeTest();

    return 0;
}
