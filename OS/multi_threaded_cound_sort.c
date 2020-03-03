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

#include <unistd.h>     /* open */
#include <fcntl.h>      /*  */
#include <sys/stat.h>   /* fstat */
#include <pthread.h>    /* pthread_t */

#include <time.h>       /* time */

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

/*======================  CONSTS FOR THIS PROGRAM  =======================*/
const char* dictionary = "/usr/share/dict/american-english";

pthread_t thread[4];

typedef struct thread_arg
{
    char *base;
    char *result;

    size_t nmemb;
    size_t range;

    size_t *histogram;

} thread_arg_t;


/*****************************************************************************

******************************************************************************/
void* SortCounting(void *args)
{
    size_t i = 0;
    long  curr_index   = 0;
    char *runner       = NULL;

    thread_arg_t *thread_arg = (thread_arg_t *) args;

    size_t range    = thread_arg->range;
    size_t nmemb    = thread_arg->nmemb;
    char *base      = thread_arg->base;
    char *result    = thread_arg->result;
    size_t *histogram = thread_arg->histogram;

    char *last_element = base + nmemb;

    memcpy(result, base, nmemb);

    /* create histogram of occurrences for the given array */
    for ( runner = base             ;
          runner < last_element          ;
          runner = runner + sizeof(char) )
    {
        ++histogram[(size_t)(*runner)];
    }

    for ( i = 1 ; i < range ; ++i )
    {
        memset(result + curr_index , i, histogram[i]);
        curr_index  += histogram[i];
    }

    return (NULL);
}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
    size_t i, j;
    size_t size;
    size_t irregular = 0;

    time_t before;
    time_t sum_time = 0;

    thread_arg_t thread_arg[4];

    char *dict_without_irreg;
    char *cmp_arr;

    char *mmap_area;
    int   descriptor = open(dictionary, O_RDONLY); /* get file descriptor */

    /*=======================  get the file size  ======================*/
    struct stat stat_stru;
    fstat (descriptor, &stat_stru);
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

    /*=======================    ======================*/
    cmp_arr = (char*) malloc(size - irregular + 1); /* will compare to this array */

    thread_arg[0].base   = dict_without_irreg;
    thread_arg[0].nmemb  = size - irregular + 1;
    thread_arg[0].range  = 256;
    thread_arg[0].result = cmp_arr; /* will hold sorted array */
    thread_arg[0].histogram = (size_t*) malloc(256 * sizeof(size_t));

    SortCounting(&thread_arg[0]);

    /*printf("%s\n", cmp_arr);*/

    for ( i = 0 ; i < 4 ; ++i )
    {
        thread_arg[i].base   = dict_without_irreg;
        thread_arg[i].nmemb  = size - irregular + 1;
        thread_arg[i].range  = 256;
        /* will hold sorted array */
        thread_arg[i].result = (char*) malloc(size - irregular + 1);
        thread_arg[i].histogram = (size_t*) malloc(256 * sizeof(size_t));
    }

    sum_time = 0;
    before = time(NULL);

    /*#pragma omp parallel*/
    for ( i = 0 ; i < 25000 ; ++i )
    {
        for ( j = 0 ; j < 4 ; ++j )
        {
            memset(thread_arg[j].histogram, 0, 256 * sizeof(size_t));
            memset(thread_arg[j].result, 0, size - irregular + 1);

            pthread_create(&thread[j], NULL, SortCounting, &thread_arg[j]);
        }

        for ( j = 0 ; j < 4 ; ++j )
        {
            pthread_join(thread[j], NULL);
            /*(strcmp(cmp_arr, thread_arg[j].result) == 0)?(PrintOK):(PrintERR);*/
        }

    }

    sum_time += difftime(time(NULL), before);
    printf("%.2f [seconds]", (double)sum_time);

    free(dict_without_irreg);
    dict_without_irreg = NULL;

    printf("\n");
    return 0;
}
