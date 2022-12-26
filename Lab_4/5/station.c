#include "stack.c"
#include <stdio.h>
#include <stdlib.h>

int action(char in_stack, char c)
{
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


int change_stacks(Stack *stack_num, Stack *stack_s, int act, char c, char c_prev)
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
            err = push(stack_s, carriage);
            break;

        case 6:
            if (!is_empty(stack_num))
            {
                err = get_top(stack_num, &carriage_last);
            }
            if (!('0' <= *carriage_last && *carriage_last <= '9'))
            {

                if (c_prev != ')')
                {
                    err = pop(stack_num, &carriage);
                    if (err)
                    {
                        return err;
                    }
                    
                    err = pop(stack_num, &carriage_e);
                    if (err)
                    {
                        return err;
                    }


                    if (!is_empty(stack_num))
                    {
                        err = get_top(stack_num, &carriage_last);
                    }

                    if (!is_empty(stack_num))
                    {
                        err = push(stack_num, carriage);
                        if (err)
                        {
                            return err;
                        }
                        

                        err = pop(stack_s, &carriage);
                        if (err)
                        {
                            return err;
                        }

                        err = push(stack_num, carriage);
                        if (err)
                        {
                            return err;
                        }

                        err = push(stack_num, carriage_e);
                        if (err)
                        {
                            return err;
                        }

                        break;
                    }
                    else
                    {
                        err = push(stack_num, carriage_e);
                        if (err)
                        {
                            return err;
                        }
                        err = push(stack_num, carriage);
                        if (err)
                        {
                            return err;
                        }
                    }
                }
            }


        case 2:
            err = pop(stack_s, &carriage);
            if (err)
            {
                return err;
            }

            err = push(stack_num, carriage);

            free(carriage);
            break;

        case 3:
            err = pop(stack_s, &carriage);
            if (err)
            {
                return err;
            }

            if (!is_empty(stack_s))
            {
                err = get_top(stack_s, &carriage);
                if (err)
                {
                    return err;
                }
                if (*carriage == '^')
                {
                    err = pop(stack_s, &carriage);
                    if (err)
                    {
                        return err;
                    }
                    err = push(stack_num, carriage);
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
                err = pop(stack_s, &carriage);
                if (err)
                {
                    return err;
                }

                if (*carriage == '(' || *carriage == ')' || *carriage == '#')
                {
                    if (*carriage == '#')
                    {
                        err = push(stack_s, carriage);
                        if (err)
                        {
                            return err;
                        }
                    }
                    continue;
                }
                err = push(stack_num, carriage);
                if (err)
                {
                    return err;
                }
            }

    }

    
    return err;

}