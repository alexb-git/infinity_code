#include <string.h>    /* strnlen */
#include <stdio.h>     /* printf */

void RevWord(char *str);
void MirrStr(char *head, char *tail);

/****************************************************************************/
int main(int argc, char const *argv[])
{
    char str[] = "";

    printf("%s\n", str);

    RevWord(str);
    printf("%s\n", str);

    return 0;
}

/****************************************************************************/
void RevWord(char *str)
{
    char *end     = str + strlen(str) - 1;
    char *b4space = str;

    MirrStr(str, end);  /* first mirror the whole string */

    while ( str <= end )
    {
        while ( *b4space != ' ' && *b4space != '\0' )
        {
            /* look for space ' ' or end of string */
            ++b4space;
        }
        --b4space;  /* point to the end of the word */

        MirrStr(str, b4space);

        b4space += 2; /* point to the begining of the next word */


        str = b4space;
    }
}

/****************************************************************************/
void MirrStr(char *head, char *tail)
{
    while ( head < tail )
    {
        char temp = *head;
            *head = *tail;
            *tail =  temp;

        --tail;
        ++head;
    }
}
/****************************************************************************/
