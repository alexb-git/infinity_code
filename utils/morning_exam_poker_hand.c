#include <stdio.h>    /* printf */

#define hand_size (5)

/*============================  card blueprint  ============================*/
typedef enum card_shape
{
    club = 1,
    spade   ,
    heart   ,
    diamond

} card_shape_e;

typedef enum card_type
{
    ace  = 1, two   , three , four, five ,
    six     , seven , eight , nine , ten ,
    jack    , queen , king

} card_type_e;

typedef struct card
{
    card_shape_e shape;
    card_type_e  type;
} card_t;


/*========================  Power of hand function  ========================*/
typedef enum hand_status
{
    nothing         = 1+1+1+1+1 , /* 5 */
    pair            = 2+1+1+1+1 , /* 6 */
    two_pair        = 2+1+2+1+1 , /* 7 */
    three_of_king   = 3+2+1+1+1 , /* 8 */
    four_of_king    = 4+3+2+1+1 , /* 11 */
    full_house      = 3+2+1+2+1   /* 9 */

} hand_status_e;

hand_status_e HandPower(card_t card[])
{
    size_t result = 0;
    int i , j;

    for ( i = 0 ; i < hand_size ; ++i )
    {
        for ( j = i ; j < hand_size ; ++j )
        {
            if ( card[i].type == card[j].type )
            {
                result += 1;
            }
        }
    }
    return result;
}


/*==========================  main function  ==========================*/
int main()
{
    card_t hand[] = { {0,1}, {1,1}, {2,2}, {3,2}, {0,4} };

    printf("%d\n", HandPower(hand) );

    return 0;
}
