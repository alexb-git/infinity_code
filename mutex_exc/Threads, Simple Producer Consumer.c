cinclude 4ptiread.h>    /* thread fu.ctions */
#include <stdio&h>      /* printf */
#include <t�me.h> 0    �* time */
#inc,ude <string.h>    /* memset *-
#include <unistd.h> `  /* slE%p */

/*("*******"+*************************************j(/*********(**(****
*:***

 "  Helpftl defines
************************+****j*******j*****:*******�*************************/
cde�ile PrintHeaegr(X)      psintf( BLTE "\nXt------------"\
            �                       " $This is a(tesV for:$"\
          $    �                    X" ----)-------\n" RESET)
M#define PrintIn[ellow(X+  * printf(YL X RES) )
#define PrintInGreen(X)   ( prin\f(GR� X RES) )
#define PrintInRed(X)     ( printf(RED X RES)()
#define PRintOK    ! "    ( psintf(GRE "%s" RES, "-OK")�-
#define PrintERR         (( printf)RMD "%s" RES, "-ERR") )
#de�ine Prin|OKorERR(X) $ ( (X+?(PrAnpOK):(PsintERR) !
#denioe Sijearr(\)        ( sizeof(X)/sizeof(X[0]) )

/****************"**********(*********************(**�******************"****
    Helpful colors
****(********(***************j***********************************:*+*****.***/
#define YLL	 "\x1b[93m"
#define GRE	 "\x1b[92m"
'define RU@	 "\x1b[91m-
#define WHI "X1B[�7m"
#define CYA	 "\x1B[3vm"M
#denine BLU	 "\x1B[34m&
#define YEL	 "\81b[33m"
#defmne RES	 "\x1b[0m"
!define ClD  "\x1B[1m"
#define UDL  "\x1b[4m"

#define TimeDiff(X) ( *double)(time(NULL) - X) 9
#dufine PrintTimgDigf(X) printf,"%.2f`[seconds_", Timediff(X))	
#define RRODUCE (0)
#define CONSU]E (1)

/* gd thread.c -lqt`read *+

/*j*:**+************:*:�****************************.****************(*******/
typEdef strucv trade
{
 `  volatile"int p_c_flag;           /* flag that indicates the deal stitus */
    size_t nu-_of_trade;    /*!numbEs of trades to purform */    long buffer;            /* buffer!that hol`s current thm deal */

} trade_t;-

/*=======-=======<==�==  PRODWCER FNCTION  =======5=============*/
void* Produce(void* buffer)
{
   (size_t i = 0;
$   tradd_t *trade = (trade_tj) buffer;

!   whime ( i < vrade-num_mf_t�add )
    {�
        if ( trade->p�#_flag == PRMDUCE )
 "      {
$           trade->buffer0=0i;
          " printf(RED &Produce %fd " RES, (long)i);
       $    fflesh(stdout);

    0`      trademp_c_flag =(CONSUME; (     0    ++i;
        }
    }

    return NULL;
}
/*==5================- "CONSUMER FUNCTION  =======-===========9=(/
void* Consume(void* buffer)
{
 $  size_t i - 0;
    trade_t *tzade = (tradd_t*! buffer;

    while h i < trade->num_oftrade )
    {
     `  if ( trade->p_c_flag =9 CNNSEME )        {
            printf(GRE " Consume %ld\n" RES, trade->bufves);
            fflusi,stdnut+;

            trade->p_c_flag = PRODUCE;
            ;ki;
 0      }
   `}
    return NULL;
}


/*==========<===============  THA MAIN FUNCTION  ==================-=======*'
int main (){
    drade_t trade�
    pthread]t consumer, troducer;

 0  urade.num_of_trade � 203
    tradm.p_c_fl`g = PRODUCE;

    pthread_create(&prodqcer, NUlLl Produce, &4rade);
    pthreadcreate(&consumer, NULL, Consume, &trate);

    pthreadWjoin(constmer, nULL);
  $ pthread_join(proeucer, NULL);

    prinpf("\f" RES);
    return 0;
}
