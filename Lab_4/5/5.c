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
        }
    }

    return 0;
}