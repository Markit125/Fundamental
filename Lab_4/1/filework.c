#include "arguments.c"
#include "process.c"
#define START_LEN 10


int ReadFiles(int argc, const char *argv)
{
    if (argc == 0) {
        return 1;
    }

    for (int i = 0; i < argc; ++i)
    {
        FILE *f = fopen(argv + i, "r");
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
                if (it == len - 1)
                {
                    char *ptr = (char *) malloc(sizeof(char) * (len * 2));
                    if (ptr == NULL)
                    {
                        return 3;
                    }

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

        }


        
        

    }
}