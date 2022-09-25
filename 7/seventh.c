#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_integer(char const* arg)
{
    int i;
    for (i = 0; i < strlen(arg); ++i)
    {
        if ('0' - 1 < arg[i] && arg[i] < '9' + 1)
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("There is no name of file!\n");
        return 1;
    }

    if (argc > 2)
    {
        printf("Too many arguments!\n");
        return 1;
    }
    
    if (!is_number_integer(argv[1]))
    {
        printf("Number must be integer number!\n");
        return 1;
    }

    // int arr_size = atoi(argv[2]);
    // int *arr = malloc(sizeof(int) * arr_size);

    int i;
    // for (i = 0; i < arr_size; ++i)
    // {
    //     arr[i] = rand();
    // }

    // for (i = 0; i < arr_size; ++i)
    // {
    //     printf("%d ", arr[i]);
    // }


    printf("Success\n");

    return 0;
}