/****************************************************************************
** Filename:    - singleton_test.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - design pattern - singleton testing
** Date:        - 20/2/2018
** Version:     - 1
*****************************************************************************/
#include <stdio.h>      /* fprintf, stderr */
#include <dlfcn.h>      /* dlopen, dlcloe */
#include <iostream>     /* count, cin */

#include <gnu/lib-names.h>  /* Defines LIBM_SO
                              (which will be a string such as "libm.so.6") */

#include "singleton.hpp"    /* singleton dp */
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
using namespace ilrd;
/*
    g++ -c -std=c++98 -fPIC singletona.cpp singletonb.cpp
    g++ -shared -o libTest.so singletona.o singletonb.o
    sudo cp libTest.so /usr/lib
    g++ singleton_test.cpp -lTest -lpthread
    ./a.out
*/

// class Animal
// {
// public:
//     ~Animal()
//     { std::cout << RED "~Animal dtor" RES << std::endl;}
//
//     void MakeSound() const
//     {
//         std::cout << YEL "I am an animal"RES << std::endl;
//     }
//
//     Animal() : m_hight(666)
//     { std::cout << GRE "Animal ctor" RES << std::endl;}
//
// private:
//     int m_hight;
//
//
//     friend class ilrd::Singleton<Animal>;
// };
//
//
void* CallSingletone(void *ignored)
{
    ilrd::Singleton<Animal>::GetSingltone()->PrintDetails();

    return NULL;
}

// class Animal : public Animal
// {
//     void MakeSound()
//     {
//         std::cout << "I am a Animal" << std::endl;
//     }
// };
//
// void Foo(const Animal &ref)
// {
//     std::cout << CYA;
//     ref.MakeSound();
//     std::cout << RES;
// }


/*==========================  THE MAIN  ==========================*/
int main(int argc, char const *argv[])
{
    // Animal *a = Voo();/* inplisit. the linker does the job */
    // Animal *b = Doo();/* inplisit. the linker does the job */
    // std::cout << "Voo() = " << RED << a << RES<< std::endl;
    // std::cout << "Doo() = " << RED << b << RES << std::endl;
    std::cout << "Singleton<Animal>::GetSingltone() " << RED
     << Singleton<Animal>::GetSingltone() << RES << std::endl;

    char *error;
    void *handle;
    Animal* (*foo_ptr)();/* function pointer declaration */


    handle = dlopen("libTest.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "Was I here?!\n");
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    foo_ptr = (Animal* (*)()) dlsym(handle, "CVoo");

    error = dlerror();
    if (error != NULL)
    {
        fprintf(stderr, "Was I here 2 ?!\n");
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    Animal* e_dog1 = (foo_ptr)();/* explisit. activate the function */
    std::cout << "(foo_ptr)() = " << RED<< e_dog1 << RES << std::endl;

    dlclose(handle);
    // exit(EXIT_SUCCESS);


    // const int n_threads = 3;
    // pthread_t threads[n_threads];
    //
    // for (int i = 0 ; i < n_threads ; ++i )
    // {
    //     pthread_create(threads + i, NULL, CallSingletone, NULL);
    // }
    //
    // for (int i = 0 ; i < n_threads ; ++i )
    // {
    //     pthread_join(threads[i], NULL);
    // }


    // Animal bob;
    // Foo(bob);




    return 0;
}
