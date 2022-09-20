
#include <math.h>
#include <stdio.h>


int power(int number, int extent)
{
    if (extent < 0) {
        return -1;
    }
    
    int answer = 1;
    while (extent--)
    {
        answer *= number;
    }
    return answer;
}


int multiply_less_hundred(int number)
{
    int exsist = 0;
    for (int i = 1; i < 101; ++i)
    {
        if (i % number == 0)
        {
            printf("%d ", i);
            exsist = 1;
        }
    }

    if (!exsist)
    {
        printf("There are no numbers within 100 multiplies of the entered number!");
    }
}


int is_prime(int number, int *prime)
{
    for (int i = 2; i < sqrt(number) + 1; ++i)
    {
        if (number % i == 0)
        {
            *prime = 0;
        }
    }
    *prime = 1;
    return 0;
}


char *spell(int number, char *str)
{
    int lenght = 0;
    int number_copy = number;
    while (number_copy > 0)
    {
        number_copy /= 10;
        ++lenght;
    }

    char *ptr = str + lenght * 2;
    *ptr = 0;

    int i;
    for (i = 0; i < lenght; i++)
    {
        str[2 * (lenght - 1 - i)] = number % 10 + '0';
        number /= 10;
        str[i * 2 - 1] = ' ';
    }
    return 0;
}


void extents(int number, int (*ext_arr)[number])
{
    int i;
    int j;
    for (i = 1; i < 11; ++i)
    {
        for (j = 1; j < number + 1; ++j)
        {
            ext_arr[i][j] = power(i, j);
            // printf("%d ", power(i, j));
        }
        printf("\n");
    }
}


int progression(int number, int *sum)
{
    *sum = 0;
    int i;
    for (i = 1; i < number + 1; ++i)
    {
        *sum += i;
    }
    return 0;
}


int factorial(int number, int *fact)
{
    *fact = 1;
    int i;
    for (i = 2; i < number + 1; ++i)
    {
        *fact *= i;
    }
    return 0;
}