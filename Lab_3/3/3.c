#include <stdio.h>
#include "filework.c"


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Wrong count of arguments!\n");
        return WRONG_COUNT_OF_ARGS;
    }

    if (!is_flag(*(argv + 2)))
    {
        printf("Wrong flag!\n");
        return WRONG_FLAG;
    }
    else if (*(*(argv + 2) + 1) != 'a' || *(*(argv + 2) + 1) != 'd')
    {
        printf("Such flag does not exists!\n");
        return WRONG_FLAG;
    }


    int err;
    err = read_file(*(argv + 1), *(argv + 2));
    switch (err)
    {
        case FILE_NOT_FOUND:
            printf("There is no such file!\n");
            break;

    }

    return err;
}