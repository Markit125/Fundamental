#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_work.c"


int is_number(char const* arg)
{
    int n;
    return (sscanf(arg, "%d", &n) == 1);
}

int is_flag_correct(char const* arg)
{
    if (arg[0] == '-' || arg[0] == '/')
    {
        if (strlen(arg) == 2 || (strlen(arg) == 3 && arg[2] == 'n'))
        {
            return 1;
        }
    }
    return 0;
}


int main(int argc, char *argv[])
{
    if (argc > 4)
    {
        printf("Too many arguments!\n");
    }

    if (argc == 1)
    {
        printf("No agruments!\n");
        return 1;
    }

    if (!is_flag_correct(argv[2]))
    {
        printf("Flag is incorrect!\n");
        return 1;
    }

    char flag;
    char *output_file_name;
    if (argv[1][1] == 'n')
    {
        if (argc != 4)
        {
            printf("Wrong number of arguments!\n");
            return 1;
        }
        flag = argv[2][2];
        output_file_name = argv[3];
    }

    else
    {
        if (argc != 3)
        {
            printf("Wrong number of arguments!\n");
            return 1;
        }
        // output_file = malloc(sizeof(char) * (4 + strlen(argv[2])));

        flag = argv[2][1];
        output_file_name = "out_";
        strcat(output_file_name, argv[2]);
    }

    FILE *in_file = fopen(argv[2], "r");
    FILE *out_file = fopen(output_file_name, "w");

    if (in_file == NULL)
    {
        printf("Input file isn't exists!\n");
        return 1;
    }

    if (out_file == NULL)
    {
        printf("Output file isn't exists!\n");
        return 1;
    }


    if (flag == 'd')
    {
        if (exclude_numbers(in_file, out_file) == 0)
        {
            
        }
        else
        {
            printf("Error\n");
            return -1;
        }
    }

    else if (flag == 'i')
    {
    
    }

    else if (flag == 's')
    {
    
    }

    else if (flag == 'a')
    {
    
    }

    else if (flag == 'f')
    {
    
    }

    

    return 0;
}
