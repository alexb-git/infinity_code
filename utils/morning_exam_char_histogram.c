#include <stdio.h>    /* printf */

void BuildCharHist(char c);
char FindMaxOcc(char arr[]);
void NullifyArr(char arr[]);

/****************************************************************************/
void BuildCharHist(char c)
{
    static char hist_arr[256] = {0};

    if ( c != '0' )
    {
        ++hist_arr[(unsigned char)c];
    }
    else /* c == '0' */
    {
        char max_occ = FindMaxOcc(hist_arr);
        printf("%c - %d\n", max_occ, (int)hist_arr[(unsigned char)max_occ]);
        NullifyArr(hist_arr);
    }
}

/****************************************************************************/
char FindMaxOcc(char arr[])
{
    long i = 0;
    unsigned char max_occ = 0;

    while ( i < 256 )
    {
        if ( arr[max_occ] < arr[i] )
        {
            max_occ = i;
        }
        ++i;
    }

    return max_occ;
}

/****************************************************************************/
void NullifyArr(char arr[])
{
    long i = 0;

    while ( i < 256 )
    {
        arr[i] = 0;
        ++i;
    }
}


/****************************************************************************/
int main(int argc, char const *argv[])
{
    long i = 0;
    char c = 0;

    while ( 1 )
    {
        scanf("%c", &c);
        BuildCharHist(c);
        ++i;
    }

    return 0;
}
