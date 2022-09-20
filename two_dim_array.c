#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n = 10;
    // int *a = (int*) malloc(sizeof(int) * n);
    // for (int i = 0; i < n; ++i) {
    //     *(a + i) = i;
    // }

    // for (int i = 0; i < n; ++i) {
    //     printf("%d ", i[a]);
    // } printf("\n");

    int m = 5;
    int **double_dim = (int**) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; ++i)
    {
        double_dim[i] = malloc(sizeof(int));
        for (int j = 0; j < m; ++j)
        {
            double_dim[i][j] = i * m + j;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            // printf("%d\t", *(*(double_dim + i) + j));
            printf("%d\t", j[i[double_dim]]);
            // printf("%d\t", double_dim[i][j]);
        } printf("\n");
    } printf("\n");


}