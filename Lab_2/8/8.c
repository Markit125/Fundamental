#include <stdio.h>


double function(double x)
{
    return (x + 2) * (x + 3) - 4;
}

double root(double a, double b, double eps)
{
    double mid;
    double f;
    while (b - a > eps)
    {
        mid = (a + b) / 2;
        f = function(mid);
        if (f * function(a) > 0)
        {
            a = mid;
        }
        else
        {
            b = mid;
        }
    }

    return a;
}


int main()
{
    double x = root(-2, 2, 0.0000001);
    printf("%.18f\n", x);
    printf("%.18f\n\n", function(x));

    x = root(-6, -2, 0.0000001);
    printf("%.18f\n", x);
    printf("%.18f\n", function(x));


    return 0;
}