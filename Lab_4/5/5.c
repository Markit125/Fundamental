#include "filework.c"
#include <stdio.h>


int main(int argc, char *argv[])
{
    int err = read_files(argc, argv);
    if (err) {
        switch (err) {
            case 1:
                printf("There are not arguments!\n");
                break;
            case 2:
                printf("There is no such file!\n");
                break;
            case 3:
                printf("Cannot allocate memory!\n");
                break;
            case 4:
                printf("Too many arguments!\n");
                break;
            case 6:
                printf("Wrong expression while calculating!\n");
                break;
            case 8:
                printf("Stack was lost\n");
                break;
            default:
                printf("Unclown error!\n");
                break;
        }
        return err;
    }

    return 0;
}