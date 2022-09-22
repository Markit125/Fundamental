#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_LEN 20


int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Too many arguments!\n");
        return 1;
    }

    if (argc == 1)
    {
        printf("There is no name of file!\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r+");

    if (file == NULL)
    {
        printf("File doesn't exists!\n");
        return 1;
    }

    char c, _c;
    
    int number_column = -1;
    char **columns = (char **) malloc(sizeof(char) * 3);

    int it = 0;

    printf("1\n");
    
    while ((c = fgetc(file)) != EOF)
    {
        if (number_column == -1)
        {
            if (columns[0])
            {
                printf("lens = %lu + %lu + %lu\n", strlen(columns[0]), strlen(columns[1]), strlen(columns[2]));
                printf("|%s %s %s|\n", columns[0], columns[1], columns[2]);

                fseek(file, -(strlen(columns[0]) + strlen(columns[1]) + strlen(columns[2]) + 4), SEEK_CUR);
                fprintf(file, "%s %s %s\n", columns[2], columns[0], columns[1]);
                fseek(file, 1, SEEK_CUR);
                printf("wrote\n");
            }

            else
            {
                int i;
                for (i = 0; i < 3; ++i)
                {
                    columns[i] = (char *) malloc(sizeof(char) * START_LEN);
                    columns[i][START_LEN - 1] = '\0';
                }
            }
            number_column = 0;
        }


        if (c != ' ' && c != '\n')
        {
            printf("====== col_num: %d, iter: %d, string: %s\n", number_column, it, columns[number_column]);
            // if (columns[number_column][it] == '\0')
            // {
            //     columns[number_column] = realloc(columns[number_column], sizeof(char) * strlen(columns[number_column]) * 2);
            // }

            sscanf(&c, "%c", &columns[number_column][it++]);
        }
        else
        {
            printf("c0, c1, c2: %s %s %s\n", columns[0], columns[1], columns[2]);

            columns[number_column][it++] = '\0';
            it = 0;
            number_column = (number_column + 1) % 3;
            if (number_column == 0)
            {
                number_column = -1;
            }
        }
        _c = c;
    }
    if (_c != '\n')
    {
        columns[number_column][it++] = '\0';
        fseek(file, -(strlen(columns[0]) + strlen(columns[1]) + strlen(columns[2]) + 3), SEEK_CUR);
        fprintf(file, "\n%s %s %s", columns[2], columns[0], columns[1]);
    }
    else
    {
        fseek(file, -(strlen(columns[0]) + strlen(columns[1]) + strlen(columns[2]) + 4), SEEK_CUR);
        fprintf(file, "\n%s %s %s\n", columns[2], columns[0], columns[1]);
    }
    printf("wrote last\n");

    fclose(file);

    return 0;
}
