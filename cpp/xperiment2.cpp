#include <iostream>
using namespace std;

/*=====================  Base class  ======================*/
class Base
{
public:
	Base(int i) :
                    m_i(i),
                    m_iptr(&m_i)
    {
        std::cout << "Base ctor" << std::endl;
    }

	virtual void foo()
    {
        cout << *(m_iptr) << endl;
    }

	virtual void bar()
    {
        cout << m_i << endl;
    }


protected:
	virtual  ~Base() = 0;

private:
	int   m_i;
	int  *m_iptr;
};

inline Base::~Base() {}

/*=====================  Derived class  ======================*/
class Derived : public Base
{
public:
    Derived(const Derived &other) : Base(other),
                                    m_c(other.m_c),
                                    m_c2(other.m_c2)
    {}

	Derived(int i, char c):
                            Base(i),
                            m_c(c),
                            m_c2(c)
    {}
	void bar()
    {
        foo();
        Base::foo();
    }


private:
	void foo()
    {
        cout << m_c << endl;
    }

	char m_c, m_c2;
};

/*=====================  OtherDerived class  ======================*/
class OtherDerived: public Base
{
public:
    OtherDerived(const OtherDerived &other) : Base(other)
    {}

    OtherDerived(int x): Base(x)
    {}

    OtherDerived& operator=(const OtherDerived &other)
    {
        this->Base::operator=(other);

        return *this;
    }
};

/*==========================  THE MAIN  ==========================*/
int main(int argc, char const *argv[])
{
    Derived d1(5, 'X');
    Derived d2(3, 'W');

    // OtherDerived z1(111);
    // OtherDerived z2(z1);
    // z1.foo();
    // z2.foo();

    // Derived d3(d2);
    // d3.bar();


    Base *b1 = &d1;
    b1->foo();
    b1->bar();

    Base *b2 = &d2;
    *b2 = *b1;
    b2->foo();
    d2.bar();

    return 0;
}
