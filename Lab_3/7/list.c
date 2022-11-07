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


int clear_list(List *list)
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
        free_habitat(node->habitat);
        prev = node;
        node = node->next;
        free(prev);
    }

    free(list);

    return 0;
}


int print_list(List *list)
{
    Node *node = list->first;
    while (node != NULL)
    {
        print_habitat(node->habitat);
        node = node->next;
    }

    return 0;
}