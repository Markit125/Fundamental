#include <stdio.h>
#include "student_funcs.c"

#define START_COUNT 3


int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("There are too many arguments!\n");
        return 1;
    }

    if (argc < 2)
    {
        printf("You should pass the path to file!\n");
        return 2;
    }

    int count_notes = START_COUNT, line_corrupt = 0;

    Student *studs = (Student *) malloc(sizeof(Student) * count_notes);
    if (NULL == studs)
    {
        printf("Cannot allocate memory!\n");
        return 3;
    }

    FILE *f = fopen(argv[1], "r");
    if (NULL == f)
    {
        printf("Such file does not exists!\n");
        return 4;
    }

    int err = read_file(f, studs, &count_notes, &line_corrupt);
    if (err == 1)
    {
        printf("There is not enough memory!\n");
        return -1;
    }
    else if (err >= 4)
    {
        printf("File is corrupted!\nWrong ");
        switch (err)
        {
            case 4:
                printf("ID");
                break;
            case 5:
                printf("Name");
                break;
            case 6:
                printf("Course");
                break;
            case 7:
                printf("Group");
                break;
            case 8:
                printf("Grade");
                break;
            default:
                printf("Something...");
        }
        printf(" at the line %d\n", line_corrupt);
        return 5;
    }



    int i;
    for (i = 0; i < count_notes; ++i)
    {
        print_student(studs + i);
    }

    free_students(studs, count_notes);


    return 0;
}