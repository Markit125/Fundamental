#include "arguments.c"
#include "station.c"
#include <stdlib.h>


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
    char *num;
    char c = *sym;
    char *top;
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
            err = StrCopy(num, sym, startIt, it);
            if (err)
            {
                free(num);
                free(top);
                ClearStack(stackNum);
                ClearStack(stackS);
                return 3;
            }

            Push(stackNum, num);
        }


        if (!number)
        {
            // push to stack

            err = Top(stackS, top);
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

            err = ChangeStacks(stackNum, stackS, act, c);


            startIt = it + (act == 2);
        }

        prevNumber = number;
        ++it;
    }

    WriteStart(sym);
    err = WriteReversePolish(stackNum);
    if (err)
    {
        return 3;
    }

    WriteAnswer(stackNum);

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
        printf("%c", *ptr);
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
        Pop(stackNum, data);
        Push(stackTemp, data);
    }

}


int WriteAnswer(Stack *stackNum);


int WriteError(FILE *fout, int it, char *sym)
{

    return 0;
}