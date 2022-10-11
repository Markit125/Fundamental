#include <stdio.h>
#include "transform.c"


int is_flag(char *arg)
{
    if (str_len(arg) != 2)
    {
        return 0;
    }
    if ((arg[0] == '/' || arg[0] == '-')
         && arg[1] <= 'z' && arg[1] >= 'a')
    {
        return 1;
    }

    return 0;
}


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Not enough arguments!\n");
        return 1;
    }

    char *str = argv[1];
    char *flag = argv[2];
    if (!is_flag(flag++))
    {
        printf("Wrong flag!\n");
        return 1;
    }

    if (*flag != 'c' && argc > 3)
    {
        printf("Too many arguments!\n");
        return 1;
    }


    int len = str_len(str);

    if (*flag == 'l')
    {
        printf("%d", len);
    }
    else if (*flag == 'r')
    {
        char *reversed = malloc(sizeof(char) * (len + 1));
        if (reversed == NULL)
        {
            printf("Not enougn memory!\n");
            return 1;
        }

        str_reverse(str, reversed, len);
        printf("%s", reversed);
        free(reversed);
    }
    else if (*flag == 'u')
    {
        char *up_odd = malloc(sizeof(char) * (len + 1));
        if (up_odd == NULL)
        {
            printf("Not enougn memory!\n");
            return 1;
        }

        upper_odd(str, up_odd);
        printf("%s", up_odd);
        free(up_odd);
    }
    else if (*flag == 'n')
    {
        char *sorted = malloc(sizeof(char) * (len + 1));
        str_sort(str, sorted, len);
        printf("%s", sorted);
        free(sorted);
    }
    else if (*flag == 'c')
    {
        if (argc != 4)
        {
            printf("Wrong count of arguments!\n");
            return 1;
        }
        char *united = malloc(sizeof(char) * (len + 1 + str_len(argv[3])));
        str_concat(str, argv[3], united);
        printf("%s", united);
        free(united);
    }

    printf("\n");

    return 0;
}