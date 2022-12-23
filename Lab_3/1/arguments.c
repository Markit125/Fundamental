#include <stdio.h>
#include <stdlib.h>

#define START_LEN 4

int is_integer(char* arg)
{
    char *ptr = arg;
    
    if (*arg == '-')
    {
        ++ptr;
    }

    while (*ptr)
    {
        if ('0' > *ptr || *ptr > '9')
        {
            return 0;
        }
        ++ptr;
    }
    if (ptr == arg)
    {
        return 0;
    }
    
    return 1;
}


int get_len(int n)
{
    int bit = 0;
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


int get_int(int *n)
{
    int len = START_LEN;
    char *num = (char *) malloc(sizeof(char) * len);
    if (NULL == num)
    {
        return 1;
    }

    int it = 0;
    char c;
    while ((c = getchar()) != '\n')
    {
        if (it == len - 1)
        {
            char *ptr = realloc(num, sizeof(char) * len * 2);
            if (NULL == ptr)
            {
                free(num);
                return 2;
            }

            len *= 2;
            num = ptr;
        }

        *(num + it++) = c;
    }
    *(num + it) = '\0';
    
    if (!is_integer(num))
    {
        free(num);
        return -1;
    }

    *n = atoi(num);
    free(num);

    return 0;
}