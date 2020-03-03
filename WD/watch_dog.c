/****************************************************************************
** Filename:    - watch_dog.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - app/test function to run alongside watchdog
** Date:        - 26/12/2017
** Version:     - 8
*****************************************************************************/
#include <stdio.h>    /* printf */
#include "wdfuncs.h"  /* watch dog implementation */

/* gd watch_dog.c semV.c wdfuncs.c lib.a -D_GNU_SOURCE -pthread -o watch_dog.out */
/* gd wd_test.c semV.c wdfuncs.c lib.a -D_GNU_SOURCE -pthread */
int main(int argc, char* const *argv)
{
    int ret_val;

    fprintf(stderr, "inside watch_dog.out about to StartWD\n");

    SetIsWD();

    ret_val = StartWD(argv);

    fprintf(stderr, "inside watch_dog.out ret_val = %d\n", ret_val);

    return 0;
}
