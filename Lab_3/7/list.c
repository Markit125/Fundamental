#include <stdio.h>
#include <stdlib.h>

#include "Habitats.c"


typedef struct Node
{
    Habitat *habitat;
    struct Node *next;
} Node;


typedef struct List
{
    Node *first;
} List;


int is_empty(List *list)
{
    return NULL == list->first;
}


int add(List *list, Habitat *hab)
{
    Node *node;

    if (is_empty(list))
    {
        node = (Node *) malloc(sizeof(Node));
        if (NULL == node)
        {
            return 1;
        }

        list->first = node;
        node->habitat = hab;
        node->next = NULL;

        return 0;
    }

    Node *new_node = (Node *) malloc(sizeof(Node)), *prev = NULL;
    if (NULL == new_node)
    {
        return 1;
    }
    new_node->habitat = hab;


    node = list->first;
    while (node != NULL)
    {
        if (is_younger(hab, node->habitat))
        {
            break;
        }

        prev = node;
        node = node->next;
    }


    if (list->first == node)
    {
        new_node->next = node;
        list->first = new_node;
        
        return 0;
    }

    prev->next = new_node;
    new_node->next = node;
    
    return 0;
}


int clear_list(List *list, int free_hab)
{
    if (list == NULL)
    {
        return 1;
    }
    if (list->first == NULL)
    {
        free(list);
    }

    Node *node = list->first, *prev;
    while (node != NULL)
    {
        if (free_hab)
        {
            free_habitat(node->habitat);
        }
        prev = node;
        node = node->next;
        free(prev);
    }

    free(list);

    return 0;
}


int print_list(List *list, int enumerate)
{
    Node *node = list->first;
    int i = 1;
    while (node != NULL)
    {
        print_habitat(node->habitat, enumerate ? i : 0);
        node = node->next;
        ++i;
    }

    return 0;
}


int remove_habitat(List *list, int number)
{
    Node *node = list->first, *prev;
    int i = 1;
    if (i == number)
    {
        list->first = node->next;
        free_habitat(node->habitat);
        free(node);

        return 0;
    }

    while (node != NULL)
    {
        if (i == number)
        {
            prev->next = node->next;
            free_habitat(node->habitat);
            free(node);

            return 0;
        }

        prev = node;
        node = node->next;
        ++i;
    }

    return 1;
}


int add_habitat(List *list)
{
    if (list == NULL)
    {
        return 9;
    }

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

    printf("Enter last name:\n");

    char c;

    while (position < 6)
    {
        c = getchar();
        if (!is_newline(c))
        {
            if (it == len)
            {
                len *= 2;
                char *ptr = realloc(in, sizeof(char) * len);
                if (ptr == NULL)
                {
                    free(in);
                    free(hab);
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
            

            if (is_newline(c) && position < 5)
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
                    free(hab);
                    return err;
                }

                ++position;

                printf("Enter ");
                switch(position)
                {
                    case 1:
                        printf("name:\n");
                        break;
                    case 2:
                        printf("middle name:\n");
                        break;
                    case 3:
                        printf("birth date:\n");
                        break;
                    case 4:
                        printf("gender:\n");
                        break;
                    case 5:
                        printf("income:\n");
                        break;
                }
            }
            else
            {
                err = set_income(hab, in) == 0 ? 0 : 9;
                if (err)
                {
                    free(in);
                    free(hab);
                    return err;
                }

                ++counter;
                position = 0;

                add(list, hab);

                printf("Habitat added:\n");
                print_habitat(hab, 0);

                break;
            }
        }
    }
    free(in);

    return 0;
}