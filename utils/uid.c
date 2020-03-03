/****************************************************************************
** Filename:    - unique_id.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementation of unique identifier
** Date:        - 10/10/2017
** Version:     - 2
*****************************************************************************/
#include <unistd.h>     /* process ID, host ID */
#include <stddef.h>     /* size_t */
#include <pthread.h>    /* thread  ID */
#include <stdio.h>      /* printf */

#include "uid.h"        /* uid */

unique_id_t g_bad_id = {0, 0, 0, 0, 0};

extern long gethostid(void);

/*****************************************************************************
** description:  create a new struct of unique identifier.
** arguments:    void.
** return value: struct of unique identifier.
******************************************************************************/
unique_id_t UIDCreate(void)
{
    static size_t counter = 0;

    unique_id_t unique_id;

    /* returns the current calendar time of the system as time since epoch  */
    unique_id.time       = time(NULL);

    /* get or set the unique identifier of the current host */
    unique_id.host_id    = gethostid();

    /* returns the caller's thread ID */
    unique_id.process_id = getpid();

    /* returns the ID of the calling thread */
    unique_id.thread_id  = pthread_self();

    unique_id.counter    = counter++;

    return unique_id;

}

/*****************************************************************************
** description:  Check if 2 given unique id are equal.
** arguments:    2 structs of unique identifier.
** return value: 1 - same unique_id,
**               0 - else unique_id.
******************************************************************************/
int UIDIsTheSame(unique_id_t uid1,unique_id_t uid2)
{
	return ( uid1.time       == uid2.time          &&
		     uid1.host_id    == uid2.host_id       &&
		     uid1.process_id == uid2.process_id    &&
		     uid1.thread_id  == uid2.thread_id     &&
		     uid1.counter    == uid2.counter       );
}

/*****************************************************************************
** description:  check if the given unique id is g_bad_id.
** arguments:    unique_id - struct of unique identifier.
** return value: 1 - unique_id is bad.
**               0 - else.
******************************************************************************/
int UIDIsBadId (unique_id_t unique_id)
{
	return (UIDIsTheSame(unique_id, g_bad_id));
}


#ifdef _DEBUG
void PrintUID(unique_id_t uid)
{
    /*printf("|time|-|host_id|-|process_id|-|thread_id|-|counter|\n");*/
    printf("|%ld|-|%ld|-|%ld|-|%ld|-|%ld|\n",
            (size_t)uid.time,
            (size_t)uid.host_id,
            (size_t)uid.process_id,
            (size_t)uid.thread_id,
            (size_t)uid.counter );
}
#else
#define PrintUID(uid)
#endif
