/****************************************************************************
** Filename:    - cpp2c.cpp
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - translate c++ to c
** Date:        - 23/1/2018
** Version:     - 6
*****************************************************************************/
#include <iostream>

using namespace std;

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
	Animal(): m_id(++s_count)
	{
		cout << BLD BLU "Animal::Ctor() " << m_id << RES << endl;
	}

    Animal(const Animal &other) : m_id(++s_count)
    {
        cout << BLD BLU "Animal::CCtor() "  << m_id << RES << endl;
    }

	virtual ~Animal()
    {
        --s_count;
        cout << BLD RED "Animal::Dtor() "  << m_id  << RES << endl;
    }

	virtual void Display()
	{
		cout << YEL "Animal::Display() : " << m_id << RES << endl;
	}

	static void PrintCount()
    {
        cout << YEL "s_count: " << s_count << RES << endl;
    }

protected:
	int GetID() { return m_id; }

private:
	static int s_count;
	int m_id;
	Animal &operator=(const Animal &); // disabled
};

int Animal::s_count = 0;

/****************************************************************************/
class Centipede: public Animal
{
public:
	Centipede() : m_numLegs(46)
	{
		cout << BLU "Centipede::Ctor()" << RES << endl;
	}

	Centipede(const Centipede &other ) : Animal(other),
	                                     m_numLegs(other.m_numLegs)
	{
		cout << BLU "Centipede::CCtor()" << RES << endl;
	}

	~Centipede()
    {
        cout << RED "Centipede::Dtor()" << RES << endl;
    }

	void Display()
    {
        cout << YEL "Centipede::Display() ID: "<< GetID()
        <<"  num legs: " << m_numLegs
        << RES << endl;
    }

	virtual void BuyShues()
    {
        cout << YEL "Centipede::BuyShues() ID: " << GetID()
        << RES << endl;
    }

private:
	int m_numLegs;
};

/****************************************************************************/
class Squirl: public Animal
{
public:
	Squirl()
    {
        cout << BLU "Squirl::Ctor()" << RES << endl;
    }

	Squirl(const Squirl &other ): Animal(other)
    {
        cout << BLU "Squirl::CCtor()" << RES << endl;
    }

	~Squirl()
    {
        cout << RED "Squirl::Dtor()" << RES << endl;
    }

	void Display()
    {
        cout << YEL "Squirl::Display() ID: "<< GetID()
        << RES << endl;
    }

private:
};

/****************************************************************************/
class FlyingSquirl : public Squirl
{
public:
	FlyingSquirl()
    {
        cout << CYA "FlyingSquirl::Ctor()" << RES << endl;
    }

	FlyingSquirl(const FlyingSquirl &other): Squirl(other)
    {
        cout << CYA "FlyingSquirl::CCtor()" << RES << endl;
    }

	~FlyingSquirl()
    {
        cout << RED "FlyingSquirl::Dtor()" << RES << endl;
    }

	void Display()
    {
        cout << YEL "FlyingSquirl::Display() ID: " << GetID() << RES <<endl;
    }

private:
};

/****************************************************************************/
class LegendaryAnimal: public Animal
{
public:
    LegendaryAnimal() : m_a1(new Centipede()),
    		            m_a2(new Squirl())
    {}

    LegendaryAnimal(const LegendaryAnimal &other) :
            m_a1( new Centipede( *dynamic_cast<Centipede*>(other.m_a1) ) ),
            m_a2( new Squirl   ( *dynamic_cast<Squirl*>   (other.m_a2) ) ),
            m_c ( other.m_c ),
            m_sq( other.m_sq )
    {}

    ~LegendaryAnimal()
    {
        delete m_a1;
        delete m_a2;
    }

    void Display()
    {
        m_a1->Display();
        m_a2->Display();
        m_c.Display();
        m_sq.Display();
    }

private:
    Animal    *m_a1;
    Animal    *m_a2;
    Centipede  m_c;
    Squirl     m_sq;
};


/*****************************************************/
void Foo(Animal &a)
{
    a.Display();
}

/****************************************************/
void Foo()
{
    Animal::PrintCount();
}

/****************************************************/
Animal Foo(int i)
{
	Centipede ret;

	cout<<"Foo(int i)"<<endl;
	ret.Display();

	return ret;
}

/****************************************************/
void FiFi(Squirl s)
{
    s.Display();
}


/****************************************************************************/
int main(int argc, char **argv, char **envp)
{
	Centipede c;
	Foo(c);
	Foo(3).Display();

	Animal *array[] =  { new Centipede(), new Squirl(), new Centipede() };

	for( int i = 0 ; i < 3 ; ++i ) {
        array[i]->Display();
    }

	for( int i = 0 ; i < 3 ; ++i ) {
        delete array[i];
    }

	Animal arr2[] ={ Centipede(), Squirl(), Animal() };

	for( int i = 0 ; i < 3 ; ++i ) {
		arr2[i].Display();
	}

	Animal::PrintCount();
	Centipede c2;
	c2.PrintCount();

	Centipede arr3[4];
	Squirl *arr4 = new Squirl[4];
	delete [] arr4;

    std::cout << std::endl;

	FlyingSquirl fs;
	FiFi(fs);

	LegendaryAnimal *la1 = new LegendaryAnimal();
	LegendaryAnimal *la2 = new LegendaryAnimal(*la1);
	la1->Display();
	la2->Display();
	delete la1;
	la2->Display(); // this crashes. fix the bug!
	delete la2;

	return 0;
}
