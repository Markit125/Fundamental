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
    int cur_len = START_LEN;
    
    while ((c = fgetc(file)) != EOF)
    {
        if (number_column == -1)
        {
            if (columns[0])
            {
                fseek(file, -(strlen(columns[0]) + strlen(columns[1]) + strlen(columns[2]) + 4), SEEK_CUR);
                fprintf(file, "%s %s %s\n", columns[2], columns[0], columns[1]);
                fseek(file, 1, SEEK_CUR);
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
            if (strlen(columns[number_column]) == cur_len)
            {
                cur_len *= 2;
                columns[number_column] = realloc(columns[number_column], sizeof(char) * cur_len);

                if (columns[number_column] == NULL)
                {
                    printf("Not enough memory!\n");
                    fclose(file);
                    return 1;
                }
            }

            sscanf(&c, "%c", &columns[number_column][it++]);
        }
        else
        {
            columns[number_column][it++] = '\0';
            cur_len = START_LEN;
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
    printf("Success\n");

    fclose(file);

    return 0;
}
