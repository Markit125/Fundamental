
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ABS 100

int get_rand_int(int max_abs_value)
{
    return rand() % max_abs_value * (rand() % 2 ? 1 : -1);
}


int matrix_gen(float ***matrix, int rows, int columns)
{
        printf("ddd");
    if (rows < 1 || columns < 1)
    {
        return 1;
    }

    // *matrix = (float **) malloc(sizeof(float *) * rows);
    // int i = 0;
    // for (i = 0; i < rows; ++i)
    // {
    //     *matrix[i] = (float *) malloc(sizeof(float) * columns);


    //     srand(time(NULL));
    //     int j;
    //     for (j = 0; j < columns; ++j)
    //     {
    //         *matrix[i][j] = get_rand_int(ABS);
    //     }
    // }

    return 0;
}


int print_matrix(float **matrix)
{
    int rows = sizeof(matrix);
    int columns = sizeof(matrix[0]);

    int i;
    for (i = 0; i < rows; ++i)
    {

        int j;
        for (j = 0; j < columns; ++j)
        {
            printf("%f ", matrix[i][j]);
        }
    }

    return 0;
}