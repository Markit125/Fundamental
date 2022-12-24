#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node
{
    struct Node *next;
    char *data;
} Node;



typedef struct Stack
{
    Node *first;
} Stack;


int is_empty(Stack *st)
{
    return st->first == NULL;
}


int print_stack(Stack *st)
{
    Node *node = st->first;
    while (node)
    {
        printf("\t| %s |\n", node->data);
        node = node->next;
    }


    return 0;
}


int clear_stack(Stack *st)
{
    Node *node = st->first, *prev;
    while (node)
    {
        // printf("node %s\n", node->data);
        prev = node;
        node = node->next;
        free(prev->data);
        free(prev);
    }
    st->first = NULL;

    return 0;
}


int free_stack(Stack *st)
{
    Node *node = st->first, *prev;
    while (node)
    {
        // printf("node %s\n", node->data);
        prev = node;
        node = node->next;
        free(prev->data);
        free(prev);
    }

    free(st);

    return 0;
}


int push(Stack *st, char *s)
{
    Node *node = st->first;
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return 1;
    }

    newNode->next = node;
    st->first = newNode;

    newNode->data = (char *) malloc(sizeof(char) * strlen(s));
    if (newNode == NULL)
    {
        return 1;
    }

    strcpy(newNode->data, s);

    return 0;
}


int pop(Stack *st, char **data)
{

    if (is_empty(st))
    {
        return 2;
    }

    Node *node = st->first;
    st->first = node->next;

    *data = (char *) malloc(sizeof(node->data));
    if (*data == NULL)
    {
        return 1;
    }

    strcpy(*data, node->data);
    free(node->data);
    free(node);

    return 0;
}


int get_top(Stack *st, char **data)
{
    if (is_empty(st))
    {
        return 2;
    }

    *data = (char *) malloc(sizeof(st->first->data));
    if (*data == NULL)
    {
        return 1;
    }

    strcpy(*data, st->first->data);
    
    return 0;
}