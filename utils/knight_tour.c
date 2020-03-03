/****************************************************************************
** Filename:    - knight_tour.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - solving the knight tour puzzle
** Date:        - 30/11/2017
** Version:     - 1
*****************************************************************************/
#include <stdlib.h> /* system */
#include <stdio.h>  /* printf */
#include <time.h>   /* time */
#include <unistd.h> /* sleep */

#include "bits_array.h" /* bits array */

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

/****************************************************************************
    Helpful defines
*****************************************************************************/
#define PrintHeader(X)      printf( BLU "\n\t------------"\
                                    "  This is a test for: "\
                                    X" ------------\n" RES)

#define PrintInYellow(X)  ( printf(YEL X RES) )
#define PrintInGreen(X)   ( printf(GRE X RES) )
#define PrintInRed(X)     ( printf(RED X RES) )
#define PrintOK           ( printf(GRE "%s" RES, "-OK") )
#define PrintERR          ( printf(RED "%s" RES, "-ERR"))
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )


#define BOARD_SIZE (8)
#define IsEmpty(X)          ( 0 == X )
#define Cell(i,j)           ((i) * (BOARD_SIZE) +(j))

/* check if didn't surpass the time limit */
#define IsTimeOut(begin)    ( (double) (clock() - *begin)\
                              / CLOCKS_PER_SEC > 180 )

#define PrintTimeDiff(X) printf("\n%f [seconds]", (double) (clock() - *X)\
                         / CLOCKS_PER_SEC )

/*************************************/
typedef enum status
{
    BACK_TRACK = -1,
    TIME_OUT, /* ==0 */
    SUCCESS   /* ==1 */
} status_t;

/****************************************************************************
    prints the board visualy. [1] - cell was not bisited,
                              [0] - cell was visited
*****************************************************************************/
void PrintBord(size_t board)
{
    size_t row,col;

    for ( row = 0 ; row < BOARD_SIZE ; ++row )
    {
        printf("\n");
        for ( col = 0 ; col < BOARD_SIZE ; ++col )
        {
             (BitsArrayIsBitOn(board, Cell(row,col)))
            ?(PrintInRed("[1]"))
            :(printf("[0]"));
        }
    }
    printf("\n");
}

/****************************************************************************
    Prints the path as array. first cell - first/starting index
                              last  cell - finishing index
*****************************************************************************/
void PrintPath(size_t path[], size_t size)
{
    size_t row,col;

    for ( row = 0 ; row < BOARD_SIZE ; ++row )
    {
        printf("\n");
        for ( col = 0 ; col < BOARD_SIZE ; ++col )
        {
            if ( size < Cell(row,col) )
            {
                return;
            }
            printf("[%2lu]", path[Cell(row,col)]/*path[Cell(row,col)]*/);
        }
    }
    printf("\n");
}

/****************************************************************************
    Helpful function. Verifies that the board indexes as expected
*****************************************************************************/
void PrintIndexes(void)
{
    size_t row,col;

    for ( row = 0 ; row < BOARD_SIZE ; ++row )
    {
        printf("\n");
        for ( col = 0 ; col < BOARD_SIZE ; ++col )
        {
            printf("[%2lu]", Cell(row,col) );
        }
    }
    printf("\n");
}

/****************************************************************************
    Prints moves/path on the board, 0 - start square, 63 - end square
*****************************************************************************/
void TranslatePath(size_t path[])
{
    size_t i;
    size_t arr[BOARD_SIZE * BOARD_SIZE];

    for ( i = 0 ; i < BOARD_SIZE * BOARD_SIZE ; ++i )
    {
        arr[path[i]] = i;
    }

    PrintPath(arr, BOARD_SIZE * BOARD_SIZE );

    printf("\n");
}

/****************************************************************************
    Was used to validate the values of LUT visually
*****************************************************************************/
void PrintAnimated(size_t arr[])
{
    size_t i;

    for ( i = 0 ; i < BOARD_SIZE * BOARD_SIZE ; ++i )
    {
        system("clear");
        PrintBord(arr[i]);
        fflush(stdout);
        sleep(1);
    }
}

/****************************************************************************
    Initializes the lookup table
*****************************************************************************/
void InitLUT(size_t lut[])
{
    long row, col, n;

    long a[] = { +1, +1, -1, -1, +2, +2, -2, -2};
    long b[] = { +2, -2, +2, -2, +1, -1, +1, -1};

    for ( row = 0 ; row < BOARD_SIZE ; ++row )
    {
        for ( col = 0 ; col < BOARD_SIZE ; ++col )
        {
            size_t var = 0;

            for ( n = 0 ; n < 8 ; ++n )
            {
                if (   row + a[n] >= 0 && row + a[n] < BOARD_SIZE
                    && col + b[n] >= 0 && col + b[n] < BOARD_SIZE  )
                {
                    var = BitsArraySetBitOn(var, Cell(row + a[n], col + b[n]));
                    lut[Cell(row, col)] = var;
                }
            }
            PrintBord(lut[Cell(row, col)]);
        }
    }
}

/****************************************************************************
    prints out the Look-Up-Table for each square
*****************************************************************************/
void PrintLut(size_t lut[])
{
    size_t i;
    printf("{");
    for ( i = 0 ; i < BOARD_SIZE * BOARD_SIZE ; ++i )
    {
        if ( i % 3 == 0 )
        {
            printf("\n");
        }
        printf("%22ld,", lut[i]);
    }
    printf("}\n");

}

/****************************************************************************
    Look-Up-Table for each square returns possible moves
*****************************************************************************/
static size_t LUT[64] = {
      9077567998918656,      4679521487814656,     38368557762871296,
     19184278881435648,      9592139440717824,      4796069720358912,
      2257297371824128,      1128098930098176,   2305878468463689728,
   1152939783987658752,  -8646761407372591104,   4899991333168480256,
   2449995666584240128,   1224997833292120064,    576469569871282176,
    288234782788157440,   4620693356194824192,  -6913025356609880064,
   5802888705324613632,   2901444352662306816,   1450722176331153408,
    725361088165576704,    362539804446949376,    145241105196122112,
     18049583422636032,     45053588738670592,     22667534005174272,
     11333767002587136,      5666883501293568,      2833441750646784,
      1416171111120896,       567348067172352,        70506185244672,
       175990581010432,        88545054707712,        44272527353856,
        22136263676928,        11068131838464,         5531918402816,
         2216203387392,          275414786112,          687463207072,
          345879119952,          172939559976,           86469779988,
           43234889994,           21609056261,            8657044482,
            1075839008,            2685403152,            1351090312,
             675545156,             337772578,             168886289,
              84410376,              33816580,               4202496,
              10489856,               5277696,               2638848,
               1319424,                659712,                329728,
                132096};


/****************************************************************************
    chooses next move according to uristic
    (move with smallest number of possible moves after him)
*****************************************************************************/
size_t NextMove(size_t board, size_t poss_move)
{
    size_t num_of_moves = 8;
    size_t square;

    size_t curr_place = 0;
    size_t result;

    while ( poss_move )
    {
        /* find a move to check */
        while ( !BitsArrayIsBitOn(poss_move, curr_place) )
        {
            ++curr_place;
        }

        /* mark move as checked */
        poss_move = BitsArraySetBitOff(poss_move, curr_place);

        result = board & LUT[curr_place];

        if ( num_of_moves >= BitsArrayCountSetBits(result) )
        {
            /* found square with less movement options */
            num_of_moves = BitsArrayCountSetBits(result);
            square = curr_place;
        }

        ++curr_place;
    }

    return square;
}

/****************************************************************************
    Simplest Next Move Search
*****************************************************************************/
size_t NextMoveS(size_t board, size_t poss_move)
{
    size_t curr_place;

    for (  curr_place = 0 ;
          !BitsArrayIsBitOn(poss_move, curr_place) ;
           ++curr_place ){}

    return curr_place;
}

/****************************************************************************
    Random Next Move Search
*****************************************************************************/
size_t NextMoveR(size_t board, size_t poss_move)
{
    size_t curr_place  = 0;
    size_t first_valid = 0;
    srand(time(NULL));

    for ( ;
          !BitsArrayIsBitOn(poss_move, curr_place) ;
          ++curr_place ){}

    first_valid = curr_place;

    while ( curr_place < BOARD_SIZE * BOARD_SIZE )
    {
        if (   BitsArrayIsBitOn(poss_move, curr_place)
            && (rand() & 0x1) )
        {
            break;
        }

        ++curr_place;
    }

    return   (curr_place < BOARD_SIZE * BOARD_SIZE)
            ?(curr_place)
            :(first_valid);
}

/****************************************************************************/
status_t GetPath( size_t board       , /* board represented as 64 bits */
                  size_t curr_place  , /* represented as place on board 0-63 */
                  size_t path[]      , /* holds the moves to finish the tour */
                  size_t path_index  , /* current index for the path array */
                  time_t *start_time ) /* time at the beginning of the program*/
{
    size_t poss_move = LUT[curr_place] & board;

    board = BitsArraySetBitOff(board, curr_place);

    path[path_index] = curr_place;

    /* finished the tour successfully */
    if ( IsEmpty(board) )
    {
        return SUCCESS;
    }

    /* if time out (limited to 3 [min]) - return */
    if ( IsTimeOut(start_time) )
    {
        return TIME_OUT;
    }

    /* dead end - backtrack */
    if ( IsEmpty(poss_move) )
    {
        return BACK_TRACK;
    }

    while ( poss_move ) /* != 0 */
    {
        status_t ret_val;

/*system("clear");*/
/*PrintInYellow("\nBoard");
PrintBord(board);*/
/*fflush(stdout);
sleep(1);*/

        /* chooses next move */
        curr_place = NextMoveS(board, poss_move);

        poss_move = BitsArraySetBitOff(poss_move, curr_place);

        ret_val = GetPath( board           ,  /* board as 64 bits */
                           curr_place      ,  /* place on board 0-63 */
                           path            ,  /* moves array */
                           path_index + 1  ,  /* next index in path */
                           start_time     );  /* limited to 3 [min] */

       /* finished the tour successfully */
       if ( SUCCESS == ret_val )
       {
           return SUCCESS;
       }

       /* time out (limited to 3 [min]) - return failed */
       if ( TIME_OUT == ret_val )
       {
           return TIME_OUT;
       }

       /* end of while => dead end - backtrack */
    }

    return BACK_TRACK; /* dead end - backtrack */
}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
/*    size_t lut[64];
    InitLUT(lut);
    PrintLut(lut);
    PrintAnimated(lut);*/
    /*PrintIndexes();*/
    /*PrintBord(board);*/
    size_t i = 0;

    for ( i = 0 ; i < BOARD_SIZE * BOARD_SIZE ; ++i )
    {
        size_t start_point = i;
        size_t board       = ~(size_t)0;
        clock_t start_time = clock();
        size_t path[64];

        status_t status =
            GetPath(board       ,  /* board represented as 64 bits */
                    start_point ,  /* represented as place on board 0-63 */
                    path        ,  /* holds the moves to finish the tour */
                    0           ,  /* current index for the path array */
                    &start_time ); /* time since beginning of the program */

        printf(YEL "\n-> Starting point/index %lu" RES, start_point);
        PrintTimeDiff(&start_time);

        if ( status == TIME_OUT ) {
            PrintInRed(" - TIME IS OUT");
        }
        else
        {
            PrintInGreen(" -  SUCCESS");
            TranslatePath(path);
        }

        printf("\n");
    }

    return 0;
}
/*==========================  END OF MAIN  ==========================*/
