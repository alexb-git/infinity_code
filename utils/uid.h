/***************************************************
  Filename: uid.h
  Purpose:  Header file for UID
  Product:  Unique Identifier
  Version:  4
 ***************************************************/
#ifndef __UNIQUE_ID_H__
#define __UNIQUE_ID_H__

#include <sys/types.h>  /* time_t, size_t, pid_t, pthread_t */

/* do not use this struct, this is an internal design */
typedef struct unique_id
{
  time_t    time;
  long      host_id;
  pid_t     process_id;
  pthread_t thread_id;
  size_t    counter;

} unique_id_t;

extern unique_id_t g_bad_id;

/*****************************************************************************
** description:  create a new struct of unique identifier.
** arguments:    void.
** return value: struct of unique identifier.
******************************************************************************/
unique_id_t UIDCreate(void);

/*****************************************************************************
** description:  Check if 2 given unique id are equal.
** arguments:    2 structs of unique identifier.
** return value: 1 - same uid,
**               0 - else uid.
******************************************************************************/
int UIDIsTheSame(unique_id_t uid1,unique_id_t uid2);

/*****************************************************************************
** description:  check if the given unique id is g_bad_id.
** arguments:    uid - struct of unique identifier.
** return value: 1 - uid is bad.
**               0 - else.
******************************************************************************/
int UIDIsBadId (unique_id_t uid);

#endif /* __UNIQUEID_H__ */
