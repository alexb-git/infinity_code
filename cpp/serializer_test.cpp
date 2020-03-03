/****************************************************************************
** Filename:    - serializer_test.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - design pattern - serializer testing
** Date:        - 26/2/2018
** Version:     - 1
*****************************************************************************/
#include <memory>   /* auto_ptr */
#include <iostream> /* cout, endl */
#include <sstream>  /* stringstream */

#include "serializer.hpp"   /* serializer */
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

template <typename T>
inline void PrintMes(const char* color, const char* message, T var)
{
    std::cout << color << message << " " << RES << var << std::endl;
}

/*==========================  Animal class  ==========================*/
class Animal
{
public:
    explicit Animal(double val = 6.66) : m_weight(val) {
        PrintMes<double>(BLD BLU, "Animal Ctor ", m_weight);
    }

    virtual ~Animal() {
        PrintMes<double>(BLD RED, "Animal Dtor ", m_weight);
    }

    virtual void MakeSound() {
        PrintMes<double>(YEL, "I am an animal ", m_weight);
    }

    virtual void ToStream(std::ostream& os) const {
        os << m_weight;
        os << ' ';
    }

    virtual void FromStream(std::istream& is) {
        is >> m_weight;
    }

protected:
    double m_weight;
};

using std::string;
/*=====================  class Dog : public Animal  ====================*/
class Dog : public Animal
{
public:
    explicit Dog(double weight = 8.88 , string name = "default") :
                                                        Animal(weight),
                                                        m_name(name)
    {
        PrintMes<string>(BLU, "Dog Ctor ", m_name);
    }

    virtual ~Dog() {
        PrintMes<string>(RED, "Dog Dtor ", m_name);
    }

    virtual void ToStream(std::ostream& os) const {

        Animal::ToStream(os);
        os << m_name;
        os << ' ';
    }

    virtual void FromStream(std::istream& is) {

        Animal::FromStream(is);
        is >> m_name;
    }

    virtual void MakeSound() {
        PrintMes<string>(YEL, "wuf wuf... my name is: ", m_name);
        PrintMes<double>(YEL, "I weigh:  ", m_weight);
    }


private:
    string m_name;
};

/*=======================  global stream function  =======================*/
std::istream& operator>>(std::istream& is, Animal& animal)
{
    animal.FromStream(is);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Animal& animal)
{
    animal.ToStream(os);

    return os;
}

/*============================  THE MAIN  ==============================*/
int main(int argc, char const *argv[])
{
    ilrd::Serializer<Animal> ser;
    std::stringstream my_stream;

    ser.Add<Animal>();
    ser.Add<Dog>();

    PrintInYellow("\n-> (Base) The creating object on the stack:\n");
    Animal a(1.11);
    ser.Serialize(a, my_stream);

    PrintInYellow("\n-> (Base) The recreation of Deserialize:\n");
    std::auto_ptr<Animal> an1(ser.Deserialize(my_stream));

    PrintInYellow("\n-> (Base) The creating object on the stack:\n");
    an1->MakeSound();


    /* code / modulate */
    PrintInYellow("\n\n\n-> (Derived) The creating object on the stack:\n");
    Dog d(2.22, "Alex");

    ser.Serialize(d, my_stream);

    /* de-code / de-modulate */
    PrintInYellow("\n-> (Derived) The recreation of Deserialize:\n");
    std::auto_ptr<Animal> an2(ser.Deserialize(my_stream));

    PrintInYellow("\n-> (Derived) Recreated object MakeSound:\n");
    an2->MakeSound();

    std::cout << "\n" << std::endl;
    return 0;
}
