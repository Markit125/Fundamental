#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "numbers.c"
#include "arguments.c"

#define START_LEN 5


int is_space(char c)
{
    return c == '\n' || c == ' ' || c == '\t';
}


int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        printf("Too many arguments!\n");
        return 1;
    }

    char *input;
    printf("Enter number system:\n");
    scanf("%s", input);

    if (!is_integer(input))
    {
        printf("You must enter integer number grater than one!\n");
        return 1;
    }
    
    int base = atoi(input);
    char max_in_base = base > 9 ? base - 10 + 'A' : '0' + base;

    if (base < 2 || base > 36)
    {
        printf("Base must be grater than one and lower than 37!\n");
        return 1;
    }

    int cur_len = START_LEN;
    char *num = (char *) malloc(sizeof(char) * START_LEN);
    int it = 0;

    char c, _c;
    char *abs_max = (char *) malloc(sizeof(char) * START_LEN);
    *abs_max = '0';
    *(abs_max + 1) = '\0';

    int wrong_base = 0;

    printf("Enter numbers:\n");
    while (!are_strings_equal(num, "STOP"))
    {
        c = getchar();
        c = toupper(c);

        if (!is_space(c))
        {
            if (cur_len == it)
            {
                cur_len *= 2;
                num = realloc(num, sizeof(char) * cur_len);
                abs_max = realloc(abs_max, sizeof(char) * cur_len);

                if (num == NULL || abs_max == NULL)
                {
                    printf("Not enough memory!\n");
                    return 1;
                }
            }
            if (c >= max_in_base)
            {
                wrong_base = 1;
            }

            *(num + it++) = c;
        }
        else
        {
            *(num + it) = '\0';

            if (wrong_base && !are_strings_equal(num, "STOP"))
            {
                printf("This number doesn't belong to the base! %s\n", num);
                return 1;
            }

            *(num + it) = '\0';
            if (compare_abs_values(abs_max, num) != 0)
            {
                printf("Error\n");
                return -1;
            }
            it = 0;
        }
    }
    free(num);


    if (base > 9)
    {
        abs_max = realloc(abs_max, sizeof(abs_max) * 4);
        if (abs_max == NULL)
        {
            printf("Not enough memory!\n");
            return 1;
        }
    }
    
    int num_dec = to_decimal(abs_max, base);
    
    int i;
    for (i = 9; i < 37; i += 9)
    {
        printf("in base %d: %s\n", i, from_decimal(num_dec, abs_max, i, sizeof(abs_max)));
    }
    free(abs_max);


    printf("\n");

    return 0;
}