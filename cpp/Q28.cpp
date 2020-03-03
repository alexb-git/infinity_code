/****************************************************************************
** Filename:    - Q28.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Intoduction question to c++
** Date:        - 10/1/2018
** Version:     - 28
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
    ABC(): m_id(++s_cntr) {}

    int GetId()
    {
        std::cout << m_id << std::endl;
        return m_id;
    }

private:
    int         m_id;
    static int  s_cntr;

};

int ABC::s_cntr = 0;


/*=======================  MAIN FUNCTION  =======================*/
int main(int argc, char const *argv[])
{
    ABC x1;
    ABC x2;

    x1.GetId();
    x2.GetId();

    return 0;
}
