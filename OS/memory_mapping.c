/****************************************************************************
** Filename:    - memory_mapping.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     -
** Date:        - 18/12/2017
** Version:     - 0
***************************************************/
#include <sys/types.h> /* pthread_t */
#include <stdlib.h>    /* malloc, free */
#include <stdio.h>     /* printf */
#include <pthread.h>   /* pthread create */

/****************************************************************************
    Helpful colors
*****************************************************************************/
#define GRE	"\x1b[92m"
#define RED "\x1b[91m"
#define YEL	"\x1b[93m"
#define YLL	"\x1b[33m"
#define RES	"\x1b[0m"
#define BLU	"\x1B[34m"
#define CYA	"\x1B[36m"
#define WHI	"\x1B[37m"
#define BLD "\x1B[1m"
#define UDL "\x1b[4m"
/****************************************************************************/

#define NUM_OF_THREADS (3)

char uninit_global;     /* uninitialized global variable */
char init_global = 1;   /* initialized global variable */

void* RecMapping(void *arg)
{
    char  x; /* local variable */
    char *y = (char*) malloc(sizeof(char));

    printf(GRE "Local Variable: %p |" RES, &x);
    printf(RED "Dynamic Variable: %p |" RES, y);
    printf(BLU "Uninitialized Global Variable: %p |" RES, &uninit_global);
    printf(YLL "Initialized Global Variable: %p\n" RES, &init_global);

    RecMapping(NULL);

    return (NULL);
}

int main(int argc, char const *argv[])
{
    size_t i = 0;
    pthread_t thread[NUM_OF_THREADS];

    printf("Main Function Local Variable: %p\n", (void*)&i);
    /*printf("RecMapping Function Pointer: %p\n",  (void*)RecMapping);*/

    for ( i = 0 ; i < NUM_OF_THREADS ; ++i )
    {
        pthread_create(&thread[i], NULL, RecMapping, NULL);
    }

    for ( i = 0 ; i < NUM_OF_THREADS ; ++i )
    {
        pthread_join(thread[i], NULL);
    }

    return 0;
}
