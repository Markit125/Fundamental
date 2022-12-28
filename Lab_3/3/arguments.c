#include <string.h>


int is_flag(char *arg)
{
    if (strlen(arg) != 2)
    {
        return 0;
    }

    if (*arg != '/' && *arg != '-')
    {
        return 0;
    }

    return 1;
}


int is_new_line(char c)
{
    return c == '\n';
}


int is_space(char c)
{
    return c == ' ' || c == '\t';
}


int is_number_positive(char *arg)
{
    char *ptr = arg;
    while (*ptr)
    {
        if (!('0' <= *ptr && *ptr <= '9'))
        {
            return 0;
        }
        ++ptr;
    }

    return 1;
}


int latin_string(char *arg)
{
    char *ptr = arg;
    while (*ptr)
    {
        if (!('a' <= *ptr && *ptr <= 'z') && !('A' <= *ptr && *ptr <= 'Z'))
        {
            return 0;
        }
        ++ptr;
    }

    return 1;
}


int is_float_positive(char *arg)
{
    int dot = 0;
    char *ptr = arg;
    while (*ptr)
    {
        if (!('0' <= *ptr && *ptr <= '9') && (*ptr != '.'))
        {
            return 0;
        }
        if (*ptr == '.')
        {
            if (dot > 1)
            {
                return 0;
            }
            ++dot;
        }
        ++ptr;
    }

    return 1;
}