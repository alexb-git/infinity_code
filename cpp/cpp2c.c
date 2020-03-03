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
static int Animal_s_count = 0;

/*==========  Class Animal Methodes Declarations  ==============*/
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
/*========== end of Class Animal Methodes Declarations  =======*/

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

/*=============  Class Centipede Methodes Declarations  ==========*/
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
/*========== end of Class Centipede Methodes Declarations  =======*/

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
    printf(BLU "Centipede::Ctor()\n" RES);
}

void CentipedeCCtor(Centipede_t *this_, const Centipede_t *other)
{
    AnimalCCtor((Animal_t*)this_, (Animal_t*)other);

    this_->animal.v_table = Centipede_vt;
    this_->m_numLegs = other->m_numLegs;

    printf(BLU "Centipede::CCtor()\n" RES);
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

/*========== end of Class Squirl Methodes Declarations  ========*/
typedef struct Squirl Squirl_t;
void SquirlCtor   (Squirl_t *this_);
void SquirlCCtor  (Squirl_t *this_, Squirl_t *other);
void SquirlDtor   (Squirl_t *this_);
void SquirlDisplay(Squirl_t *this_);

typedef void (*SquirlVT_t)(Squirl_t*);
SquirlVT_t Squirl_vt[2] = { SquirlDtor      ,
                            SquirlDisplay   };
/*========== end of Class Squirl Methodes Declarations  =======*/

struct Squirl
{
    Animal_t animal;
};

void SquirlCtor(Squirl_t *this_)
{
    AnimalCtor((Animal_t*)this_);
    this_->animal.v_table = Squirl_vt;
    printf(BLU "Squirl::Ctor()\n" RES);
}

void SquirlCCtor(Squirl_t *this_, Squirl_t *other)
{
    AnimalCCtor((Animal_t*)this_, (Animal_t*)other);
    this_->animal.v_table = Squirl_vt;

    printf(BLU "Squirl::CCtor()\n" RES);
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
        ==========  class FlyingSquirl : public Squirl  ==========
*****************************************************************************/

/*========== end of Class FlyingSquirl Methodes Declarations  =======*/
typedef struct FlyingSquirl FlyingSquirl_t;
void FlyingSquirlCtor   (FlyingSquirl_t *this_);
void FlyingSquirlCCtor  (FlyingSquirl_t *this_, FlyingSquirl_t *other);
void FlyingSquirlDtor   (FlyingSquirl_t *this_);
void FlyingSquirlDisplay(FlyingSquirl_t *this_);

typedef void (*FlyingSquirlVT_t)(FlyingSquirl_t*);
FlyingSquirlVT_t FlyingSquirl_vt[2] = { FlyingSquirlDtor      ,
                                        FlyingSquirlDisplay   };
/*========== end of Class FlyingSquirl Methodes Declarations  =======*/


struct FlyingSquirl
{
    Squirl_t squirl;
};

void FlyingSquirlCtor(FlyingSquirl_t *this_)
{
    SquirlCtor((Squirl_t*)this_);
    this_->squirl.animal.v_table = FlyingSquirl_vt;
    printf(CYA "FlyingSquirl::Ctor()\n" RES);
}

void FlyingSquirlCCtor(FlyingSquirl_t *this_, FlyingSquirl_t *other)
{
    SquirlCCtor((Squirl_t*)this_, (Squirl_t*)other);
    this_->squirl.animal.v_table = FlyingSquirl_vt;

    printf(CYA "FlyingSquirl::CCtor()\n" RES);
}

void FlyingSquirlDtor(FlyingSquirl_t *this_)
{
    printf(RED "FlyingSquirl::Dtor()\n" RES);

    this_->squirl.animal.v_table = Squirl_vt;
    SquirlDtor((Squirl_t*)this_);
}

void FlyingSquirlDisplay(FlyingSquirl_t *this_)
{
    printf( YEL "FlyingSquirl::Display() ID: %d\n" RES,
            AnimalGetID((Animal_t*)this_));

}

/****************************************************************************
        ==========  class LegendaryAnimal: public Animal  ==========
*****************************************************************************/

/*========== end of Class LegendaryAnimal Methodes Declarations  =======*/
typedef struct LegendaryAnimal LegendaryAnimal_t;
void LegendaryAnimalCtor   (LegendaryAnimal_t *this_);
void LegendaryAnimalDtor   (LegendaryAnimal_t *this_);
void LegendaryAnimalDisplay(LegendaryAnimal_t *this_);

typedef void (*LegendaryAnimalVT_t)(LegendaryAnimal_t*);
LegendaryAnimalVT_t LegendaryAnimal_vt[2] = { LegendaryAnimalDtor      ,
                                              LegendaryAnimalDisplay   };
/*========== end of Class LegendaryAnimal Methodes Declarations  =======*/



struct LegendaryAnimal
{
    Animal_t     animal;

    Animal_t    *m_a1;
    Animal_t    *m_a2;
    Centipede_t  m_c;
    Squirl_t     m_sq;
};
/* LegendaryAnimal() : m_a1(new Centipede()), m_a2(new Squirl()) {} */
void LegendaryAnimalCtor(LegendaryAnimal_t *this_)
{
    AnimalCtor((Animal_t*)this_);
    this_->animal.v_table = LegendaryAnimal_vt;

    this_->m_a1 = (Animal_t*) malloc(sizeof(Centipede_t));
    CentipedeCtor( (Centipede_t*)this_->m_a1);

    this_->m_a2 = (Animal_t*) malloc(sizeof(Squirl_t));
    SquirlCtor( (Squirl_t*)this_->m_a2);

    CentipedeCtor(&this_->m_c);
    SquirlCtor(&this_->m_sq);
}

/* LegendaryAnimal(const LegendaryAnimal &other) :
        m_a1( new Centipede( *dynamic_cast<Centipede*>(other.m_a1) ) ),
        m_a2( new Squirl   ( *dynamic_cast<Squirl*>   (other.m_a2) ) ),
        m_c ( other.m_c ),  m_sq( other.m_sq ) {} */
void LegendaryAnimalCCtor(LegendaryAnimal_t *this_, LegendaryAnimal_t *other)
{
    AnimalCCtor( (Animal_t*)this_, (Animal_t*)other);
    this_->animal.v_table = LegendaryAnimal_vt;

    this_->m_a1 = (Animal_t*) malloc(sizeof(Centipede_t));
    CentipedeCCtor( (Centipede_t*)this_->m_a1 , /* in c++ dynamic operation */
                    (Centipede_t*)other->m_a1 );

    this_->m_a2 = (Animal_t*) malloc(sizeof(Squirl_t));
    SquirlCCtor( (Squirl_t*)this_->m_a2 ,       /* in c++ dynamic operation */
                 (Squirl_t*)other->m_a2 );

    CentipedeCCtor(&this_->m_c , &other->m_c);
    SquirlCCtor   (&this_->m_sq, &other->m_sq);
}


void LegendaryAnimalDtor(LegendaryAnimal_t *this_)
{
    AnimalVT_t* func;

    /* delete m_a1; */
    func = (AnimalVT_t*)this_->m_a1->v_table;
    func[Dtor](this_->m_a1);

    free(this_->m_a1);
    this_->m_a1 = NULL;

    /* delete m_a2; */
    func = (AnimalVT_t*)this_->m_a2->v_table;
    func[Dtor](this_->m_a2);

    free(this_->m_a2);
    this_->m_a2 = NULL;

    SquirlDtor(&this_->m_sq);
    CentipedeDtor(&this_->m_c);

    this_->animal.v_table = Animal_vt;
    AnimalDtor((Animal_t*)this_);
}

void LegendaryAnimalDisplay(LegendaryAnimal_t *this_)
{
    AnimalVT_t* func;

    /* m_a1->Display(); */
    func = (AnimalVT_t*)this_->m_a1->v_table;
    func[Display](this_->m_a1);

    /* m_a2->Display(); */
    func = (AnimalVT_t*)this_->m_a2->v_table;
    func[Display](this_->m_a2);

    /* m_c.Display(); */
    CentipedeDisplay(&this_->m_c);

    /* m_sq.Display(); */
    SquirlDisplay(&this_->m_sq);
}


/****************************************************************************
        ==========  Functions  ==========
*****************************************************************************/
void Foo_Display(Animal_t *this_)
{
    /* a.Display(); */
    AnimalVT_t* func = (AnimalVT_t*)this_->v_table;
    func[Display](this_);
}

void Foo_Count()
{
    /* Animal::PrintCount(); */
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

    /* Foo(c); */
    Foo_Display( (Animal_t*) &c);

    /* Foo(3).Display(); */
    Animal_t re_animal;
    Foo_Int(3, &re_animal);
    AnimalDisplay(&re_animal);
    AnimalDtor(&re_animal);

    /* Animal *array[] = { new Centipede(), new Squirl(), new Centipede() }; */
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

    /* Animal arr2[] ={ Centipede(), Squirl(), Animal() }; */
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

    /*================  Part two of the c++ to c exercise  ================*/
    printf("\n");

    /* FlyingSquirl fs; */
    FlyingSquirl_t fs;
    FlyingSquirlCtor(&fs);

    /* FiFi(fs); */
    Squirl_t fifi_tmp;
    SquirlCCtor(&fifi_tmp, &fs.squirl);
    FiFi(&fifi_tmp);
    SquirlDtor(&fifi_tmp);

    /* LegendaryAnimal *la1 = new LegendaryAnimal(); */
    LegendaryAnimal_t *la1 = (LegendaryAnimal_t*) malloc(sizeof(LegendaryAnimal_t));
    LegendaryAnimalCtor(la1);

    /* LegendaryAnimal *la2 = new LegendaryAnimal(); */
    LegendaryAnimal_t *la2 = (LegendaryAnimal_t*) malloc(sizeof(LegendaryAnimal_t));
    LegendaryAnimalCCtor(la2, la1);

    /* la1->Display(); */
    func = (AnimalVT_t*) la1->animal.v_table;
    func[Display](&la1->animal);

    /* la2->Display(); */
    func = (AnimalVT_t*) la2->animal.v_table;
    func[Display](&la2->animal);

    /* delete la1; */
    func = (AnimalVT_t*) la1->animal.v_table;
    func[Dtor](&la1->animal);
    free(la1); la1 = NULL;

    /* la2->Display(); */
    func = (AnimalVT_t*) la2->animal.v_table;
    func[Display](&la2->animal);

    /* delete la2; */
    func[Dtor](&la2->animal);
    free(la2); la2 = NULL;

    FlyingSquirlDtor(&fs);
    /*=====  Destructor for stack variable will be called from here  ======*/

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
