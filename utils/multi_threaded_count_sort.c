/****************************************************************************
** Filename:    - multi_threaded_cound_sort.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     -
** Date:        - 14/12/2017
** Version:     - 1
***************************************************/
#include <stdio.h>      /* printf, fopen, fclose, fscanf */
#include <stdlib.h>     /* malloc, free */
#include <string.h>     /* memcpy */
#include <assert.h>     /* assert */
#include <sys/mman.h>   /* mmap */

#include <unistd.h> /* open */
#include <fcntl.h>
#include <sys/stat.h> /* fstat */

#include <time.h>    /* time */


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

#define Next(X)     ( (char*)X + size )
#define Prev(X)     ( (char*)X - size )

/*#define TimeDiff(X) ( (double)(time(NULL) - X) )
#define PrintTimeDiff(X) printf("%.2f [seconds]", TimeDiff(X))*/
/****************************************************************************
    Macros for this program
*****************************************************************************/

/*======================  CONSTS FOR THIS PROGRAM  =======================*/
const char* dictionary = "/usr/share/dict/american-english";


/*****************************************************************************
**  description: the weight function, is a user define function that return
**               the weight of the inputed element in [0, range]
**  arguments: element - that we need to weight.
**             param   - the user given input.
**  return: weight of the inputed element.
**  notes:  used in radix.
******************************************************************************/
size_t Char2Num(char *element)
{
    return (size_t)(*element);
}

/*****************************************************************************
**  description:  sort an array of elements.
**  arguments:    base   - Pointer to the first object of the array
**                         to be sorted, converted to a void*.
**                nmem   - Number of elements in the array pointed to by base
**                size   - Size in bytes of each element in the array.
**                range  - the number of possible values for an element.
**                weight - a function that return the weight of the element.
**  return value: void
**  notes:        Can, and should, be use in radix sort.
******************************************************************************/
void SortCounting(  char *base, size_t nmemb, size_t range,
                    size_t (*func)(char*), char * dup_array, char * result)
{
    size_t i = 0;
    long curr_index = 0;
    char *runner       = NULL;
    char *last_element = dup_array + nmemb;

    size_t histogram[256] = {0};

    /*size_t *histogram  = (size_t*)calloc(range, sizeof(size_t));*/

    memcpy(dup_array, base, nmemb);

    assert( (base != NULL) && (func != NULL) );

    /* create histogram of occurrences for the given array */
    for ( runner = dup_array             ;
          runner < last_element          ;
          runner = runner + sizeof(char) )
    {
        ++histogram[func(runner)];
    }

    /* make the reulting sorted array. */
    for ( i = 1 ; i < range ; ++i )
    {
        memset(result + curr_index , i, histogram[i]);
        curr_index  += histogram[i];
    }

}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
    size_t i, j;
    size_t size;
    size_t irregular = 0;

    time_t before;
    time_t sum_time = 0;

    char *dict_without_irreg;
    char *result;

    char *dup_array = NULL;

    char *mmap_area;
    struct stat stat_stru;

    int descriptor = open(dictionary, O_RDONLY); /* get file descriptor */
    fstat (descriptor, &stat_stru); /* Get the size of the file. */
    size = stat_stru.st_size;

    mmap_area = (char*) mmap(0, size, PROT_READ, MAP_PRIVATE, descriptor, 0);

    /*=======================  count irregular chars  ======================*/
    for ( i = 0 ; i < size ; ++i )
    {
        if ( mmap_area[i] == '\n' || mmap_area[i] < 0 )
        {
            ++irregular;
        }
    }

    /*=====  copy mmap_area to dictionary array without irregular chars  ====*/
    dict_without_irreg = (char*) malloc(size - irregular + 1);
    for ( j = 0, i = 0 ; i < size ; ++i )
    {
        if ( mmap_area[i] != '\n' && mmap_area[i] >= 0 )
        {
            dict_without_irreg[j] = mmap_area[i];
            ++j;
        }
    }
    dict_without_irreg[j] = '\0';

    dup_array    = (char*)malloc(size - irregular + 1);

    before = time(NULL);
    /*=======================    ======================*/
    result = (char*) malloc(size - irregular + 1);

    sum_time = 0;

    for ( i = 0 ; i < 100000 ; ++i )
    {
        SortCounting(dict_without_irreg, size - irregular, 256, Char2Num, dup_array, result);
        /*printf("%s\n", result);*/

        memset(result, 0, size - irregular + 1);
    }

    sum_time += difftime(time(NULL), before);
    printf("%.2f [seconds]", (double)sum_time);

    /*printf("\n\ntotal size, in bytes %lu", size);
    printf("\ntotal characters %lu", size/sizeof(char));
    printf("\nNum of new lines : %lu", irregular);
    printf("\nOnly chars : %lu\n", size - irregular);*/

        free(dup_array);
        dup_array = NULL;

    free(dict_without_irreg);
    dict_without_irreg = NULL;

    printf("\n");
    return 0;
}
