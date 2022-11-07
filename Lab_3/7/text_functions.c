#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


int is_date(char *str, int *day, int *month, int *year)
{
    if (strlen(str) != 10)
    {
        return 0;
    }

    if (*(str + 2) != '.' || *(str + 5) != '.')
    {
        return 0;
    }

    char day_str[3], month_str[3], year_str[5];
    *(day_str + 2) = '\0';
    *(month_str + 2) = '\0';
    *(year_str + 4) = '\0';
    // char *day_str = (char *) malloc(sizeof(char) * 2);
    // if (NULL == day_str)
    // {
    //     return 0;
    // }
    // char *month_str = (char *) malloc(sizeof(char) * 2);
    // if (NULL == month_str)
    // {
    //     free(day_str);
    //     return 0;
    // }
    // char *year_str = (char *) malloc(sizeof(char) * 4);
    // if (NULL == year_str)
    // {
    //     free(day_str);
    //     free(month_str);
    //     return 0;
    // }

    strncpy(day_str, str, 2);
    strncpy(month_str, str + 3, 2);
    strncpy(year_str, str + 6, 4);

    if (!is_integer_range(month_str, month, 1, 12))
    {
        // free(day_str);
        // free(month_str);
        // free(year_str);
        return 0;
    }
    if (!is_integer_range(year_str, year, 2000, 2022))
    {
        // free(day_str);
        // free(month_str);
        // free(year_str);
        return 0;
    }

    int count_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    *(count_days + 1) += (*year % 4 == 0 && *year % 100) ? 1 : 0;

    if (!is_integer_range(day_str, day, 1, *(count_days + *month - 1)))
    {
        // free(day_str);
        // free(month_str);
        // free(year_str);
        return 0;
    }


    // free(day_str);
    // free(month_str);
    // free(year_str);

    return 1;
}


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


int is_double(char *str, double *to, int grater_or_equal)
{
    if (is_number(str))
    {
        *to = atof(str);
        if (*to >= grater_or_equal)
        {
            return 1;
        }
    }
    
    return 0;
}


int get_input(char *num, int *cur_len)
{
    char c = getchar();
    int it = 0;
    while (!is_space(c) && !is_newline(c) || it == 0)
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


int validate(char *str_num, int *n, int from, int to)
{
    if (is_integer_range(str_num, n, from, to))
    {
        if (n > 0)
        {
            return 0;
        }
    }

    return 1;
}