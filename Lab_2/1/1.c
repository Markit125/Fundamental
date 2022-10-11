#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARR_LEN 10
#define MAX_ABS 100
#define INF 2147483647

int absolute(int a)
{
    return a > 0 ? a : -a;
}

int get_rand_positive_int(int max_abs_value)
{
    int x = random() % max_abs_value + 1;
}

int get_rand_int(int max_abs_value)
{
    return random() % max_abs_value * (random() % 2 ? 1 : -1);
}

int partition(int *a, int left, int right);


int swap(int *a, int i, int j)
{   
    int t = a[i];
    a[i] = a[j];
    a[j] = t;

    return 0;
}

void quick_sort(int *a, int left, int right)
{
    if (left < right) {
        int part = partition(a, left, right);
        quick_sort(a, left, part - 1);
        quick_sort(a, part + 1, right);
    }

}

int partition(int *a, int left, int right)
{
    int pivot = a[right];
    int i = (left - 1);
  
    for (int j = left; j <= right - 1; j++) {
        if (a[j] < pivot) {
            ++i;
            swap(a, i, j);
        }
    }
    swap(a, i + 1, right);
    return (i + 1);
}
  



int main(int argc, char *argv[])
{
    srandom(time(NULL));

    int len_a = get_rand_positive_int(10);
    int len_b = get_rand_positive_int(10);

    int a[len_a];
    int b[len_b];
    int c[len_a];

    int i;
    for (i = 0; i < len_a; ++i)
    {
        a[i] = get_rand_int(MAX_ABS);
    }

    for (i = 0; i < len_b; ++i)
    {
        b[i] = get_rand_int(MAX_ABS);
    }

    quick_sort(b, 0, len_b - 1);

    for (i = 0; i < len_b; ++i)
    {
        printf("%d ", b[i]);
    }
    printf("\n");


    int j;
    for (j = 0; j < len_a; ++j)
    {
        int done = 0;
        for (i = 1; i < len_b; ++i)
        {
            if (a[j] <= b[i])
            {
                if (absolute(a[j] - b[i - 1]) < absolute(b[i] - a[j]))
                {
                    c[j] = a[j] + b[i - 1];
                }
                else
                {
                    c[j] = a[j] + b[i];
                }
                done = 1;
                break;
            }
        }
        if (!done)
        {
            c[j] = a[j] + b[len_b - 1];
        }
    }

    for (i = 0; i < len_a; ++i)
    {
        printf("%d ", c[i]);
    }

    printf("\n");

    return 0;
}