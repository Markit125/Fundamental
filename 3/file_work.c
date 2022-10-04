#include <ctype.h>
#include <stdio.h>


int is_number_character(char c)
{
    int n;
    return (sscanf(&c, "%d", &n) == 1);
}

int is_letter_character(char c)
{
    return 'a' <= c && c <= 'z' ||
           'A' <= c && c <= 'Z';
}

int is_specific_symbol(char c)
{
    return !is_number_character(c) && !is_letter_character(c) && c != ' ';
}



int exclude_numbers(FILE *in, FILE *out)
{
    char c;
    while ((c = fgetc(in)) != EOF)
    {
        if (!is_number_character(c))
        {
            fputc(c, out);
        }
    }

    return 0;
}

int count_of_characters(FILE *in, FILE *out)
{
    char c, c_prev;
    int counter = 0;
    while ((c = fgetc(in)) != EOF)
    {
        if (c == '\n')
        {
            fprintf(out, "%d\n", counter);
            counter = 0;
        }

        if (is_letter_character(c))
        {
            ++counter;
        }
        c_prev = c;
    }
    if (c_prev != '\n')
    {
        fprintf(out, "%d\n", counter);
    }

    return 0;
}

int specific_symbols(FILE *in, FILE *out)
{
    char c, c_prev;
    int counter = 0;
    while ((c = fgetc(in)) != EOF)
    {
        if (c == '\n')
        {
            fprintf(out, "%d\n", counter);
            counter = 0;
        }

        if (is_specific_symbol(c))
        {
            ++counter;
        }
        c_prev = c;
    }
    if (c_prev != '\n')
    {
        fprintf(out, "%d\n", counter);
    }

    return 0;
}

int non_numbers_to_ascii(FILE *in, FILE *out)
{
    char c;
    while ((c = fgetc(in)) != EOF)
    {
        if (!is_number_character(c))
        {
            fprintf(out, "%d", c);
        }
        else
        {
            fputc(c, out);
        }
    }

    return 0;
}

int lexems_changing(FILE *in, FILE *out)
{
    char c, c_prev;
    int five_counter = 0;
    int two_counter = 0;

    while ((c = fgetc(in)) != EOF)
    {
        if (c == '\n' || c == ' ')
        {
            if (two_counter)
            {
                two_counter = 0;
            }
            else if (five_counter == 4)
            {
                five_counter = 0;
            }
            else
            {
                ++five_counter;
                ++two_counter;
            }
            fputc(c, out);
            continue;
        }

        if (two_counter)
        {
            c = tolower(c);
        }

        if (five_counter == 4)
        {
            fprintf(out, "%d", c);
        }
        else
        {
            fputc(c, out);
        }

    }

    return 0;
}