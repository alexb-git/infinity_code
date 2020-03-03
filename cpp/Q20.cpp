/****************************************************************************
** Filename:    - cppworksheet.c
** Code Author: - Eyal Barak / Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - inroduction to c++ (1st worksheet)
** Date:        - 1/1/2018
** Version:     - 1
*****************************************************************************/
/* Purpose: 	q20 in C++ worksheet */

#include <iostream>  		/* printf */
#include <iomanip>

/****************************************************************************
    Helpful colors
*****************************************************************************/
#define CBALL	 "\x1b[93m"
#define GRE	 "\x1b[92m"
#define RED	 "\x1b[91m"
#define WHI	 "\x1B[37m"
#define CCBAA	 "\x1B[36m"
#define BLU	 "\x1B[34m"
#define CBAEL	 "\x1b[33m"
#define RES	 "\x1b[0m"
#define BLD  "\x1B[1m"
#define UDL  "\x1b[4m"
/****************************************************************************/

struct ABC
{
	// explicit ABC();                      /* default constructor */
	explicit ABC(int a_, int b_=8);      /* regular constructor */
	~ABC();                              /* destructor */

	ABC(const ABC &other_);                /* copy constructor */
	ABC& operator = (const ABC &other_);   /* '=' operator */

    ABC& operator++ ();                   /* '++' operator */

	int m_a;                           /* struct variable */
	int m_b;                           /* struct variable */

private:

    int id;
    static size_t num_of_obj;

    void print_data(const char *str, int &m_a, int &m_b,
                    size_t &num_of_obj, int &id)
    {
        std::cout << "this: " << std::left << std::setw(14) << this
        << std::left << std::setw(31) << str
        << "| m_a: "<< std::left << std::setw(4) << m_a
        << " m_b: " << std::left << std::setw(4) << m_b
        << " | id " << std::left << std::setw(2) << id
        << " | num_of_obj " << num_of_obj
        << std::endl;
    }

};

size_t ABC::num_of_obj = 0;

/*==========================  default constructor  ==========================*/
// ABC::ABC() : m_a(3), m_b(4)
// {
//     ++num_of_obj;
//     id = num_of_obj;
//
//     print_data(" | ABC default constructor ", m_a, m_b, num_of_obj, id);
// }

/*==========================  regular constructor  ==========================*/
ABC::ABC(int a_, int b_): m_b(b_)
{
    m_a = a_;

    ++num_of_obj;
    id = num_of_obj;

    print_data(" | ABC (int,int) constructor ", m_a, m_b, num_of_obj, id);
}

/*==========================  copy constructor  ==========================*/
ABC::ABC(const ABC&other_) : m_a(other_.m_a), m_b(other_.m_b)
{
    ++num_of_obj;
    id = num_of_obj;

    print_data(" | ABC copy constructor ", m_a, m_b, num_of_obj, id);
}

/*==========================  '=' operator  ==========================*/
ABC& ABC::operator = (const ABC& other_)
{
	m_a = other_.m_a;
	m_b = other_.m_b;

    print_data(" | ABC assignment operator ", m_a, m_b, num_of_obj, id);

	return *this;
}

/*========================  '++' prefic operator  ========================*/
ABC& ABC::operator++ ()
{
    this->m_a = 666;
    this->m_b = 666;

    print_data(" | ABC::operator++ ", m_a, m_b, num_of_obj, id);

    return *this;
}

/*==========================  destructor  ==========================*/
ABC::~ABC()
{
    --num_of_obj;
    print_data(" | ABC f#@k you i'm invincible ", m_a, m_b, num_of_obj, id);
}


void foo(int * & var)
{
    std::cout << var << std::endl;;
}

/*==========================  STRUCT CBA  ==========================*/
struct CBA
{
    ABC m_x;
    int m_i;
};

/*==========================  THE MAIN  ==========================*/
int main()
{
	// ABC x1;                /* expecting "m_a 3   m_b 4"  */
	ABC x2(15);            /* expecting "m_a 15  m_b 8"  */
	ABC* px = new ABC(x2); /* expecting "m_a 15  m_b 8"  */
	ABC x3(36,63);         /* expecting "m_a 36  m_b 69" */
	// ABC x4(x1);            /* expecting "m_a 3   m_b 4"  */

	// x1 = x3;           /* expecting "m_a 36  m_b 63"  */
    // ++x1;

    // ABC *xp = new ABC[10];
    // delete[] xp;

    // std::cout << "about to create CBA objects" << std::endl;
    // CBA y1;
    // y1.m_x.m_a = 250;
    // y1.m_x.m_b = 750;
    //
    // CBA y2(y1);
    // CBA y3;
    // y3 = y1;

    std::cout << "sizeof(x3) " << sizeof(x3) << std::endl;
    // std::cout << "sizeof(y1) " << sizeof(y1) << std::endl;

    delete px;         /* expecting "m_a 15  m_b 8"   */
    px=0;              /* - */

	return 0;
}
