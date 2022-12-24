#include "arguments.c"
#include "funcs.c"
#include <stdio.h>

#define START_COUNT_LEN 10
#define STR_LEN 35


int main()
{
    int k, l;
    int count = 0;
    int cur_len = LEN;
    int err;
    int i;
    unsigned int *numbers;

    char *num = (char *) malloc(sizeof(char) * cur_len);
    if (num == NULL)
    {
        return 1;
    }

    printf("Enter the k parameter:\n");

    while (count < 2)
    {
        err = get_input(num, &cur_len);
        if (err == 1)
        {
            printf("There is not enough memory!\n");
            return 1;
        }

        if (count == 0)
        {
            err = validate(num, &k);

            if (err == 0)
            {
                printf("Enter the l parameter:\n");
                ++count;
            }
            else
            {
                printf("Wrong positive integer, try again!\n");
            }
        }
        else
        {
            err = validate(num, &l);

            if (err == 0 && l <= k)
            {
                ++count;
            }
            else
            {
                printf("l must be less or equal to k!\n");
            }
        }
    }

    printf("Enter the number of function (1/2):\n");
    while (1)
    {
        err = get_input(num, &cur_len);
        if (err == 0)
        {
            if (*num == '1' || *num == '2')
            {
                count = atoi(num);
                break;
            }
            printf("You should enter 1 or 2\n");
        }
        else
        {
            printf("There is not enough memory!\n");
            return 1;
        }
    }
    free(num);


    cur_len = (count == 1) ? count_l_ones(k, l) : count_one_row(k, l);

    if (count == 1)
    {
        err = l_ones(k, l, &numbers);
    }
    else
    {
        cur_len = 0;
        err = l_ones_row(k, l, &numbers, &cur_len);
    }

    if (err == 1)
    {
        printf("Cannot allocate memory!\n");
        return 2;
    }
    else if (err == 2)
    {
        printf("Cannot reallocate memory!\n");
        return 3;
    }

    printf("There are %d such numbers:\n", cur_len);
    for (i = 0; i < cur_len; ++i)
    {
        printf("%d\n", int_to_int(*(numbers + i)));
        printf("%d\n", *(numbers + i));
    }
    

    free(numbers);

    return 0;
}