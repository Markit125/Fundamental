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
        if (strlen(arg) == 2 || (strlen(arg) == 3 && arg[1] == 'n'))
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
        output_file_name = (char*) malloc(sizeof(char) * (4 + strlen(argv[2]) + 1));

        sscanf("out_", "%s", output_file_name);
        sscanf(argv[2], "%s", output_file_name + 4);
    }

    FILE *in_file = fopen(argv[2], "r");
    FILE *out_file = fopen(output_file_name, "w");
    free(output_file_name);

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
