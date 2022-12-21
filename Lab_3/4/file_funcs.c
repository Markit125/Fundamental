#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "text_funcs.c"

#define IN_LEN 15


typedef struct message
{
    unsigned int id;
    char *text;
    unsigned int len;
} message;



int write_mes(message *m)
{
    printf("%d | %s | %d\n", (*m).id, (*m).text, (*m).len);

    return 0;
}


char get_random_character()
{
    if (rand() % 2)
    {
        return rand() % 10 + '0';
    }
    else
    {
        return rand() % 26 + 'a';
    }
}


int generate_file_name(char *name, int len)
{
    srand(time(NULL));
    
    char *ptr = name;
    int i;
    for (i = 0; i < len; ++i)
    {
        *(ptr++) = get_random_character();
    }
    
    char *extension = ".csv";
    for (i = 0; i < 4; ++i)
    {
        *(ptr++) = *(extension + i);
    }

    return 0;
}


int write_to_file(message msg, FILE *f)
{
    fprintf(f, "%d,%s,%d\n", msg.id, msg.text, msg.len);

    return 0;
}


int read_notes(int *count, message ***msgs, FILE *f, unsigned int *corrupt_line)
{
    
    **msgs = (message *) malloc(sizeof(message));
    if (**msgs == NULL)
    {
        return 3;
    }
    
    // ========================================================

    int err, n, it = 0, counter = 0, len = IN_LEN;
    char *in = (char *) malloc(sizeof(char) * len);
    if (in == NULL)
    {
        return 4;
    }

    int count_lines = 0;
    int commas = 0;
    char c, c_prev = ' ';
    c = fgetc(f);
    if (c == EOF)
    {
        *count = 1;
        return 0;
    }

    while (c_prev != EOF)
    {
        // printf("c = %c\n", c);
        if (c == EOF && c_prev != '\n')
        {
            c = '\n';
            fputc('\n', f);
        }

        if (is_comma(c))
        {
            *(in + it) = '\0';

            if (commas == 0)
            {
                err = !is_integer(in, &n, 1);


                if (err)
                {
                    free(in);
                    *corrupt_line = count_lines + 1;
                    return 1;
                }

                (*(*msgs + counter))->id = n;
            }
            else if (commas == 1)
            {
                err = check_message(in);

                if (err)
                {
                    free(in);
                    *corrupt_line = count_lines;
                    return 1;
                }

                (*(*msgs + counter))->text = (char *) malloc(sizeof(char) * it);
                if (NULL == (*(*msgs + counter))->text)
                {
                    return 6;
                }
                strcpy((*(*msgs + counter))->text, in);

            }
            
            ++commas;
            it = 0;
        }
        else if (is_newline(c))// && it != 0)
        {
            ++count_lines;

            *(in + it) = '\0';
            it = 0;

            err = !is_integer(in, &n, 0);

            if (err || commas != 2)
            {
                free(in);
                *corrupt_line = count_lines;
                return 1;
            }


            (*(*msgs + counter))->len = n;


            ++counter;
            if (counter >= *count)
            {
                *count *= 2;
                message **ptr = realloc(*msgs, sizeof(message *) * *count);
                if (ptr == NULL)
                {
                    free(in);
                    return 2;
                }

                *msgs = ptr;
            }
            
            *(*msgs + counter) = (message *) malloc(sizeof(message));
            if (*(*msgs + counter) == NULL)
            {
                return 5;
            }
            // ========================================================

            commas = 0;
        }
        else
        {
            if (it == len)
            {
                len *= 2;
                char *ptr = realloc(in, sizeof(char) * len);
                if (ptr == NULL)
                {
                    free(in);
                    return 2;
                }

                in = ptr;
            }

            *(in + it++) = c;
        }

        c_prev = c;
        if (c != EOF)
        {
            c = fgetc(f);
        }
    }
    free(in);

    
    if (counter + 1 < *count)
    {
        message **ptr = realloc(*msgs, sizeof(message *) * (counter + 1));
        if (ptr == NULL)
        {
            return 2;
        }

        *count = counter + 1;
        *msgs = ptr;
    }

    return 0;
}


int write_notes(message **msgs, int count)
{
    printf("\nNotes (%d):\n\n", count);
    int i;
    for (i = 0; i < count; ++i)
    {
        printf("ID: %d\nMessage:\n%s\nLength of message: %d\n\n",
                    (*(msgs + i))->id, (*(msgs + i))->text, (*(msgs + i))->len);
    }

    return 0;
}


int free_messages(message **msgs, int count)
{
    int i;
    for (i = 0; i < count; ++i)
    {
        free((*(msgs + i))->text);
        free(*(msgs + i));
    }
    free(msgs);

    return 0;
}