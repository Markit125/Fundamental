#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "arguments.c"
#include "station.c"

#define START_LEN 10

enum mistakes
{
    mis_braces = 1,
    mis_sign = 2,
    mis_number = 3,
    mis_file = 4,
    mis_unknown = 5,
};


int write_error(FILE *fout, int it, char *sym, int number, int err_type);
int write_start(char *sym);
int write_reverse_polish(Stack *stackNum);
int write_answer(Stack *stack_num);
int get_answer(Stack *stackNum, float *result);


int process(FILE *fout, char *sym, int expression_number)
{
    Stack *stack_num = (Stack *) malloc(sizeof(Stack));
    if (stack_num == NULL)
    {
        return 3;
    }
    stack_num->first = NULL;

    Stack *stack_s = (Stack *) malloc(sizeof(Stack));
    if (stack_s == NULL)
    {
        return 3;
    }
    stack_s->first = NULL;
    push(stack_s, "#");



    int err;
    int number = 0;
    int prev_number = 0;
    int it = 0, start_it = 0, prev_it = -1;
    int act = -1;
    int brace = 0;
    int len = START_LEN;
    char *num = (char *) malloc(sizeof(char) * START_LEN);
    if (NULL == num)
    {
        return 3;
    }

    char c = ' ', c_prev = ' ', before_ext = ' ';
    char *top;

    while (c != '\0')
    {
        c_prev = c;
        c = *(sym + it++);
        if (c == '^')
        {
            before_ext = c_prev;
        }
        if (it != prev_it)
        {
            if (c == '(' && prev_it != it)
            {
                if (is_num_symbol(c_prev) && c_prev != '(')
                {
                    write_error(fout, it, sym, expression_number, mis_braces);
                    return 5;
                }
                ++brace;
            }
            else if (c == ')' && prev_it != it)
            {
                if (!is_num_symbol(c_prev) && c_prev != ')')
                {
                    write_error(fout, it, sym, expression_number, mis_sign);
                    return 5;
                }
                --brace;
            }

            
            if (is_sign(c) && is_sign(c_prev))
            {
                write_error(fout, it, sym, expression_number, mis_sign);
                return 5;
            }

            if (brace < 0)
            {
                write_error(fout, it, sym, expression_number, mis_braces);
                return 5;
            }
        }
        prev_it = it;

        if (is_num_symbol(c))
        {
            number = 1;
        }
        else
        {
            number = 0;
        }


        if (prev_number == 1 && !number)
        {
            err = str_copy(&num, sym, start_it, it, &len);
            if (err)
            {
                free(num);
                free(top);
                free_stack(stack_num);
                free_stack(stack_s);
                return 6;
            }
            
            err = push(stack_num, num);
            if (err)
            {
                return err;
            }
        }


        if (!number)
        {
            // push to stack

            err = get_top(stack_s, &top);
            if (err)
            {
                write_error(fout, it, sym, expression_number, mis_braces);
                free(num);
                free(top);
                free_stack(stack_num);
                free_stack(stack_s);
                return 5;
            }

            act = action(*top, c);
            if (act == 5)
            {
                write_error(fout, it, sym, expression_number, mis_braces);
                free(num);
                free(top);
                free_stack(stack_num);
                free_stack(stack_s);

                return 5;
            }
            else if (act == 2 || act == 6 || act == 7)
            {
                --it;
            }
            else if (act == 4)
            {
                break;
            }

            err = change_stacks(stack_num, stack_s, act, c, before_ext);
            if (err == 1)
            {
                write_error(fout, it, sym, expression_number, mis_file);
                free(num);
                free(top);
                free_stack(stack_num);
                free_stack(stack_s);

                return 3;
            }
            else if (err == 2)
            {
                write_error(fout, it, sym, expression_number, mis_braces);
                free(num);
                free(top);
                free_stack(stack_num);
                free_stack(stack_s);

                return 5;
            }

            start_it = it + (act == 2);
        }

        prev_number = number;
    }

    write_start(sym);
    err = write_reverse_polish(stack_num);
    if (err)
    {
        return 3;
    }

    err = write_answer(stack_num);
    if (err)
    {
        return err;
    }


    free(num);
    free(top);
    free_stack(stack_num);
    free_stack(stack_s);

    return 0;
}


int write_start(char *sym)
{
    char *ptr = sym;
    while (*ptr)
    {
        if (*ptr != '#')
        {
            printf("%c", *ptr);
        }
        ++ptr;
    }
    printf("\n");

    return 0;
}

int write_reverse_polish(Stack *stackNum)
{
    Stack *stackTemp = (Stack *) malloc(sizeof(Stack));
    if (stackTemp == NULL)
    {
        return 1;
    }
    
    int err;
    char *data;
    while (!is_empty(stackNum))
    {
        err = pop(stackNum, &data);
        if (err)
        {
            return err;
        }
        err = push(stackTemp, data);
        if (err)
        {
            return err;
        }
    }

    while (!is_empty(stackTemp))
    {
        err = pop(stackTemp, &data);
        if (err)
        {
            return err;
        }
        err = push(stackNum, data);
        if (err)
        {
            return err;
        }
        printf("%s ", data);
    }
    printf("\n");

    free(stackTemp);

    return 0;

}


int calculate(float a, float b, char c, float *res)
{
    switch (c)
    {
        case '*':
            *res = a * b;
            break;
        case '/':
            if (b == 0)
            {
                return 1;
            }
            *res = a / b;
            break;
        case '+':
            *res = a + b;
            break;
        case '-':
            *res = a - b;
            break;
        case '^':
            *res = pow(a, b);
            break;
        default:
            return 2;
    }

    return 0;
}


int write_answer(Stack *stack_num)
{
    int err;
    float ans;
    err = get_answer(stack_num, &ans);
    if (err)
    {
        switch (err)   
        {
            case 1:
                err = 3;
                break;
            case 2:
                err = 6;
                break;
            case 3:
                err = 7;
                break;
            case 4:
                err = 8;
                break;
        }
        return err;
    }
    printf("Answer: %f\n", ans);

    return 0;
}


int get_answer(Stack *stack_num, float *result)
{
    if (is_empty(stack_num))
    {
        return 4;
    }

    char *c, *arg_0, *arg_1;
    float res_0, res_1;
    int err;
    err = pop(stack_num, &c);
    if (err)
    {
        return err;
    }

    if (is_sign(*c))
    {
        
        err = get_answer(stack_num, &res_1);
        if (err)
        {
            return err;
        }

        err = get_answer(stack_num, &res_0);
        if (err)
        {
            return err;
        }

        err = calculate(res_0, res_1, *c, result);
        if (err)
        {
            return err + 10;
        }
        
    }
    else
    {
        if (!is_number(c))
        {
            return 3;
        }
        *result = atof(c);
    }

    return 0;
}


int write_error(FILE *fout, int it, char *sym, int number, int err_type)
{
    if (NULL == fout)
    {
        return 1;
    }

    if (err_type == mis_file)
    {
        fprintf(fout, "File doesn't exists\n");
        return 0;
    }

    int i;
    char *ptr = sym;
    char c;
    c = fgetc(fout);
    if (c == EOF)
    {
        fprintf(fout, "Wrong expression %d:\n", number);
    }
    else
    {
        fseek(fout, -1, SEEK_END);
        if (fgetc(fout) == '\n')
        {
            fprintf(fout, "Wrong expression %d:\n", number);
        }
        else
        {
            fprintf(fout, "\nWrong expression %d:\n", number);
        }
    }


    while (*ptr != '#' && *ptr != '\0')
    {
        fputc(*ptr++, fout);
    }
    fputc('\n', fout);

    for (i = 0; i < it - 1; ++i)
    {
        fputc(' ', fout);
    }
    fprintf(fout, "^\n");

    switch (err_type)
    {
        case mis_braces:
            fprintf(fout, "Wrong braces\n");
            break;
        case mis_number:
            fprintf(fout, "Wrong number\n");
            break;
        case mis_sign:
            fprintf(fout, "Wrong sign sequence\n");
            break;
        case mis_unknown:
            fprintf(fout, "Unknown symbol\n");
            break;
    }
    

    return 0;
}