#include <stdio.h>
#include <stdarg.h>

#define MAX_DOUBLE 1.7976931348623157e+308


typedef struct
{
    double x;
    double y;
} point;


double sq_distance(point p0, point p1)
{
    return (p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y);
}


int orientation(point p0, point p1, point p2)
{
    int d = (p1.y - p0.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - p0.x);
    if (d > 0)
    {
        return 1;
    }
    else if (d < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


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

    double min_x = MAX_DOUBLE;
    int min_index = 0;

    int i;
    for (i = 0; i < count_dots; ++i)
    {
        dots[i].x = va_arg(ap, double);
        dots[i].y = va_arg(ap, double);
        
        if (dots[i].x < min_x)
        {
            min_x = dots[i].x;
            min_index = i;
        }
    }

    point on_hull = dots[min_index]; 

    int count_in_hull = 0;
    
    while (1)
    {
        ++count_in_hull;
        point next = dots[0];
        for (i = 0; i < count_dots; ++i)
        {
            int orient = orientation(on_hull, next, dots[i]);
            if (((next.x == on_hull.x) && (next.y == on_hull.y)) || orient == -1 ||
                (orient == 0 && sq_distance(on_hull, dots[i]) > sq_distance(on_hull, next)))
            {
                next = dots[i];
            }
        }
        on_hull = next;

        if ((on_hull.x == dots[min_index].x) && (on_hull.y == dots[min_index].y))
        {
            break;
        }
    }

    if (count_dots == count_in_hull)
    {
        return 1;
    }
    return 0;
}


int main()
{
    int conv = is_convex(8, (double) 2, (double) 3, (double) 0, (double) 0, (double) 4, (double) 0, (double) 2, (double) 1);
    //    .
    //  
    //    .
    //.       .
    printf("%s convex\n", conv ? "Is" : "Isn't");

    conv = is_convex(8, (double) 2, (double) 3, (double) 1, (double) 2, (double) 4, (double) 0, (double) 2, (double) 1);
    //    .
    //  .  
    //    .
    //        .
    printf("%s convex\n", conv ? "Is" : "Isn't");

    conv = is_convex(24, (double) 1.2351, (double) 3, (double) 5, (double) 3, (double) 7, (double) 2, (double) 10, (double) -1,
                    (double) 9, (double) -3, (double) 7.9, (double) -4, (double) 4, (double) -5, (double) 2, (double) -4,
                    (double) -1, (double) -2, (double) -2, (double) -1, (double) -2, (double) 1, (double) -1, (double) 2.5);
    //       .        .
    //   .                .
    // .
    // 
    // .                         .
    //   .
    //                        .
    //         .            .
    //             .
    printf("%s convex\n", conv ? "Is" : "Isn't");

     conv = is_convex(24, (double) 1.2351, (double) 3, (double) 5, (double) 3, (double) 7, (double) 2, (double) 10, (double) -1,
                    (double) 9, (double) -3, (double) 8.5, (double) -4, (double) 4, (double) -5, (double) 2, (double) -4,
                    (double) -1, (double) -2, (double) -2, (double) -1, (double) -2, (double) 1, (double) -1, (double) 2.5);
    //       .        .
    //   .                .
    // .
    // 
    // .                         .
    //   .
    //                        .
    //         .             .
    //             .
    printf("%s convex\n", conv ? "Is" : "Isn't");

    return 0;
}