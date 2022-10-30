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


int main(int argc, char *argv[])
{
    srandom(time(NULL));

    int len_a = get_rand_positive_int(10);
    int len_b = get_rand_positive_int(10);

    // scanf("%d %d", &len_a, &len_b);

    int *a = (int *) malloc(sizeof(int) * len_a);
    int *b = (int *) malloc(sizeof(int) * len_b);
    int *c = (int *) malloc(sizeof(int) * len_a);

    int i;
    for (i = 0; i < len_a; ++i)
    {
        *(a + i) = get_rand_int(MAX_ABS);
        printf("%d ", *(a + i));

        // scanf("%d", (a + i));
    } printf("\n");

    for (i = 0; i < len_b; ++i)
    {
        *(b + i) = get_rand_int(MAX_ABS);
        printf("%d ", *(b + i));

        // scanf("%d", (b + i));
    } printf("\n");



    int min_diff_index = 0;

    int j;
    for (j = 0; j < len_a; ++j)
    {
        for (i = 0; i < len_b; ++i)
        {
            if (abs(*(a + j) - *(b + i)) < abs(*(a + j) - *(b + min_diff_index)))
            {
                min_diff_index = i;
            }
        }
        *(c + j) = *(a + j) + *(b + min_diff_index);
    }

    for (i = 0; i < len_a; ++i)
    {
        printf("%d ", *(c + i));
    } printf("\n");

    free(a);
    free(b);
    free(c);

    return 0;
}