/****************************************************************************
** Filename:    - morning_exam_print_tree.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Morning exam - print tree
** Date:        - 12/1/2017
** Version:     - 1
*****************************************************************************/

/* (!) PSEUDO CODE (!) */
void PrintTree(tree_t *tree, queue_t *queue)
{
    node_t *x = tree->root;

    if ( x = NULL ) return; /* case: tree is empty */

    Enqueue(queue,x);

    while ( !IsQueueEmpty(queue) )
    {
        /* Dequeue the node and print node */
        x = Dequeue(queue);
        printf(x);

        /* push children to the queue */
        if ( x.right != NULL )
        {
            Enqueue(queue, x.right);
        }

        if ( x.left != NULL )
        {
            Enqueue(queue, x.left);
        }
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
