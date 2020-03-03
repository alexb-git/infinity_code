#include <cstring>    /* functions_used */
#include <iostream>    /* functions_used */
#include <cmath>    /* functions_used */
/****************************************************************************/
void PrintBinary(size_t len, std::string str = "")
{
    if ( len == 0 )
    {
        std::cout << str << std::endl;
    }
    else
    {
        PrintBinary(len - 1 , str + "0");
        PrintBinary(len - 1 , str + "1");
    }
}

/****************************************************************************/
void PermutNum(size_t input, int choose = 0)
{
    if ( input == 0 )
    {
        std::cout << choose << std::endl;
    }
    else
    {
        for (size_t i = 0 ; i < input ; ++i )
        {
            size_t mult = pow(10, i);

            // choose
            choose *= 10;
            choose += (input / mult) % 10;
            input = (input / (10 * mult)) * mult + input % mult; // erase


            // explore
            PermutNum(input, choose);


            // un-chose
            input *= 10;
            input += (choose / mult) % 10;
            choose = (choose / (10 * mult)) * mult + choose % mult; // erase
        }
    }
}


int main(int argc, char const *argv[])
{
    const size_t digits_choose = 3;

    PrintBinary(digits_choose);

    std::cout << std::endl;

    PermutNum(1234, 4);



    return 0;
}
