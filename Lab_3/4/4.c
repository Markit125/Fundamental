#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_funcs.c"

#define START_COUNT_NOTES 2
#define START_LEN 20
#define NAME_LEN 10


int main(int argc, char *argv[])
{
    if (argc > 3)
    {
        printf("Wrong count of arguments!\n");
        return 1;
    }

    if (argc == 1)
    {
        printf("Enter message:\n");

        int text_len = START_LEN;
        char *text = (char *) malloc(sizeof(char) * text_len);
        if (text == NULL)
        {
            printf("Memory cannot be allocated!\n");
            return 2;
        }

        int err;
        int attempts = 3;

        while (attempts--)
        {
            err = read_message(text, text_len);

            if (err == 1)
            {
                printf("There is not enough memory!\n");

                free(text);
                
                return 3;
            }
            else if (err == 2)
            {
                printf("The message cannot contain any separators!\nTry again:\n");
            }
            else
            {
                break;
            }
        }


        char *file_name = (char *) malloc(sizeof(char) * (NAME_LEN + 4));
        if (file_name == NULL)
        {
            printf("Memory cannot be allocated!\n");

            free(text);

            return 2;
        }

        err = generate_file_name(file_name, NAME_LEN);
        if (err)
        {
            printf("Some error!\n");

            free(file_name);
            free(text);

            return 5;
        }

        FILE *file = fopen(file_name, "w");
        free(file_name);
        if (file == NULL)
        {
            printf("File cannot be created!\n");

            free(text);

            return 6;
        }

        message msg;
        msg.id = 1;
        msg.text = text;
        msg.len = strlen(text);

        write_to_file(msg, file);
        
        fclose(file);
        free(text);
    }
    else
    {
        FILE *f = fopen(argv[1], "r+");
        if (f == NULL)
        {
            printf("Such file does not exists!\n");
            return 7;
        }

        int err = check_message(argv[2]);
        if (err == 1)
        {
            printf("Message cannot contain any separators!\n");

            fclose(f);

            return 4;
        }

        printf("%s\n", argv[2]);

        int count_notes = START_COUNT_NOTES;
        message *messages = (message *) malloc(sizeof(message) * count_notes);
        // message **messages = (message **) malloc(sizeof(message *) * count_notes);

        if (messages == NULL)
        {
            printf("Memory cannot be allocated!\n");

            fclose(f);
            free(messages);

            return 2;
        }

        err = read_notes(&count_notes, messages, f);

        if (err == 1)
        {
            printf("File is corrupted!\n");
            return 8;
        }
        else if (err == 2)
        {
            printf("There is not enough memory!\n");

            fclose(f);
            free(messages);

            return 3;
        }

        if (count_notes > 0)
        {
            (messages + count_notes - 1)->id = (messages + (count_notes - 1))->id + 1;
        }
        else
        {
            (messages + count_notes - 1)->id = 1;
        }
        (messages + count_notes - 1)->text = argv[2];
        (messages + count_notes - 1)->len = strlen(argv[2]);

        write_to_file(*(messages + count_notes - 1), f);

        write_notes(messages, count_notes);

        fclose(f);
        free(messages);
    }


    return 0;
}