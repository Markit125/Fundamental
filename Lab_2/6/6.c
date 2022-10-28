#include <stdio.h>
#include <stdarg.h>


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


int get_table(char *str, int tab[], int size)
{
    tab[0] = 0;

    if (size < 2)
    {
        return 1;
    }

    int index = 0;

    int i = 1;
    while (i < size)
    {
        if (str[i] != str[index])
        {
            if (index != 0)
            {
                index = tab[tab[index]];
            }
            else
            {
                ++i;
            }
            
            continue;
        }

        if (str[i] == str[index])
        {
            tab[i] = index + 1;
            ++index;
            ++i;
            continue;
        }
    }

    return 0;
}


int kmp(int tab[], char *str, FILE *f, int size)
{
    int index = 0;

    char c = fgetc(f);
    int it = 0;


    while (c != EOF)
    {
        if (c == str[it])
        {
            ++it;
        }
        else if (it != 0)
        {
            it = tab[it - 1];
            continue;
        }
        ++index;

        if (it == size - 1)
        {
            return index - it;
        }

        c = fgetc(f);
    }


    return -1;
}


int find_substring(char *sub, int count, ...)
{
    va_list ap;
    va_start(ap, count);

    int size = str_len(sub);
    int tab[size];
    get_table(sub, tab, size);

    int i;
    for (i = 0; i < count; ++i)
    {
        FILE *f = fopen(va_arg(ap, char *), "r");

        if (f == NULL)
        {
            printf("There is not such file!\n");
            return 1;
        }

        int index = kmp(tab, sub, f, size);
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
            printf("%c", sub[j]);
        } printf("\n\n");
    }

    return 0;
}


int main()
{
    char *substing = "ababaaba";

    find_substring(substing, 3, "test.txt", "test2.txt", "test3.txt");
}