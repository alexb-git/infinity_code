/****************************************************************************
** Filename:    - Q24.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Intoduction question to c++
** Date:        - 5/1/2018
** Version:     - 24
*****************************************************************************/
#include <iostream>    /* cout */

struct ABC
{
    ABC(int a_, int b_);

    void Inc();
    void Dec();

    int m_a;
    int m_b;
};

ABC::ABC(int a_, int b_): m_a(a_), m_b(b_)
{
    std::cout << "Ctor\b" << std::endl;
}

void ABC::Inc()
{
    ++m_a;
    ++m_b;

    std::cout << "Inc func"
    << " | m_a = " << m_a
    << "  m_b = " << m_b
    << std::endl;
}

void ABC::Dec()
{
    --m_a;
    --m_b;

    std::cout << "Dec func"
    << " | m_a = " << m_a
    << "  m_b = " << m_b
    << std::endl;
}

/*=======================  MAIN FUNCTION  =======================*/
int main(int argc, char const *argv[])
{
    ABC x1(0, 0);
    ABC x2(x1);

    x1.Inc();
    x1.Inc();
    x2.Dec();

    return 0;
}
