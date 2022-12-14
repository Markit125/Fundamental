#include <stdio.h>
#include <stdlib.h>


int get_len(int n)
{
    int bit = 1;
    int len = 0;
    while (bit < 32)
    {
        if ((1 << bit++) & n)
        {
            len = bit;
        }
    }
    return len;
}


int to_two_based(int n, int r, char **new_num)
{
    if (r < 1 || 5 < r)
    {
        return 1;
    }

    int negative = 0;
    if (n < 0)
    {
        n = -n;
        negative = 1;
    }

    int count_bits = get_len(n);
    int len = (count_bits / r) + ((count_bits % r) != 0) + negative;

    *new_num = (char *) malloc(sizeof(char) * len);
    if (new_num == NULL)
    {
        return 1;
    }


    int i;
    int buf_num;
    int pos = len - 1;
    int bit = 0;

    while (bit < count_bits)
    {
        buf_num = 0;

        for (i = 0; i < r; ++i)
        {
            if (bit > 32)
            {
                break;
            }

            if (n & (1 << bit))
            {
                buf_num |= (1 << bit);
            }
            ++bit;
        }

        buf_num = buf_num >> (bit - r);

        *(*new_num + pos--) = buf_num > 9 ? 'A' + buf_num - 10 : '0' + buf_num;
    }

    if (negative) {
        *(*new_num + pos) = '-';
    }

    // printf("%s\n", new_num);

    return 0;
}


int main()
{
    char *new_number;

    int n = 32;
    int r = 5;

    scanf("%d%d", &n, &r);

    int err = to_two_based(n, r, &new_number);

    if (err == 1)
    {
        printf("r must be between 1 and 5 inclusively!\n");
        free(new_number);
        return 2;
    }
    else if (err == 2)
    {
        printf("There is no enough memory!\n");
        free(new_number);
        return 3;
    }
    else
    {
        printf("%s\n", new_number);
    }

    free(new_number);

    return 0;
}