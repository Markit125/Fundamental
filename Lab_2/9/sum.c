#include <stdarg.h>
int str_len(char *str)
{
    int len = 0;
    char *ptr = str;
    while (*(ptr++))
    {
        ++len;
    }

    return len;
}


int sum_of_two(char *sum, char *num, int base)
{
    int len_n = str_len(num);
    char *ptr = sum + str_len(sum) - 1;
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


char *sum_of_nums(char *answer, int length, int base, int count, ...)
{
    char *ptr = answer + length - 1;
    *(ptr--) = '\0';
    int i;
    for (i = 0; i < length; ++i)
    {
        *(ptr--) = '0';
    }
    ptr = answer + length - 1;

    va_list ap;
    va_start(ap, count);

    char *num;
    for (i = 0; i < count; ++i)
    {
        num = va_arg(ap, char *);
        sum_of_two(answer, num, base);
    }
    va_end(ap);

    ptr = answer;
    while (*ptr == '0')
    {
        ++ptr;
    }

    return ptr;
}