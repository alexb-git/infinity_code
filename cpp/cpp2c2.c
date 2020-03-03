/****************************************************************************
** Filename:    - cpp2c2.c
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - translate c++ to c
** Date:        - 30/1/2018
** Version:     - 1
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
                ==========  Class Public_Transport  ==========
*****************************************************************************/
static int Public_Transport_s_count = 0;

/*==========  Class Public_Transport Methodes Declarations  ==============*/
typedef struct Public_Transport Public_Transport_t;
void Public_TransportCtor   (Public_Transport_t *this_);
void Public_TransportCCtor  (      Public_Transport_t *this_,
                             const Public_Transport_t *other);
void Public_TransportDtor   (Public_Transport_t *this_);
void Public_TransportDisplay(Public_Transport_t *this_);
int  Public_TransportGetID  (Public_Transport_t *this_);
void Public_TransportPrintCount();

typedef void (*Public_TransportVT_t)(Public_Transport_t*);
Public_TransportVT_t Public_Transport_vt[2] = { Public_TransportDtor      ,
                                                Public_TransportDisplay   };
/*========== end of Class Public_Transport Methodes Declarations  =======*/

struct Public_Transport
{
    void *v_table;
    int   m_license_plate;
};

void Public_TransportCtor(Public_Transport_t *this_)
{
    this_->m_license_plate    = ++Public_Transport_s_count;
    this_->v_table = Public_Transport_vt;
    printf( BLD BLU "Public_Transport::Ctor() %d\n" RES,
            this_->m_license_plate);
}

void Public_TransportCCtor(       Public_Transport_t *this_,
                            const Public_Transport_t *other)
{
    this_->v_table = Public_Transport_vt;
    this_->m_license_plate    =  ++Public_Transport_s_count;
    printf( BLD BLU "Public_Transport::CCtor() %d\n" RES,
            this_->m_license_plate);
}

void Public_TransportDtor(Public_Transport_t *this_)
{
    --Public_Transport_s_count;
    printf( BLD RED "Public_Transport::Dtor() %d\n" RES,
            this_->m_license_plate);
}

void Public_TransportDisplay(Public_Transport_t *this_)
{
    printf( BLD YEL "Public_Transport::Display() %d\n" RES,
            this_->m_license_plate);
}

void Public_TransportPrintCount()
{
    printf( BLD YEL "s_count: %d\n" RES,
            Public_Transport_s_count);
}

int Public_TransportGetID(Public_Transport_t *this_)
{
    return this_->m_license_plate;
}


/****************************************************************************
        ==========  class Minibus: public Public_Transport  ==========
*****************************************************************************/

/*=============  Class Minibus Methodes Declarations  ==========*/
typedef struct Minibus Minibus_t;
void MinibusCtor    (Minibus_t *this_);
void MinibusCCtor   (Minibus_t *this_, const Minibus_t *other);
void MinibusDtor    (Minibus_t *this_);
void MinibusDisplay (Minibus_t *this_);
void MinibusWash(Minibus_t *this_);

typedef void (*MinibusVT_t)(Minibus_t*);
MinibusVT_t Minibus_vt[3] = { MinibusDtor   ,
                              MinibusDisplay,
                              MinibusWash   };
/*========== end of Class Minibus Methodes Declarations  =======*/

struct Minibus
{
    Public_Transport_t Public_Transport;
    int                m_numSeats;
};

void MinibusCtor(Minibus_t *this_)
{
    Public_TransportCtor((Public_Transport_t*)this_);
    this_->Public_Transport.v_table = Minibus_vt;
    this_->m_numSeats =  20;
    printf(BLU "Minibus::Ctor()\n" RES);
}

void MinibusCCtor(Minibus_t *this_, const Minibus_t *other)
{
    Public_TransportCCtor((Public_Transport_t*)this_,
                          (Public_Transport_t*)other);

    this_->Public_Transport.v_table = Minibus_vt;
    this_->m_numSeats = other->m_numSeats;

    printf(BLU "Minibus::CCtor()\n" RES);
}

void MinibusDtor(Minibus_t *this_)
{
    printf(RED "Minibus::Dtor()\n" RES);

    this_->Public_Transport.v_table = Public_Transport_vt;
    Public_TransportDtor((Public_Transport_t*)this_);
}

void MinibusDisplay(Minibus_t *this_)
{
    printf(YEL "Minibus::Display() ID: %d num seats: %d\n" RES,
          Public_TransportGetID((Public_Transport_t*)this_), this_->m_numSeats);
}

void MinibusWash(Minibus_t *this_)
{
    printf(YEL "Minibus::Wash() ID: %d\n" RES,
            Public_TransportGetID((Public_Transport_t*)this_));
}

/****************************************************************************
        ==========  class Taxi: public Public_Transport  ==========
*****************************************************************************/

/*========== end of Class Taxi Methodes Declarations  ========*/
typedef struct Taxi Taxi_t;
void TaxiCtor   (Taxi_t *this_);
void TaxiCCtor  (Taxi_t *this_, Taxi_t *other);
void TaxiDtor   (Taxi_t *this_);
void TaxiDisplay(Taxi_t *this_);

typedef void (*TaxiVT_t)(Taxi_t*);
TaxiVT_t Taxi_vt[2] = { TaxiDtor      ,
                            TaxiDisplay   };
/*========== end of Class Taxi Methodes Declarations  =======*/

struct Taxi
{
    Public_Transport_t Public_Transport;
};

void TaxiCtor(Taxi_t *this_)
{
    Public_TransportCtor((Public_Transport_t*)this_);
    this_->Public_Transport.v_table = Taxi_vt;
    printf(BLU "Taxi::Ctor()\n" RES);
}

void TaxiCCtor(Taxi_t *this_, Taxi_t *other)
{
    Public_TransportCCtor( (Public_Transport_t*)this_ ,
                           (Public_Transport_t*)other );
    this_->Public_Transport.v_table = Taxi_vt;

    printf(BLU "Taxi::CCtor()\n" RES);
}

void TaxiDtor(Taxi_t *this_)
{
    printf(RED "Taxi::Dtor()\n" RES);

    this_->Public_Transport.v_table = Public_Transport_vt;
    Public_TransportDtor((Public_Transport_t*)this_);
}

void TaxiDisplay(Taxi_t *this_)
{
    printf( YEL "Taxi::Display() ID: %d\n" RES,
            Public_TransportGetID((Public_Transport_t*)this_));
}

/****************************************************************************
        ==========  class Special_Taxi : public Taxi  ==========
*****************************************************************************/

/*========== end of Class Special_Taxi Methodes Declarations  =======*/
typedef struct Special_Taxi Special_Taxi_t;
void Special_TaxiCtor   (Special_Taxi_t *this_);
void Special_TaxiCCtor  (Special_Taxi_t *this_, Special_Taxi_t *other);
void Special_TaxiDtor   (Special_Taxi_t *this_);
void Special_TaxiDisplay(Special_Taxi_t *this_);

typedef void (*Special_TaxiVT_t)(Special_Taxi_t*);
Special_TaxiVT_t Special_Taxi_vt[2] = { Special_TaxiDtor      ,
                                        Special_TaxiDisplay   };
/*========== end of Class Special_Taxi Methodes Declarations  =======*/


struct Special_Taxi
{
    Taxi_t Taxi;
};

void Special_TaxiCtor(Special_Taxi_t *this_)
{
    TaxiCtor((Taxi_t*)this_);
    this_->Taxi.Public_Transport.v_table = Special_Taxi_vt;
    printf(CYA "Special_Taxi::Ctor()\n" RES);
}

void Special_TaxiCCtor(Special_Taxi_t *this_, Special_Taxi_t *other)
{
    TaxiCCtor((Taxi_t*)this_, (Taxi_t*)other);
    this_->Taxi.Public_Transport.v_table = Special_Taxi_vt;

    printf(CYA "Special_Taxi::CCtor()\n" RES);
}

void Special_TaxiDtor(Special_Taxi_t *this_)
{
    printf(RED "Special_Taxi::Dtor()\n" RES);

    this_->Taxi.Public_Transport.v_table = Taxi_vt;
    TaxiDtor((Taxi_t*)this_);
}

void Special_TaxiDisplay(Special_Taxi_t *this_)
{
    printf( YEL "Special_Taxi::Display() ID: %d\n" RES,
            Public_TransportGetID((Public_Transport_t*)this_));

}

/****************************************************************************
========  class Public_Convoy: public Public_Transport  ========
*****************************************************************************/

/*======== end of Class Public_Convoy Methodes Declarations  ===*/
typedef struct Public_Convoy Public_Convoy_t;
void Public_ConvoyCtor   (Public_Convoy_t *this_);
void Public_ConvoyDtor   (Public_Convoy_t *this_);
void Public_ConvoyDisplay(Public_Convoy_t *this_);

typedef void (*Public_ConvoyVT_t)(Public_Convoy_t*);
Public_ConvoyVT_t Public_Convoy_vt[2] =
                                        { Public_ConvoyDtor     ,
                                          Public_ConvoyDisplay  };
/*======= end of Class Public_Convoy Methodes Declarations  =====*/



struct Public_Convoy
{
    Public_Transport_t   Public_Transport;

    Public_Transport_t  *m_pt1;
    Public_Transport_t  *m_pt2;
    Minibus_t            m_m;
    Taxi_t               m_t;
};
/* Public_Convoy() : m_pt1(new Minibus()), m_pt2(new Taxi()) {} */
void Public_ConvoyCtor(Public_Convoy_t *this_)
{
    Public_TransportCtor((Public_Transport_t*)this_);
    this_->Public_Transport.v_table = Public_Convoy_vt;

    this_->m_pt1 = (Public_Transport_t*) malloc(sizeof(Minibus_t));
    MinibusCtor( (Minibus_t*)this_->m_pt1);

    this_->m_pt2 = (Public_Transport_t*) malloc(sizeof(Taxi_t));
    TaxiCtor( (Taxi_t*)this_->m_pt2);

    MinibusCtor(&this_->m_m);
    TaxiCtor(&this_->m_t);
}

/* Public_Convoy(const Public_Convoy &other) :
        m_pt1( new Minibus( *dynamic_cast<Minibus*>(other.m_pt1) ) ),
        m_pt2( new Taxi   ( *dynamic_cast<Taxi*>   (other.m_pt2) ) ),
        m_m ( other.m_m ),  m_t( other.m_t ) {} */
void Public_ConvoyCCtor(Public_Convoy_t *this_, Public_Convoy_t *other)
{
    Public_TransportCCtor( (Public_Transport_t*)this_ ,
                           (Public_Transport_t*)other );
    this_->Public_Transport.v_table = Public_Convoy_vt;

    this_->m_pt1 = (Public_Transport_t*) malloc(sizeof(Minibus_t));
    MinibusCCtor( (Minibus_t*)this_->m_pt1 ,
                  (Minibus_t*)other->m_pt1 );

    this_->m_pt2 = (Public_Transport_t*) malloc(sizeof(Taxi_t));
    TaxiCCtor( (Taxi_t*)this_->m_pt2 ,
               (Taxi_t*)other->m_pt2 );

    MinibusCCtor(&this_->m_m , &other->m_m);
    TaxiCCtor   (&this_->m_t, &other->m_t);
}


void Public_ConvoyDtor(Public_Convoy_t *this_)
{
    Public_TransportVT_t* func;

    /* delete m_pt1; */
    func = (Public_TransportVT_t*)this_->m_pt1->v_table;
    func[Dtor](this_->m_pt1);

    free(this_->m_pt1);
    this_->m_pt1 = NULL;

    /* delete m_pt2; */
    func = (Public_TransportVT_t*)this_->m_pt2->v_table;
    func[Dtor](this_->m_pt2);

    free(this_->m_pt2);
    this_->m_pt2 = NULL;

    TaxiDtor(&this_->m_t);
    MinibusDtor(&this_->m_m);

    this_->Public_Transport.v_table = Public_Transport_vt;
    Public_TransportDtor((Public_Transport_t*)this_);
}

void Public_ConvoyDisplay(Public_Convoy_t *this_)
{
    Public_TransportVT_t* func;

    /* m_pt1->Display(); */
    func = (Public_TransportVT_t*)this_->m_pt1->v_table;
    func[Display](this_->m_pt1);

    /* m_pt2->Display(); */
    func = (Public_TransportVT_t*)this_->m_pt2->v_table;
    func[Display](this_->m_pt2);

    /* m_m.Display(); */
    MinibusDisplay(&this_->m_m);

    /* m_t.Display(); */
    TaxiDisplay(&this_->m_t);
}


/****************************************************************************
        ==========  Functions  ==========
*****************************************************************************/
/* template<class T> Max(const T &t1, const T &t2) */
int maxFunc(int t1, int t2)
{
    return ((t1 > t2) ? t1 : t2);
}

void PrintInfoDisplay(Public_Transport_t *this_)
{
    /* a.Display(); */
    Public_TransportVT_t* func = (Public_TransportVT_t*)this_->v_table;
    func[Display](this_);
}

void PrintInfoCount()
{
    /* Public_Transport::PrintCount(); */
    Public_TransportPrintCount();
}

void PrintInfo(int i, Public_Transport_t *re_Public_Transport)
{
	Minibus_t ret;
    MinibusCtor(&ret);

    printf("PrintInfo(int i)\n");

    /*ret.Display();*/
    MinibusDisplay(&ret);

    /* return ret; */
    Public_TransportCCtor(re_Public_Transport, &ret.Public_Transport);
    MinibusDtor(&ret);
}


void FTaxiDisplay(Taxi_t *Taxi)
{
    TaxiDisplay(Taxi);
}

/****************************************************************************
        ==========  The MAIN  ==========
*****************************************************************************/
int main(int argc, char const *argv[])
{
    int i;

    /* c++ Minibus c; */
    Minibus_t m;
    MinibusCtor(&m);

    /* PrintInfo(m);; */
    PrintInfoDisplay( (Public_Transport_t*) &m);

    /* Foo(3).Display(); */
    Public_Transport_t re_Public_Transport;
    PrintInfo(3, &re_Public_Transport);
    Public_TransportDisplay(&re_Public_Transport);
    Public_TransportDtor(&re_Public_Transport);

    /* Public_Transport *array[] = { new Minibus(), new Taxi(), new Minibus() }; */
    Public_Transport_t *array[3];

    {
        array[0] = (Public_Transport_t*) malloc( sizeof(Minibus_t) );
        MinibusCtor( (Minibus_t*) array[0]);

        array[1] = (Public_Transport_t*) malloc( sizeof(Taxi_t) );
        TaxiCtor( (Taxi_t*) array[1]);

        array[2] = (Public_Transport_t*) malloc( sizeof(Minibus_t) );
        MinibusCtor( (Minibus_t*) array[2]);
    }

    /* for loop array[i]->Display() */
    Public_TransportVT_t* func;
    for ( i = 0 ; i < 3 ; ++i )
    {
        func = (Public_TransportVT_t*)array[i]->v_table;
        func[Display](array[i]);
    }

    /* for loop  "delete array[i];" */
    for ( i = 0 ; i < 3 ; ++i )
    {
        func = (Public_TransportVT_t*)array[i]->v_table;
        func[Dtor](array[i]);

        free(array[i]);
        array[i] = NULL;
    }

    /* Public_Transport arr2[] ={ Minibus(), Taxi(), Public_Transport() }; */
    Public_Transport_t arr2[3];

    {
        /* create Minibus */
        Minibus_t cen;
        MinibusCtor(&cen);

        /*  slice Public_Transport out of Minibus,
            copy construct Public_Transport into the arr2 */
        Public_TransportCCtor(&arr2[0], &cen.Public_Transport);
        MinibusDtor(&cen);


        /* create Taxi */
        Taxi_t squ;
        TaxiCtor(&squ);

        /*  slice Public_Transport out of Taxi
            copy construct Public_Transport into the arr2 */
        Public_TransportCCtor(&arr2[1], &squ.Public_Transport);
        TaxiDtor(&squ);


        /* construct Public_Transport into the arr2 */
        Public_TransportCtor(&arr2[2]);
    }

    /* for loop array[i]->Display() */
    for ( i = 0 ; i < 3 ; ++i )
    {
        Public_TransportDisplay(arr2 + i);
    }

    Public_TransportPrintCount();   /* Public_Transport::PrintCount(); */
    Minibus_t m2;                   /* Minibus m2; */
    MinibusCtor(&m2);
    Public_TransportPrintCount();   /* m2.PrintCount(); */

    /* Minibus arr3[4]; */
    Minibus_t arr3[4];
    for ( i = 0 ; i < (int)SizeArr(arr3) ; ++i )
    {
        MinibusCtor(arr3 + i);
    }

    /* Taxi *arr4 = new Taxi[4] */
    Taxi_t *arr4;
    arr4 = (Taxi_t*) malloc( 4 * sizeof(Taxi_t) );
    for ( i = 0 ; i < 4 ; ++i )
    {
        TaxiCtor(arr4 + i);
    }

    /* for loop  "delete [] arr4;" */
    for ( i = 3 ; i >= 0 ; --i )
    {
        func = (Public_TransportVT_t*) (arr4 + i)->Public_Transport.v_table;
        func[Dtor]( &(arr4 + i)->Public_Transport );
    }
    free(arr4);
    arr4 = NULL;

    printf("%d\n" ,maxFunc(1 ,2));

    /* Special_Taxi st; */
    Special_Taxi_t st;
    Special_TaxiCtor(&st);

    /* TaxiDisplay(st); */
    Taxi_t TaxiDisplay_tmp;
    TaxiCCtor(&TaxiDisplay_tmp, &st.Taxi);
    FTaxiDisplay(&TaxiDisplay_tmp);
    TaxiDtor(&TaxiDisplay_tmp);

    /* Public_Convoy *ts1 = new Public_Convoy(); */
    Public_Convoy_t *ts1 = (Public_Convoy_t*) malloc(sizeof(Public_Convoy_t));
    Public_ConvoyCtor(ts1);

    /* Public_Convoy *ts2 = new Public_Convoy(); */
    Public_Convoy_t *ts2 = (Public_Convoy_t*) malloc(sizeof(Public_Convoy_t));
    Public_ConvoyCCtor(ts2, ts1);

    /* ts1->Display(); */
    func = (Public_TransportVT_t*) ts1->Public_Transport.v_table;
    func[Display](&ts1->Public_Transport);

    /* ts2->Display(); */
    func = (Public_TransportVT_t*) ts2->Public_Transport.v_table;
    func[Display](&ts2->Public_Transport);

    /* delete ts1; */
    func = (Public_TransportVT_t*) ts1->Public_Transport.v_table;
    func[Dtor](&ts1->Public_Transport);
    free(ts1); ts1 = NULL;

    /* ts2->Display(); */
    func = (Public_TransportVT_t*) ts2->Public_Transport.v_table;
    func[Display](&ts2->Public_Transport);

    /* delete ts2; */
    func[Dtor](&ts2->Public_Transport);
    free(ts2); ts2 = NULL;

    Special_TaxiDtor(&st);

    /* call dtor on arr3 */
    for ( i = (int)SizeArr(arr3) - 1 ; i >= 0 ; --i )
    {
        MinibusDtor(arr3 + i);
    }

    /* call dtor on m2 */
    MinibusDtor(&m2);

    /* call dtor on arr2 */
    for ( i = 2 ; i >= 0 ; --i )
    {
        Public_TransportDtor(arr2 + i);
    }

    /* call dtor on m */
    MinibusDtor(&m);

    return 0;
}
