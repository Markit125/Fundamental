#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 10


int IsNumber(char *arg)
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


int IsInteger(char *arg, int *num)
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


int Validate(char *str_num, int *n)
{
    if (IsInteger(str_num, n))
    {
        if (n > 0)
        {
            return 0;
        }
    }

    return 1;
}


int IsSpace(char c)
{
    return c == '\n' || c == ' ' || c == '\t' || c == EOF;
}


int GetInput(char *num, int *cur_len)
{
    char c = getchar();
    int it = 0;
    while (!IsSpace(c) || it == 0)
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


int Permitted(char c)
{
    return  '0' <= c && c <= '9' || c == '(' || c == ')' ||
            c == '/' || c == '*' || c == '%' || c == '^' ||
            c == '+' || c == '-';
}


int IsNumSymbol(char c)
{
    return '0' <= c && c <= '9' || c == '.';
}


int StrCopy(char **dest, char *str, int startIt, int it, int *len)
{
    if (NULL == *dest)
    {
        return 1;
    }

    if (*len < strlen(str))
    {
        char *ptr = (char *) realloc(*dest, sizeof(char) * (*len * 2));
        if (NULL == ptr)
        {
            return 1;
        }
        *len *= 2;

        *dest = ptr;
    }

    int i = startIt;
    int j = 0;
    while (*(str + i) != '\0' && i < it)
    {
        *(*dest + j++) = *(str + i++);
    }

    *(*dest + j - 1) = '\0';

    // if (i != it)
    // {
    //     char *ptr = realloc(*dest, sizeof(char) * (j + 1));
    //     if (NULL == ptr)
    //     {
    //         return 1;
    //     }

    //     *dest = ptr;
    // }
    
    return 0;
}