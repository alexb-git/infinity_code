/****************************************************************************
** Filename:    - shared_ptr_test.cpp
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - Share pointer data structure testing
** Date:        - 4/2/2018
** Version:     - 1
*****************************************************************************/
#include <iostream>      /* cin, cout */
#include "shared_ptr.h"  /* Bits array data structure */

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

/****************************************************************************
    Helpful defines and inline functions
*****************************************************************************/
inline void PrintHeader(const char *str)
{
    std::cout << BLU BLD "\n\t------------  This is a test for: "
              << str << " ------------\n" RES << std::endl;
}

inline void PrintInYellow(const char *str)\
{ std::cout << YLL << str << RES;}
inline void PrintOK()  { std::cout << GRE "-OK" RES; }
inline void PrintERR() { std::cout << RED "-ERR" RES; }

#define Alighl(X)         ( std::left << setw(X) )
#define PrintOKorERR(X)   ( (X)?(PrintOK()):(PrintERR()) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )
/****************************************************************************/
// #define PrintStatus(BitArr, len)
// std::cout << BitArr <<"   ";
// std::cout << CYA "BitsOn = " << BitArr.CountSetBit() << RES;
// PrintOKorERR(BitArr.CountSetBit() == len);

class Animal
{
public:
    Animal(int i = 0) : m_i(i)
    {
        std::cout << BLU BLD "Animal Ctor" RES << std::endl;
    }

    virtual void MakeSound()
    {
        std::cout << BLD YEL "I am anilmal I have no sound" RES << std::endl;
    }

    virtual ~Animal()
    {
        std::cout << RED BLD "Animal Dtor" RES << std::endl;
    }

private:
    inline Animal(const Animal& other){}
    inline Animal& operator=(const Animal& other){return *this;}
    int m_i;
};

class Dog : public Animal
{
public:
    Dog(double d = 3.14) : m_d(d)
    {
        std::cout << GRE BLD "Dog Ctor wuf wuf" RES << std::endl;
    }

    virtual void MakeSound()
    {
        std::cout << YEL "WUF WUF WUF WUF WUF WUF" RES << std::endl;
    }

    virtual ~Dog()
    {
        std::cout << RED "Dog Dtor noooo..." RES << std::endl;
    }

private:
    double m_d;
};


/*==========================  THE MAIN  ==========================*/
int main(int argc, char const *argv[])
{
    PrintInYellow("\n-> Create Dog\n");
    ilrd::SharedPtr<Dog> dog_ptr1(new Dog(0.666));


    /*==========================  pointer operators  =======================*/
    PrintInYellow(BLD UDL"\n ----- testing pointer operators -----\n");

    PrintInYellow("\n-> check operator-> ('dog_ptr1->MakeSound()')\n");
    dog_ptr1->MakeSound();

    PrintInYellow("\n-> check operator* ('(*dog_ptr1).MakeSound()')\n");
    (*dog_ptr1).MakeSound();

    PrintInYellow("\n-> check GetPtr\n");
    std::cout << "dog_ptr1.GetPtr() = "<< dog_ptr1.GetPtr() << std::endl;


    /*==========================  CCtors  ==================================*/
    PrintInYellow(BLD UDL"\n ----- testing CCtors -----\n");

    PrintInYellow("\n-> CCtor on animal_ptr1 (other type)\n");
    ilrd::SharedPtr<Animal> animal_ptr1(dog_ptr1);

    PrintInYellow("\n-> CCtor on Animal (same type)\n");
    ilrd::SharedPtr<Dog> dog_ptr2(dog_ptr1);


    /*==========================  Assigment operators  ======================*/
    PrintInYellow(BLD UDL"\n ----- testing Assigment operators -----\n");

    PrintInYellow("\n-> Create Animal\n");
    ilrd::SharedPtr<Animal> animal_ptr2(new Animal(666));

    PrintInYellow("\n-> check operator= (same type)\n");
    animal_ptr1 = animal_ptr2;

    PrintInYellow("\n-> check operator= (other type)\n");
    animal_ptr1 = dog_ptr1;

    PrintInYellow("\n-> check operator= (other type) Dtor need to be called\n");
    animal_ptr2 = dog_ptr1;

    PrintInYellow("\n-> check self assigment (self)\n");
    animal_ptr2 = animal_ptr2;
    animal_ptr2->MakeSound();

    PrintInYellow("\n-> check self assigment (other)\n");
    animal_ptr2 = dog_ptr2;
    animal_ptr2->MakeSound();


    // ilrd::SharedPtr<int> int_ptr1(new int(5));
    // ilrd::SharedPtr<int> int_ptr2(int_ptr1);

    // ilrd::SharedPtr<Dog> animal_ptr1(new Dog(0.666));
    // ilrd::SharedPtr<Animal> animal_ptr2(animal_ptr1);


    PrintInYellow("\n-> About to exit STACK, call detractors\n");
    std::cout << std::endl;
    return 0;
}
