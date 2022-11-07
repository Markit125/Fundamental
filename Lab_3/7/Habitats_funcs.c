#include "list.c"
#include <stdio.h>
#include <stdlib.h>


int read_file(FILE *f, List *list, int *line_corrupt)
{
    int err = 0, n, position = 0, counter = 0, it = 0, len = START_LEN;
    char *in = (char *) malloc(sizeof(char) * len);
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
            if (it == len)
            {
                len *= 2;
                char *ptr = realloc(in, sizeof(char) * len);
                if (ptr == NULL)
                {
                    free(in);
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