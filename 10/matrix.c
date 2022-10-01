
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ROWS 3
#define COLS 3

#define ABS 100


int get_rand_int(int max_abs_value)
{
    return random() % max_abs_value * (random() % 2 ? 1 : -1);
}


int matrix_gen(float ***matrix, int rows, int columns)
{
    if (rows < 1 || columns < 1)
    {
        return 1;
    }

    *matrix = (float **) malloc(sizeof(float *) * (rows + 1));

    (*matrix)[0] = (float *) malloc(sizeof(int) * 2);
    (*matrix)[0][0] = rows;
    (*matrix)[0][1] = columns;


    int i;
    for (i = 1; i < rows + 1; ++i)
    {
        (*matrix)[i] = (float *) malloc(sizeof(float) * columns);

        int j;
        for (j = 0; j < columns; ++j)
        {
            (*matrix)[i][j] = get_rand_int(ABS);
            // (*matrix)[i][j] = (i - 1) * columns + j;
        }
    }

    return 0;
}


int matrix_print(float ***matrix)
{
    int rows = (*matrix)[0][0];
    int columns = (*matrix)[0][1];

    int i;
    for (i = 1; i < rows + 1; ++i)
    {
        int j;
        for (j = 0; j < columns; ++j)
        {
            printf("%f ", (*matrix)[i][j]);
        } printf("\n");
    } printf("\n");
    

    return 0;
}


int matrix_delete(float ***matrix)
{
    int rows = (*matrix)[0][0];
    int columns = (*matrix)[0][1];

    int i;
    for (i = 1; i < rows + 1; ++i)
    {
        free((*matrix)[i]);
    }
    free((*matrix[0]));
    free(*matrix);

    return 0;
}


int matrix_multiply(float ***m1, float ***m2, float ***m3)
{
    if ((*m1)[0][1] != (*m2)[0][0])
    {
        return 1;
    }


    int rows = (*m1)[0][0];
    int columns = (*m2)[0][1];
    int factors = (*m2)[0][0];


    *m3 = (float **) malloc(sizeof(float *) * (rows + 1));
    
    (*m3)[0] = (float *) malloc(sizeof(int) * 2);
    (*m3)[0][0] = rows;
    (*m3)[0][1] = columns;


    int a = 0;
    int y;
    for (y = 1; y < rows + 1; ++y)
    {
        (*m3)[y] = (float *) malloc(sizeof(float) * columns);
        int x;
            a = 0;
        for (x = 0; x < columns; ++x)
        {
            int i;
            for (i = 0; i < factors; ++i)
            {
                (*m3)[y][x] += (*m1)[y][i] * (*m2)[i + 1][x];
            }
        }
    }

    return 0;
}


int determinant(float ***matrix, float *det)
{
    int rows = (*matrix)[0][0];
    int columns = (*matrix)[0][1];

    if (rows != columns)
    {
        return 1;
    }

    float **triangle = (float **) malloc(sizeof(float *) * (rows + 1));
    triangle[0] = (float *) malloc(sizeof(int) * 2);
    triangle[0][0] = rows;
    triangle[0][1] = columns;
    
    int i;
    for (i = 1; i < rows + 1; ++i)
    {
        triangle[i] = (float *) malloc(sizeof(float) * columns);
        int j;
        for (j = 0; j < columns; ++j)
        {
            triangle[i][j] = (*matrix)[i][j];
        }
    }

    for (i = 2; i < rows + 1; ++i)
    {
        int j;
        for (j = 0; j < i - 1; ++j)
        {
            float diff = triangle[i][j] / triangle[j + 1][j];

            // printf("\n%f / %f\n", triangle[i][j], triangle[j + 1][j]);
            // printf("dff:%f\n\n", diff);

            int k;
            for (k = 0; k < columns; ++k)
            {
                triangle[i][k] -= diff * triangle[j + 1][k];
            }
            
            // printf("Matrix:\n");
            // printf("\n");
        }
    }

    *det = 1;
    for (i = 1; i < rows + 1; ++i)
    {
        *det *= triangle[i][i - 1];
    }

    matrix_print(&triangle);
    matrix_delete(&triangle);

    return 0;
}