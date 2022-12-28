#include <stdlib.h>
#include <stdio.h>
#include "arguments.c"
#include "employee.h"
#include "exits.h"


int get_note(FILE *f, char *line);


int add_employees(employee **employees, FILE *f)
{
    
    if (NULL == employees)
    {
        *employees = (employee *) malloc(sizeof(employee) * START_COUNT);
        if (NULL == *employees)
        {
            return NO_MEMORY;
        }
    }

    char *line;
    int err;
    int count = 0;
    int it = 0;
    char *c;
    int len = START_LEN;
    char *field;

    while (1)
    {
        err = get_note(f, line);
        count = 0;
        it = 0;
        c = line - 1;
        field = (char *) malloc(sizeof(char) * len);
        if (NULL == field)
        {
            return NO_MEMORY;
        }


        
        while (*(++c) != '\0')
        {
            if (is_space(*c))
            {
                *(field + it) = '\0';
                
                switch (count)
                {
                    case 1:
                        if (!is_number_positive(field))
                        {
                            free(field);
                            return INVALID_ID;
                        }
                        (*employees + count++)->id = atoi(field);

                        break;
                    case 2:
                        if (!latin_string(field))
                        {
                            free(field);
                            return INVALID_NAME;
                        }
                        strcpy((*employees + count++)->name, field);
                    
                        break;
                    case 3:
                        if (!latin_string(field))
                        {
                            free(field);
                            return INVALID_SURNAME;
                        }
                        strcpy((*employees + count++)->surname, field);

                        break;
                    default:
                        free(field);
                        return INVALID_NOTE;
                }
                continue;
            }

            *(field + it++) = *c;

            if (it == len - 1)
            {
                char *ptr = realloc(field, sizeof(char) * (len * 2));
                if (NULL == ptr)
                {
                    free(field);
                    return NO_MEMORY;
                }
                len *= 2;
                field = ptr;
            }
        }

        if (!is_float_positive(field) || count != 4)
        {
            free(field);
            return INVALID_SALARY;
        }

        (*employees + count)->salary = atof(field);
    }

    free(field);
    
    return SUCCESS;
}


int get_note(FILE *f, char *line)
{
    if (NULL == f)
    {
        return FILE_NOT_FOUND;
    }

    int len;
    char c, c_prev = ' ';
    int it = 0;

    if (NULL == line)
    {
        len = START_LEN;
        line = (char *) malloc(sizeof(char) * len);
    }
    else
    {
        len = strlen(line);
    }

    while (!is_new_line(c = getc(f)))
    {
        if (c == EOF)
        {
            break;
        }

        if (is_space(c) && is_space(c_prev))
        {
            c_prev = c;
            continue;
        }

        if (it == len - 1)
        {
            char *ptr = realloc(line, sizeof(char) * (len * 2));
            if (NULL == ptr)
            {
                free(line);
                return NO_MEMORY;
            }
            len *= 2;
            line = ptr;
        }
        
        *(line + it++) = c;
        c_prev = c;
    }

    *(line + it++) = '\0';
    if (it < len)
    {
        char *ptr = realloc(line, sizeof(char) * it);
        if (NULL == ptr)
        {
            free(line);
            return NO_MEMORY;
        }
        line = ptr;
    }

    return SUCCESS;
}