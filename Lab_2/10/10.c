#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_COUNT_REMAINDERS 10
#define FIND_TILL 20


int is_endless(double n, int base)
{
    if (n == 1 || n == 0)
    {
        return 0;
    }

    int rems_count = DEFAULT_COUNT_REMAINDERS;
    double *rems = (double *) malloc(sizeof(double) * rems_count);
    
    if (rems == NULL)
    {
        return -1;
    }

    rems[0] = n;

    double rem;
    int i;
    int j;
    for (i = 0; i < FIND_TILL; ++i)
    {
        rem = rems[i] * base;
        rem -= (int) rem;

        if (rem == 0)
        {
            free(rems);
            return 0;
        }

        rems[i + 1] = rem;

        for (j = 0; j < i; ++j)
        {
            if (rems[j] == rem)
            {
                free(rems);
                return 1;
            }
        }

        if (i == rems_count - 1)
        {
            rems_count *= 2;
            double *ptr = (double *) realloc(rems, sizeof(double) * rems_count);

            if (ptr == NULL)
            {
                free(rems);
                return -1;
            }

            rems = ptr;
        }
    }

    free(rems);

    return 1;
}


int check_endless(double a[], int base, int count, ...)
{
    if (count > 10)
    {
        return 1;
    }

    va_list ap;
    va_start(ap, count);

    int i;
    double *ptr = a;
    double num;

    for (i = 0; i < count; ++i)
    {
        num = va_arg(ap, double);
        int endless = is_endless(num, base);
        
        if (!endless)
        {
            *(ptr++) = num;
        }
        else if (endless == -1)
        {
            va_end(ap);
            return -1;
        }
    }

    va_end(ap);
    *(ptr) = -1;

    return 0;
}


int main()
{
    double arr[11];
    arr[10] = -1;

    int err = check_endless(arr, 8, 3, (double) 0.74, (double) 0.5, (double) 0.5625);

    if (err == 1)
    {
        printf("Too many numbers!\n");
        return 1;
    }
    else if (err == -1)
    {
        printf("Memory error!\n");
        return 1;
    }

    int i = 0;
    printf("These decimal numbers aren't endless in binary system:\n");

    while (arr[i] != -1)
    {
        printf("%f\n", arr[i++]);
    }

}