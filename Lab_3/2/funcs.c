#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647


unsigned int int_to_int(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_int(k / 2)));
}


int count_l_ones(int k, int l);


//                                                 default 0         default 1   default 1
int l_ones(int k, int l, unsigned int **nums, unsigned int number, int one_count, int pos)
{
    static unsigned int it = -1;

    if (it == -1)
    {
        *nums = (unsigned int *) malloc(sizeof(unsigned int) * count_l_ones(k, l));
        if (*nums == NULL) 
        {
            return 1;
        }

        number |= (1 << (k - 1));
        it = 0;
    }


    if (l == one_count)
    {
        *(*nums + it++) = number;
        
        return 0;
    }

    if (k - 1 - pos < l - one_count)
    {
        return 0;
    }

    l_ones(k, l, nums, number, one_count, pos + 1);
    l_ones(k, l, nums, number | (1 << pos), one_count + 1, pos + 1);
    

    return 0;
}


int count_one_row(int k, int l);


int l_ones_in_row(int k, int l, unsigned int **nums, unsigned int number, int row, int pos, int rest)
{
    static unsigned int it = -1;

    if (it == -1)
    {
        *nums = (unsigned int *) malloc(sizeof(unsigned int) * count_one_row(k, l));
        if (*nums == NULL) 
        {
            return 1;
        }

        number |= (1 << k);
        --number;
        row = 1;
        pos = k - 2;
        it = 0;
    }

    // printf("%d\t rest: %d\trow: %d\tpos: %d\n", int_to_int(number), rest, row, pos);
    // for (int i = 0; i < k - pos - 1; ++i)
    // {
    //     printf(" ");
    // }
    // printf("^\n");

    if (pos < 0)
    {
        if (rest || l == row)
        {
            *(*nums + it++) = number;
            // printf("======================\n");
        }

        return 0;
    }

    


    if (rest || l == row)
    {
        // printf("%d\t%d\t%d\n", int_to_int(number), rest, row);

        l_ones_in_row(k, l, nums, number & ~(1 << pos), 0, pos - 1, 1);

        l_ones_in_row(k, l, nums, number, row + 1, pos - 1, rest);
    }
    else
    {
        l_ones_in_row(k, l, nums, number & ~(1 << pos), 0, pos - 1, rest);
        
        l_ones_in_row(k, l, nums, number, row + 1, pos - 1, rest);
    }    

    return 0;
}


int count_one_row(int k, int l)
{
    if (k - l <= 1)
    {
        return 1;
    }

    return (1 << (k - l - 1)) + (k - 2 - l) * (1 << (k - 3 - l)) + (1 << (k - 2 - l));
}

int count_l_ones(int k, int l)
{
    int c = 1;
    int n = (k - l > l - 1) ? (k - l) : (l - 1);
    int m = (n != k - l) ? (k - l) : (l - 1);

    int i;
    for (i = n + 1; i < k; ++i)
    {
        c *= i;
    }

    for (i = 2; i <= m; ++i)
    {
        c /= i;
    }

    return c;
}