/****************************************************************************
** Filename:    - morning_exam_bursa.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Morning exam - bursa problem (buy, sell, max profit)
** Date:        - 12/1/2017
** Version:     - 1
*****************************************************************************/
#include <stdio.h>    /* printf */
#include <string.h>   /* memcpy */

/*==========================  DEAL STRUCT  ==========================*/
typedef struct deal
{
    int buy;    /* index */
    int sell;   /* index */
    int profit;
} deal_t;

/****************************************************************************
    finds the buy point (index), the sell point (index) and the profit
    of the best deal (biggest profit/lowest loss) for a given bursa array
*****************************************************************************/
int BuySellProfit(int bursa[], size_t size, int *buy, int *sell)
{
    deal_t curr_best_deal = {0,0,0};
    deal_t prev_best_deal = {0,0,0};

    int curr_profit = 0;
    size_t i;

    for ( i = 1 ; i < size ; ++i )
    {
        curr_profit = bursa[i] - bursa[curr_best_deal.buy];

        /* case: current sell point is more profitable */
        if ( curr_profit > curr_best_deal.profit )
        {
            curr_best_deal.sell   = i;
            curr_best_deal.profit = curr_profit;
        }

        /* case: current buy value is lower => potential profit */
        if ( bursa[i] < bursa[curr_best_deal.buy] )
        {
            /*  copy 'current best deal' into 'previous best deal'
                only if its more profitable */
            if ( curr_best_deal.profit > prev_best_deal.profit )
            {
                memcpy(&prev_best_deal, &curr_best_deal, sizeof(deal_t));
            }

            curr_best_deal.buy    = i;
            curr_best_deal.sell   = i;
            curr_best_deal.profit = 0;
        }
    }

    /* init retrun values */
    if ( curr_best_deal.profit > prev_best_deal.profit )
    {
        *buy  = curr_best_deal.buy;
        *sell = curr_best_deal.sell;
        return curr_best_deal.profit;
    }
    else /* case: previous deal is more profitable */
    {
        *buy  = prev_best_deal.buy;
        *sell = prev_best_deal.sell;
        return prev_best_deal.profit;
    }
}

/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
    int buy_sell[2];
    int profit;

    int arr[] = {3,4,2,5,1,2};

    profit = BuySellProfit( arr, sizeof(arr)/sizeof(arr[0]),
                            buy_sell, buy_sell + 1);

    printf("Buy index:  %d, Buy val:  %d\n", buy_sell[0], arr[buy_sell[0]]);
    printf("Sell index: %d, Sell val: %d\n", buy_sell[1], arr[buy_sell[1]]);
    printf("Profit: %d\n", profit);


    return 0;
}
