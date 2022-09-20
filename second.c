#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_number(char const* arg)
{
    // Add the logic to check whether arg is a number
    // The code here can be simple or complex depending on the 
    // level of checking that is necessary.
    // Should we return true or false if the argument is "1abc"?

    // This is a very simple test.
    int n;
    return (sscanf(arg, "%d", &n) == 1);
}


int main(int argc, char *argv[])
{
    // if (argc > 3)
    // {
    //     printf("Too many arguments!\n");
    // }
    // char *output = malloc(sizeof(char) * strlen(argv[1] + 4));
    char *output = malloc(1000);
    
    output[0] = *"out_";

    printf("%s\n", output);
    return 0;

    int kk = 4;
    // printf("%d\n", kk);
    for (int i = 0; argv[1][i] != '\0'; ++i)
    {
        output[kk] = argv[1][i];
        printf("%d\n", kk);
        ++kk;
    }
    printf("%s\n", output);


    if (argc == 1)
    {
        printf("No agruments!\n");
        return 1;
    }

    int number = -1;
    char *flag = NULL;


    

    return 0;
}
