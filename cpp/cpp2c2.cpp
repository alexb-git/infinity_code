/****************************************************************************
** Filename:    - cpp2c2.cpp
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - translate c++ to c
** Date:        - 30/1/2018
** Version:     - 1
*****************************************************************************/
#include <iostream>
using namespace std;

/****************************************************************************
    Helpful colors
*****************************************************************************/
#define  YLL  "\x1b[93m"
#define  GRE  "\x1b[92m"
#define  RED  "\x1b[91m"
#define  WHI  "\x1B[37m"
#define  CYA  "\x1B[36m"
#define  BLU  "\x1B[34m"
#define  YEL  "\x1b[33m"
#define  RES  "\x1b[0m"
#define  BLD  "\x1B[1m"
#define  UDL  "\x1b[4m"

/*==========================  Public_Transport  ==========================*/
class Public_Transport
{
public:
	Public_Transport() :
                        m_license_plate(++s_count)
	{
		cout << BLD BLU "Public_Transport::Ctor() " << m_license_plate
        << RES << endl;
	}

    Public_Transport(const Public_Transport &other) :
                                            m_license_plate(++s_count)
    {
        cout << BLD BLU "Public_Transport::CCtor() " << m_license_plate
        << RES << endl;
    }

	virtual ~Public_Transport()
	{
		--s_count;
		cout << BLD RED "Public_Transport::Dtor() " << m_license_plate
        << RES << endl;
	}

	virtual void Display()
	{
		cout << BLD YEL "Public_Transport::Display() " << m_license_plate
        << RES << endl;
	}

	static void PrintCount()
    {
        cout << BLD YEL "s_count: " << s_count << endl;
    }

protected:
	int GetID()
    {
        return m_license_plate;
    }

private:
    Public_Transport &operator=(const Public_Transport &); // disabled

	static int s_count;
	int        m_license_plate;
};

int Public_Transport::s_count = 0;


/*===============  class Minibus: public Public_Transport  ==================*/
class Minibus: public Public_Transport
{
public:
	Minibus():
            m_numSeats(20)
	{
		cout << BLU "Minibus::Ctor()" << RES << endl;
	}

	Minibus(const Minibus &other ):
                                Public_Transport(other),
                            	m_numSeats(other.m_numSeats)
	{
		cout << BLU "Minibus::CCtor()" << RES << endl;
	}

   virtual ~Minibus()
   {
       cout << RED "Minibus::Dtor()" << RES << endl;
   }

	virtual void Display()
	{
		cout << YEL "Minibus::Display() ID: "<< GetID();
		cout << " num seats: " << m_numSeats << RES << endl;
	}

	virtual void Wash()
    {
        cout << YEL "Minibus::Wash() ID: " << GetID() << RES << endl;
    }

private:
	int m_numSeats;
};


/*===============  class Minibus: public Public_Transport  ==================*/
class Taxi: public Public_Transport
{
public:
	Taxi()
    {
        cout << BLU "Taxi::Ctor()" << RES << endl;
    }

	Taxi(const Taxi &other ) :
                            Public_Transport(other)
    {
        cout << BLU "Taxi::CCtor()" << RES << endl;
    }

    virtual ~Taxi()
    {
       cout << RED "Taxi::Dtor()" << RES << endl;
    }

	virtual void Display()
    {
        cout << YEL "Taxi::Display() ID: " << GetID() << RES << endl;
    }


private:
};


/*===================  class Special_Taxi : public Taxi  ====================*/
class Special_Taxi : public Taxi
{
public:
    Special_Taxi()
    {
        cout << CYA "Special_Taxi::Ctor()" << RES << endl;
    }

    Special_Taxi(const Special_Taxi &other) :
                                            Taxi(other)
    {
    	cout << CYA "Special_Taxi::CCtor()" << RES << endl;
    }

    virtual ~Special_Taxi()
    {
       cout << RED "Special_Taxi::Dtor()" << RES << endl;
    }

    virtual void Display()
    {
        cout << YEL "Special_Taxi::Display() ID: " << GetID() << RES <<endl;
    }

private:
};


/*============  class Public_Convoy: public Public_Transport  ===============*/
class Public_Convoy: public Public_Transport
{
public:
    Public_Convoy() :
                    m_pt1(new Minibus()),
                    m_pt2(new Taxi())
    {}

    Public_Convoy(const Public_Convoy &other) :
            m_pt1( new Minibus( *static_cast<Minibus*>(other.m_pt1) ) ),
            m_pt2( new Taxi   ( *static_cast<Taxi*>   (other.m_pt2) ) ),
            m_m( other.m_m ),
            m_t( other.m_t )
    {}

    virtual ~Public_Convoy()
    {
    	delete m_pt1;
    	delete m_pt2;
    }

    virtual void Display()
    {
    	m_pt1->Display();
    	m_pt2->Display();
    	m_m.Display();
    	m_t.Display();
    }

private:
    Public_Transport  *m_pt1;
    Public_Transport  *m_pt2;
    Minibus            m_m;
    Taxi               m_t;
};


/*=============================  FUNCTIONS  ================================*/
template<class T>
inline T maxFunc(const T &t1, const T &t2)
{
    return ((t1 > t2)? t1: t2);
}

void PrintInfo(Public_Transport &a)
{
    a.Display();
}

void PrintInfo()
{
    Public_Transport::PrintCount();
}

Public_Transport PrintInfo(int i)
{
	Minibus ret;
	cout << "PrintInfo(int i)" << endl;
	ret.Display();
	return ret;
}

void TaxiDisplay(Taxi s)
{
    s.Display();
}


/*==========================  THE MAIN  ==========================*/
int main(int argc, char **argv, char **envp)
{
	Minibus m;
	PrintInfo(m);
	PrintInfo(3).Display();

	Public_Transport *array[] =
	{
		new Minibus(),
		new Taxi(),
		new Minibus()
	};

	for(int i = 0; i < 3; ++i)
    {
        array[i]->Display();
    }

	for(int i = 0; i < 3; ++i)
    {
        delete array[i];
    }


	Public_Transport arr2[] =
	{
		Minibus(),
		Taxi(),
		Public_Transport()
	};

	for(int i = 0; i < 3; ++i)
	{
		arr2[i].Display();
	}

	Public_Transport::PrintCount();
	Minibus m2;
	m2.PrintCount();

	Minibus arr3[4];
	Taxi *arr4 = new Taxi[4];
	delete [] arr4;

	// std::cout << maxFunc<int>(1,2) << std::endl;
	Special_Taxi st;
	TaxiDisplay(st);


	Public_Convoy *ts1 = new Public_Convoy();
	Public_Convoy *ts2 = new Public_Convoy(*ts1);
	ts1->Display();
	ts2->Display();
	delete ts1;
	ts2->Display(); // this crashes. fix the bug!
	delete ts2;

	return 0;
}
