/****************************************************************************
** Filename:    - Q30.cpp
** Code Author: - Alex Parent
** Mail:        - aether.alex@gmail.com
** Purpose:     - Intoduction question to c++
** Date:        - 15/1/2018
** Version:     - 30
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

using std::cout;
using std::endl;
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

inline void PrintStatus( const char *color   , const char *caller,
                         const char *descr   , double      input ,
                         void       *this_ptr, size_t      id    )
{
    cout << color
    << std::left << std::setw(9) << caller
    << "| "
    << "this : " << this_ptr << " | "
    << std::left << std::setw(9) << descr
    << input << " | id = " << id
    << RES << endl << std::flush;
}


/*========================== CLASS Parent =================================*/
class Base
{
public:
    Base(int a_ = 11) : m_a(a_)
    {
        ++count;
        id = count;
        arr = new char;
        PrintStatus(BLU, "Base", "Ctor | m_a = ", m_a, this, id);
    }


    Base(const Base &ref) : m_a(ref.m_a)
    {
        ++count;
        id = count;
        arr = new char;
        PrintStatus(CYA, "Base", "CCtor | m_b = ", m_a, this, id);
    }


    virtual ~Base()
    {
        // cout << RED << "~Base() dtor " << endl << std::flush;
        PrintStatus(RED, "~Base", " base dtor | m_a = ", m_a, this, id);
        delete arr;
    }

    virtual void BullShit(void)
    {
        std::cout << "I am doning something" << std::endl;
    }

private:
    int    m_a;

    char  *arr;
    size_t id;
    static size_t count;
};

size_t Base::count = 0;

/*============================== CLASS Child =====================================*/
class Derived: public Base
{
public:
    Derived(int a_ = 99) : m_b(a_)
    {
        ++count;
        id = count;
        arr = new char;
        PrintStatus(CYA, "Derived", "Ctor | m_b = ", m_b, this,id);
    }

    Derived(const Derived &ref) : m_b(ref.m_b)
    {
        ++count;
        id = count;
        arr = new char;
        PrintStatus(CYA, "Derived", "CCtor | m_b = ", m_b, this,  id);
    }

    ~Derived()
    {
        // cout << RED << "~Derived() dtor " << endl << std::flush;
        PrintStatus(RED, "~Derived", " derived dtor | m_b = ", m_b, this, id);
        delete arr;
    }

private:
    int    m_b;

    char  *arr;
    size_t id;
    static size_t count;
};

size_t Derived::count = 0;

/****************************************************************************/
void Foo(Base base)
{
    std::cout << "Foo function | I am doning something" << std::endl;
}

/*==========================  THE MAIN  ==========================*/
int main(int argc, char const *argv[], char const *envp[])
{
    Derived derived;
    Foo(derived);

    // Base *base = new Derived[3];
    //
    // {
    //     cout << endl;
    //     cout << "sizeof(*base)          = " << sizeof(*base) << endl;
    //     cout << "sizeof(class base)     = " << sizeof(class Base) << endl;
    //     cout << "sizeof(class Derived)  = " << sizeof(class Derived) << endl;
    // }
    //
    // delete[] base/*static_cast<Derived*>(base)*/;



    return 0;
}
