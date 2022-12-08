#include "process.c"
#include <stdio.h>


int ReadFiles(int argc, const char **argv)
{
    if (argc == 1) {
        return 1;
    }


    for (int i = 1; i < argc; ++i)
    {
        FILE *f = fopen(*(argv + i), "r");
        printf("%s \n", *(argv + i));
        if (NULL == f) {
            return 2;
        }


        FILE *fout;

        char c = getc(f);

        int it = 0;
        int len = START_LEN;
        char *sym = (char *) malloc(sizeof(char) * len);
        if (sym == NULL)
        {
            return 3;
        }



        while (c != EOF)
        {
            if (!IsSpace(c))
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
                
                if (!Permitted(c))
                {
                    if (fout == NULL)
                    {
                        fout = fopen("out.txt", "w");
                        if (fout == NULL)
                        {
                            return 3;
                        }
                    }
                    WriteError(fout, it, sym);

                }

                *(sym + it++) = c;                    
            }
            else if (c == '\n')
            {
                *(sym + it++) = '#';
                *(sym + it) = '\0';
                if (fout == NULL)
                {
                    fout = fopen("out.txt", "w");
                    if (fout == NULL)
                    {
                        return 3;
                    }
                }

                int err = Process(f, fout, sym);
            }
            c = getc(f);

        }

    }

    return 0;
}