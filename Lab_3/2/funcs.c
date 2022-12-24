#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647
#define COUNT 5

unsigned int int_to_int(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_int(k / 2)));
}


static int int_compare(const void *p1, const void *p2)
{
    unsigned int int_a = *((unsigned int *) p1);
    unsigned int int_b = *((unsigned int *) p2);

    if (int_a == int_b) return 0;
    else if (int_a < int_b) return -1;
    else return 1;
}


int count_l_ones(int k, int l);
int l_ones_in_a_num(int k, int l, unsigned int **nums, unsigned int number, int one_count, int pos);

int l_ones(int k, int l, unsigned int **nums)
{
    int err;
    int count = count_l_ones(k, l);
    
    *nums = (unsigned int *) malloc(sizeof(unsigned int) * count);
    if (*nums == NULL) 
    {
        return 1;
    }

    err = l_ones_in_a_num(k, l, nums, 1 << (k - 1), 1, 0);
    if (err)
    {
        return err;
    }

    qsort(*nums, count, sizeof(unsigned int), int_compare);

    return 0;
}

//                                                 default 0         default 1   default 1
int l_ones_in_a_num(int k, int l, unsigned int **nums, unsigned int number, int one_count, int pos)
{
    static unsigned int it = 0;

    if (l == one_count)
    {
        *(*nums + it++) = number;
        
        return 0;
    }

    if (k - 1 - pos < l - one_count)
    {
        return 0;
    }

    l_ones_in_a_num(k, l, nums, number, one_count, pos + 1);
    l_ones_in_a_num(k, l, nums, number | (1 << pos), one_count + 1, pos + 1);
    

    return 0;
}


int count_one_row(int k, int l);
int l_ones_in_row(int k, int l, unsigned int **nums, int *count, int number, int row, int pos, int rest, int *len);

int l_ones_row(int k, int l, unsigned int **nums, int *count)
{
    int nums_len = COUNT;
    int err;
    *count = 0;

    *nums = (unsigned int *) malloc(sizeof(unsigned int) * COUNT);
    if (*nums == NULL) 
    {
        return 1;
    }

    err = l_ones_in_row(k, l, nums, count, (1 << k) - 1, 1, k - 2, 0, &nums_len);
    if (err)
    {
        free(*nums);
        return err;
    }

    if (*count < nums_len)
    {
        unsigned int *ptr = realloc(*nums, sizeof(unsigned int) * *count);
        if (NULL == ptr)
        {
            return 2;
        }
        *nums = ptr;
    }
    
    qsort(*nums, *count, sizeof(unsigned int), int_compare);

    return 0;
}


int l_ones_in_row(int k, int l, unsigned int **nums, int *count, int number, int row, int pos, int rest, int *len)
{
    if (pos < 0)
    {
        if (rest || l == row)
        {
            if (*count == *len)
            {
                unsigned int *ptr = realloc(*nums, sizeof(unsigned int) * (*len * 2));
                if (NULL == ptr)
                {
                    return 2;
                }
                *nums = ptr;
            }
            *(*nums + (*count)++) = number;
        }

        return 0;
    }



    if (rest || l == row)
    {
        l_ones_in_row(k, l, nums, count, number & ~(1 << pos), 0, pos - 1, 1, len);

        l_ones_in_row(k, l, nums, count, number, row + 1, pos - 1, rest, len);
    }
    else
    {
        l_ones_in_row(k, l, nums, count, number & ~(1 << pos), 0, pos - 1, rest, len);
        
        l_ones_in_row(k, l, nums, count, number, row + 1, pos - 1, rest, len);
    }

    return 0;
}


int count_one_row(int k, int l)
{
    if (k - l <= 1)
    {
        return 1;
    }

    if (l == 1)
    {
        return (1 << (k - 2)) * (0);
    }

    return (1 << (k - l - 1)) + (k - 2 - l) * (1 << (k - 3 - l)) + (1 << (k - 2 - l)) - (k - l - 2 != 0);
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