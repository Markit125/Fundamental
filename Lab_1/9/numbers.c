#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


int power(char base, int extent)
{
    int ans = 1;
    int factor = base > 'A' ? base - 'A' + 10 : base - '0';
    int i;
    for (i = 0; i < extent; ++i)
    {
        ans *= factor;
    }
    
    return ans;
}


int to_decimal(char *number, int base)
{
    int answer = 0;
    int sign = 1;
    char *ptr = number;
    
    if (*(ptr--) == '-')
    {
        sign = -1;
        ++ptr;
    }

    while (*(++ptr))
    {
        answer = answer * base + (*ptr > '9' ? *ptr - 'A' + 10 : *ptr - '0');
    }
    answer *= sign;

    return answer;
}


char *from_decimal(int number, char *answer, int base, int size)
{
    char *it = answer + size - 1;
    *(it--) = '\0';

    int negative = 0;
    if (number < 0)
    {
        number *= -1;
        negative = 1;
    }

    int rem;
    while (number != 0)
    {
        rem = number % base;
        *(it--) = rem > 9 ? rem + 'A' - 10 : rem + '0';
        number /= base;
    }

    if (negative)
    {
        *(it--) = '-';
    }


    return it + 1;
}


int compare_abs_values(char *max, char *num)
{
    char *it_max = max;
    char *it_num = num;
    if (*it_num == '-')
    {
        ++it_num;
    }

    int renew = 0;

    while (1)
    {
        if (*it_max == '\0' && *it_num == '\0')
        {
            break;
        }
        else if (*it_max == '\0' && *it_num != '\0')
        {
            renew = 1;
            break;
        }
        else if (*it_max != '\0' && *it_num == '\0')
        {
            renew = 0;
            break;
        }
        else if (!renew)
        {
            if (*it_max < *it_num)
            {
                renew = 1;
            }
        }

        ++it_max;
        ++it_num;
    }
    
    if (renew)
    {
        it_num = num;
        int i = 0;
        while (*it_num != '\0')
        {
            *(max + i) = *it_num;
            ++it_num;
            ++i;
        }
        *(max + i) = '\0';
    }

    return 0;
}