#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int sum_of_two(char *sum, char *num, int base)
{
    int len_n = strlen(num);
    char *ptr = sum + strlen(sum) - 1;
    char *ptr_n = num + len_n - 1;

    int a, b, rem = 0, sm = 0, memory = 0;
    while (len_n--)
    {
        sm = memory;
        a = *ptr > '9' ? *ptr - 'A' + 10 : *ptr - '0';
        b = *ptr_n > '9' ? *ptr_n - 'A' + 10 : *ptr_n - '0';
        sm += a + b;
        
        rem = sm % base;
        *(ptr--) = rem > 9 ? rem + 'A' - 10 : rem + '0';
        memory = sm / base;
        --ptr_n;
    }
    while (memory > 0)
    {
        sm = memory + (*ptr > '9' ? *ptr - 'A' + 10 : *ptr - '0');
        rem = sm % base;
        *(ptr--) = rem > 9 ? rem + 'A' - 10 : rem + '0';
        memory = sm / base;
    }

    return 0;
}


char *sum_of_nums(char *answer, int base, int count, ...)
{

    va_list apa;
    va_start(apa, count);
    char *num = va_arg(apa, char *);

    int len = strlen(num);
    int mx = len;
    int i;
    for (i = 0; i < count - 1; ++i)
    {
        len = strlen(va_arg(apa, char *));
        if (mx < len)
        {
            mx = len;
        }
    }
    len = mx + 2;

    answer = (char *) malloc(sizeof(char) * (len + 1));
    if (NULL == answer)
    {
        return NULL;
    }

    for (i = 0; i < len; ++i)
    {
        *(answer + i) = '0';
    }
    *(answer + len) = '\0';


    va_list ap;
    va_start(ap, count);

    for (i = 0; i < count; ++i)
    {
        num = va_arg(ap, char *);
        sum_of_two(answer, num, base);
    }
    va_end(ap);

    char *ptr = answer;
    i = 0;
    while (*ptr == '0' && i < len - 1)
    {
        ++ptr;
        ++i;
    }

    return ptr;
}
