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


int read_message(char *text, int len)
{
    int it = 0;
    int error = 0;
    char c;

    while ((c = getchar()) != EOF)
    {
        if (it == len)
        {
            len *= 2;
            char *ptr = realloc(text, sizeof(char) * len);
            if (ptr == NULL)
            {
                return 1;
            }
            
            text = ptr;
        }

        if (is_space(c) || is_comma(c))
        {
            error = 2;
        }
        else if (is_newline(c))
        {
            break;
        }

        *(text + it++) = c;
    }

    *(text + it) = '\0';

    return error;
}


int check_message(char *msg)
{
    char *ptr = msg;

    while (*ptr)
    {
        if (is_space(*(ptr++)) || is_comma(*(ptr++)))
        {
            return 1;
        }
    }

    return 0;
}


int is_integer(char *arg, int *num, int grater_or_equal)
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

    if (*num < grater_or_equal)
    {
        return 0;
    }

    return 1;
}
