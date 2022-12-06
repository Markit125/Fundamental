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


int IsEmpty(Stack *st)
{
    return st->first == NULL;
}


int ClearStack(Stack *st)
{
    Node *node = st->first, *prev;
    while (node)
    {
        prev = node;
        node = node->next;
        free(prev->data);
        free(prev);
    }

    free(st);

    return 0;
}


int Push(Stack *st, char *s)
{
    Node *node = st->first;
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
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


int Pop(Stack *st, char *data)
{
    Node *node = st->first;
    st->first = node->next;
    data = (char *) malloc(sizeof(node->data));
    if (data == NULL)
    {
        return 1;
    }

    strcpy(data, node->data);
    free(node->data);
    free(node);

    return 0;
}