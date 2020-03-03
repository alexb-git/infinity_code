/****************************************************************************
** Filename:    - dlist_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - testing the Doubly Linked List Data Structure
** Date:        - 02/10/2017
** Version:     - 20
*****************************************************************************/
#include <stdio.h>	/* printf */
#include "dlist.h"

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
	return value: 0 - equal, 1 - not equal
******************************************************************************/
int myLongCmp( const void *data_1, const void *data_2)
{
    return !( (long*)data_1 == (long*)data_2 );
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
void DInfoAndComp(dlist_t *dlist, int ex_is_em, size_t ex_size)
{
    printf(YELLOWS "|IsEmpty|: " RESET);
    printf("%d  ", DlistIsEmpty(dlist));                    /* |IsEmpty|    */
    (DlistIsEmpty(dlist)==ex_is_em)?(PrintOK):(PrintERR);   /* |T IsEmpty|  */

    printf(YELLOWS "  |Count|: " RESET);
    printf("%ld  ", DlistCount(dlist));                     /* |Size|       */
    (DlistCount(dlist)==ex_size)?(PrintOK):(PrintERR);      /* |T Size|     */

    printf("\n");

    /*DInfoAndComp(queue_1, 0, 10);*//* |IsEmpty| |T IsEmpty| |Size| |T Size| */
}

/****************************************************************************/
void PrintDlist(dlist_t *dlist)
{
    itr_t itr = DlistBegin(dlist);
    itr_t end = DlistEnd(dlist);

    printf("\x1b[90m" "NULL<->" RESET);

    for ( ; itr != end ; itr = DlistNext(itr) )
    {
        printf("| %ld |<->", *(long*)DlistGetData(itr));
    }
    printf("\x1b[90m" "NULL  " RESET);
}

/****************************************************************************/
void VerifySumOfElements(dlist_t *dlist, long ex_sum)
{
    itr_t itr = DlistBegin(dlist);
    itr_t end = DlistEnd(dlist);
    long sum = 0;

    for ( ; itr != end ; itr = DlistNext(itr) )
    {
        sum += *(long*)DlistGetData(itr);
    }

    printf(YELLOWS "\nVerify Sum Of Elements: " RESET);
    ( sum == ex_sum )?(PrintOK):(PrintERR);
}

/****************************************************************************/
void VerifyOrderOfElements(dlist_t *dlist, long beg_val, int flag)
{
    /* flag = 0 - increase each loop,  flag = 1 - decrease each loop,*/
    itr_t itr = NULL;

    for (   itr  = DlistBegin(dlist)    ;
            itr != DlistEnd(dlist)      ;
            itr  = DlistNext(itr)       )
    {
        if ( beg_val == *(long*)DlistGetData(itr) )
        {
            PrintOK; printf(" ");
        }
        else
        {
            PrintERR; printf(" ");
        }
        (flag)?(--beg_val):(++beg_val);
    }
}


/****************************************************************************
    Test Functions for Dlist DT
*****************************************************************************/
void PushPopFrontEnd()
{
    itr_t    itr   = NULL;
    itr_t    end   = NULL;
    dlist_t *dlist = DlistCreate();
	long arr[] = {1,2,3,4,5};

    PrintHeader("Push Pop Front/End SameIterator");

    itr = DlistBegin(dlist);
    end = DlistEnd(dlist);

    PrintInYellow("\n--> Created Doubly Linked\n");
    DInfoAndComp(dlist, 1, 0); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);

    PrintInYellow("\n--> SameIterator for DlistBegin and DlistEnd?");
    (DlistSameIterator(itr, end))
    ?(PrintInGreen("  SameIterator"))
    :(PrintInRed("  Not the SameIterator"));

    PrintInYellow("\n\n--> PushFront | 1 |\n");
    itr = DlistPushFront(dlist, &arr[0]);
    DInfoAndComp(dlist, 0, 1); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);
    PrintOKorERR( DlistGetData(itr)==&arr[0] ); /* arr[0] == 1 */

    end = DlistEnd(dlist);
    PrintInYellow("\n--> SameIterator for DlistBegin and DlistEnd?");
    (DlistSameIterator(itr, end))
    ?(PrintInRed("  SameIterator"))
    :(PrintInGreen("  Not the SameIterator"));

    PrintInYellow("\n\n--> PushFront | 2 |\n");
    itr = DlistPushFront(dlist, &arr[1]);
    DInfoAndComp(dlist, 0, 2); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);
    PrintOKorERR( DlistGetData(itr)==&arr[1] ); /* arr[1] == 2 */

    PrintInYellow("\n\n--> PushBack | 3 |\n");
    itr = DlistPushBack(dlist, &arr[2]);
    DInfoAndComp(dlist, 0, 3); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);
    PrintOKorERR( DlistGetData(itr)==&arr[2] ); /* arr[2] == 3 */

    PrintInYellow("\n\n--> PushBack | 4 |\n");
    itr = DlistPushBack(dlist, &arr[3]);
    DInfoAndComp(dlist, 0, 4); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);
    PrintOKorERR( DlistGetData(itr)==&arr[3] ); /* arr[3] == 4 */

    PrintInYellow("\n\n--> PopFront\n");
    itr = DlistPopFront(dlist);
    DInfoAndComp(dlist, 0, 3); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);
    PrintOKorERR( DlistGetData(itr)==&arr[0] ); /* arr[0] == 1 */

    PrintInYellow("\n\n--> PopBack\n");
    itr = DlistPopBack(dlist);
    DInfoAndComp(dlist, 0, 2); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);
    PrintOKorERR( DlistGetData(itr)==&arr[2] ); /* arr[2] == 3 */

    PrintInYellow("\n\n--> PopBack\n");
    itr = DlistPopBack(dlist);
    DInfoAndComp(dlist, 0, 1); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);
    PrintOKorERR( DlistGetData(itr)==&arr[0] ); /* arr[0] == 1 */

    PrintInYellow("\n\n--> PopFront\n");
    itr = DlistPopFront(dlist);
    DInfoAndComp(dlist, 1, 0); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);

    PrintInYellow("\n\n--> PopFront on an empty list\n");
     (DlistPopFront(dlist)==DlistEnd(dlist))
    ?( printf(GREEN "Dlist end was returned" RESET) )
    :( printf(RED "Dlist end was NOT returned" RESET) );

    PrintInYellow("\n\n--> PopBack on an empty list\n");
     (DlistPopBack(dlist)==DlistEnd(dlist))
    ?( printf(GREEN "Dlist end was returned" RESET) )
    :( printf(RED "Dlist end was NOT returned" RESET) );

    PrintInYellow("\n\n--> PushBack | 4 |\n");
    itr = DlistPushBack(dlist, &arr[3]);
    DInfoAndComp(dlist, 0, 1); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);
    PrintOKorERR( DlistGetData(itr)==&arr[3] ); /* arr[3] == 4 */

    printf("\n");
    DlistDestroy(dlist);
}

/****************************************************************************/
void InsertEraseFind()
{
    dlist_t *dlist = DlistCreate();
    itr_t    itr   = DlistEnd(dlist);
	long arr[] = {1,2,3,4,5,6,7,8,9,10};
    long sixsix = 66;
    int i = 0;

    PrintHeader("Insert Find Erase");

    PrintInYellow("\n--> Insert 10 values\n");
    while ( i < SizeArr(arr) )
    {
        itr = DlistInsert(dlist, itr, &arr[i]);
        ++i;
    }
    DInfoAndComp(dlist, 0, 10); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);

    PrintInYellow("\n\n--> Verify order of insertion:\n");
    VerifyOrderOfElements(dlist, 10, 1);

    PrintInYellow("\n\n--> Find element | 1 | and erase it (last element)\n");
    itr = DlistFind(DlistBegin(dlist), DlistEnd(dlist), myLongCmp, &arr[0]);
    DlistErase(dlist, itr);
    DInfoAndComp(dlist, 0, 9); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);
    VerifySumOfElements(dlist, 54);

    PrintInYellow("\n\n--> Find element | 6 | and erase it (regular case)\n");
    itr = DlistFind(DlistBegin(dlist), DlistEnd(dlist), myLongCmp, &arr[5]);
    DlistErase(dlist, itr);
    DInfoAndComp(dlist, 0, 8); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);
    VerifySumOfElements(dlist, 48);

    PrintInYellow("\n\n--> Find element | 10 | and erase it (first element)\n");
    itr = DlistFind(DlistBegin(dlist), DlistEnd(dlist), myLongCmp, &arr[9]);
    DlistErase(dlist, itr);
    DInfoAndComp(dlist, 0, 7); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);
    VerifySumOfElements(dlist, 38);

    PrintInYellow("\n\n--> Find element | 66 | (desn't exist)\n");
    itr = DlistFind(DlistBegin(dlist), DlistEnd(dlist), myLongCmp, &sixsix);
    (NULL==itr)
   ?( printf(GREEN "NULL was returned" RESET) )
   :( printf(RED "NULL was NOT returned" RESET) );
    VerifySumOfElements(dlist, 38);


    printf("\n");
    DlistDestroy(dlist);
}

/****************************************************************************/
void InsertAfterForEach()
{
    dlist_t *dlist = DlistCreate();
    itr_t    start = DlistBegin(dlist);
    itr_t    end   = DlistEnd(dlist);
    itr_t    itr   = end;
	long arr[] = {1,2,3,4,5,6,7,8,9,10};
    long param = 0;
    int i = 0;

    PrintHeader("Insert-After ForEach");

    PrintInYellow("\n--> Insert-After 10 values\n");
    itr = DlistInsert(dlist, itr, &arr[0]);
    ++i;

    while ( i < SizeArr(arr) )
    {
        itr = DlistInsertAfter(dlist, itr, &arr[i]);
        ++i;
    }
    DInfoAndComp(dlist, 0, 10); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist);

    PrintInYellow("\n\n--> Verify order of insertion:\n");
    VerifyOrderOfElements(dlist, 1, 0);

    param = 1;
	PrintInYellow("\n\n--> Find the first element that is >= 1 ");
	PrintInYellow("(beginning of the list):\n");
	itr = DlistForEach( DlistBegin(dlist), DlistEnd(dlist),
                        SmallerThanParam, &param );
    printf("| %ld | - ", *(long*)DlistGetData(itr));
    PrintOKorERR(DlistGetData(itr)==&arr[0]);


    param = 5;
	PrintInYellow("\n\n--> Find the first element that is >= 5 ");
	PrintInYellow("(stop in the middle):\n");
	itr = DlistForEach( DlistBegin(dlist), DlistEnd(dlist),
                        SmallerThanParam, &param );
    printf("| %ld | - ", *(long*)DlistGetData(itr));
    PrintOKorERR(DlistGetData(itr)==&arr[4]);

	param = 10;
	PrintInYellow("\n\n--> Find the first element that is >= 10 ");
	PrintInYellow("(last element)\n");
    itr = DlistForEach( DlistBegin(dlist), DlistEnd(dlist),
                        SmallerThanParam, &param );
    printf("| %ld | - ", *(long*)DlistGetData(itr));
    PrintOKorERR(DlistGetData(itr)==&arr[9]);

	param = 66;
	PrintInYellow("\n\n--> Find the first element that is >= 66 ");
	PrintInYellow("(doesn't exist)\n");
    itr = DlistForEach( DlistBegin(dlist), DlistEnd(dlist),
                        SmallerThanParam, &param );
    (NULL==itr)
   ?( printf(GREEN "NULL was returned" RESET) )
   :( printf(RED "NULL was NOT returned" RESET) );

    param = 2;
    PrintInYellow("\n\n--> Find the first element that is >= 2 ");
    PrintInYellow("(start with element | 4 |):\n");
    start = DlistFind(DlistBegin(dlist), DlistEnd(dlist), myLongCmp, &arr[3]);
    itr   = DlistForEach( start, DlistEnd(dlist), SmallerThanParam, &param );
    printf("| %ld | - ", *(long*)DlistGetData(itr));
    PrintOKorERR(DlistGetData(itr)==&arr[3]);

    param = 8;
    PrintInYellow("\n\n--> Find the first element that is >= 8 ");
    PrintInYellow("(start with element | 3 | end with element | 9 |):\n");
    start = DlistFind(DlistBegin(dlist), DlistEnd(dlist), myLongCmp, &arr[2]);
    end   = DlistFind(DlistBegin(dlist), DlistEnd(dlist), myLongCmp, &arr[8]);
    itr   = DlistForEach( start, end, SmallerThanParam, &param );
    printf("| %ld | - ", *(long*)DlistGetData(itr));
    PrintOKorERR(DlistGetData(itr)==&arr[7]);

    param = 8;
    PrintInYellow("\n\n--> Find the first element that is >= 8\n\t(start with");
    PrintInYellow(" element | 3 | end with element | 8 | [exclusive]):\n");
    start = DlistFind(DlistBegin(dlist), DlistEnd(dlist), myLongCmp, &arr[2]);
    end   = DlistFind(DlistBegin(dlist), DlistEnd(dlist), myLongCmp, &arr[7]);
    itr   = DlistForEach( start, end, SmallerThanParam, &param );
    (NULL==itr)
   ?( printf(GREEN "NULL was returned" RESET) )
   :( printf(RED "NULL was NOT returned" RESET) );

    printf("\n");
    DlistDestroy(dlist);
}

/***************************************************************************/
void SpliceBefore()
{
    itr_t    itr   = NULL;
    itr_t    start = NULL;
    itr_t    end   = NULL;
    dlist_t *dlist_1 = DlistCreate();
    dlist_t *dlist_2 = DlistCreate();
	long arr_1[] = {0,1,2,8,9};
    long arr_2[] = {3,4,5,6,7};
    long push_back = -1;
    int i = 0;

    PrintHeader("Splice Before");


    itr = DlistEnd(dlist_1);
    itr = DlistInsert(dlist_1, itr, &arr_1[0]);
    i = 1;
    while ( i < SizeArr(arr_1) )
    {
        itr = DlistInsertAfter(dlist_1, itr, &arr_1[i]);
        ++i;
    }
    PrintInYellow("\nDlist #1:\n");
    PrintDlist(dlist_1);
    printf("\n");



    itr = DlistEnd(dlist_2);
    itr = DlistInsert(dlist_2, itr, &arr_2[0]);
    i = 1;
    while ( i < SizeArr(arr_2) )
    {
        itr = DlistInsertAfter(dlist_2, itr, &arr_2[i]);
        ++i;
    }
    PrintInYellow("\nDlist #2:\n");
    PrintDlist(dlist_2);


    PrintInYellow("\n\nSplice Before element | 2 | in dlist #1 from dlist #2");
    PrintInYellow("\n- start at element | 7 | till element | 3 | \n");

    itr   = DlistFind(  DlistBegin(dlist_1), DlistEnd(dlist_1),
                        myLongCmp, &arr_1[2]    );

    start = DlistFind(  DlistBegin(dlist_2), DlistEnd(dlist_2),
                        myLongCmp, &arr_2[0]    );

    end   = DlistFind(  DlistBegin(dlist_2), DlistEnd(dlist_2),
                        myLongCmp, &arr_2[4]    );

    DlistSpliceBefore(itr, start, end);

    PrintInYellow("\nDlist #1:\n");
    DInfoAndComp(dlist_1, 0, 10); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist_1);
    printf("\n");

    PrintInYellow("\nDlist #2:\n");
    DInfoAndComp(dlist_2, 1, 0); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist_2);

    PrintInYellow("\n--> Verify order of insertion:\n");
    VerifyOrderOfElements(dlist_1, 0, 0);

    PrintInYellow("\n\n--> Dlist #2 push front | -1 |:\n");
    itr = DlistPushFront(dlist_2, &push_back);
    PrintDlist(dlist_2);

    printf("\n\n");
    PrintInYellow("\nSplice Before element | -1 | in dlist #2 from dlist #1");
    PrintInYellow("\n- start at element | 0 | till element | 4 | \n");

    start = DlistFind(  DlistBegin(dlist_1), DlistEnd(dlist_1),
                        myLongCmp, &arr_1[0]    ); /* arr_1[0]==0 */

    end   = DlistFind(  DlistBegin(dlist_1), DlistEnd(dlist_1),
                        myLongCmp, &arr_2[1]    ); /* arr_2[1]==4 */

    DlistSpliceBefore(itr, start, end);

    PrintInYellow("\nDlist #1:\n");
    DInfoAndComp(dlist_1, 0, 5); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist_1);
    PrintInYellow("\n--> Verify order of insertion:\n");
    VerifyOrderOfElements(dlist_1, 5, 0);
    printf("\n");

    PrintInYellow("\nDlist #2:\n");
    DInfoAndComp(dlist_2, 0, 6); /* |IsEmpty| |T IsEmpty| |Size| |T Size| */
    PrintDlist(dlist_2);
    PrintInYellow("\n--> Verify order of insertion:\n");
    VerifyOrderOfElements(dlist_2, -1, 0);

    printf("\n");
    DlistDestroy(dlist_1);
    DlistDestroy(dlist_2);

}

/***************************************************************************/
void TestDlist()
{
    PushPopFrontEnd();
    InsertEraseFind();
    InsertAfterForEach();
    SpliceBefore();
}


int main()
{
	TestDlist();

    return 0;
}
