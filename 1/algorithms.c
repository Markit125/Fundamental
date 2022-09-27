
#include <math.h>


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


int multiply_less_hundred(int number, int *arr)
{
    int exist = 0;
    int i, count = 0;
    for (i = 1; i < 101; ++i)
    {
        if (i % number == 0)
        {
            arr[count++] = i;
            exist = 1;
        }
    }
    arr[count] = 0;

    if (!exist)
    {
        arr = 0;
    }
    return 0;
}


int is_prime(int number, int *prime)
{
    for (int i = 2; i < sqrt(number) + 1; ++i)
    {
        if (number % i == 0)
        {
            *prime = 0;
            return 0;
        }
    }
    *prime = 1;
    return 0;
}


int spell(int number, char *str)
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


int extents(int number, int **ext_arr)
{
    int i;
    int j;
    for (i = 0; i < 10; ++i)
    {
        for (j = 0; j < number; ++j)
        {
            ext_arr[i][j] = power(i + 1, j + 1);
        }
    }
    return 0;
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