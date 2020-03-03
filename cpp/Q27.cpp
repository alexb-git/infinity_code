/****************************************************************************
** Filename:    - Q27.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Intoduction question to c++
** Date:        - 5/1/2018
** Version:     - 27
*****************************************************************************/
#include <iostream>    /* cout */
#include <iomanip>     /* std::setw */

/****************************************************************************
    Helpful colors
*****************************************************************************/
#define YLL	 "\x1b[93m"
#define GRE	 "\x1b[92m"
#define RED	 "\x1b[91m"
#define WHI	 "\x1B[37m"
#define CYA	 "\x1B[36m"
#define BLU	 "\x1B[34m"
#define YEL	 "\x1b[33m"
#define RES	 "\x1b[0m"
#define BLD  "\x1B[1m"
#define UDL  "\x1b[4m"

/****************************************************************************/

class ABC
{
public:
    /*explicit*/ ABC(int n): m_num(n)
    {
        std::cout << YLL << "Ctor was called | "
        << "n_num = " << m_num
        << RES << std::endl;
    }

    operator int() const
    {
        std::cout << RED << "operator int() const - "
        << "converting from ABC (type) to int (type)"
        << RES << std::endl;

        return 42;
    }

    int GetNum() const
    {
        return m_num;
    }

private:
    int m_num;

};

/*==========================  Foo func  ==========================*/
void Foo(const ABC& x)
{
    std::cout << "inside Foo func | x.GetNum() = " << x.GetNum() << std::endl;

    /* conversion from int (type) to ABC (type) was performed here*/
    std::cout << "inside Foo func | x = " << x << std::endl;
}

/*==========================  Bar func  ==========================*/
void Bar(int num)
{
    std::cout << "inside Bar func | num = " << num << std::endl;
}

/*=======================  MAIN FUNCTION  =======================*/
int main(int argc, char const *argv[])
{
    std::cout << UDL BLD << "\nAbout to call Foo func" << RES << std::endl;
    Foo(3.14);

    std::cout << UDL BLD << "\nAbout to create ABC instant" << RES <<std::endl;
    ABC x_inst(3);

    std::cout << UDL BLD << "\nAbout to call Foo func" << RES << std::endl;
    Foo(x_inst);

    std::cout << UDL BLD << "\nAbout to call Bar func" << RES << std::endl;
    Bar(x_inst);

    std::cout << UDL BLD << "\nAbout to Distruct" << RES << std::endl;
    return 0;
}
