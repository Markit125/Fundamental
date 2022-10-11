#include <stdio.h>
#include <stdlib.h>

#include "matrix.c"

#define INT_MAX 2147483647


int main(int argc, char *argv[])
{
    srandom(time(NULL));
    
    double **matrix_0;
    int err = enter_matrix(&matrix_0);
    if (err != 0)
    {
        switch (err) {
            case 1:
                printf("Too large size!\n");
                break;
            case 2:
                printf("This is not a positive integer number!\n");
                break;
            case 3:
                printf("Wrong size!\n");
                break;
            case 4:
                printf("Too large number!\n");
                break;
            case 5:
                printf("This is not a number!\n");
                break;
            // case
        }
        return 1;
    }
    
    matrix_print(matrix_0);
    printf("Second\n");

    double **matrix_1;
    err = enter_matrix(&matrix_1);
    if (err != 0)
    {
        switch (err) {
            case 1:
                printf("Too large size!\n");
                break;
            case 2:
                printf("This is not a positive integer number!\n");
                break;
            case 3:
                printf("Wrong size!\n");
                break;
            case 4:
                printf("Too large number!\n");
                break;
            case 5:
                printf("This is not a number!\n");
                break;
        }
        return 1;
    }
    matrix_print(matrix_1);

    double **matrix_mp;
    


    if (matrix_multiply(&matrix_0, &matrix_1, &matrix_mp) != 0)
    {
        printf("Incorrect number of rows or columns!\n");
        return 1;
    }

    matrix_print(matrix_mp);

    double det;
    if (determinant(&matrix_mp, &det) == 0)
    {
        printf("Determinant = %f\n", det);
    }
    else
    {
        printf("Determinant cannot be found!\n");
    }


    matrix_delete(&matrix_0);
    matrix_delete(&matrix_1);
    matrix_delete(&matrix_mp);

    printf("\n");

    return 0;
}