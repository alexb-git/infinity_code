/****************************************************************************
** Filename:    - Q29.cpp
** Code Author: - Alex Parent
** Mail:        - aether.alex@gmail.com
** Purpose:     - Intoduction question to c++
** Date:        - 10/1/2018
** Version:     - 29
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

inline void PrintStatus( const char* color ,
                         const char* caller,
                         const char* descr , double input)
{
    cout << color
    << std::left << std::setw(9) << caller
    << "| "
    << std::left << std::setw(9) << descr
    << input << RES << endl;
}


/*========================== CLASS Parent =================================*/
class Parent
{
public:
    Parent(int a_ = 11) : m_a(a_)
    { PrintStatus(GRE, "Parent", "Ctor", m_a); }

    Parent(const Parent& b): m_a(b.m_a)
    { PrintStatus(GRE, "Parent", "Cctor", m_a);}

    virtual ~Parent()
    { PrintStatus(GRE, "Parent", "Dtor", m_a); }

    virtual void Print1() const
    { PrintStatus(GRE, "Parent", "Print1", m_a); }

    virtual void Print2() const
    { PrintStatus(GRE, "Parent", "Print2", m_a); }

    virtual void Print3() const
    { PrintStatus(GRE, "Parent", "Print3", m_a); }

private:
    int     m_a;
    double  pi;
};

/*============================== CLASS Child =====================================*/
class Child: public Parent
{
public:
    Child(): Parent(22) ,m_b(100)
    { PrintStatus(RED, "Child", "Ctor", m_b); }

    ~Child()
    { PrintStatus(RED, "Child", "Dtor", m_b); }

    void Print1() const
    {
        PrintStatus(RED, "Child", "Print1 S", m_b);
        // this->Parent::Print1();
        Parent::Print1();
        PrintStatus(RED, "Child", "Print1 E", m_b);
    }

    void Print2() const
    { PrintStatus(RED, "Child", "Print2", m_b); }

    void PrintConst() const
    { PrintStatus(RED, "Child", "This is not kosher ", m_b); }


private:
        int m_b ;
};

/*==========================  THE MAIN  ==========================*/
int main(int argc, char const *argv[], char const *envp[])
{
    PrintInYellow("\n-> About to allocate parent and child classes\n");
    Parent* parent = new Parent;
    Parent* child  = new Child;

    {
        cout << endl;
        cout << "sizeof(*parent)      = " << sizeof(*parent) << endl;
        cout << "sizeof(*child)       = " << sizeof(*child) << endl;
        cout << "sizeof(class Parent) = " << sizeof(class Parent) << endl;
        cout << "sizeof(class Child)  = " << sizeof(class Child) << endl;
    }

    {
        PrintInYellow("\n-> Parent calls\n");
        parent->Print1();
        parent->Print2();
        parent->Print3();
    }


    {
        PrintInYellow("\n-> Child calls");

        cout << "\n...child->Parent::Print1()" << endl;
        child->Parent::Print1();

        cout << "\n...child->Print1()" << endl;
        child->Print1();

        cout << "\n...child->Print2()" << endl;
        child->Print2();

        cout << "\n...child->Print3()" << endl;
        child->Print3();
    }


    Child* new_child = static_cast<Child*>(child);

    {
        PrintInYellow("\n-> new_child ptr calls");
        cout << "\n...child->Print2()" << endl;
        child->Print2();
        cout << "\n...new_child->Print2()" << endl;
        new_child->Print2();

        new_child->PrintConst();
    }

    PrintInYellow("\n-> About to delete allocations\n");
    delete parent;
    delete child;

    return 0;
}
