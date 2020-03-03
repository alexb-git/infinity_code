#include <stdio.h>    /* printf */

#define ArrSize(arr) (sizeof(arr)/sizeof(arr[0]))

/*==============================  SecondMin  ==============================*/
int SecondMin(int arr[], size_t size)
{
    int sec_min   = arr[0];
    int first_min = arr[0];

    int i = 0;

    for ( i = 1 ; i < size ; ++i )
    {
        if (  arr[i] < sec_min )
        {
            if ( arr[i] < first_min )   /* arr[i] < first_min < sec_min */
            {
                  sec_min = first_min;
                first_min = arr[i];
            }
            else
            {
                sec_min = arr[i];           /* first_min < arr[i] < sec_min */
            }
        }
    }

    return sec_min;
}

/*===========================  Missing Element  ===========================*/
int MissingElement(int arr[], size_t size)
{
    int sum = 0;
    int i   = 0;

    for ( i = 0 ; i < size ; ++i )
    {
        sum += arr[i];
    }

    return ( size * (size + 1) ) / 2 - sum;
}


/*===========================  SimpleSortFind  ============================*/
int SimpleSortFind(int *start, int *end, int to_find)
{
    int left   = 0;
    int right  = end - start;

    while ( left <= right )
    {
        int middle = left + (right - left)/2;

        if ( start[middle] == to_find )
        {
            return middle;
        }

        if ( start[middle] < to_find )
        {
            left = middle + 1;
        }
        else/* to_find < start[middle] */
        {
            right = middle - 1;
        }
    }

    return (-1);
}

/*========================  FindInInfinantSorted  =========================*/
int FindInInfinantSorted(int arr[], int to_find)
{
    int index = 1;

    if ( to_find == arr[0] ) /* special case */
    {
        return 0;
    }

    while ( to_find > arr[index] )
    {
        index *= 2;
    }

    return index / 2 + SimpleSortFind( arr + index/2, arr + index, to_find);
}




/*=============================  MAIN function  =============================*/
int main()
{
/*    int arr[] = {11, 3, 8, 10, 2, -1};
    printf("SecondMin: %d\n", SecondMin( arr, ArrSize(arr) ) );*/

/*    int arr[] = {0,1,4,2,5};

    printf("MissingElement: %d\n", MissingElement( arr, ArrSize(arr) ) );
*/

    int arr[] = {1,2,3,4,5,6,7};
    int to_find = 7;
    int found_index;

    found_index = SimpleSortFind(arr, arr + ArrSize(arr) - 1, to_find);
    printf("Index of element: %d\n", found_index);
    printf("FindInInfinantSorted: %d\n", FindInInfinantSorted(arr, to_find));
    printf("arr[FindInInfinantSorted(arr, to_find)] = %d\n", arr[FindInInfinantSorted(arr, to_find)]);
    return 0;
}
