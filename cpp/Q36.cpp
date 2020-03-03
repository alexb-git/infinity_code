/****************************************************************************
** Filename:    - Q36.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Intoduction question to c++
** Date:        - 30/1/2018
** Version:     - 36
*****************************************************************************/
#include <iostream>  /* cout */
#include <iomanip>   /* std::setw */
#include <cstdlib>   /* exit */
#include <cstring>   /* string */

#include <exception>      // std::set_terminate
#include <cstdlib>        // std::abort

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

using namespace std;
/****************************************************************************
    Helpful defines and inline functions
*****************************************************************************/
inline void PrintHeader(const char *str)
{
    std::cout << BLU BLD "\n\t------------  This is a test for: "
              << str << " ------------\n" RES << std::endl;
}

inline void PrintInYellow(const char *str) {cout << YLL << str << RES;}
inline void PrintOK()  { std::cout << GRE "-OK" RES; }
inline void PrintERR() { std::cout << RED "-ERR" RES; }

#define Alighl(X)         ( std::left << std::setw(X) )
#define PrintOKorERR(X)   ( (X)?(PrintOK()):(PrintERR()) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )
/****************************************************************************/

struct BadDog: public runtime_error
{
    // default ctor
    BadDog(const std::string &s_ = "This is a bad dog") : runtime_error(s_)
    {}
};

/*==========================  CLASS ANIMAL  =================================*/
class Animal
{
public:
    Animal(size_t val) : m_nun_of_legs(val)
    {
        std::cout << BLU BLD "Animal Ctor | num of legs = " << m_nun_of_legs
        << RES << std::endl;
    }

    ~Animal()
    {
        std::cout << BLU RED "Animal Dtor | num of legs = " << m_nun_of_legs
        << RES << std::endl;
    }

private:
    size_t m_nun_of_legs;
};
/*==========================  END OF CLASS ANIMAL  ==========================*/

void Fifi()
{
    Animal   stack_snake(0);
    Animal  *heap_snake = new Animal(0);

    throw BadDog("bad pup");
    std::cerr << YEL "Fifi() after throw" RES << std::endl;
}

void Foo()
{
    Animal   stack_human(2);
    Animal  *heap_human = new Animal(2);

    Fifi();
    std::cerr << YEL "Foo() after Fifi()" RES << std::endl;
}

void Bar()
{
    Animal   stack_dog(4);
    Animal  *heap_dog = new Animal(4);

    Foo();
    std::cerr << YEL "Bar() after Foo()" RES << std::endl;
}

void myterminate ()
{
  std::cerr << RED "terminate handler called" RES << std::endl;
  abort();  // forces abnormal termination
}

/*==========================  THE MAIN  ==========================*/
int main(int argc, char const *argv[], char const *envp[])
{
    set_terminate (myterminate);
    try
    {
        Bar();
    }
    catch (bad_alloc)
    {
        std::cerr << RED "Out of memory! exiting " RES << std::endl;
        exit(2);
    }
    // catch (BadDog &b)
    // {
    //     std::cerr << RED "Bad dog exeption: " RES << b.what() << std::endl;
    //     // exit(3);
    // }
    catch (exception &r)
    {
        std::cerr << RED "unknown exeption: " RES << r.what() << std::endl;
        // exit(4);
    }
    // catch(...)
    // {
    // 	cerr << "default catch"<< endl;;
    // 	// exit(5);
    // }

    std::cout << BLD CYA "MADE IT TO THE END" RES << std::endl;
    return 0;
}
