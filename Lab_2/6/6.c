#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 5
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


int find_substring(int ***results, char *sub, int count, ...)
{
    va_list ap;
    va_start(ap, count);

    int size = str_len(sub);
    int *tab = (int *) malloc(sizeof(int) * size);
    if (NULL == tab)
    {
        return 1;
    }
    
    get_table(sub, &tab, size);

    int i;
    for (i = 0; i < count; ++i)
    {
        *(*results + i) = (int *) malloc(sizeof(int) * COUNT);
        FILE *f = fopen(va_arg(ap, char *), "r");
        if (f == NULL)
        {
            free(tab);
            return 1;
        }

        int index;
        if (strcmp(sub, "") == 0)
        {
            index = 0;    
        }
        else
        {
            index = kmp(tab, sub, f, size);
        }
        *(*(*results + i) + 1) = index;

        if (index == -1)
        {
            continue;
        }
        
        
    }
    free(tab);

    return 0;
}


int print_out(int ***results, char *sub, int count, ...)
{
    va_list ap;
    va_start(ap, count);
    FILE *f = fopen(va_arg(ap, char *), "r");
    if (f == NULL)
    {
        printf("There is not such file!\n");
        return 1;
    }

    int size = strlen(sub);
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


int main()
{
    int count = 3;

    int **results = (int **) malloc(sizeof(int *) * count);
    if (NULL == results)
    {
        return 1;
    }

    char *substring = "ca";

    find_substring(&results, substring, count, "test.txt", "test2.txt", "test3.txt");

    print_out(&results, count, "test.txt", "test2.txt", "test3.txt");

    

}