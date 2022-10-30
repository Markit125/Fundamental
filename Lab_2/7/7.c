#include <stdio.h>
#include "functions.c"


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

    conv = is_convex(8, (double) 1, (double) 1, (double) 0, (double) 1, (double) 0, (double) 0, (double) 1, (double) 0);
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

    // conv = is_convex(24, (double) 1.2351, (double) 3, (double) 5, (double) 3, (double) 7, (double) 2, (double) 10, (double) -1,
    //                 (double) 9, (double) -3, (double) 8.5, (double) -4, (double) 4, (double) -5, (double) 2, (double) -4,
    //                 (double) -1, (double) -2, (double) -2, (double) -1, (double) -2, (double) 1, (double) -1, (double) 2.5);
    // //       .        .
    // //   .                .
    // // .
    // // 
    // // .                         .
    // //   .
    // //                        .
    // //         .             .
    // //             .
    // printf("%s convex\n", conv ? "Is" : "Isn't");


    // double polynom_at_x;
    // double x;

    // printf("x\t\ty\n");
    // for (x = -2; x < 2; x += 0.5)
    // {
    //     polynom_at_x = polynom((double) x, (int) 4, (int) 1, (int) -5, (int) -3, (int) 3, (int) -10);
    //     printf("%f\t%f\n", x, polynom_at_x);
    // }

    // printf("\nx\t\ty\n");
    // for (x = -5; x < 5; x += 0.5)
    // {
    //     polynom_at_x = polynom((double) x, (int) 2, (int) 1, (int) 0, (int) -1);
    //     printf("%f\t%f\n", x, polynom_at_x);
    // }



    return 0;
}