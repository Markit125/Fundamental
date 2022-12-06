#include "filework.c"


int main(int argc, char *argv[])
{
    int err = ReadFiles(argc, *argv);
    if (err) {
        switch (err) {
            case 1:
                printf("FO \n");
        }
    }

    return 0;
}