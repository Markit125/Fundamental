#include <stdio.h>
#include <stdlib.h>


int is_space(char c)
{
    return c == ' ' || c == '\t';
}


int is_comma(char c)
{
    return c == ',';
}


int is_newline(char c)
{
    return c == '\n';
}


int is_integer_range(char *arg, int *num, int grater_or_equal, int less_or_equal)
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

    if (*num < grater_or_equal || less_or_equal < *num)
    {
        return 0;
    }

    return 1;
}


int is_latin(char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}


int is_right_string(char *str, int flag)
{
    char *ptr = str;

    while (*ptr)
    {
        if (is_space(*ptr) || is_comma(*ptr))
        {
            return 0;
        }

        if (flag == 1 && !is_latin(*ptr))
        {
            return 0;
        }
        ptr++;
    }

    return 1;
}