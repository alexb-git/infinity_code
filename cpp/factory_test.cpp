/****************************************************************************
** Filename:    - factory_test.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - design pattern - factory testing
** Date:        - 25/2/2018
** Version:     - 1
*****************************************************************************/
#include <stdio.h>      /* fprintf, stderr */
#include "factory.hpp"    /* factory dp */
#include <memory>    /* functions_used */
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
class Animal
{
public:
    explicit Animal(int val) : m_int(val)
    {
        std::cout << BLD BLU "Animal Ctor " RES << m_int << std::endl;
    }

    virtual ~Animal()
    {
        std::cout << BLD RED "Animal Dtor " RES << m_int << std::endl;
    }

    static Animal* AnimalCtor(int val)
    {
        return (new Animal(val));
    }

private:

    int m_int;
};

class Dog : public Animal
{
public:
    explicit Dog(int val) : Animal(val), m_dbl(6.66)
    {
        std::cout << GRE CYA "Dog Ctor " RES << m_dbl << std::endl;
    }
    virtual ~Dog()
    {
        std::cout << RED "Dog Dtor " RES << m_dbl << std::endl;
    }

    static Animal* DogCtor(int val)
    {
        return (new Dog(val));
    }

private:
    double m_dbl;
};

/*============================  THE MAIN  ==============================*/
int main(int argc, char const *argv[])
{
    ilrd::Factory<Animal, std::string, int> factory;

    factory.Add("Alex", Animal::AnimalCtor);
    factory.Add("Bob", Dog::DogCtor);

    std::auto_ptr<Animal> an1(factory.Create("Alex", 5));
    std::auto_ptr<Animal> an2(factory.Create("Bob", 9));


    return 0;
}
