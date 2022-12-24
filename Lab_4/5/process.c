#include <stdio.h>
#include <stdlib.h>
#include "arguments.c"
#include "station.c"

#define START_LEN 10


int write_error(FILE *fout, int it, char *sym);
int write_start(char *sym);
int write_reverse_polish(Stack *stackNum);
int write_answer(Stack *stackNum);


int process(FILE *fout, char *sym)
{
    Stack *stackNum = (Stack *) malloc(sizeof(Stack));
    if (stackNum == NULL)
    {
        return 3;
    }
    stackNum->first = NULL;

    Stack *stackS = (Stack *) malloc(sizeof(Stack));
    if (stackS == NULL)
    {
        return 3;
    }
    stackS->first = NULL;
    push(stackS, "#");



    int err;
    int number = 0;
    int prevNumber = 0;
    int it = 0, startIt = 0;
    int act = -1;
    int len = START_LEN;
    char *num = (char *) malloc(sizeof(char) * START_LEN);
    if (NULL == num)
    {
        return 3;
    }

    char c = ' ', c_prev = ' ', before_ext = ' ';
    char *top;

    printf("BEGIN %s\n", sym);
    while (c != '\0')
    {
        c_prev = c;
        c = *(sym + it++);
        if (c == '^')
        {
            before_ext = c_prev;
        }

        printf("\n%c on input\n\n", c);
        if (is_num_symbol(c))
        {
            number = 1;
        }
        else
        {
            number = 0;
        }


        if (prevNumber == 1 && !number)
        {
            err = str_copy(&num, sym, startIt, it, &len);
            if (err)
            {
                free(num);
                free(top);
                free_stack(stackNum);
                free_stack(stackS);
                return 3;
            }
            

            push(stackNum, num);
            printf("\n\nAfter pushing:\n  Num\n");
            print_stack(stackNum);
            printf("  S\n");
            print_stack(stackS);
            printf("OK\n");

        }


        if (!number)
        {
            // push to stack
            

            err = get_top(stackS, &top);
            if (err)
            {
                write_error(fout, it, sym);
                free(num);
                free(top);
                free_stack(stackNum);
                free_stack(stackS);
                return 3;
            }
            printf("Top done!\n");

            // printf("%s %c before action\n", top, c);
            act = action(*top, c);
            
            printf("%d - action\n", act);
            if (act == 5)
            {
                write_error(fout, it, sym);
                free(num);
                free(top);
                free_stack(stackNum);
                free_stack(stackS);
                return 4;
            }
            else if (act == 2 || act == 6)
            {
                --it;
            }
            else if (act == 4)
            {
                print_stack(stackNum);
                break;
            }

            err = change_stacks(stackNum, stackS, act, c, before_ext); // here
            if (err == 1)
            {
                printf("Cannot allocate memory!\n");
                write_error(fout, it, sym);
                free(num);
                free(top);
                free_stack(stackNum);
                free_stack(stackS);

                return 5;
            }
            else if (err == 2)
            {
                printf("Stack empty error\n");
                write_error(fout, it, sym);
                free(num);
                free(top);
                free_stack(stackNum);
                free_stack(stackS);

                return 6;
            }
            
            printf("\n\nAfter changing:\n  Num\n");
            print_stack(stackNum);
            printf("  S\n");
            print_stack(stackS);

            startIt = it + (act == 2);
        }

        prevNumber = number;
        

        printf("%c end\n", c);
    }

    printf("\n\nFinal stack:\n");
    print_stack(stackNum);
    print_stack(stackS);

    write_start(sym);
    err = write_reverse_polish(stackNum);
    if (err)
    {
        return 3;
    }

    // WriteAnswer(stackNum);

    free(sym);
    free(num);
    free(top);
    free_stack(stackNum);
    free_stack(stackS);
    // printf("%p ============\n", stackNum);

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
    
    char *data;
    while (!is_empty(stackNum))
    {
        pop(stackNum, &data);
        push(stackTemp, data);
    }

    while (!is_empty(stackTemp))
    {
        pop(stackTemp, &data);
        printf("%s ", data);
    }
    printf("\n");

    return 0;

}


int write_answer(Stack *stackNum);


int write_error(FILE *fout, int it, char *sym)
{

    return 0;
}