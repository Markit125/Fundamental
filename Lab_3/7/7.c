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
    if (NULL == list)
    {
        return 11;
    }

    int err, line_corrupt = -1, len = START_LEN;
    err = read_file(f, list, &line_corrupt, &len);
    fclose(f);
    if (err == 1)
    {
        printf("There is not enough memory!\n");
        clear_list(list);
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
        clear_list(list);
        return 5;
    }

    print_list(list);

    char *out = "new.txt";

    FILE *f_out = fopen(out, "r+");
    if (NULL == f_out)
    {
        printf("Cannot create new file!\n");
        return 7;
    }

    err = write_to_file(f_out, list);
    if (err == 1)
    {
        printf("New file does not exists!\n");
        return 3;
    }
    else if (err == 2)
    {
        printf("List does not exists!\n");
        return 10;
    }


    int by;
    int cur_len = START_LEN, action, attempts = 3, i;
    List *found;

    char *num = (char *) malloc(sizeof(char) * cur_len);
    if (NULL == num)
    {
        printf("There is not enough memory!\n");
        return 11;
    }
    
    while (attempts)
    {
        printf("To find enter 1\nTo edit enter 2\nTo go through enter 3:\n");

        err = get_input(num, &cur_len);
        if (err == 1)
        {
            printf("There is not enough memory!\n");
            free(num);
            return 1;
        }
        

        err = validate(num, &action, 1, 3);
        if (err)
        {
            printf("Try again\n");
            --attempts;
        }
        else if (action == 1)
        {
            // find
            attempts = 3;
            while (attempts)
            {
                printf("Find by\n1 - last name\n2 - name\n3 - middle name\n4 - birth date\n5 - gender\n6 - income");
                err = get_input(num, &cur_len);
                if (err == 1)
                {
                    break;
                }

                err = validate(num, &action, 1, 6);
                if (err)
                {
                    printf("Try again\n");
                    --attempts;
                    continue;
                }

                printf("Enter the value:\n");
                err = get_input(num, &cur_len);
                if (err == 1)
                {
                    break;
                }

                found = (List *) malloc(sizeof(List));
                if (NULL == found)
                {
                    return 11;
                }

                err = find_habs(list, by, found, len);

                break;
            }
            if (err == 1)
            {
                printf("There is not enough memory!\n");
                free(num);
                return 1;
            }
        }
        else if (action == 2)
        {
            // sort
            attempts = 3;
            while (attempts)
            {
                printf("Choose edit option:\n1 - add\n2 - delete\n");
                err = get_input(num, &cur_len);
                if (err == 1)
                {
                   printf("There is not enough memory!\n");
                    free(num);
                    break;
                }

                err = validate(num, &action, 1, 2);
                if (err)
                {
                    printf("Try again\n");
                    --attempts;
                    continue;
                }

                if (action == 1)
                {
                    add_habitat(list);
                }
                else
                {
                    print_list(list, 1);
                    remove_habitat(list);
                }
                
                break;
            }
        }
        else
        {
            break;
        }
    }
    free(num);

    



    clear_list(list);

    return 0;
}