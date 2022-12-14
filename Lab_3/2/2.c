#include "arguments.c"
#include "funcs.c"
#include <stdio.h>

#define START_COUNT_LEN 10


unsigned int IntToInt(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * IntToInt(k / 2)));
}


int main()
{
    int k, l;

    int count = 0;
    int cur_len = LEN;
    int err;
    int count_nums;
    int i;
    int *numbers;

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
        }
    }

    printf("Enter the number of function:\n");
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
    
    numbers = (int *) malloc(sizeof(int) * cur_len);
    if (numbers == NULL) 
    {
        printf("There is not enough memory!\n");
        return 1;
    }

    count_nums = 0;
    printf("There are %d such numbers:\n", cur_len);

    if (count == 1)
    {
        l_ones(k, l, numbers, &count_nums, &cur_len);
    }
    else
    {
        printf("%d %d input\n", k, l);
        l_ones_in_a_row(k, l, numbers, &count_nums, &cur_len);
    }

    
    for (i = 0; i < count_nums; ++i)
    {
        printf("%d\n", IntToInt(*(numbers + i)));
    } printf("\n");



    free(numbers);

    return 0;
}