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

Animal* Doo()
{
    return (ilrd::Singleton<ilrd::Animal>::GetSingltone());
}

}
