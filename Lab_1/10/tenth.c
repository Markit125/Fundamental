#include <stdio.h>

#include "matrix.c"

#define INT_MAX 2147483647


int main(int argc, char *argv[])
{
    srandom(time(NULL));

    int rows = ROWS;
    int columns = COLS;


    float **matrix_0;

    if (matrix_gen(&matrix_0, rows, columns) != 0)
    {
        printf("Incorrect number of rows or columns!\n");
        return 1;
    }

    matrix_print(&matrix_0);


    float **matrix_1;

    if (matrix_gen(&matrix_1, columns, rows) != 0)
    {
        printf("Incorrect number of rows or columns!\n");
        return 1;
    }

    matrix_print(&matrix_1);


    float **matrix_mp;

    if (matrix_multiply(&matrix_0, &matrix_1, &matrix_mp) != 0)
    {
        printf("Incorrect number of rows or columns!\n");
        return 1;
    }

    matrix_print(&matrix_mp);

    float det;
    if (determinant(&matrix_mp, &det) == 0)
    {
        printf("Determinant = %f", det);
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