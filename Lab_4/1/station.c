#include "stack.c"
#include <stdio.h>
#include <stdlib.h>

int Action(char inStack, char c)
{
    if (inStack == '#')
    {
        if (c == ')')
        {
            return 5;
        }
        else if (c == '#')
        {
            return 4;
        }

        return 1;
    }

    if (inStack == '+' || inStack == '-')
    {
        if (c == '+' || c == '#' || c == ')')
        {
            return 2;
        }

        return 1;
    }

    if (inStack == '*' || inStack == '/')
    {
        if (c == '(')
        {
            return 1;
        }

        return 2;
    }

    if (inStack == '(')
    {
        if (c == '#')
        {
            return 5;
        }

        if (c == ')')
        {
            return 3;
        }

        return 1;
    }

    if (c == '^')
    {
        return 1;
    }

    return 5;
}


int ChangeStacks(Stack *stackNum, Stack *stackS, int act, char c)
{
    int err = 0;
    char *carriage;
    switch (act)
    {
        case 1:
            carriage = (char *) malloc(sizeof(char) * 2);
            if (NULL == carriage)
            {
                return 1;
            }

            *carriage = c;
            *(carriage + 1) = '\0';
            err = Push(stackS, carriage);
            printf("%s -> stackS\n", carriage);
            break;
        case 2:
            err = Pop(stackS, &carriage);
            if (err)
            {
                return err;
            }

            err = Push(stackNum, carriage);

            printf("stackS -> %s -> stackS\n", carriage);

            free(carriage);
            break;
        case 3:
            err = Pop(stackS, &carriage);
            free(carriage);
            break;
    }

    
    return err;

}