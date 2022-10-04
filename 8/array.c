#include <stdlib.h>

#define INT_MAX 2147483647


int odd_indexes(int arr[], int new_arr[], int *size)
{
    int new_size = 0;
    
    int i;
    for (i = 0; i < *size; i += 2)
    {
        *(new_arr + i / 2) = arr[i];
        ++new_size;
    }

    *size = new_size;
    new_arr = realloc(new_arr, sizeof(int) * *size);

    return 0;
}

int even_nums(int arr[], int new_arr[], int *size)
{
    int new_size = 0;
    int i;
    for (i = 0; i < *size; ++i)
    {
        if (arr[i] % 2)
        {
            continue;
        }
        new_arr[new_size] = arr[i];
        ++new_size;
    }

    *size = new_size;
    new_arr = realloc(new_arr, sizeof(int) * *size);

    return 0;
}

int furthest(int arr[], int *ans, int index, int size)
{
    int max = -INT_MAX;
    int min = INT_MAX;
    int i;
    for (i = 0; i < size; ++i)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
        if (min > arr[i])
        {
            min = arr[i];
        }
    }
    *ans = (max - arr[index]) > (min - arr[index]) ? max : min;

    return 0;
}

int sum_before_index(int arr[], int *ans, int index)
{
    *ans = 0;
    int i;
    for (i = 0; i < index; ++i)
    {
        *ans += arr[i];
    }

    return 0;
}

int sum_lower_than_index(int arr[], int *ans, int index, int size)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        if (arr[i] < arr[index])
        {
            *ans += arr[i];
        }
    }

    return 0;
}