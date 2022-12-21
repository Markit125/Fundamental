#include <stdio.h>
#include <stdlib.h>

#include "matrix.c"

#define INT_MAX 2147483647


int main(int argc, char *argv[])
{
    srandom(time(NULL));
    
    printf("First matrix\n");
    printf("Enter count of rows and coloumns:\n");

    double **matrix_0;
    int err = enter_matrix(&matrix_0);
    if (err != 0)
    {
        if (err <= 5)
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
            free(matrix_0);
        }
        else
        {
            if (err == 14)
            {
                printf("Cannot allocate memory!\n");
            }
            else if (err == 11)
            {
                printf("Wrong number!\n");
            }
            matrix_delete(&matrix_0);
        }
        
        return err;
    }
    
    matrix_print(matrix_0);
    printf("Second matrix\n");

    double **matrix_1;
    err = enter_matrix(&matrix_1);
    if (err != 0)
    {
        if (err <= 5)
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
            free(matrix_0);
        }
        else
        {
            if (err == 14)
            {
                printf("Cannot allocate memory!\n");
            }
            else if (err == 11)
            {
                printf("Wrong number!\n");
            }
            matrix_delete(&matrix_1);
        }
        matrix_delete(&matrix_0);

        return err;
    }
    matrix_print(matrix_1);

    double **matrix_mp;
    

    err = matrix_multiply(&matrix_0, &matrix_1, &matrix_mp);
    if (err)
    {
        printf("Incorrect number of rows or columns!\n");
        matrix_delete(&matrix_0);
        matrix_delete(&matrix_1);
        matrix_delete(&matrix_mp);
        return 3;
    }


    double det;
    err = determinant(&matrix_0, &det);
    
    if (err == 0)
    {
        printf("Determinant of the matrix 0 = %f\n", det);   
    }
    else if (err == 1)
    {
        matrix_delete(&matrix_0);
        matrix_delete(&matrix_1);
        matrix_delete(&matrix_mp);
        printf("Determinant cannot be found!\n");
        return 4;
    }
    else if (err == 2)
    {
        matrix_delete(&matrix_0);
        matrix_delete(&matrix_1);
        matrix_delete(&matrix_mp);
        printf("Cannot allocate memory!\n");
        return 5;
    }


    err = determinant(&matrix_1, &det);
    
    if (err == 0)
    {
        printf("Determinant of the matrix 1 = %f\n\n\n", det);
    }
    else if (err == 1)
    {
        matrix_delete(&matrix_0);
        matrix_delete(&matrix_1);
        matrix_delete(&matrix_mp);
        printf("Determinant cannot be found!\n");
        return 4;
    }
    else if (err == 2)
    {
        matrix_delete(&matrix_0);
        matrix_delete(&matrix_1);
        matrix_delete(&matrix_mp);
        printf("Cannot allocate memory!\n");
        return 5;
    }



    printf("Composed matrix:\n");
    matrix_print(matrix_mp);

    err = determinant(&matrix_mp, &det);
    
    if (err == 0)
    {
        printf("Determinant of the new matrix = %f\n", det);   
    }
    else if (err == 1)
    {
        matrix_delete(&matrix_0);
        matrix_delete(&matrix_1);
        matrix_delete(&matrix_mp);
        printf("Determinant cannot be found!\n");
        return 4;
    }
    else if (err == 2)
    {
        matrix_delete(&matrix_0);
        matrix_delete(&matrix_1);
        matrix_delete(&matrix_mp);
        printf("Cannot allocate memory!\n");
        return 5;
    }



    matrix_delete(&matrix_0);
    matrix_delete(&matrix_1);
    matrix_delete(&matrix_mp);

    printf("\n");

    return 0;
}