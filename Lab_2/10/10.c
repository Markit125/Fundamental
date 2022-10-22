#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_COUNT_REMAINDERS 10


int is_endless(double n, int base)
{
    if (n == 1 || n == 0)
    {
        return 0;
    }

    int rems_count = DEFAULT_COUNT_REMAINDERS;
    int *rems = (int *) malloc(sizeof(int) * rems_count);
    if (rems == NULL)
    {
        return -1;
    }

    double checker = n;
    int divisor = 1;

    while (checker != (double) ((int) checker))
    {
        checker *= 10;
        divisor *= 10;
        if (checker > 300)
        {
            checker -= (((int) checker) / 1000) * 1000;
        }
    }

    rems[0] = (int) checker;
    int set[base - 1];
    int i;
    for (i = 0; i < base - 1; ++i)
    {
        set[i] = 0;
    }

    int rem;
    for (i = 0; i < 20; ++i)
    {
        rem = rems[i] % base;

        if (rem == 0)
        {
            free(rems);
            return 0;
        }

        rems[i + 1] = rem;

        if (set[rem - 1] == 0)
        {
            set[rem - 1] = 1;
        }
        else
        {
            free(rems);
            return 1;
        }

        if (i == rems_count - 1)
        {
            rems_count *= 2;
            int *ptr = (int *) realloc(rems, sizeof(int) * rems_count);
            if (ptr == NULL)
            {
                free(rems);
                return -1;
            }
            rems = ptr;
            free(ptr);
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
        printf("%d\n", endless);
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

    int err = check_endless(arr, 2, 3, (double) 0.8, (double) 0.5, (double) 0.23);

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