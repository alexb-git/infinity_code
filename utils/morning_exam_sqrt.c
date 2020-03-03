#include <stdio.h>    /* printf */


#define Abs(X) ( (X < 0) ? ( (-1)*(X) ) : ( (X) ) )
#define IsEqual(param, cmp, pres) ( Abs(param - cmp) <= pres )

/****************************************************************************
    desen't work on numbers between 0-1
*****************************************************************************/
double MySqrt(double input)
{
    double pres     = 0.000001;

    double res      = input;
    double segment  = res / 2;

    while ( !IsEqual( res*res, input, pres ) )
    {
        if ( res*res < input )
        {
            res += segment;
        }
        else /* res*res >= input */
        {
            res -= segment;
        }

        segment /= 2;
    }

    return res;
}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
    printf("sqrt(2) = %f\n", MySqrt(2) );

    return 0;
}
