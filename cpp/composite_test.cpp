/****************************************************************************
** Filename:    - composite_test.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - testing composite design pattern
** Date:        - 13/2/2018
** Version:     - 1
*****************************************************************************/
#include "composite.hpp"

/*==========================  THE MAIN  ==========================*/
int main(int args, char** argv)
{
    try
    {
        ilrd::Directory d("/home/xyz/svn/Proj");
        d.Print();
    }
    catch (std::exception &e)
    {
        /* user may do something according to exception */
        return 1;
    }

    return 0;
}
/*==========================  END OF MAIN  ==========================*/
