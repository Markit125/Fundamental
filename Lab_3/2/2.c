#include "arguments.c"
#include "funcs.c"
#include <stdio.h>

#define START_COUNT_LEN 10

// int get_len(int n)
// {
//     int bit = 1;
//     int len = 0;
//     while (bit < 32)
//     {
//         if ((1 << bit++) & n)
//         {
//             len = bit;
//         }
//     }
//     return len;
// }


unsigned int IntToInt(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * IntToInt(k / 2)));
}



int main()
{
    int k, l;

    int count = 0;
    int cur_len = LEN;

    char *num = (char *) malloc(sizeof(char) * cur_len);
    
    if (num == NULL)
    {
        return 1;
    }

    printf("Enter the k parameter:\n");

    while (count < 2)
    {
        int err = get_input(num, &cur_len);
        if (err == 1)
        {
            printf("There is not enough memory!\n");
            return 1;
        }

        if (count == 0)
        {
            int err = validate(num, &k);

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
            int err = validate(num, &l);

            if (err == 0 && l <= k)
            {
                ++count;
            }
            else
            {
                printf("Wrong positive integer, l should be less or equal to k, try again!\n");
            }
        }
    }

    printf("Enter the number of function:\n");
    while (1)
    {
        int err = get_input(num, &cur_len);
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
    
    // printf("len: %d\n", cur_len);


    int *numbers = (int *) malloc(sizeof(int) * cur_len);

    if (numbers == NULL) 
    {
        printf("There is not enough memory!\n");
        return 1;
    }

    int count_nums = 0;

    if (count == 1)
    {
        l_ones(k, l, numbers, &count_nums, &cur_len);
    }
    else
    {
        l_ones_in_a_row(k, l, numbers, &count_nums, &cur_len);
    }


    int i;
    for (i = 0; i < count_nums; ++i)
    {
        // printf("%d ", *(numbers + i));
        printf("%d\n", IntToInt(*(numbers + i)));
    } printf("\n");



    free(numbers);

    return 0;
}