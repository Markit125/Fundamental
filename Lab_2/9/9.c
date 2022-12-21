#include <stdio.h>
#include <stdlib.h>

#include "sum.c"


int main()
{
    char *ans;
    char *sum;
    
    // sum = sum_of_nums(ans, 2, 3, "0", "0", "0");

    // sum = sum_of_nums(ans, 2, 2, "0000000000000000000000000000000001001", "00000000000000000000");

    // sum = sum_of_nums(ans, 16, 3, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "2", "0");


    // printf("AA + Z + 12 36th\n");
    // sum = sum_of_nums(ans, 36, 3, "AA", "Z", "12");


    // printf("GIANT + GIGANT 33th\n");
    // sum = sum_of_nums(ans, 33, 2, "GIANT", "GIGANT");
    


    if (NULL == sum)
    {
        printf("Cannot allocate memory!\n");
        return 1;
    }
    printf("%s\n", sum);

    free(ans);

    return 0;
}