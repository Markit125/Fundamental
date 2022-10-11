
#include <ctype.h>
#include <stdlib.h>


int str_len(char *s)
{
    char *ptr = s;
    int length = 0;

    while (*(ptr++))
    {
        ++length;
    }

    return length;
}


int str_reverse(char *s, char *reversed, int len)
{
    char *ptr = s;
    char *ptr_backwards = reversed + len;
    *(ptr_backwards--) = '\0';

    while (*ptr)
    {
        *ptr_backwards-- = *ptr++;
    }

    return 0;
}


int upper_odd(char *s, char *up_odd)
{
    char *ptr = s;
    char *ptr_up = up_odd;

    int i;
    int odd = 1;
    
    while (*ptr)
    {
        if ('a' - 1 < *ptr && *ptr < 'z' + 1 && odd)
        {
            *(ptr_up++) = *(ptr++) + 'A' - 'a';
        }
        else
        {
            *(ptr_up++) = *(ptr++);
        }
        odd = !odd;
    }

    *ptr_up = '\0';

    return 0;
}


int str_sort(char *s, char *sorted, int len)
{
    char *fill = sorted;
    char *letters = malloc(sizeof(char) * len);
    char *other = malloc(sizeof(char) * len);

    char *letter_ptr = letters;
    char *other_ptr = other;

    char *ptr = s;
    int i;
    while (*ptr)
    {
        if ('0' - 1 < *ptr && *ptr < '9' + 1)
        {
            *(fill++) = *(ptr++);
        }
        else if ('a' - 1 < tolower(*ptr) && tolower(*ptr) < 'z' + 1)
        {
            *(letter_ptr++) = *(ptr++);
        }
        else
        {
            *(other_ptr++) = *(ptr++);
        }
    }

    *letter_ptr = '\0';
    *other_ptr = '\0';
    letter_ptr = letters;
    other_ptr = other;

    while (*letter_ptr)
    {
        *(fill++) = *(letter_ptr++);
    }
    free(letters);

    while (*other_ptr)
    {
        *(fill++) = *(other_ptr++);
    }
    free(other);
    
    *fill = '\0';

    return 0;
}


int str_concat(char *s_0, char *s_1, char *united)
{
    char *ptr = united;
    char *ptr_s_0 = s_0;
    char *ptr_s_1 = s_1;

    while (*s_0)
    {
        *(ptr++) = *(s_0++);
    }
    while (*s_1)
    {
        *(ptr++) = *(s_1++);
    }
    *ptr = '\0';

    return 0;
}