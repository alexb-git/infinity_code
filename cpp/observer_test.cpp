/****************************************************************************
** Filename:    - observer_test.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - design pattern - observer testing
** Date:        - 26/2/2018
** Version:     - 1
*****************************************************************************/
#include <iostream> /* count, cin */
#include <string>   /* string */

#include "observer.hpp"    /* observer dp */
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

/****************************************************************************
    Helpful defines and inline functions
*****************************************************************************/
inline void PrintHeader(const char *str)
{
    std::cout << BLU BLD "\n\t------------  This is a test for: "
              << str << " ------------\n" RES << std::endl;
}

inline void PrintInYellow(const char *str) { std::cout << YLL << str << RES;}
inline void PrintOK()  { std::cout << GRE "-OK" RES; }
inline void PrintERR() { std::cout << RED "-ERR" RES; }

#define Alighl(X)         ( std::left << setw(X) )
#define PrintOKorERR(X)   ( (X)?(PrintOK()):(PrintERR()) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )
/****************************************************************************/
using std::string;
using namespace ilrd;

template <typename T>
inline void PrintMes(const char* color, const char* message, T var)
{
    std::cout << color << message << " " << RES << var << std::endl;
}

class Subscriber
{
public:
    /*****************************************************************
        Ctor and Dtor
    ******************************************************************/
    Subscriber(const string &name) : m_name(name),
                                     m_notifier(  this                ,
                                                 &Subscriber::Notify  ,
                                                 &Subscriber::DisDead )
    {
        PrintMes<string>(BLD BLU, "Subscriber ctor", m_name);
    }

    ~Subscriber ()
    {
        PrintMes<string>(BLD RED, "Subscriber dtor", m_name);
    }

    /*****************************************************************
        function to support communication with dispacher
    ******************************************************************/
    void Notify(const string &message)
    {
        PrintMes<string>(CYA, "\nNotify Subscriber ", m_name);
            PrintMes<string>(WHI ,"\t", message);
    }

    void DisDead()
    {
        PrintMes<string>(CYA, "\nSubscriber DisDead", m_name);
    }

    CallBack<string, Subscriber>* GetCommunicator()
    {
        return &m_notifier;
    }


private:
    string m_name;

    CallBack<string, Subscriber> m_notifier;
};

void TestOnlyDespacher()
{
    Dispatcher<int> local;
}

void TestOnlyObserver()
{
    Subscriber local("Only one");
}

/*=============================  THE MAIN  =============================*/
int main(int argc, char const *argv[])
{
    PrintInYellow("\n-> \"Test Only Despacher\",  \"Test Only Observer\"\n");
    TestOnlyDespacher();
    TestOnlyObserver();

    PrintInYellow("\n-> Create First on stack\n");
    Subscriber s1("First");  /* should get all messages,
                                the only one that gets the DisDead message */

    PrintInYellow("\n-> Create Dispatcher\n");
    Dispatcher<string> YouTube;

    PrintInYellow("\n-> Create Second on stack and Third on heap\n");
    Subscriber s2("Second"); /* should get all messages */
    Subscriber *s3 = new Subscriber("Third");

    YouTube.Subscribe(s1.GetCommunicator());
    YouTube.Subscribe(s2.GetCommunicator());
    YouTube.Subscribe(s3->GetCommunicator());

    PrintInYellow("\n-> NotifyAll(\"Fist Message\")");
    YouTube.NotifyAll("Fist Message");

    PrintInYellow("\n-> delete Third. create Forth and Subscribe him\n");
    delete s3;              /* should not get the second message */
    Subscriber s4("Forth"); /* should not get the first  message */
    YouTube.Subscribe(s4.GetCommunicator());

    PrintInYellow("\n-> NotifyAll(\"Second Message\")");
    YouTube.NotifyAll("Second Message");

    PrintInYellow("\n-> end of program. destroy objects from the stack\n");
    return 0;
}
