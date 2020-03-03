/****************************************************************************
** Filename:    - unique_id_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - testing of unique identifier
** Date:        - 10/10/2017
** Version:     - 2
*****************************************************************************/

#include <stdio.h>      /* printf */
#include <pthread.h>    /* thread  ID */
#include "uid.h"

extern void PrintUID(unique_id_t uid);


/****************************************************************************
    Helpful colors
*****************************************************************************/
#define GREEN	"\x1b[92m"
#define RED		"\x1b[91m"
#define YELLOW	"\x1b[93m"
#define YELLOWS	"\x1b[33m"
#define RESET	"\x1b[0m"
#define BLUE	"\x1B[94m"
#define WHITE	"\x1B[37m"


/****************************************************************************
    Helpful defines
*****************************************************************************/
#define PrintInYellow(X)  ( printf(YELLOW X RESET) )
#define PrintInGreen(X)   ( printf(GREEN  X RESET) )
#define PrintInRed(X)     ( printf(RED    X RESET) )
#define PrintOK           ( printf(GREEN "%-12s" RESET, "-OK") )
#define PrintERR          ( printf(RED "%-12s" RESET, "-ERR") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
/****************************************************************************/

int main()
{
    unique_id_t uid;
    unique_id_t bad_uid = g_bad_id;

    size_t i = 0;

    while ( i < 15 )
    {
        uid = UIDCreate();
        printf(YELLOWS "\nUID #%ld\n" RESET, i);
        PrintUID(uid);

        ++i;
    }

    PrintInYellow("\n-->tseting UIDIsBadId:");

    printf("\nIs 'bad_uid' UID IsBadId:\t");
    PrintOKorERR( UIDIsBadId(bad_uid)==1 );

    printf("\nIs 'kosher'  UID IsBadId:\t");
    PrintOKorERR( UIDIsBadId(uid)==0 );


    PrintInYellow("\n\n-->tseting UIDIsTheSame:\n");

    PrintOKorERR( UIDIsTheSame(bad_uid, uid)==0 );

    PrintOKorERR( UIDIsTheSame(uid, uid) ); /* ==1 */

    PrintOKorERR( UIDIsTheSame(bad_uid, bad_uid) ); /* ==1 */

    printf("\n");
    return 0;
}
