/****************************************************************************
** Filename:    - cpp2c.c
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - translate c++ to c
** Date:        - 23/1/2018
** Version:     - 4
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

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

#define SizeArr(X) ( sizeof(X)/sizeof(X[0]) )

/*=============  Defines for this program  ===============*/
#define Dtor    (0)
#define Display (1)


/****************************************************************************
                ==========  Class Animal  ==========
*****************************************************************************/
typedef struct Animal Animal_t;
void AnimalCtor   (Animal_t *this_);
void AnimalDtor   (Animal_t *this_);
void AnimalCCtor  (Animal_t *this_, const Animal_t *other);
void AnimalDisplay(Animal_t *this_);
int  AnimalGetID  (Animal_t *this_);
void AnimalPrintCount();

typedef void (*AnimalVT_t)(Animal_t*);
AnimalVT_t Animal_vt[2] = { AnimalDtor      ,
                            AnimalDisplay   };

/****************************************************************************
        ==========  class Centipede: public Animal  ==========
*****************************************************************************/
typedef struct Centipede Centipede_t;
void CentipedeCtor    (Centipede_t *this_);
void CentipedeCCtor   (Centipede_t *this_, const Centipede_t *other);
void CentipedeDtor    (Centipede_t *this_);
void CentipedeDisplay (Centipede_t *this_);
void CentipedeBuyShues(Centipede_t *this_);

typedef void (*CentipedeVT_t)(Centipede_t*);
CentipedeVT_t Centipede_vt[3] = { CentipedeDtor     ,
                                  CentipedeDisplay  ,
                                  CentipedeBuyShues };

/****************************************************************************
        ==========  class Squirl: public Animal  ==========
*****************************************************************************/
typedef struct Squirl Squirl_t;
void SquirlCtor   (Squirl_t *this_);
void SquirlCCtor  (Squirl_t *this_, Squirl_t *other);
void SquirlDtor   (Squirl_t *this_);
void SquirlDisplay(Squirl_t *this_);

typedef void (*SquirlVT_t)(Squirl_t*);
SquirlVT_t Squirl_vt[2] = { SquirlDtor      ,
                            SquirlDisplay   };


/****************************************************************************
                ==========  Class Animal  ==========
*****************************************************************************/
static int Animal_s_count = 0;
struct Animal
{
    void *v_table;
    int   m_id;
};

void AnimalCtor(Animal_t *this_)
{
    this_->m_id =  ++Animal_s_count;
    this_->v_table = Animal_vt;
    printf(BLD BLU "Animal::Ctor() %d\n" RES, this_->m_id);
}

void AnimalCCtor(Animal_t *this_, const Animal_t *other)
{
    this_->v_table = Animal_vt;
    this_->m_id =  ++Animal_s_count;
    printf(BLD BLU "Animal::CCtor() %d\n" RES, this_->m_id);
}

void AnimalDtor(Animal_t *this_)
{
    --Animal_s_count;
    printf(BLD RED "Animal::Dtor() %d\n" RES, this_->m_id);
}

void AnimalDisplay(Animal_t *this_)
{
    printf(YEL "Animal::Display() %d\n" RES, this_->m_id);
}

void AnimalPrintCount()
{
    printf(YEL "s_count: %d\n" RES, Animal_s_count);
}

int AnimalGetID(Animal_t *this_)
{
    return this_->m_id;
}


/****************************************************************************
        ==========  class Centipede: public Animal  ==========
*****************************************************************************/
struct Centipede
{
    Animal_t animal;
    int      m_numLegs;
};

void CentipedeCtor(Centipede_t *this_)
{
    AnimalCtor((Animal_t*)this_);
    this_->animal.v_table = Centipede_vt;
    this_->m_numLegs =  46;
    printf(CYA "Centipede::Ctor()\n" RES);
}

void CentipedeCCtor(Centipede_t *this_, const Centipede_t *other)
{
    AnimalCCtor((Animal_t*)this_, (Animal_t*)other);

    this_->animal.v_table = Centipede_vt;
    this_->m_numLegs = other->m_numLegs;

    printf(CYA "Centipede::CCtor()\n" RES);
}

void CentipedeDtor(Centipede_t *this_)
{
    printf(RED "Centipede::Dtor()\n" RES);

    this_->animal.v_table = Animal_vt;
    AnimalDtor((Animal_t*)this_);
}

void CentipedeDisplay(Centipede_t *this_)
{
    printf(YEL "Centipede::Display() ID: %d | num legs: %d\n" RES,
            AnimalGetID((Animal_t*)this_), this_->m_numLegs);
}

void CentipedeBuyShues(Centipede_t *this_)
{
    printf(YEL "Centipede::BuyShues() ID: %d\n" RES,
            AnimalGetID((Animal_t*)this_));
}

/****************************************************************************
        ==========  class Squirl: public Animal  ==========
*****************************************************************************/
struct Squirl
{
    Animal_t animal;
};

void SquirlCtor(Squirl_t *this_)
{
    AnimalCtor((Animal_t*)this_);
    this_->animal.v_table = Squirl_vt;
    printf(CYA "Squirl::Ctor()\n" RES);
}

void SquirlCCtor(Squirl_t *this_, Squirl_t *other)
{
    AnimalCCtor((Animal_t*)this_, (Animal_t*)other);
    this_->animal.v_table = Squirl_vt;

    printf(CYA "Squirl::CCtor()\n" RES);
}

void SquirlDtor(Squirl_t *this_)
{
    printf(RED "Squirl::Dtor()\n" RES);

    this_->animal.v_table = Animal_vt;
    AnimalDtor((Animal_t*)this_);
}

void SquirlDisplay(Squirl_t *this_)
{
    printf( YEL "Squirl::Display() ID: %d\n" RES,
            AnimalGetID((Animal_t*)this_));
}



/****************************************************************************
        ==========  Functions  ==========
*****************************************************************************/
void Foo_Display(Animal_t *this_)
{
    /*a.Display();*/
    AnimalVT_t* func = (AnimalVT_t*)this_->v_table;
    func[Display](this_);
}

void Foo_Count()
{
    /*Animal::PrintCount();*/
    AnimalPrintCount();
}

void Foo_Int(int i, Animal_t *re_animal)
{
	Centipede_t ret;
    CentipedeCtor(&ret);

    printf("Foo(int i)\n");

    /*ret.Display();*/
    CentipedeDisplay(&ret);

    /* return ret; */
    AnimalCCtor(re_animal, &ret.animal);
    CentipedeDtor(&ret);
}


void FiFi(Squirl_t *squirl)
{
    SquirlDisplay(squirl);
}

/****************************************************************************
        ==========  The MAIN  ==========
*****************************************************************************/
int main(int argc, char const *argv[])
{
    int i;

    /* c++ Centipede c; */
    Centipede_t c;
    CentipedeCtor(&c);

    /*Foo(c);*/
    Foo_Display( (Animal_t*) &c);

    /*Foo(3).Display();*/
    Animal_t re_animal;
    Foo_Int(3, &re_animal);
    AnimalDisplay(&re_animal);
    AnimalDtor(&re_animal);

    /*Animal *array[] = { new Centipede(), new Squirl(), new Centipede() };*/
    Animal_t *array[3];

    {
        array[0] = (Animal_t*) malloc( sizeof(Centipede_t) );
        CentipedeCtor( (Centipede_t*) array[0]);

        array[1] = (Animal_t*) malloc( sizeof(Squirl_t) );
        SquirlCtor( (Squirl_t*) array[1]);

        array[2] = (Animal_t*) malloc( sizeof(Centipede_t) );
        CentipedeCtor( (Centipede_t*) array[2]);
    }

    /* for loop array[i]->Display() */
    AnimalVT_t* func;
    for ( i = 0 ; i < 3 ; ++i )
    {
        func = (AnimalVT_t*)array[i]->v_table;
        func[Display](array[i]);
    }

    /* for loop  "delete array[i];" */
    for ( i = 0 ; i < 3 ; ++i )
    {
        func = (AnimalVT_t*)array[i]->v_table;
        func[Dtor](array[i]);

        free(array[i]);
        array[i] = NULL;
    }

    /*Animal arr2[] ={ Centipede(), Squirl(), Animal() };*/
    Animal_t arr2[3];

    {
        /* create Centipede */
        Centipede_t cen;
        CentipedeCtor(&cen);

        /*  slice Animal out of Centipede,
            copy construct animal into the arr2 */
        AnimalCCtor(&arr2[0], &cen.animal);
        CentipedeDtor(&cen);


        /* create Squirl */
        Squirl_t squ;
        SquirlCtor(&squ);

        /*  slice Animal out of Squirl
            copy construct animal into the arr2 */
        AnimalCCtor(&arr2[1], &squ.animal);
        SquirlDtor(&squ);


        /* construct animal into the arr2 */
        AnimalCtor(&arr2[2]);
    }

    /* for loop array[i]->Display() */
    for ( i = 0 ; i < 3 ; ++i )
    {
        AnimalDisplay(arr2 + i);
    }

    AnimalPrintCount(); /* Animal::PrintCount(); */
    Centipede_t c2;     /* Centipede c2; */
    CentipedeCtor(&c2);
    AnimalPrintCount(); /* c2.PrintCount(); */

    /* Centipede arr3[4]; */
    Centipede_t arr3[4];
    for ( i = 0 ; i < (int)SizeArr(arr3) ; ++i )
    {
        CentipedeCtor(arr3 + i);
    }


    /* Squirl *arr4 = new Squirl[4] */
    Squirl_t *arr4;
    arr4 = (Squirl_t*) malloc( 4 * sizeof(Squirl_t) );
    for ( i = 0 ; i < 4 ; ++i )
    {
        SquirlCtor(arr4 + i);
    }

    /* for loop  "delete [] arr4;" */
    for ( i = 3 ; i >= 0 ; --i )
    {
        func = (AnimalVT_t*) (arr4 + i)->animal.v_table;
        func[Dtor]( &(arr4 + i)->animal );
    }
    free(arr4);
    arr4 = NULL;

    /* call dtor on arr3 */
    for ( i = (int)SizeArr(arr3) - 1 ; i >= 0 ; --i )
    {
        CentipedeDtor(arr3 + i);
    }

    /* call dtor on c2 */
    CentipedeDtor(&c2);

    /* call dtor on arr2 */
    for ( i = 2 ; i >= 0 ; --i )
    {
        AnimalDtor(arr2 + i);
    }

    /* call dtor on c */
    CentipedeDtor(&c);
    return 0;
}
