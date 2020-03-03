/* Author: Alex B
** Last update: 11.09.17 17:00
** Program: 
*/

#include <stdio.h>  /* printf */
#include "bits_array.h"
#include <string.h>

#define BITS_ARRAY_SIZE (64)

#define PRINT_IN_GREEN  "\x1b[32m"
#define PRINT_IN_RED    "\x1b[31m"
#define PRINT_IN_YELLOW "\x1b[93m"
#define PRINT_CO_RESET  "\x1b[0m"

#define PRINT_IN_BLUE   "\x1B[34m"
#define PRINT_IN_MAG    "\x1B[35m"
#define PRINT_IN_CYN    "\x1B[36m"
#define PRINT_IN_WHT    "\x1B[37m"

void PrintBitsArray(size_t bits_array);
void CompareAndPrint(size_t func_result, size_t ex_result);

void TestBitsArrayAllOn();
void TestPrintBitsArrayAllOn(size_t input, size_t expected_result);

void TestBitsArrayAllOff();
void TestPrintBitsArrayAllOff(size_t input , size_t expected_result);

void TestBitsArraySetBitOn();
void TestPrintBitsArraySetBitOn(size_t input , size_t ex_result, size_t index);

void TestBitsArraySetBitOff();
void TestPrintBitsArraySetBitOff(size_t input , size_t ex_result, size_t index);

void TestBitsArraySetBit();
void TestPrintBitsArraySetBit(  size_t bits_array, size_t ex_result, 
                                size_t index, int BitValue);

void TestBitsArrayIsBitOn();
void TestPrintBitsArrayIsBitOn( size_t bits_array, size_t ex_result, 
                                size_t index);

void TestBitsArrayIsBitOff();
void TestPrintBitsArrayIsBitOff(size_t bits_array, size_t ex_result, 
                                size_t index);

void TestBitsArrayInvertBits();
void TestPrintBitsArrayInvertBits(size_t bits_array, size_t expected_result);

void TestBitsArrayCountSetBits();
void TestPrintBitsArrayCountSetBits(size_t bits_array, size_t expected_result);

void TestBitsArrayCountOffBits();
void TestPrintBitsArrayCountOffBits(size_t bits_array, size_t expected_result);

void TestPrintBitsArrayMirror();
void TestBitsArrayMirror(size_t func_result, size_t ex_result);

void TestPrintBitsArrayRotateLeft();
void TestBitsArrayRotateLeft(size_t func_result, size_t ex_result, size_t n);

void TestPrintBitsArrayRotateRight();
void TestBitsArrayRotateRight(size_t func_result, size_t ex_result, size_t n);

void TestBitsArrayLutCountOn();
void TestPrintBitsArrayLutCountOn(size_t bits_array, size_t expected_result);

void TestPrintBitsArrayLutMirror(size_t input , size_t ex_result);
void TestBitsArrayLutMirror();

void TestBitsArrayLutCountOn();
void TestPrintBitsArrayLutCountOn(size_t bits_array, size_t expected_result);

void TestPrintBitsArrayLutMirror(size_t input , size_t ex_result);
void TestBitsArrayLutMirror();


int main(int argc, char const *argv[])
{
    TestBitsArrayAllOn();
    TestBitsArrayAllOff();
    TestBitsArraySetBitOn();
    TestBitsArraySetBitOff();
    TestBitsArraySetBit();
    TestBitsArrayIsBitOn();
    TestBitsArrayIsBitOff();
    TestBitsArrayInvertBits(); 
    TestBitsArrayCountSetBits();
    TestBitsArrayCountOffBits();
    TestPrintBitsArrayMirror();
    TestPrintBitsArrayRotateLeft();
    TestPrintBitsArrayRotateRight();
    TestBitsArrayLutCountOn();
    TestBitsArrayLutMirror();

    return 0;
}


/*******************************************************************************
        FUNCTION that compares between the two inputes and prints accordingly
*******************************************************************************/
void CompareAndPrint(size_t func_result, size_t ex_result)
{

        if (func_result == ex_result)
        {
                printf(PRINT_IN_GREEN " [== CORRECT ==] " PRINT_CO_RESET "\n");
        }
        else
        {
                printf(PRINT_IN_RED " [== INCORRECT ==] " PRINT_CO_RESET "\n");
        }
}


/******************************************************************************
        auxiliary function for the tests functions. simply prints colorful header
        with function name that we test
******************************************************************************/
void PrintHeader(char *function_name)
{
        printf(PRINT_IN_YELLOW
                "\n\t-----This is a test for %s function-----\n"
                PRINT_CO_RESET, function_name);
}


/*******************************************************************************
        prints the bits of size_t type
*******************************************************************************/
void PrintBitsArray(size_t bits_array)
{
        long i = 0;

        for (i = (BITS_ARRAY_SIZE - 1); i >= 0; --i)
        {
                printf("%ld", (bits_array >> i) & 1);
                /* prints " " (separations) every 4 bits */
                printf("%s", ( (i)%4 )?(""):(" ") );
        }
        printf("\n");
}


/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArrayAllOn()
{
    PrintHeader("BitsArrayAllOn");

    TestPrintBitsArrayAllOn(0x0123456789ABCDEF,0xFFFFFFFFFFFFFFFF);

}
/******************************************************************************/

void TestPrintBitsArrayAllOn(size_t input , size_t ex_result)
{
        size_t func_result = BitsArrayAllOn(input);
        printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
        PrintBitsArray(input);
        printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
        PrintBitsArray(func_result);
        printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
        PrintBitsArray(ex_result);
        CompareAndPrint(func_result, ex_result);
        printf(PRINT_CO_RESET"\n");
}



/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArrayAllOff()
{
    PrintHeader("BitsArrayAllOff");

    TestPrintBitsArrayAllOff(0x0123456789ABCDEF,0);

}


/******************************************************************************/
void TestPrintBitsArrayAllOff(size_t input , size_t ex_result)
{
        size_t func_result = BitsArrayAllOff(input);
        printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
        PrintBitsArray(input);
        printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
        PrintBitsArray(func_result);
        printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
        PrintBitsArray(ex_result);
        CompareAndPrint(func_result, ex_result);
        printf("\n");
}


/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArraySetBitOn()
{
    PrintHeader("BitsArraySetBitOn");

    TestPrintBitsArraySetBitOn(0, 1, 63);

    TestPrintBitsArraySetBitOn(0, 0x0080000000000000, 8);
}


/******************************************************************************/
void TestPrintBitsArraySetBitOn(size_t input , size_t ex_result, size_t index)
{
    size_t func_result = BitsArraySetBitOn(input, index);
    printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
    PrintBitsArray(input);
    printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
    PrintBitsArray(func_result);
    printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
    PrintBitsArray(ex_result);
    CompareAndPrint(func_result, ex_result);
    printf("\n");
}

/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArraySetBitOff()
{
    PrintHeader("BitsArraySetBitOff");
    TestPrintBitsArraySetBitOff(~0, 0xFF7FFFFFFFFFFFFF, 8);
    TestPrintBitsArraySetBitOff(1, 0, 63);
}


/******************************************************************************/
void TestPrintBitsArraySetBitOff(size_t input , size_t ex_result, size_t index)
{
    size_t func_result = BitsArraySetBitOff(input, index);
    printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
    PrintBitsArray(input);
    printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
    PrintBitsArray(func_result);
    printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
    PrintBitsArray(ex_result);
    CompareAndPrint(func_result, ex_result);
    printf("\n");
}


/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArraySetBit()
{
    PrintHeader("BitsArraySetBit");

    TestPrintBitsArraySetBit(0xd, 0xf, 62, 1);

    TestPrintBitsArraySetBit(0x1, 0x1, 63, 1);

    TestPrintBitsArraySetBit(0xff, 0xfe, 63, 0);

}

/******************************************************************************/
void TestPrintBitsArraySetBit(  size_t input, size_t ex_result, 
                                size_t index, int BitValue)
{
    size_t func_result = BitsArraySetBit(input, index, BitValue);
    printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
    PrintBitsArray(input);
    printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
    PrintBitsArray(func_result);
    printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
    PrintBitsArray(ex_result);
    CompareAndPrint(func_result, ex_result);
    printf("\n");
}


/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArrayIsBitOn()
{
    PrintHeader("BitsArrayIsBitOn");
    TestPrintBitsArrayIsBitOn(1, 1, 63);
    TestPrintBitsArrayIsBitOn(0xFFFFFFFFFFFFFFFF, 1, 2);
    TestPrintBitsArrayIsBitOn(0xFFFFFFFFFFFFFFeF, 0, 59);

    printf("\n");
}


/******************************************************************************/
void TestPrintBitsArrayIsBitOn(size_t bits_array, size_t ex_result, size_t index)
{
    int result = BitsArrayIsBitOn(bits_array, index);
    PrintBitsArray(bits_array);

    if (ex_result == result)
    {
        printf( PRINT_IN_GREEN "IsBitOn at index %lu is  - %d (%s)" 
                PRINT_CO_RESET "\n", index, result,(result)?("on"):("off") );
    }
    else
    {
        printf( PRINT_IN_RED "IsBitOn at index %lu is  - %d (%s)" 
                PRINT_CO_RESET "\n", index, result,(result)?("on"):("off") );
    }
}


/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArrayIsBitOff()
{
    PrintHeader("BitsArrayIsBitOff");
    TestPrintBitsArrayIsBitOn(1, 0, 62);
    TestPrintBitsArrayIsBitOn(0xFFFFFFFFFFFFFFFF, 1, 2);
    TestPrintBitsArrayIsBitOn(0xFFFFFFFFFFFFFFeF, 0, 59);

    printf("\n");
}


/******************************************************************************/
void TestPrintBitsArrayIsBitOff(size_t bits_array, size_t ex_result, size_t index)
{
    int result = BitsArrayIsBitOff(bits_array, index);
    PrintBitsArray(bits_array);

    if (ex_result == result)
    {
        printf( PRINT_IN_GREEN "IsBitOn at index %lu is  - %d (%s)" 
                PRINT_CO_RESET "\n", index, result,(result)?("on"):("off") );
    }
    else
    {
        printf( PRINT_IN_RED "IsBitOn at index %lu is  - %d (%s)" 
                PRINT_CO_RESET "\n", index, result,(result)?("on"):("off") );
    }
}


/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArrayInvertBits()
{
        printf("========= Testing BitsArrayInvertBits ========\n");

        TestPrintBitsArrayInvertBits(0xFFFFFFFF00000000, 0x00000000FFFFFFFF);
        TestPrintBitsArrayInvertBits(0xAAAAAAAA33333333, 0x55555555cccccccc);

}

/******************************************************************************/
void TestPrintBitsArrayInvertBits(size_t input, size_t ex_result)
{
    size_t func_result = BitsArrayInvertBits(input);
        printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
        PrintBitsArray(input);
        printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
        PrintBitsArray(func_result);
        printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
        PrintBitsArray(ex_result);
        CompareAndPrint(func_result, ex_result);
        printf("\n");
}        


/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArrayCountSetBits()
{
        printf("========= Testing BitsArrayCountSetBits ========\n");

        TestPrintBitsArrayCountSetBits(1+2+4+8+16+32, 6);
        TestPrintBitsArrayCountSetBits(0, 0);
        TestPrintBitsArrayCountSetBits(32+64+128+256,4);
        TestPrintBitsArrayCountSetBits(0xFFFFFFFFFFFFFFFF,64);
}

/******************************************************************************/
void TestPrintBitsArrayCountSetBits(size_t input, size_t ex_result)
{
        size_t func_result = BitsArrayCountSetBits(input);
        printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
        PrintBitsArray(input);
        printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
        PrintBitsArray(func_result);
        printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
        PrintBitsArray(ex_result);
        CompareAndPrint(func_result, ex_result);
        printf("\n");
}


/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArrayCountOffBits()
{
    printf("========= Testing BitsArrayCountOffBits ========\n");
    TestPrintBitsArrayCountOffBits(1+2+4+8+16, 64-5);
    TestPrintBitsArrayCountOffBits(0, 64);
    TestPrintBitsArrayCountOffBits(32+64+128+256,64-4);
    TestPrintBitsArrayCountOffBits(32+64+128+256+1024+2048,64-6);
    TestPrintBitsArrayCountOffBits(32+64+128+256,64-4);
    TestPrintBitsArrayCountOffBits(127,64-7);
    TestPrintBitsArrayCountOffBits(0xFFFFFFFFFFFFFFFF,0);
}


/******************************************************************************/
void TestPrintBitsArrayCountOffBits(size_t input, size_t ex_result)
{
        size_t func_result = BitsArrayCountOffBits(input);
        printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
        PrintBitsArray(input);
        printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
        PrintBitsArray(func_result);
        printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
        PrintBitsArray(ex_result);
        CompareAndPrint(func_result, ex_result);
        printf("\n");
}


/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArrayRotateRight(size_t input, size_t ex_result, size_t n)
{
        size_t func_result = BitsArrayRotateRight(input,n);
        printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
        PrintBitsArray(input);
        printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
        PrintBitsArray(func_result);
        printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
        PrintBitsArray(ex_result);
        CompareAndPrint(func_result, ex_result);
        printf("\n");
}

/******************************************************************************/
void TestPrintBitsArrayRotateRight()
{

        PrintHeader("BitsArrayRotateRight");

        TestBitsArrayRotateRight(0xf000000000000000, 0x000000000000000f, 60);

        TestBitsArrayRotateRight(0x00000000000000ff, 0xf00000000000000f, 4);        

        TestBitsArrayRotateRight(0x8000000000000000, 0x4000000000000000, 1);

        TestBitsArrayRotateRight(0x0000000000000001, 0x0000000000000002, 127);
}


/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArrayRotateLeft(size_t input , size_t ex_result, size_t n)
{
        size_t func_result = BitsArrayRotateLeft(input,n);
        printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
        PrintBitsArray(input);
        printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
        PrintBitsArray(func_result);
        printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
        PrintBitsArray(ex_result);
        CompareAndPrint(func_result, ex_result);
        printf("\n");
}

/******************************************************************************/
void TestPrintBitsArrayRotateLeft()
{

        PrintHeader("BitsArrayRotateLeft");

        TestBitsArrayRotateLeft(0x000000000000000f, 0x0000000000000f00, 8);

        TestBitsArrayRotateLeft(0xf000000000000000, 0xc000000000000003, 2);        

        TestBitsArrayRotateLeft(0x8000000000000000, 0x0000000000000001, 1);

        TestBitsArrayRotateLeft(0x0000000000000001, 0x0000000000000002, 65);
}


/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/

void TestBitsArrayMirror(size_t input , size_t ex_result)
{
        size_t func_result = BitsArrayMirror(input);
        printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
        PrintBitsArray(input);
        printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
        PrintBitsArray(func_result);
        printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
        PrintBitsArray(ex_result);
        CompareAndPrint(func_result, ex_result);
        printf("\n");
}


/******************************************************************************/
void TestPrintBitsArrayMirror()
{

        PrintHeader("ArrayMirror");

        TestBitsArrayMirror(0x0000000000000001, 0x8000000000000000);

        TestBitsArrayMirror(0xffff100000000000, 0x000000000008ffff);

        TestBitsArrayMirror(0xaaaa00f000000001, 0x800000000f005555);

        TestBitsArrayMirror(0x0000000100000000, 0x0000000080000000);

}



/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestBitsArrayLutCountOn()
{
        PrintHeader("BitsArrayLutCountOn");
        TestPrintBitsArrayLutCountOn(1+2+4+8+16+32, 6);
        TestPrintBitsArrayLutCountOn(0, 0);
        TestPrintBitsArrayLutCountOn(32+64+128+256,4);
        TestPrintBitsArrayLutCountOn(0xFFFFFFFFFFFFFFFF,64);
}

/******************************************************************************/
void TestPrintBitsArrayLutCountOn(size_t input, size_t ex_result)
{
        size_t func_result = BitsArrayLutCountOn(input);
        printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
        PrintBitsArray(input);
        printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
        PrintBitsArray(func_result);
        printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
        PrintBitsArray(ex_result);
        CompareAndPrint(func_result, ex_result);
        printf("\n");
}

/******************************************************************************
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
******************************************************************************/
void TestPrintBitsArrayLutMirror(size_t input , size_t ex_result)
{
        size_t func_result = BitsArrayLutMirror(input);
        printf(PRINT_IN_BLUE "Input:\n"PRINT_CO_RESET);
        PrintBitsArray(input);
        printf(PRINT_IN_BLUE"Function result:\n"PRINT_CO_RESET);
        PrintBitsArray(func_result);
        printf(PRINT_IN_BLUE"Expected result:\n"PRINT_CO_RESET);
        PrintBitsArray(ex_result);
        CompareAndPrint(func_result, ex_result);
        printf("\n");
}


/******************************************************************************/
void TestBitsArrayLutMirror()
{
        PrintHeader("BitsArrayMirrorLut");

        TestBitsArrayMirror(0x0000000000000001, 0x8000000000000000);
        TestBitsArrayMirror(0xffff100000000000, 0x000000000008ffff);
        TestBitsArrayMirror(0xaaaa00f000000001, 0x800000000f005555);
        TestBitsArrayMirror(0x0000000100000000, 0x0000000080000000);
}
/******************************************************************************/