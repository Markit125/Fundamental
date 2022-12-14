#include <stdio.h>
#define INT_MAX 2147483647

void l_ones(int k, int l, int *nums, int *count, int *cur_len)
{
    int i, n;
    int count_ones = 0;
    for (i = (1 << (k - 1)); i < (1 << k); ++i)
    {
        n = i;
        count_ones = 0;
        for (; n; n >>= 1)
        {
            count_ones += n & 1;
        }

        if (count_ones == l)
        {
            *(nums + *count) = i;
            ++(*count);
        }
    }
}


void l_ones_in_a_row(int k, int l, int *nums, int *count, int *cur_len)
{
    int i, n, x;
    int count_ones = 0;
    int in_a_row = 0;
    
    for (i = (1 << (k - 1)); i < (1 << k); ++i)
    {
        n = i;
        count_ones = 0;
        in_a_row = 0;

        for (; n; n >>= 1)
        {
            x = n & 1;
            count_ones += x;

            if (x)
            {
                ++in_a_row;
            }
            else
            {
                if (in_a_row == l)
                {
                    *(nums + *count) = i;
                    ++(*count);
                    break;
                }
                in_a_row = 0;
            }
        }
        if (in_a_row == l && !n)
        {
            *(nums + *count) = i;
            ++(*count);
        }
    }
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