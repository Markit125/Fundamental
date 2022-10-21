#include <stdio.h>
#include <stdlib.h>

#include "sum.c"


int main()
{
    int len = 32;
    char *ans = (char*) malloc(sizeof(char) * len);
    
    printf("11 + 11 binary\n");
    char *sum = sum_of_nums(ans, len, 2, 2, "11", "11");
    printf("%s\n\n", sum);

    printf("25 + 99 + 1000 decimal\n");
    sum = sum_of_nums(ans, len, 10, 3, "25", "99", "1000");
    printf("%s\n\n", sum);

    printf("AA + Z + 12 36th\n");
    sum = sum_of_nums(ans, len, 36, 3, "AA", "Z", "12");
    printf("%s\n\n", sum);

    return 0;
}