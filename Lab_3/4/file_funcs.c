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


int read_notes(int *count, message ***msgs, FILE *f)
{
    // if (*count == 0)
    // {
    //     ++(*count);
    // }
    
    *(*msgs + 0) = malloc(sizeof(message));
    
    // ========================================================

    int err, n, it = 0, counter = 0, len = IN_LEN;
    char *in = malloc(sizeof(char) * len);

    int commas = 0;
    char c;
    while ((c = fgetc(f)) != EOF)
    {
        if (is_comma(c))
        {
            *(in + it) = '\0';

            if (commas == 0)
            {

                err = !is_integer(in, &n, 1);

                // printf("in: %s\n", in);

                if (err)
                {
                    free(in);
                    return 1;
                }

                (*(*msgs + counter))->id = n;
                ++commas;
            }
            else if (commas == 1)
            {
                err = check_message(in);

                // printf("in: %s\n", in);

                if (err)
                {
                    free(in);
                    return 1;
                }

                (*(*msgs + counter))->text = malloc(sizeof(char) * it);
                strcpy((*(*msgs + counter))->text, in);

                ++commas;
            }
            it = 0;
        }
        else if (is_newline(c))
        {
            *(in + it) = '\0';
            it = 0;

            err = !is_integer(in, &n, 0);
            if (err)
            {
                free(in);
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
            
            *(*msgs + counter) = malloc(sizeof(message));
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
    printf("\nNotes (%d)\n", count);
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