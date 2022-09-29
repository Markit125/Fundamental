

#include "matrix.c"
#include <stdio.h>

#define INT_MAX 2147483647

#define ROWS 2
#define COLS 2



int main(int argc, char *argv[])
{
    float **matrix;

    int rows = ROWS;
    int columns = COLS;

    printf("Incorrect!\n");
    if (matrix_gen(&matrix, rows, columns) != 0)
    {
        printf("Incorrect number of rows or columns!\n");
        return 1;
    }

    print_matrix(matrix);
}