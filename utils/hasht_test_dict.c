/****************************************************************************
** Filename:    - hasht_test_dict.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Hash table testing (based on DLL)
** Date:        - 22/11/2017
** Version:     - 1
***************************************************/
#include <stdio.h>	/* printf, fopen, fclose, fscanf */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */

#include "hasht.h"   /* Stack data structure */

/* gd hasht.c hasht_test_dict.c dlist.c */
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
#define TABLESIZE (10000)
#define W_LENGTH  (25)

const char* dictionary = "/usr/share/dict/american-english";

/****************************************************************************
    hash function which maps "key" to index in array
*****************************************************************************/
size_t HashFunc(const void *key)
{
	char* my_key = (char*) key;
    size_t hash = 0, i = 0;

    while( '\0' != my_key[i] )
    {
        hash += my_key[i++];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash % TABLESIZE;
}
/****************************************************************************
    fetch a key from element
*****************************************************************************/
void* GetKey(const void* element)
{
    return (void*)element;
}
/****************************************************************************
    compares two keys
*****************************************************************************/
int CompKeys(const void *key_1, const void *key_2)
{
    return strcmp((char*)key_1, (char*)key_2) == 0;
}
/****************************************************************************
    for ForEach function
*****************************************************************************/
int ReleaseElements(void* element, void *param)
{
    free(element);
    element = NULL;
    return 1;
}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
    char spell[W_LENGTH];
    char buffer[W_LENGTH];
    void *result;

    hash_t *hash = HashCreate(TABLESIZE, HashFunc, CompKeys, GetKey);

    /* open dictionary and check */
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open file.");
        return 0;
    }

    /* load the dictionary into the Hash Table */
    while(fscanf(dict, "%s", buffer) != EOF)
    {
        size_t length = strlen(buffer) + 1;

        /* if there is a word initiate variable to store the word */
        char* dword = (char*)malloc(length);

        /*  */
        memcpy(dword, buffer, length);

        /* insert the word into the hash */
        HashInsert(hash, dword);
    }

    fclose(dict);

    /*===================  "SpellCheck"  ===================*/
    PrintInYellow("\nFind words that exists:");
    strcpy(spell, "nonprofessional's");
    result = HashFind(hash, spell);
    printf("\n%s\t", spell);
    PrintOKorERR(NULL != result);

    strcpy(spell, "obstructionist's");
    result = HashFind(hash, spell);
    printf("\n%s\t", spell);
    PrintOKorERR(NULL != result);

    strcpy(spell, "émigré's");
    result = HashFind(hash, spell);
    printf("\n%s\t\t", spell);
    PrintOKorERR(NULL != result);


    /*===================  "SpellCheck"  ===================*/
    PrintInYellow("\n\nFind word that DO NOT exists:");
    strcpy(spell, "nonpr0fessional's");
    result = HashFind(hash, spell);
    printf("\n%s\t", spell);
    PrintOKorERR(NULL == result);

    strcpy(spell, "obstructio_ist's");
    result = HashFind(hash, spell);
    printf("\n%s\t", spell);
    PrintOKorERR(NULL == result);

    strcpy(spell, "émIgré's");
    result = HashFind(hash, spell);
    printf("\n%s\t\t", spell);
    PrintOKorERR(NULL == result);


    HashForEach(hash, ReleaseElements, NULL);
    HashDestroy(hash);
    printf("\n");
    return 0;
}
