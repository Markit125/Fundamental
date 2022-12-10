
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arguments.c"


#define ROWS 3
#define COLS 3

#define ABS 100


int read_number(double ***m, int i, int j)
{
    char c = 0;
    char *num = (char *) malloc(sizeof(char) * 15);
    if (NULL == num)
    {
        return 2;
    }

    int it = 0;
    while (is_space(c))
    {
        c = getchar();
    }
    
    
    do
    {
        *(num + it++) = c;
    } while (!is_space(c = getchar()));
    *(num + it) = '\0';

    if (!is_number(num))
    {
        return 1;
    }
    (*m)[i][j] = atof(num);
    free(num);

    return 0;
}


int matrix_genf(double ***matrix, int rows, int columns)
{
    *matrix = (double **) malloc(sizeof(double *) * (rows + 1));
    if (NULL == *matrix)
    {
        return 2;
    }

    (*matrix)[0] = (double *) malloc(sizeof(int) * 2);
    if (NULL == (*matrix)[0])
    {
        return 2;
    }
    (*matrix)[0][0] = rows;
    (*matrix)[0][1] = columns;

    printf("Enter values:\n");
    int err;
    int i;
    for (i = 1; i <= rows; ++i)
    {
        (*matrix)[i] = (double *) malloc(sizeof(double) * columns);
        if (NULL == (*matrix)[i])
        {
            return 2;
        }

        int j;
        for (j = 0; j < columns; ++j)
        {
            err = read_number(matrix, i, j);
            if (err != 0)
            {
                return err;
            }
            // scanf("%lf", &(*matrix)[i][j]);
        }
    }

    return 0;
}


int get_rand_int(int max_abs_value)
{
    return random() % max_abs_value * (random() % 2 ? 1 : -1);
}


int matrix_gen(double ***matrix, int rows, int columns)
{
    if (rows < 1 || columns < 1)
    {
        return 1;
    }

    *matrix = (double **) malloc(sizeof(double *) * (rows + 1));
    if (NULL == *matrix)
    {
        return 2;
    }

    (*matrix)[0] = (double *) malloc(sizeof(int) * 2);
    if (NULL == (*matrix)[0])
    {
        return 2;
    }

    (*matrix)[0][0] = rows;
    (*matrix)[0][1] = columns;


    int i;
    for (i = 1; i <= rows; ++i)
    {
        (*matrix)[i] = (double *) malloc(sizeof(double) * columns);
        if (NULL == (*matrix)[i])
        {
            return 2;
        }

        int j;
        for (j = 0; j < columns; ++j)
        {
            (*matrix)[i][j] = get_rand_int(ABS);
        }
    }

    return 0;
}


int matrix_print(double **matrix)
{
    int rows = matrix[0][0];
    int columns = matrix[0][1];

    int i;
    for (i = 1; i <= rows; ++i)
    {
        int j;
        for (j = 0; j < columns; ++j)
        {
            printf("%f ", matrix[i][j]);
        } printf("\n");
    } printf("\n");
    

    return 0;
}


int matrix_delete(double ***matrix)
{
    int rows = (*matrix)[0][0];
    int columns = (*matrix)[0][1];

    int i;
    for (i = 0; i <= rows; ++i)
    {
        free((*matrix)[i]);
    }
    
    free(*matrix);

    return 0;
}


int matrix_multiply(double ***m1, double ***m2, double ***m3)
{
    if ((*m1)[0][1] != (*m2)[0][0])
    {
        return 1;
    }


    int rows = (*m1)[0][0];
    int columns = (*m2)[0][1];
    int factors = (*m2)[0][0];

    *m3 = (double **) malloc(sizeof(double *) * (rows + 1));
    if (NULL == *m3)
    {
        return 2;
    }
    
    (*m3)[0] = (double *) malloc(sizeof(int) * 2);
    if (NULL == *m3)
    {
        return 2;
    }

    (*m3)[0][0] = rows;
    (*m3)[0][1] = columns;


    int a = 0;
    int y;
    for (y = 1; y <= rows; ++y)
    {
        (*m3)[y] = (double *) malloc(sizeof(double) * columns);
        if (NULL == (*m3)[y])
        {
            return 2;
        }
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


int determinant(double ***matrix, double *det)
{
    int rows = (*matrix)[0][0];
    int columns = (*matrix)[0][1];

    if (rows != columns)
    {
        return 1;
    }

    double **triangle = (double **) malloc(sizeof(double *) * (rows + 1));
    if (NULL == triangle)
    {
        return 2;
    }
    triangle[0] = (double *) malloc(sizeof(int) * 2);
    if (NULL == triangle[0])
    {
        return 2;
    }
    triangle[0][0] = rows;
    triangle[0][1] = columns;
    
    int i;
    for (i = 1; i <= rows; ++i)
    {
        triangle[i] = (double *) malloc(sizeof(double) * columns);
        if (NULL == triangle[i])
        {
            return 2;
        }
        int j;
        for (j = 0; j < columns; ++j)
        {
            triangle[i][j] = (*matrix)[i][j];
        }
    }

    *det = 1;
    if (triangle[1][0] == 0 && rows > 1)
    {
        int i;
        for (i = 2; i <= rows; ++i)
        {
            if (triangle[i][0] != 0)
            {
                double *ptr = triangle[i];
                triangle[i] = triangle[1];
                triangle[1] = ptr;
                *det = -1;
                break;
            }
        }
    }

    for (i = 2; i <= rows; ++i)
    {
        int j;
        for (j = 0; j < i - 1; ++j)
        {
            double diff = triangle[i][j] / triangle[j + 1][j];
            int k;
            for (k = 0; k < columns; ++k)
            {
                triangle[i][k] -= diff * triangle[j + 1][k];
            }
        }
    }

    for (i = 1; i <= rows; ++i)
    {
        *det *= triangle[i][i - 1];
    }

    matrix_print(triangle);
    matrix_delete(&triangle);

    return 0;
}


int read_size(int *rows, int *columns)
{
    *rows = -1;
    *columns = -1;
    char *number = (char *) malloc(sizeof(char) * 10);
    if (NULL == number)
    {
        return 4;
    }

    char c = ' ';
    int it = 0;
    int count = 0;
    while (count < 2)
    {
        c = getchar();
        if (!is_space(c))
        {
            *(number + it++) = c;

            if (it == 10) {
                return 1;
            }
        }
        else if (it != 0)
        {
            *(number + it) = '\0';
            if (is_integer(number))
            {
                *rows == -1 ? (*rows = arg_to_int(number)) : (*columns = arg_to_int(number));
                it = 0;
                ++count;
            }
            else
            {
                return 2;
            }
        }
    }

    if (*rows < 1 || *columns < 1)
    {
        return 3;
    }

    return 0;
}


int enter_matrix(double ***m)
{
    printf("Enter count of rows and coloumns:\n");
    int rows = 0;
    int columns = 0;

    int err = read_size(&rows, &columns);
    if (err != 0)
    {
        return err;
    }
    err = matrix_genf(m, rows, columns);
    

    if (err != 0)
    {
        return err;
    }

    return 0;
}