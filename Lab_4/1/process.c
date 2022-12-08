#include <stdlib.h>
#include "arguments.c"
#include "station.c"

#define START_LEN 10


int WriteError(FILE *fout, int it, char *sym);
int WriteStart(char *sym);
int WriteReversePolish(Stack *stackNum);
int WriteAnswer(Stack *stackNum);


int Process(FILE *f, FILE *fout, char *sym)
{
    Stack *stackNum = (Stack *) malloc(sizeof(Stack));
    if (stackNum == NULL)
    {
        return 3;
    }

    Stack *stackS = (Stack *) malloc(sizeof(Stack));
    if (stackS == NULL)
    {
        return 3;
    }
    Push(stackS, "#");



    int err;
    int number = 0;
    int prevNumber = 0;
    int it = 0, startIt = 0;
    int act = -1;
    int len = START_LEN;
    char *num = (char *) malloc(sizeof(char) * START_LEN);
    char c = *sym;
    char *top;

    printf("BEGIN %s\n", sym);
    while (c != '\0')
    {
        if (IsNumSymbol(c))
        {
            number = 1;
        }
        else
        {
            number = 0;
        }


        if (prevNumber == 1 && !number)
        {
            err = StrCopy(&num, sym, startIt, it, &len);
            if (err)
            {
                free(num);
                free(top);
                ClearStack(stackNum);
                ClearStack(stackS);
                return 3;
            }
            
            printf("%s -> stackNum\n", num);
            Push(stackNum, num);
        }


        if (!number)
        {
            // push to stack

            err = Top(stackS, &top);
            if (err)
            {
                WriteError(fout, it, sym);
                free(num);
                free(top);
                ClearStack(stackNum);
                ClearStack(stackS);
                return 4;
            }


            act = Action(*top, c);
            if (act == 5)
            {
                WriteError(fout, it, sym);
                free(num);
                free(top);
                ClearStack(stackNum);
                ClearStack(stackS);
                return 4;
            }
            else if (act == 2)
            {
                --it;
            }
            else if (act == 4)
            {
                break;
            }

            err = ChangeStacks(stackNum, stackS, act, c);

            startIt = it + (act == 2);
        }

        prevNumber = number;
        c = *(sym + it++);
    }

    PrintStack(stackNum);
    // PrintStack(stackS);

    WriteStart(sym);
    err = WriteReversePolish(stackNum);
    if (err)
    {
        return 3;
    }

    // WriteAnswer(stackNum);

    free(sym);
    free(num);
    free(top);
    ClearStack(stackNum);
    ClearStack(stackS);

    return 0;
}


int WriteStart(char *sym)
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

int WriteReversePolish(Stack *stackNum)
{
    Stack *stackTemp = (Stack *) malloc(sizeof(Stack));
    if (stackTemp == NULL)
    {
        return 1;
    }
    
    char *data;
    while (!IsEmpty(stackNum))
    {
        Pop(stackNum, &data);
        Push(stackTemp, data);
    }

    while (!IsEmpty(stackTemp))
    {
        Pop(stackTemp, &data);
        printf("%s ", data);
    }
    printf("\n");

    return 0;

}


int WriteAnswer(Stack *stackNum);


int WriteError(FILE *fout, int it, char *sym)
{

    return 0;
}