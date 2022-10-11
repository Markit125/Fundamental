
#include <stdio.h>
#include <stdlib.h>

#include "solve.c"
#include "arguments.c"


int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("No agruments!\n");
        return 1;
    }

    char *flag = NULL;

    if (is_flag(argv[1]))
    {
        flag = argv[1];
    }
    else
    {
        printf("Flag is incorrect!\n");
        return 1;
    }

    ++flag;
    int success = 1;

    if (*flag == 'q')
    {
        if (argc != 5)
        {
            printf("Wrong number of arguments!\n");
            return 1;
        }

        if (!(is_number(argv[2]) && is_number(argv[3]) && is_number(argv[4])))
        {
            printf("Coeficients aren't correct!");
            return 1;
        }

        float a = atof(argv[2]);
        float b = atof(argv[3]);
        float c = atof(argv[4]);

        int result;
        float x1, x2;
        if (solve_square_equation(a, b, c, &x1, &x2, &result) == 0)
        {
            if (result == 0)
            {
                printf("There is no real solutions");
            }
            else if (result == 1)
            {
                printf("x = %f", x1);
            }
            else if (result == 2)
            {
                printf("x1 = %f, x2 = %f", x1, x2);
            }
            else
            {
                printf("There are infinitive amount of solutions");
            }
        }
        else
        {
            success = 0;
        }
    }

    else if (*flag == 'm')
    {
        if (argc != 4)
        {
            printf("Wrong number of arguments!\n");
            return 1;
        }
        if (!(is_number(argv[2]) && is_number(argv[3])))
        {
            printf("Numbers aren't correct!");
            return 1;
        }

        int a = arg_to_int(argv[2]);
        int b = arg_to_int(argv[3]);

        if (a == 0 || b == 0)
        {
            printf("Both numbers must be non-zero\n");
            return 1;
        }

        if (a % b == 0)
        {
            printf("The first number is a multiple of the second");
        }
        else
        {
            printf("The first number is not a multiple of the second");
        }
    }

    else if (*flag == 't')
    {
        if (argc != 5)
        {
            printf("Wrong number of arguments!\n");
            return 1;
        }

        if (!(is_number(argv[2]) && is_number(argv[3]) && is_number(argv[4])))
        {
            printf("Coeficients aren't correct!");
            return 1;
        }

        float a = atof(argv[2]);
        float b = atof(argv[3]);
        float c = atof(argv[4]);

        int result;
        if (right_triangle(a, b, c, &result) == 0)
        {
            printf("These numbers can%s be the sides of a right triangle", result ? "" : "not");
        }
        else
        {
            success = 0;
        }
    }

    else
    {
        printf("This flag is not exists!\n");
        return 1;
    }

    if (!success)
    {
        printf("Error\n");
        return -1;
    }


    printf("\n");

    return 0;
}
