#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_work.c"
#include "arguments.c"


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

    if (!is_flag_correct(argv[1]))
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
        
        flag = argv[1][2];
        output_file_name = argv[3];
    }

    else
    {
        if (argc != 3)
        {
            printf("Wrong number of arguments!\n");
            return 1;
        }

        flag = argv[1][1];
        output_file_name = (char *) malloc(sizeof(char) * (4 + strlen(argv[2]) + 1));
        
        char *out = "out_";
        int i = 0;
        while (*out)
        {
            *(output_file_name + i) = *out;
            ++out;
            ++i;
        }

        out = argv[2];
        while (*out)
        {
            *(output_file_name + i) = *out;
            ++out;
            ++i;
        }
    }

    

    FILE *in_file = fopen(argv[2], "r");
    FILE *out_file = fopen(output_file_name, "w");

    if (argc == 3)
    {
        free(output_file_name);
    }

    if (in_file == NULL)
    {
        if (out_file != NULL)
        {
            fclose(out_file);
        }

        printf("Input file doesn't exists!\n");
        return 1;
    }

    if (out_file == NULL)
    {
        fclose(in_file);

        printf("Output file doesn't exists!\n");
        return 1;
    }


    int success = 1;
    
    if (flag == 'd')
    {
        if (exclude_numbers(in_file, out_file) != 0)
        {
            success = 0;
        }
    }

    else if (flag == 'i')
    {
        if (count_of_characters(in_file, out_file) != 0)
        {
            success = 0;
        }
    }

    else if (flag == 's')
    {
        if (specific_symbols(in_file, out_file) != 0)
        {
            success = 0;
        }
    }

    else if (flag == 'a')
    {
        if (non_numbers_to_ascii(in_file, out_file) != 0)
        {
            success = 0;
        }
    }

    else if (flag == 'f')
    {
        if (lexems_changing(in_file, out_file) != 0)
        {
            success = 0;
        }
    }

    else
    {
        printf("There is no such flag!\n");
        success = 0;
    }

    fclose(in_file);
    fclose(out_file);

    if (!success)
    {
        printf("Error\n");
        return -1;
    }
    
    printf("Succeed\n");

    return 0;
}
