#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "numberizm.c"

#define NUM_LEN 10


int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("There is no name of file!\n");
        return 1;
    }

    if (argc > 2)
    {
        printf("Too many arguments!\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("There is no such file!\n");
        return 1;
    }

    FILE *out = fopen("out.txt", "w+");
    if (out == NULL)
    {
        printf("Cannot create output file!\n");
        return 1;
    }


    char c, _c = ' ';
    c = fgetc(file);

    char *num = malloc(sizeof(char) * NUM_LEN);
    int it = 0;
    int num_len = NUM_LEN;


    while (_c != EOF)
    {
        if (c != ' ' && c != '\n' && c != '\t' && c != EOF)
        {
            if (it == num_len)
            {
                num_len *= 2;
                num = realloc(num, num_len);
            }

            sscanf(&c, "%c", &num[it++]);
        }
        else if (it != 0)
        {
            int success = 0;
            num[it] = '\0';
            it = 0;

            int num_sys;
            if (number_system(&num_sys, num) == 0)
            {
                int num_decimal;

                if (convert_to_decimal(num, num_sys, &num_decimal) == 0)
                {
                    fprintf(out, "%s %d %d\n", num, num_sys, num_decimal);
                    success = 1;
                }
            }

            if (!success)
            {
                printf("Error\n");
                fclose(file);
                fclose(out);
                return -1;
            }
        }

        _c = c;
        c = fgetc(file);
    }

    fclose(file);
    fclose(out);

    printf("Success\n");

    return 0;
}