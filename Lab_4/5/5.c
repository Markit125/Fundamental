#include "filework.c"
#include <stdio.h>


int main(int argc, char *argv[])
{
    int err = ReadFiles(argc, argv);
    if (err) {
        switch (err) {
            case 1:
                printf("There are not arguments!\n");
                break;
            case 2:
                printf("There is not such file!\n");
                break;
            case 3:
                printf("Cannot allocate memory!\n");
                break;
        }
    }

    return 0;
}