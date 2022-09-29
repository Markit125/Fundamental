#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "algorithms.c"


int is_number(char const* arg)
{
    int n;
    return (sscanf(arg, "%d", &n) == 1);
}

int is_integer(char const* arg)
{
    int i;
    for (i = 0; i < strlen(arg); ++i)
    {
        if (!is_number(&arg[i]))
        {
            return 0;
        }
    }
    return 1;
}

int is_flag(char const* arg)
{
    return arg[0] == '-' || arg[0] == '/';
}


int main(int argc, char *argv[])
{
    if (argc > 3)
    {
        printf("Too many arguments!\n");
        return 1;
    }

    if (argc == 1)
    {
        printf("No agruments!\n");
        return 1;
    }

    int number = -1;
    char *flag = NULL;



    if (is_number(argv[1]))
    {
        if (!is_integer(argv[1]))
        {
            printf("Number must be integer!\n");
            return 1;
        }
        number = atoi(argv[1]);
    }
    
    else if (is_flag(argv[1]))
    {
        flag = argv[1];
    }
    
    if (argc == 2)
    {

        if (flag == NULL)
        {
            printf("You must input a flag\n");
        }
        
        else
        {
            printf("You must input a number\n");
        }
        return 1;
    }

    if (flag == NULL)
    {
        if (is_flag(argv[2]))
        {
            flag = argv[2];
        }
        
        else
        {
            printf("Flag is incorrect!\n");
            return 1;
        }
    }
    
    else
    {
        if (is_number(argv[2]))
        {
            if (!is_integer(argv[1]))
            {
                printf("Number must be integer!\n");
                return 1;
            }
            number = atoi(argv[2]);
        }
        
        else
        {
            printf("Number is incorrect!\n");
            return 1;
        }
    }

    if (number < 1)
    {
        printf("Number must be positive!\n");
        return 1;
    }

    ++flag;
    int success = 0;
    
    if (*flag == 'h')
    {
        int mult_array[100];
        if (multiply_less_hundred(number, mult_array) == 0)
        {
            int i = 0;
            while (mult_array[i] != 0)
            {
                printf("%d ", mult_array[i++]);
            }
            success = 1;
        }
    }
    
    else if (*flag == 'p')
    {
        int prime;
        if (is_prime(number, &prime) == 0)
        {
            printf("%s", prime ? "Prime" : "Composite");
            success = 1;
        }
    }
    
    else if (*flag == 's')
    {
        char *spelled_number = (char *) malloc(sizeof(char) * 15);
        if (spell(number, spelled_number) == 0)
        {
            printf("%s", spelled_number);
            success = 1;
        }
    }

    else if (*flag == 'e')
    {
        if (number > 10)
        {
            printf("Number must be less or equal to 10 for this flag!\n");
            return 1;
        }
        int **arr = malloc(sizeof(int *) * number);
        int i;
        for (i = 0; i < 10; ++i)
        {
            arr[i] = (int *) malloc(sizeof(int) * 10);
        }

        if (extents(number, arr) == 0)
        {
            int i, j;
            for (i = 0; i < 10; ++i)
            {
                for (j = 0; j < number; ++j)
                {
                    printf("%d ", arr[i][j]);
                } printf("\n");
            }
            for (i = 0; i < 10; ++i)
            {
                free(arr[i]);
            }
        }
        else
        {
            for (i = 0; i < 10; ++i)
            {
                free(arr[i]);
            }
            success = 0;
        }
    }

    else if (*flag == 'a')
    {
        int sum;
        if (progression(number, &sum) == 0)
        {
            printf("%d", sum);
            success = 1;
        }
    }

    else if (*flag == 'f')
    {
        int fact;
        if (factorial(number, &fact) == 0)
        {
            printf("%d", fact);
            success = 1;
        }
    }

    else
    {
        printf("This flag is not exists!\n");
        return 1;
    }

    if (!success)
    {
        printf("Error\n");
        return -1;
    }

    printf("\n");

    return 0;
}
