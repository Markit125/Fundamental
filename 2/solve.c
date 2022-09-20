
#include <math.h>
#include <stdio.h>

int solve_square_equation(float a, float b, float c, float *x1, float *x2, int *result)
{
    if (a == 0 && b == 0)
    {
        *result = 3;
    }
    else if (a == 0)
    {
        *x1 = -c / b;
        *result = 1;
    }
    else if (b == 0)
    {
        if (c > 0)
        {
            *result = 0;
        }
        else
        {
            *x1 = -sqrt(-c / a);
            *x2 = sqrt(-c / a);
            *result = 2;
            if (*x1 == *x2)
            {
                --*result;
            }
        }
    }
    else
    {
        float disc = b * b - 4 * a * c;
        if (disc < 0)
        {
            *result = 0;
        }
        else if (disc == 0)
        {
            *x1 = -b / a / 2;
            *result = 1;
        }
        else
        {
            *x1 = (-b - sqrtf(disc)) / a / 2;
            *x2 = (-b + sqrtf(disc)) / a / 2;
            *result = 2;
        }
    }

    return 0;
}

int right_triangle(float a, float b, float c, int *result)
{
    if (!(a > 0 && b > 0 && c > 0))
    {
        *result = 0;
        return 0;
    }

    a *= a;
    b *= b;
    c *= c;
    if (a + b == c || a + c == b || b + c == a)
    {
        *result = 1;
    }
    else
    {
        *result = 0;
    }
    return 0;
}