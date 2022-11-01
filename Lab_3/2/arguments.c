#include <stdio.h>
#include <stdlib.h>

#define LEN 10


int is_number(char *arg)
{
    char *ptr = arg;
    int dot = 0;

    if (*ptr == '-')
    {
        ++ptr;
    }

    while (*ptr)
    {
        if (*ptr == '.')
        {
            if (dot > 0)
            {
                return 0;
            }
            ++dot;
            
        }
        else if ('0' > *ptr || *ptr > '9')
        {
            return 0;
        }
        ++ptr;
    }

    return 1;
}


int is_integer(char *arg, int *num)
{
    char *ptr = arg;

    *num = 0;
    int factor = 1;
    
    if (*ptr == '-')
    {
        factor = -1;
        ++ptr;
    }

    while (*ptr)
    {
        if ('0' <= *ptr && *ptr <= '9')
        {
            *num = *num * 10 + (*ptr - '0');
        }
        else
        {
            return 0;
        }
        ++ptr;
    }
    *num *= factor;

    return 1;
}


int validate(char *str_num, int *n)
{
    if (is_integer(str_num, n))
    {
        if (n > 0)
        {
            return 0;
        }
    }

    return 1;
}


int is_space(char c)
{
    return c == '\n' || c == ' ' || c == '\t' || c == EOF;
}


int get_input(char *num, int *cur_len)
{
    char c = getchar();
    int it = 0;
    while (!is_space(c) || it == 0)
    {
        if (it == *cur_len)
        {
            *cur_len *= 2;
            char *ptr = realloc(num, *cur_len);
            if (ptr == NULL)
            {
                return 1;
            }

            num = ptr;
        }

        *(num + it++) = c;
        c = getchar();
    }
    *(num + it) = '\0';

    return 0;
}