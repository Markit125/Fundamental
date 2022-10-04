
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INT_MAX 2147483647
#define ABS 1000


int get_rand_int(int max_abs_value)
{
    return random() % max_abs_value * (random() % 2 ? 1 : -1);
}

int swap(int arr[], int arr_size, int max_index, int min_index)
{
    if (max_index >= arr_size || min_index >= arr_size)
    {
        return 1;
    }
    if (max_index == min_index)
    {
        return 0;
    }

    arr[max_index] = arr[max_index] + arr[min_index];
    arr[min_index] = arr[max_index] - arr[min_index];
    arr[max_index] = arr[max_index] - arr[min_index];

    return 0;
}

int is_integer(char const* arg)
{
    char *ptr = arg;
    
    if (*arg == '-')
    {
        ++ptr;
    }

    while (*ptr)
    {
        if ('0' > *ptr || *ptr > '9')
        {
            return 0;
        }
        ++ptr;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("You must enter size of array!\n");
        return 1;
    }

    if (argc > 2)
    {
        printf("Too many arguments!\n");
        return 1;
    }
    
    if (!is_integer(argv[1]))
    {
        printf("Number must be integer number!\n");
        return 1;
    }

    int arr_size = atoi(argv[1]);
    if (arr_size < 1)
    {
        printf("An array must have positive size!\n");
        return 1;
    }
    
    srandom(time(NULL));
    int arr[arr_size];

    int max = -INT_MAX;
    int min = INT_MAX;
    int max_index = 0;
    int min_index = 0;
    
    int i;
    for (i = 0; i < arr_size; ++i)
    {
        int rand_num = get_rand_int(ABS);
        arr[i] = rand_num;

        if (rand_num > max)
        {
            max = rand_num;
            max_index = i;
        }
        if (rand_num < min)
        {
            min = rand_num;
            min_index = i;
        }
    }

    printf("Start array:\n");
    for (i = 0; i < arr_size; ++i)
    {
        printf("%d ", arr[i]);
    } printf("\n\n");

    printf("Max: %d\nMin: %d\n\n", max, min);


    if (swap(arr, arr_size, max_index, min_index) == 0)
    {
        printf("New array:\n");
        for (i = 0; i < arr_size; ++i)
        {
            printf("%d ", arr[i]);
        } printf("\n\n");

    }
    else
    {
        printf("Swap error\n");
    }

    printf("Success\n");

    return 0;
}