#include <stdio.h>
#include <stdlib.h>


int is_number_character(char *arg)
{
    int n;
    return (sscanf(arg, "%d", &n) == 1);
}


int exclude_numbers(FILE *in, FILE *out)
{
    char c;
    while ((c = fgetc(in)) != EOF)
    {
        if (!is_number_character(&c))
        {
            fprintf(out, "%c", c);
        }
    }

    return 0;
}