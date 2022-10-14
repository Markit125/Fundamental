#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arguments.c"


int is_space(char c)
{
    return c == '\n' || c == '\t' || c == ' ' || c == EOF;
}


int main()
{
    srand(time(NULL));

    int a[10];

    printf("Enter a range [a, b] of random values (two integer numbers):\n");

    char *num = malloc(sizeof(char) * 12);
    if (num == NULL)
    {
        printf("Not enough memory!\n");
        return 1;
    }

    int it = 0;
    int range[2];
    char c;
    int count = 0;
    
    while (count < 2)
    {
        c = getchar();
        if (!is_space(c))
        {
            *(num + it++) = c;
        }
        else if (it != 0)
        {
            *(num + it) = '\0';
            it = 0;
            if (is_integer(num))
            {
                range[count++] = arg_to_int(num);
            }
            else
            {
                printf("It is not number!\nTry again\n");
            }
        }
    }
    free(num);

    if (range[0] > range[1])
    {
        range[0] += range[1];
        range[1] = range[0] - range[1];
        range[0] -= range[1];
    }

    int i;
    for (i = 0; i < 10; ++i)
    {
        a[i] = get_rand_int(range[0], range[1]);
    }

    for (i = 0; i < 10; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("%s\n%s\n%s\n",
            "Choose changing:",
            "To swap min and max element in array enter 0",
            "To get a set of elements enter 1");

    while (c != '0' && c != '1')
    {
        c = getchar();   
    }

    if (c == '0')
    {
        swap_max_min(a);
        for (i = 0; i < 10; ++i)
        {
            printf("%d ", a[i]);
        }
    }
    else
    {
        int set[10];
        int set_len = make_set(a, set);
        for (i = 0; i < set_len; ++i)
        {
            printf("%d ", set[i]);
        }
    }

    printf("\n");

    return 0;
}