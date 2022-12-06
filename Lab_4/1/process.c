#include "stack.c"

int Process(FILE *f, FILE *fout, char *sym)
{
    int number = 0;
    int prevNumber = 0;
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack == NULL)
    {
        return 3;
    }

    char c = *sym;
    while (c != '\0')
    {
        if (number == prevNumber)
        {
            
        }
    }

    return 0;
}


int WriteError(FILE *fout, int it, char *sym)
{

    return 0;
}