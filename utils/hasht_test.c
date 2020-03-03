/****************************************************************************
** Filename:    - hasht_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Hash table testing (based on DLL)
** Date:        - 22/11/2017
** Version:     - 1
***************************************************/
#include <stdio.h>	/* printf */

#include "hasht.h"   /* Stack data structure */

/* gd hasht.c hasht_test.c dlist.c */
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
#define BLD     "\x1B[1m"
#define UDL     "\x1b[4m"

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

typedef struct my_type
{
    const char  *name;
    long         id;

} my_type_t;

/*=========================  FUNCTION DECLARATION  =========================*/

/****************************************************************************
    hash function which maps "key" to index in array
*****************************************************************************/
size_t HashFunc(const void *key)
{
    return *(long*)key % 10;
}
/****************************************************************************
    fetch a key from element
*****************************************************************************/
void* GetKey(const void* element)
{
    my_type_t *my_type = (my_type_t*)element;

    return &my_type->id;
}
/****************************************************************************
    compares two keys
*****************************************************************************/
int CompKeys(const void *key_1, const void *key_2)
{
    return *(long*)key_1 == *(long*)key_2;
}
/****************************************************************************
    for ForEach function
*****************************************************************************/
int SumHash(void* element, void *param)
{
    *(long*)param += *(long*)GetKey(element);
    return 1;
}
/****************************************************************************
    for ForEach function
*****************************************************************************/
int DivisibleByParam(void* element, void *param)
{
    my_type_t *my_type = (my_type_t*)element;

    return ( ( my_type->id % *(long*)param ) != 0  );
}



/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
    size_t i;
    long  look4;
    void *found;
    long  hash_size = 0;
    long  arr_sum   = 0;

    hash_t *hash = HashCreate(10, HashFunc, CompKeys, GetKey);

    my_type_t arr[] = {  {"a", 1},  {"b", 2},  {"c", 3},  {"d", 4},  {"e", 5},
                         {"f", 6},  {"g", 7},  {"h", 8},  {"i", 9}, {"j", 10},
                        {"k", 11}, {"l", 12}, {"m", 13}, {"n", 14}, {"o", 15},
                        {"p", 16}, {"q", 17}, {"r", 18}, {"s", 19}, {"t", 20},
                        {"u", 21}, {"v", 22}, {"w", 23}, {"x", 24}, {"y", 25},
                        {"z", 26}, {"{", 27}, {"|", 28}, {"}", 29}, {"~", 30} };

    PrintInYellow("\n\nChecking Empty Hash Table");
    printf("\nHashIsEmpty");
    PrintOKorERR( 0 == HashSize(hash) );
    PrintOKorERR( 1 == HashIsEmpty(hash) );

    PrintInYellow("\n\nChecking Insertion");
    for ( i = 0 ; i < SizeArr(arr) ; ++i )
    {
        arr_sum += arr[i].id;
        printf("\nInserting: {%s, %ld}  |  ", arr[i].name, arr[i].id);
        printf("HashInsert: %d  |  ", HashInsert(hash, &arr[i]));
        printf("HashSize: %ld  ", HashSize(hash));
        PrintOKorERR( i + 1 == HashSize(hash) );
        PrintOKorERR( 0 == HashIsEmpty(hash) );
    }

    PrintInYellow("\n\nChecking Find");
    /*===================  Find Element  ===================*/
    look4 = 23;
    found = HashFind(hash, (const void*)&look4);
    printf( "\nHashFind %ld | Found  {%s, %ld}  ",
            look4, ((my_type_t*)found)->name, ((my_type_t*)found)->id );
    PrintOKorERR( look4 == ((my_type_t*)found)->id );

    /*===================  Find Element  ===================*/
    look4 = 30;
    found = HashFind(hash, (const void*)&look4);
    printf( "\nHashFind %ld | Found  {%s, %ld}  ",
            look4, ((my_type_t*)found)->name, ((my_type_t*)found)->id );;
    PrintOKorERR( look4 == ((my_type_t*)found)->id );

    /*==============  Find Element that doesnt exist  ==============*/
    look4 = 200;
    found = HashFind(hash, (const void*)&look4);
    printf("\nHashFind element that doesnt exist (returns NULL)  ");
    PrintOKorERR( found == NULL );

    /*==============  Hash ForEach   ==============*/
    PrintInYellow("\n\nCount hash table sum with HashForEach");
    found = HashForEach(hash, SumHash, &hash_size);
    PrintOKorERR( hash_size == arr_sum );
    PrintOKorERR( found == NULL );

    /*==============  Hash ForEach   ==============*/
    look4 = 11;
    printf(YELLOWS "\n\nFind Element that is divisible by: %ld  " RESET, look4);
    found = HashForEach(hash, DivisibleByParam, &look4);
    printf( "\nHashForEach %ld | Found  {%s, %ld}  ",
            look4, ((my_type_t*)found)->name, ((my_type_t*)found)->id );
    PrintOKorERR( ( ((my_type_t*)found)->id % look4 ) == 0 );

    /*===================  HashRemove  ===================*/
    look4 = 20; arr_sum -= look4; hash_size = 0;
    printf(YELLOWS "\n\nHashRemove element: %ld  " RESET, look4);
    HashRemove(hash, (const void*)&look4);
    HashForEach(hash, SumHash, &hash_size);
    PrintOKorERR( hash_size == arr_sum );

    /*===================  HashRemove  ===================*/
    look4 = 12; arr_sum -= look4; hash_size = 0;
    printf(YELLOWS "\n\nHashRemove element: %ld  " RESET, look4);
    HashRemove(hash, (const void*)&look4);
    HashForEach(hash, SumHash, &hash_size);
    PrintOKorERR( hash_size == arr_sum );


    HashDestroy(hash);
    printf("\n");
    return 0;
}
