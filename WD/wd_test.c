/****************************************************************************
** Filename:    - wd_teat.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - app/test function to run alongside watchdog
** Date:        - 26/12/2017
** Version:     - 5
*****************************************************************************/
#include <unistd.h>     /* sleep */
#include <stdlib.h>     /* system */
#include <stdio.h>      /* printf */

#include "wdfuncs.h"  /* watch dog implementation */

/* gd watch_dog.c semV.c wdfuncs.c lib.a -D_GNU_SOURCE -pthread -o watch_dog.out */
/* gd wd_test.c semV.c wdfuncs.c lib.a -D_GNU_SOURCE -pthread */
int main(int argc, char* const *argv)
{
    int ret_val;

    /*int sleep_interval = 50;*/ /* [sec] */
    fprintf(stderr, "inside wd_test.c about to StartWD\n");

    ret_val = StartWD(argv);

    while ( 1 ) { }
    /*while((sleep_interval = sleep(sleep_interval)) > 0){}*/

    fprintf(stderr, "inside watch_dog.out ret_val = %d\n", ret_val);

    StopWD();

    sleep(6);
    printf("\nA am the APP and I am still alive\n");

    return 0;
}
