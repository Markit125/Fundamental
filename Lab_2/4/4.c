#include <math.h>
#include <stdio.h>
#include <stdarg.h>


double power(double num, int extent)
{
    if (extent == 0)
    {
        return 1;
    }

    if (extent > 0)
    {
        return num * power(num, extent - 1);
    }

    return (double) 1 / power(num, -extent);
}


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
    double a = 0.5, m = 1.25, pi = 3.14159, G = 8.86, e = 2.718281828;

    printf("a = %lf, m = %lf, pi = %lf, G = %lf, e = %lf\n", a, m, pi, G, e);

    printf("%s%lf\n%s%lf\n%s%lf\n%s%lf\n",
            "gaverage of a and m is ", geometric_average(2, a, m),
            "gaverage of a, m, pi, G is ", geometric_average(4, a, m, pi, G),
            "gaverage of pi, e is ", geometric_average(2, pi, e),
            "gaverage of all these is ", geometric_average(5, a, m, pi, G, e));


    printf("%s%lf\n%s%lf\n%s%lf\n%s%lf\n%s%lf\n",
            "pi^2 is ", power(pi, 2),
            "e^(-1) is ", power(e, -1),
            "a^(-50) is ", power(a, -50),
            "G^(-3) is ", power(G, -3),
            "a^10 is ", power(a, 10));
}