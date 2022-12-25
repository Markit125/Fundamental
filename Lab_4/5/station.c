#include "stack.c"
#include <stdio.h>
#include <stdlib.h>

int action(char in_stack, char c)
{
    printf("in stack: %c, c = %c\n", in_stack, c);
    if (in_stack == '#')
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

    if (in_stack == '+' || in_stack == '-')
    {
        if (c == '+' || c == '#' || c == ')')
        {
            return 2;
        }

        return 1;
    }

    if (in_stack == '*' || in_stack == '/')
    {
        if (c == '(')
        {
            return 1;
        }
        if (c == '^')
        {
            return 1;
        }

        return 2;
    }

    if (in_stack == '(')
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

    if (in_stack == '^')
    {
        if (c == '(')
        {
            return 1;
        }
        if (c == ')')
        {
            return 1;
        }

        return 6;
    }

    if (in_stack == ')')
    {
        if (c == '#')
        {
            return 7;
        }
    }

    return 5;
}


int change_stacks(Stack *stackNum, Stack *stackS, int act, char c, char c_prev)
{
    int err = 0;
    char *carriage, *carriage_e, *carriage_last;
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

        case 6:
            printf("\n\n\nPrevious %c\n\n", c_prev);
            if (!is_empty(stackNum))
            {
                err = get_top(stackNum, &carriage_last);
            }
            if (!('0' <= *carriage_last && *carriage_last <= '9'))
            {

                if (c_prev != ')')
                {
                    err = pop(stackNum, &carriage);
                    if (err)
                    {
                        return err;
                    }

                    printf("stackNum -> %s -> memory_1\n\n", carriage);


                    
                    err = pop(stackNum, &carriage_e);
                    if (err)
                    {
                        return err;
                    }

                    printf("stackNum -> %s -> memory_2\n\n", carriage);

                    printf("%s %s carrrrrrs\n", carriage, carriage_e);

                    if (!is_empty(stackNum))
                    {
                        err = get_top(stackNum, &carriage_last);
                    }

                    if (!is_empty(stackNum))
                    {
                        err = push(stackNum, carriage);
                        if (err)
                        {
                            return err;
                        }
                        
                        printf("memory_1 -> %s -> stackNum\n\n", carriage);

                        err = pop(stackS, &carriage);
                        if (err)
                        {
                            return err;
                        }

                        printf("stackS -> %s -> memory_1\n\n", carriage);

                        err = push(stackNum, carriage);
                        if (err)
                        {
                            return err;
                        }

                        printf("memory_1 -> %s -> stackNum\n\n", carriage);

                        err = push(stackNum, carriage_e);
                        if (err)
                        {
                            return err;
                        }

                        printf("memory_2 -> %s -> stackNum\n\n", carriage);
                
                        break;
                    }
                    else
                    {
                        err = push(stackNum, carriage_e);
                        if (err)
                        {
                            return err;
                        }
                        printf("memory_2 -> %s -> stackNum\n\n", carriage);
                        err = push(stackNum, carriage);
                        if (err)
                        {
                            return err;
                        }
                        printf("memory_1 -> %s -> stackNum\n\n", carriage);
                    }
                }
            }


        case 2:
            err = pop(stackS, &carriage);
            if (err)
            {
                return err;
            }

            err = push(stackNum, carriage);

            printf("stackS -> %s -> stackNum\n", carriage);

            free(carriage);
            break;

        case 3:
            err = pop(stackS, &carriage);
            if (err)
            {
                return err;
            }

            if (!is_empty(stackS))
            {
                err = get_top(stackS, &carriage);
                if (err)
                {
                    return err;
                }
                if (*carriage == '^')
                {
                    err = pop(stackS, &carriage);
                    if (err)
                    {
                        return err;
                    }
                    err = push(stackNum, carriage);
                    if (err)
                    {
                        return err;
                    }
                }
            }

            free(carriage);
            break;

        case 7:
            while (*carriage != '#')
            {
                err = pop(stackS, &carriage);
                if (err)
                {
                    return err;
                }

                if (*carriage == '(' || *carriage == ')' || *carriage == '#')
                {
                    if (*carriage == '#')
                    {
                        err = push(stackS, carriage);
                        if (err)
                        {
                            return err;
                        }
                    }
                    continue;
                }
                err = push(stackNum, carriage);
                if (err)
                {
                    return err;
                }
            }

    }

    
    return err;

}