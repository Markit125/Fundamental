#include <stdio.h>
#include <stdarg.h>


typedef struct
{
    int x;
    int y;
} point;

int is_convex(int count, ...)
{
    if (count % 2)
    {
        return -1;
    }
    int count_dots = count / 2;

    point dots[count_dots];
    va_list ap;

    va_start(ap, count);

    int i;
    for (i = 0; i < count_dots; ++i)
    {
        dots[i].x = va_arg(ap, double);
        dots[i].y = va_arg(ap, double);
    }



}


int main()
{
    
}