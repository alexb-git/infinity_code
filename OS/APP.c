/****************************************************************************
** Filename:    - APP.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - app/test function to run alongside watchdog
** Date:        - 26/12/2017
** Version:     - 1
*****************************************************************************/
#include <unistd.h>     /* sleep */
#include <stdlib.h>     /* system */
#include <stdio.h>      /* printf */

#include "WDFUNCS.h"  /* watch dog implementation */

/*  gd wd_test.c semV.c WDFUNCS.c lib.a -D_GNU_SOURCE -pthread -o WD.out */
int main(int argc, char* const *argv)
{
    int sleep_interval = 30; /* [sec] */

    StartWD(argv);

    /*while ( 1 ) { }*/
    while((sleep_interval = sleep(sleep_interval)) > 0){}

    StopWD();

    sleep(6);
    printf("\nA am the APP and I am still alive\n");

    return 0;
}
