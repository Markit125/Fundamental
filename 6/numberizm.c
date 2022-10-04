#include <ctype.h>


int number_system(int *num_sys, char *number)
{
    char *c, max_num = '0';
    for (c = number; *c != '\0'; ++c)
    {
        *c = toupper(*c);
        if (*c > max_num)
        {
            max_num = *c;
        }
    }
    *num_sys = max_num > '9' ? max_num - 'A' + 10: max_num - '0';
    ++(*num_sys);
    
    return 0;
}


int convert_to_decimal(char *number, int base, int *dec_num)
{
    *dec_num = 0;

    char *c;
    for (c = number; *c != '\0'; ++c)
    {
        *c = toupper(*c);
        *dec_num = *dec_num * base + (*c > '9' ? *c - 'A' + 10 : *c - '0');
    }

    return 0;
}