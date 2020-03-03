/****************************************************************************
** Filename:    - stackcalc_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Stack Calculator testing
** Date:        - 8/1/2017
** Version:     - 2
***************************************************/
#include <stdio.h>      /* printf */
#include <float.h>		/* DBL_MAX */
#include <string.h>     /* strcpy */

#include "stackcalc.h"  /* Stack Calculator */

/****************************************************************************
    Helpful colors
*****************************************************************************/
#define GREEN	"\x1b[92m"
#define RED		"\x1b[91m"
#define YELLOW	"\x1b[93m"
#define YELLOWS	"\x1b[33m"
#define RESET	"\x1b[0m"
#define BLUE	"\x1B[34m"
#define CYAN	"\x1B[36m"
#define WHITE	"\x1B[37m"

/****************************************************************************
    Helpful defines
*****************************************************************************/
#define PrintHeader(X)      printf( BLUE "\n\t------------"\
                                    "  This is a test for: "\
                                    X" ------------\n" RESET)

#define PrintInYellow(X)  ( printf(YELLOW X RESET) )
#define PrintInGreen(X)   ( printf(GREEN  X RESET) )
#define PrintInRed(X)     ( printf(RED    X RESET) )
#define PrintOK           ( printf(GREEN "%-5s" RESET, "-OK") )
#define PrintERR          ( printf(RED "%-5s" RESET, "-ERR") )
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************
    Macros for this program
*****************************************************************************/
#define ERRCODE (DBL_MAX)


void CalcAndComp(char *equation, double ex_result)
{
    char   str[40];
    double result;

    printf("__________________________________________________\n");
    strcpy(str, equation);
    printf("%s = ", str);
    result = StackCalculator(str);

    if ( result == ERRCODE )
    {
        printf("ERROR");
    }
    else
    {
        printf("%.2f  ", result );
    }

    PrintOKorERR(result == ex_result);

    printf("\n");
}

/*==========================  THE MAIN FUNCTIONS  ==========================*/
int main(int argc, char const *argv[])
{
    /*======  simple equations  ======*/
    CalcAndComp("1", 1);
    CalcAndComp("1+2-3", 0);
    CalcAndComp("1+2*3", 7);
    CalcAndComp("1*2+3", 5);


    /*======  cheking error inputs  ======*/
    CalcAndComp("1-*1", ERRCODE);
    CalcAndComp("1-1)", ERRCODE);
    CalcAndComp("(1-1", ERRCODE);
    CalcAndComp("1-a", ERRCODE);
    CalcAndComp("a-1", ERRCODE);
    CalcAndComp("*", ERRCODE);


    /*======  support braces  ======*/
    CalcAndComp("15/(7-(1+1))*3", 9);
    CalcAndComp("6/(2*2+2)", 1);
    CalcAndComp("(2)-(2)*(2)", -2);
    CalcAndComp("2*(2*(2*(1+1)+1))", 20);


    /*======  support unary minus  ======*/
    CalcAndComp("1*-2", -2);
    CalcAndComp("2---1", 1);
    CalcAndComp("1--1", 2);
    CalcAndComp("-(2+2*2)-2*3+12", 0);
    CalcAndComp("(2*-(2+4))/(-4+1)", 4);


    /*======  support unary plus  ======*/
    CalcAndComp("2++2", 4);


    /*======  support white spaces  ======*/
    CalcAndComp("-1+(4-2)+((5*5) + -8) / 2+1", 10.5);


    printf("\n");
    return 0;
}
/*=========================  END OF MAIN FUNCTIONS  =========================*/
