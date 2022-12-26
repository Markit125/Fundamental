#include "process.c"
#include <stdio.h>


int read_files(int argc, char **argv)
{
    if (argc == 1) {
        return 1;
    }

    if (argc > 2)
    {
        return 4;
    }


    for (int i = 1; i < argc; ++i)
    {
        FILE *f = fopen(*(argv + i), "r");
        if (NULL == f) {
            return 2;
        }

        FILE *fout;
        char c = getc(f);
        char prev_c;
        int it = 0, err_it = -1;
        int expression_number = 0;
        int len = START_LEN;
        char *sym = (char *) malloc(sizeof(char) * len);
        if (sym == NULL)
        {
            return 3;
        }



        while (1)
        {
            if (!is_space(c))
            {
                if (it == len - 2)
                {
                    char *ptr = (char *) realloc(sym, sizeof(char) * (len * 2));
                    if (ptr == NULL)
                    {
                        return 3;
                    }
                    len *= 2;

                    sym = ptr;
                }
                
                *(sym + it++) = c;

                if (!permitted(c) && err_it == -1)
                {
                    err_it = it;
                }
            }
            else if (c == '\n' || c == EOF)
            {
                if (err_it != -1)
                {
                    if (fout == NULL)
                    {
                        fout = fopen("out.txt", "w");
                        if (fout == NULL)
                        {
                            return 3;
                        }
                    }
                    write_error(fout, err_it, sym, expression_number, mis_unknown);
                    return 5;
                }

                if (c == EOF && prev_c == '\n')
                {
                    break;
                }
                
                *(sym + it++) = '#';
                *(sym + it) = '\0';
                it = 0;
                if (fout == NULL)
                {
                    fout = fopen("out.txt", "w");
                    if (fout == NULL)
                    {
                        return 3;
                    }
                }

                int err = process(fout, sym, expression_number++);
                if (err && err != 4)
                {
                    free(sym);
                    return err;
                }

                if (c == EOF)
                {
                    break;
                }
            }

            prev_c = c;
            c = getc(f);
        }

        free(sym);
    }

    return 0;
}