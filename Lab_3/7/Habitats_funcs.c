#include "list.c"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define eps 0.000001


int read_file(FILE *f, List *list, int *line_corrupt, int *len)
{
    if (f == NULL)
    {
        return 3;
    }
    if (list == NULL)
    {
        return 9;
    }

    int err = 0, n, position = 0, counter = 0, it = 0;
    char *in = (char *) malloc(sizeof(char) * *len);
    if (NULL == in)
    {
        return 1;
    }

    Habitat *hab = (Habitat *) malloc(sizeof(Habitat));
    if (NULL == hab)
    {
        return 1;
    }

    char c;

    while ((c = fgetc(f)) != EOF)
    {
        if (!is_space(c) && !is_newline(c))
        {
            if (it == *len)
            {
                *len *= 2;
                char *ptr = realloc(in, sizeof(char) * *len);
                if (ptr == NULL)
                {
                    free(in);
                    free(hab);
                    return 1;
                }

                in = ptr;
            }

            *(in + it++) = c;
        }
        else
        {
            *(in + it) = '\0';
            it = 0;
            

            if (is_space(c))
            {
                switch (position)
                {
                    case 0:
                        err = set_last_name(hab, in) == 0 ? 0 : 4;
                        break;
                    case 1:
                        err = set_name(hab, in) == 0 ? 0 : 5;
                        break;
                    case 2:
                        err = set_middle_name(hab, in) == 0 ? 0 : 5;
                        break;
                    case 3:
                        err = set_birth_date(hab, in) == 0 ? 0 : 7;
                        break;
                    case 4:
                        err = set_gender(hab, in) == 0 ? 0 : 8;
                        break;

                }

                if (err)
                {
                    free(in);
                    free(hab);
                    *line_corrupt = counter + 1;
                    return err;
                }

                ++position;
            }
            else
            {
                err = set_income(hab, in) == 0 ? 0 : 9;
                if (err)
                {
                    free(in);
                    free(hab);
                    *line_corrupt = counter + 1;
                    return err;
                }

                ++counter;
                position = 0;

                add(list, hab);


                hab = (Habitat *) malloc(sizeof(Habitat));
                if (NULL == hab)
                {
                    return 1;
                }

            }
        }
    }
    free(hab);
    free(in);

    return 0;
}


int write_to_file(FILE *f, List *list)
{
    if (f == NULL)
    {
        return 1;
    }
    if (list == NULL)
    {
        return 2;
    }

    fseek(f, 0, SEEK_END);
    Node *node = list->first;

    while (node != NULL)
    {
        if (node->habitat != NULL)
        {
            file_print_habitat(f, node->habitat);
        }
        node = node->next;
    }

    return 0;
}


int find_habs(List *list, int by, List *found, int len, char *str)
{
    if (NULL == list)
    {
        return 1;
    }
    if (NULL == found)
    {
        return 2;
    }

    char *in = (char *) malloc(sizeof(char) * len);
    if (NULL == in)
    {
        return 3;
    }

    int not_copy = 1, err = 0, gender;
    char c;
    double income;

    Node *node = list->first;

    while (node != NULL)
    {
        not_copy = 1;
        switch(by)
        {
            case 1:
                not_copy = strcmp(node->habitat->last_name, str);
                break;
            case 2:
                not_copy = strcmp(node->habitat->name, str);
                break;
            case 3:
                not_copy = strcmp(node->habitat->middle_name, str);
                break;
            case 4:
                not_copy = strcmp(node->habitat->birth_date, str);
                break;
            case 5:
                gender = node->habitat->gender;
                c = gender ? 'w' : 'm';

                not_copy = strcmp(&c, str);
                break;
            case 6:
                is_double(str, &income, 0);
                not_copy = fabs(node->habitat->income - income) < eps ? 0 : 1;
                break;
        }

        if (!not_copy)
        {
            add(found, node->habitat);
        }

        node = node->next;
    }

    return 0;
}