#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


#define VIEW_SEEK 5


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


int get_table(char *str, int **tab, int size)
{
    **tab = 0;

    if (size < 2)
    {
        return 1;
    }

    int index = 0;

    int i = 1;
    while (i < size)
    {
        if (*(str + i) != *(str + index))
        {
            if (index != 0)
            {
                index = *(*tab + *(*tab + index));
            }
            else
            {
                ++i;
            }
            continue;
        }

        if (*(str + i) == *(str + index))
        {
            *(*tab + i) = index + 1;
            ++index;
            ++i;
            continue;
        }
    }

    return 0;
}


int kmp(int *tab, char *str, FILE *f, int size)
{
    int i = 0;
    int j = 0;
    char c = fgetc(f);
    while (c != EOF)
    {
        if (*(str + j) == c)
        {
            i++;
            j++;
            c = fgetc(f);
        }

        if (j == size)
        {
            return i - size;
        }
        else if (*(str + j) != c)
        {
            if (j == 0)
            {
                i++;
                c = fgetc(f);
            }
            else
            {
                j = *(tab + j - 1);
            }
        }
    }

    return -1;
}


int find_substring(char *sub, int count, ...)
{
    va_list ap;
    va_start(ap, count);

    int size = str_len(sub);
    int *tab = (int *) malloc(sizeof(int) * size);
    
    get_table(sub, &tab, size);

    int i;
    for (i = 0; i < count; ++i)
    {
        FILE *f = fopen(va_arg(ap, char *), "r");
        if (f == NULL)
        {
            printf("There is not such file!\n");
            free(tab);
            return 1;
        }

        int index = kmp(tab, sub, f, size);
        if (index == -1)
        {
            printf("No matches\n");
            continue;
        }
        
        int seek = (index - VIEW_SEEK > 0) ? (index - VIEW_SEEK) : 0;
        fseek(f, seek, SEEK_SET);




        if (seek > 0)
        {
            printf("...");
        }
        int j = 0;
        char c = fgetc(f);
        while (c != EOF && j < index + size + VIEW_SEEK)
        {
            printf("%c", c);
            c = fgetc(f);
            ++j;
        }

        if (c != EOF)
        {
            printf("...");
        }
        
        printf("\n");
        
        if (seek > 0)
        {
            printf("   ");
        }

        for (j = 0; j < index - seek; ++j)
        {
            printf(" ");
        }

        for (j = 0; j < size; ++j)
        {
            printf("%c", *(sub + j));
        } printf("\n\n");
    }
    free(tab);

    return 0;
}


int main()
{
    char *substing = "ba";

    find_substring(substing, 3, "test.txt", "test2.txt", "test3.txt");
}