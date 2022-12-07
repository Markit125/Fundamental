#include "stack.c"

int Action(char inStack, char c)
{
    if (inStack == '#')
    {
        if (c == ')')
        {
            return 5;
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
            err = Push(stackS, &c);
            break;
        case 2:
            err = Pop(stackS, carriage);
            if (err)
            {
                return err;
            }

            err = Push(stackNum, carriage);
            break;
        case 3:
            err = Pop(stackS, carriage);
            break;
    }

    free(carriage);
    return err;

}