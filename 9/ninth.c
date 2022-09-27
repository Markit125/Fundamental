

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define START_LEN 8
#define ABS 1000


int is_flag(char const* arg)
{
    return arg[0] == '-' || arg[0] == '/';
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

    char * input;
    printf("Enter number system:\n");
    scanf("%s", input);

    if (!is_number_integer(input))
    {

    }
    int base;

    printf("\n");

    return 0;
}