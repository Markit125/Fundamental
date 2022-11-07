#include <stdio.h>
#include <stdlib.h>

#include "Habitats_funcs.c"


int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("There are too many arguments!\n");
        return 6;
    }

    if (argc < 2)
    {
        printf("You should pass the path to file!\n");
        return 2;
    }

    FILE *f = fopen(argv[1], "r");
    if (NULL == f)
    {
        printf("Such file does not exists!\n");
        return 3;
    }

    
    List *list = (List *) malloc(sizeof(List));

    int err, line_corrupt = -1;
    err = read_file(f, list, &line_corrupt);
    if (err == 1)
    {
        printf("There is not enough memory!\n");
        return 1;
    }

    else if (err >= 4)
    {
        printf("File is corrupted!\nWrong ");
        switch (err)
        {
            case 4:
                printf("Last name");
                break;
            case 5:
                printf("Name");
                break;
            case 6:
                printf("Middle name");
                break;
            case 7:
                printf("Birth date");
                break;
            case 8:
                printf("Gender");
                break;
            case 9:
                printf("Income");
                break;
            default:
                printf("Something...");
        }
        printf(" at the line %d\n", line_corrupt);
        return 5;
    }

    print_list(list);






    return 0;
}