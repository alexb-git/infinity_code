/*	IMPORTANT !!!  This program need to be copiled with the command: "-lm"	*/
/*	gc programs_name.c -lm	*/

#include<stdio.h> 	/*	printf, scanf	*/
#include<math.h>	/*	pow - x^y	*/


void Swap (int *a, int *b); /* self explanatory	*/

/*	will print "Hello Word!" from hex values to char*/
void PrintHelloHexa ();

/* 	solves for 10^x	for given x*/
double TenToPower(int power);

/*	receives an int and flips ot (-12340 will turn into -4321)	*/
int FlipInt (int input);

/*	compares between expected result and function result. prints for ints*/
void CompareAndPrintInt (int input, int func_result, int ex_result);

/*	compares between expected result and function result. prints for float*/
void CompareAndPrintDouble (int input, double func_result, double ex_result);

/*	prints |input value| |function result| |expected result| as title */
void PrintHeaders();


#define PRINT_IN_GREEN 	"\x1b[32m"
#define PRINT_IN_RED 	"\x1b[31m"
#define PRINT_CO_RESET 	"\x1b[0m"
#define BASE 			10	/*	for the FlipInt function. 10 for decimal base*/
#define PRECISION_DIGIT	6 	/*	when comparing two doubles	*/
/*______________________________________________________________________________
	START OF MAIN FUNCTION
  ______________________________________________________________________________*/
int main()
{
	int i; /*	variable for loops	*/
	
	/* -------------ARRAY FOR TESTING THE FlipInt FUNCTION------------------*/
	/*array in the format of 
	{input_value#1, expected_result#1, input_value#2, expected_result#2....}*/
	int inputsANDresults[][2] = { { -12, -21 }, { -123, -321}, { -1, 1},
								  { 34567, 876443}, { -95173, -37159}	};	
	
	int arr_length = sizeof(inputsANDresults)/sizeof(inputsANDresults[0]);
	
	
	
	/* -------------ARRAY FOR TESTING THE TenToPower FUNCTION---------------*/
	/*array in the format of 
  	{input_value#1, input_value#2, input_value#3....}*/
	int inputsToCheck[] = { -2, 3, -15, -1, 1, 25, -3};	
	
	int arr_length2 = sizeof(inputsToCheck)/sizeof(inputsToCheck[0]);

	
	/*	will print "Hello Word!" from hex values to char*/
	PrintHelloHexa ();


	/*	This will test The FlipInt function	*/
	printf ("\n\n This will test The FlipInt function \n");
	PrintHeaders(); /* prints |input value| |function result| |expected result|*/
	
	for ( i = 0 ; i < arr_length ; ++i )
	{
		CompareAndPrintInt	( inputsANDresults[i][0]			, 
							  FlipInt (inputsANDresults[i][0])	, 
							  inputsANDresults[i][1]			);
	}	
	printf("\n-----------------------------------------------------------------\n");
	
	/*	This will test The TenToPower function	*/
	printf ("\n\n This will test The TenToPower function \n");
	PrintHeaders(); /* prints |input value| |function result| |expected result|*/
	
	for ( i = 0 ; i < arr_length2 ; ++i)
	{
		CompareAndPrintDouble 	( inputsToCheck[i]				,
								  TenToPower (inputsToCheck[i])	, 
								  pow(10,inputsToCheck[i])		);
	}
	printf("\n-----------------------------------------------------------------\n");
	
	return 0;
}
/*______________________________________________________________________________
	END OF MAIN FUNCTION
______________________________________________________________________________*/


/* Simplest SWAP function */
/*
	printf("\nSwap: Enter a and b\n");
	scanf ("%d", &a);
	scanf ("%d", &b);
	printf("Before Swap:\t a=%d , b=%d\n", a, b);
	Swap (&a, &b);
	printf("After Swap:\t a=%d , b=%d\n", a, b);
	
*/
void Swap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;	
}

/*******************************************************************************
	prints 	|input|  	|function|  	|expected|
			|value|		|result|		|result|
*******************************************************************************/
void PrintHeaders ()
{
	/*int i; */
	
	printf("\n|input|\t\t|function|\t\t|expected|\n");
	printf("|value|\t\t|result|\t\t|result|\n\n");
	
	/*
	for ( i = 0 ; i < arr_length ; i = i + 2)
	{
		TestFunction (arr[i], FlipInt (arr[i]), arr[i+1]);
	}
	*/
}


/*******************************************************************************
	FUNCTION that tests/compares between function output and expected result
*******************************************************************************/

void CompareAndPrintInt (int input, int func_result, int ex_result)
{
	printf("%d"   "\t->\t" 	"%d"   "\t==\t"		"%d"   "\t-->\t", 
			input, 			func_result, 		ex_result);

	if (func_result == ex_result)
	{	
		printf(PRINT_IN_GREEN " CORRECT" PRINT_CO_RESET "\n");				
	}
	else
	{
		printf(PRINT_IN_RED " INCORRECT" PRINT_CO_RESET "\n");
	}

}


void CompareAndPrintDouble (int input, double func_result, double ex_result)
{
	double precision = pow (10 , -PRECISION_DIGIT);
	delta = func_result - ex_result;	/* later. instead of using ABS function */
	
	printf(	"%d"   "\t->\t"  "%f"   "\t==\t"		"%f"   "\t-->\t", 
			input, 			(double)func_result, 	(double)ex_result);

	if (delta < 0)
	{
		delta *= -1;
	}

	if ( delta <= precision)
	{				
		printf(PRINT_IN_GREEN " CORRECT" PRINT_CO_RESET "\n");			
	}
	else
	{
		printf(PRINT_IN_RED " INCORRECT" PRINT_CO_RESET "\n");	
	}

}
/*******************************************************************************
	FUNCTION that receives an int and flips ot (-12340 will turn into -4321)
*******************************************************************************/
/*
	int x;
	printf ("\nThis program flips an integer.\n");
	printf ("Enter integer x:  ");
	scanf ("%d", &x);
	
	printf ("\nResult of flip = %d\n",FlipInt(x) );
*/

int FlipInt (int input)
{
	int result;
	int sign = 0; /* "0" for "+" sign | "1" for "-" sign*/
	
	/* Case - input is a negative number */
	if (input < 0)
	{
		sign = 1;
		input *= -1;
	}

	result = 0;
	
	/* the flip operation */
	/* NOTE: this will work on single digit number as well */
	while ( input > 0)
	{
		result = (result * BASE) + (input % BASE);
		input /= BASE;	
	}
	
	return (1 == sign) ? (-1)*(result) : (result) ;
}



/*******************************************************************************
	FUNCTION that receives an int number and returns 10^number
*******************************************************************************/
/*
	int x;
	printf ("\nThis program solves for 10^x.\n");
	printf ("Enter integer x:  ");
	scanf ("%d", &x);
	
	printf ("\nResult of 10^(%d) = %f\n",x , TenToPower(x) );
*/

double TenToPower(int power)
{
	
	int i;
	double result = 1, input = 10;
	
	if (power < 0)
	{
		power *= -1;
		input = 1./10;
	}
	
	for ( i = 0 ; i < power ; ++i)
	{
		result *= input ;
	
	}
	return result;
	
}


/*******************************************************************************
	print "Hello Word!" (including quotation marks) by usin hexadecimal numbers 
	in string (use ANCII table to convert characters to hexadecimal values)
*******************************************************************************/
void PrintHelloHexa ()
{
    char arr[] = {"\"Hello Word!\""};
    
    int i=0;
    
    printf("\nThis functin deals with representing the chars of the ");
    printf("\nstring 'Hello word!' with hexadecimal numbers and then printing ");
    printf("\nthe string from hex represntation");
    
    printf("\n\n(char) (hex)\n");
    printf("\n_____  _____\n");
    for ( i = 0 ; i < sizeof arr ; ++i)
    {
    	/*	THIS PRINT IS USED TO ILLUSTRATE THE CORISPONDING 
    		VALUES OF CHARS AND HEX IN THE STRING*/
    	printf(" %c  -  0x%x\n", (char) arr[i], arr[i]);
    	
    	/*	THIS PRINT WAS USED FO GET THE HEX 
    		VALUES OF THE STRING IN A SINGLE LINE
    	printf("\\x%x", arr[i]);
    	*/
    }
    
	
	printf("\nprintf(\"\\x22\\x48\\x65\\x6c\\x6c\\x6f\\x20\\x57\\x6f\\x72\\x64\\x21\\x22\")\n");
	
    printf("\n\x22\x48\x65\x6c\x6c\x6f\x20\x57\x6f\x72\x64\x21\x22\n\n");
    
    printf("----------------------------------------------------------------------");
}


/*	Answer what will be the values of 
	x and y after we run the program
void Experiment ()
{
	int x = 20 , y = 35;
	x = y++ + x++;
	y = ++y + ++x;
	printf("\n%d %d\n", x, y);
}
*/

