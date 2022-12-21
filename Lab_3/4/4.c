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
                printf("The message cannot contain any separators and commas!\n");
                if (attempts > 0)
                {
                    printf("Try again:\n");
                }
            }
            else
            {
                break;
            }
        }

        if (attempts == -1)
        {
            printf("Too many attempts!\n");
            return 4;
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

        if (argc < 3)
        {
            printf("You should enter a message!\n");
            return 8;
        }

        int count_notes = START_COUNT_NOTES;
        unsigned int corrupt_line = 0;
        int err = check_message(argv[2]);
        if (err == 1)
        {
            printf("Message cannot contain any separators and commas!\n");

            fclose(f);

            return 4;
        }


        message **messages = (message **) malloc(sizeof(message *) * count_notes);
        if (messages == NULL)
        {
            printf("Memory cannot be allocated!\n");

            fclose(f);
            free_messages(messages, count_notes);

            return 2;
        }


        err = read_notes(&count_notes, &messages, f, &corrupt_line);
        if (count_notes == 1)
        {
            printf("File was empty\n");
        }

        if (err == 1)
        {
            printf("File is corrupted at line %u\n", corrupt_line);
            return 8;
        }
        else if (err == 2)
        {
            printf("There is not enough memory!\n");

            fclose(f);

            free_messages(messages, count_notes);

            return 3;
        }


        *(messages + count_notes) = (message *) malloc(sizeof(message));
        if (*(messages + count_notes) == NULL)
        {
            printf("Cannot allocate memory for a new message!\n");
            return 11;
        }

        message *mess = NULL;
        if (count_notes > 1)
        {
            mess = *(messages + (count_notes - 1));
            mess->id = (*(messages + (count_notes - 2)))->id + 1;
        }
        else
        {
            mess = *messages;
            mess->id = 1;
        }

        

        mess->text = (char *) malloc(sizeof(char) * strlen(argv[2]));
        if (NULL == mess->text)
        {
            printf("Memory cannot be allocated!\n");

            fclose(f);
            free_messages(messages, count_notes);

            return 2;
        }

        strcpy(mess->text, argv[2]);
        mess->len = strlen(argv[2]);

        write_to_file(*mess, f);
        write_notes(messages, count_notes);

        free_messages(messages, count_notes);
        fclose(f);

    }

    return 0;
}