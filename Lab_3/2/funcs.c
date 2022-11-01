#include <stdio.h>
#define INT_MAX 2147483647


//                                                  default 0  default 0    default 1    default 1
// void l_ones(int k, int l, int *nums, int *cur_len, int *count, int number, int one_count, int zap)
// {
//     number |= (1 << k);
//     printf("number %d\n", number);

//     if (l == one_count)
//     {
//         *(nums + *count) = number;
//         ++(*count);
//         return;
//     }

//     if (k - zap < l - one_count)
//     {
//         return;
//     }

//     if (number & (1 << (one_count - 1)))
//     {
//         l_ones(k, l, nums, cur_len, count, number, one_count, zap + 1);
//         l_ones(k, l, nums, cur_len, count, number | (1 << zap), one_count + 1, zap + 1);
//     }
//     else
//     {
//         l_ones(k, l, nums, cur_len, count, number | (1 << zap), one_count + 1, zap + 1);
//         l_ones(k, l, nums, cur_len, count, number, one_count, zap + 1);
//     }
// }

void l_ones(int k, int l, int *nums, int *count, int *cur_len)
{
    int i, n;
    int count_ones = 0;
    for (i = (1 << k); i < (1 << (k + 1)); ++i)
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
    
    for (i = (1 << k); i < (1 << (k + 1)); ++i)
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