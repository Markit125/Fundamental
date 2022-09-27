

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_LEN 5


int is_space(char c)
{
    return c == '\n' || c == ' ' || c == '\t';
}

int is_number(char const* arg)
{
    float n;
    return (sscanf(arg, "%f", &n) == 1);
}

int is_number_integer(char const* arg)
{
    int n;
    return (sscanf(arg, "%d", &n) == 1);
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        printf("Too many arguments!\n");
        return 1;
    }

    char *input;
    printf("Enter number system:\n");
    scanf("%s", input);

    if (!is_number_integer(input))
    {
        printf("You must enter integer number grater than one!\n");
        return 1;
    }
    
    int base = atoi(input);
    if (base < 2)
    {
        printf("Base must be grater than one!\n");
        return 1;
    }

    int cur_len = START_LEN;
    char *num = (char *) malloc(sizeof(char) * START_LEN);

    char c, _c;

    while (strcmp(num, "Stop") != 0)
    {
        c = getchar();
        if (c != '\n' && c != ' ' && c != '\t')

    }


    printf("\n");

    return 0;
}