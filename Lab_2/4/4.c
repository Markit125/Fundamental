#include <math.h>
#include <stdio.h>
#include <stdarg.h>


double geometric_average(int i, ...)
{
    double mult = 1;

    va_list ap;
    va_start(ap, i);

    int j;
    for (j = 0; j < i; ++j)
    {
        mult *= va_arg(ap, double);
    }

    va_end(ap);
    mult = pow(mult, (double) 1 / i);
    return mult;
}


int main()
{
    double a = 5, m = 1.25, pi = 3.14159, G = 8.86, e = 2.718281828;

    printf("a = %lf, m = %lf, pi = %lf, G = %lf, e = %lf\n", a, m, pi, G, e);

    printf("%s%lf\n%s%lf\n%s%lf\n%s%lf\n",
            "gaverage of a and m is ", geometric_average(2, a, m),
            "gaverage of a, m, pi, G is ", geometric_average(4, a, m, pi, G),
            "gaverage of pi, e is ", geometric_average(2, pi, e),
            "gaverage of all these is ", geometric_average(5, a, m, pi, G, e));
}