/****************************************************************************
** Filename:    - singleton_test.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - design pattern - singleton testing
** Date:        - 20/2/2018
** Version:     - 1
*****************************************************************************/
#include <iostream>    /* count, cin */

#include "singleton.hpp"    /* singleton dp */

namespace ilrd
{

Animal* Voo()
{
    return (ilrd::Singleton<ilrd::Animal>::GetSingltone());
}

extern "C"
{
    void* CVoo()
    {
        std::cout << "in extern \"C\"" << std::endl;
        return ilrd::Voo();
    }
}

}
