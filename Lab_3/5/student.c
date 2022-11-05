#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text_functions.c"

#define INF 2147483647


typedef struct Student
{
    int id;
    char *name;
    short course;
    char *group;
    short *grades;
} Student;


int set_id(char *in, Student *student)
{
    int id;
    if (is_integer_range(in, &id, 1, INF))
    {
        student->id = id;
        return 0;
    }
    return 1;
}


int set_name(char *in, Student *student)
{
    if (is_right_string(in, 1) && strlen(in) > 0)
    {
        student->name = (char *) malloc(sizeof(char) * strlen(in));
        strcpy(student->name, in);
        return 0;
    }
    return 1;
}


int set_course(char *in, Student *student)
{
    int course;
    if (is_integer_range(in, &course, 1, 4))
    {
        student->course = (short) course;
        return 0;
    }
    return 1;
}


int set_group(char *in, Student *student)
{
    if (is_right_string(in, 0) && strlen(in) > 0)
    {
        student->group = (char *) malloc(sizeof(char) * strlen(in));
        strcpy(student->group, in);
        return 0;
    }
    return 1;
}


int set_grade(char *in, Student *student, int position)
{
    if (position > 4)
    {
        return 1;
    }

    int grade;
    if (is_integer_range(in, &grade, 2, 5))
    {   
        if (NULL == student->grades)
        {
            student->grades = (short *) malloc(sizeof(short) * 5);
        }

        *(student->grades + position) = (short) grade;
        return 0;
    }
    return 1;
}


int print_student(Student *s)
{
    printf("======\n");
    printf("ID: %d\nName: %s\nCourse %d\nGroup %s\nGrades: ",
            (*s).id, (*s).name, (*s).course, (*s).group);

    int i;
    for (i = 0; i < 5; ++i)
    {
        printf("%d ", *((*s).grades + i));
    }
    printf("\n======\n");

    return 0;
}


int free_students(Student *studs, int count)
{
    int i;
    for (i = 0; i < count; ++i)
    {
        free((studs + i)->grades);
        free((studs + i)->name);
        free((studs + i)->group);
    }
    free(studs);

    return 0;
}