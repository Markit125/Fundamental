#include "stack.c"
#include <stdio.h>
#include <stdlib.h>

int action(char inStack, char c)
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

    if (inStack == '^')
    {
        return 2;
    }

    return 5;
}


int change_stacks(Stack *stackNum, Stack *stackS, int act, char c)
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
            err = push(stackS, carriage);
            printf("%s -> stackS\n", carriage);
            break;
        case 2:
            err = pop(stackS, &carriage);
            if (err)
            {
                return err;
            }


            err = push(stackNum, carriage);

            printf("stackS -> %s -> stackS\n", carriage);

            free(carriage);
            break;
        case 3:
            err = pop(stackS, &carriage);
            free(carriage);
            break;
    }

    
    return err;

}