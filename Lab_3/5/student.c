#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text_functions.c"

#define INF 2147483647


typedef struct Student
{
    int id;
    char *name;
    char *last_name;
    short course;
    char *group;
    short *grades;
} Student;


typedef struct Node
{
    Student *student;
    struct Node *next;
} Node;


typedef struct Student_list
{
    int length;
    Node *first;
} Student_list;


int student_copy(Student *from, Student *to);
int free_student(Student *stud);


int insert_student(Student_list *sl, Student *student_new)
{
    Node *stud = sl->first;
    if (NULL == stud)
    {
        sl->first = (Node *) malloc(sizeof(Node));
        if (NULL == sl->first)
        {
            return 1;
        }

        sl->first->student = (Student *) malloc(sizeof(Student));
        if (NULL == sl->first->student)
        {
            return 1;
        }
        
        if (student_copy(student_new, sl->first->student) != 0)
        {
            free_student(sl->first->student);
            return 2;
        }
        
        sl->first->next = NULL;
        ++(sl->length);
        
        return 0;
    }

    while (stud->next != NULL)
    {
        stud = stud->next;
    }

    stud->next = (Node *) malloc(sizeof(Node));
    if (NULL == stud->next)
    {
        return 1;
    }
    
    stud->next->student = (Student *) malloc(sizeof(Student));

    if (student_copy(student_new, stud->next->student) != 0)
    {
        free_student(sl->first->student);
        return 2;
    }
    stud->next->next = NULL;
    ++(sl->length);

    return 0;
}




int clear_list(Student_list *sl)
{
    Node *stud = (*sl).first, *prev;
    while (stud != NULL)
    {
        free_student(stud->student);
        prev = stud;
        stud = stud->next;
        free(prev);
    }

    return 0;
}


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
        if (NULL == student->name)
        {
            return 1;
        }

        strcpy(student->name, in);
        return 0;
    }
    return 1;
}


int set_last_name(char *in, Student *student)
{
    if (is_right_string(in, 1) && strlen(in) > 0)
    {
        student->last_name = (char *) malloc(sizeof(char) * strlen(in));
        if (NULL == student->last_name)
        {
            return 1;
        }

        strcpy(student->last_name, in);
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
        if (NULL == student->group)
        {
            return 1;
        }

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
            if (NULL == student->grades)
            {
                return 1;
            }
        }

        *(student->grades + position) = (short) grade;
        return 0;
    }
    return 1;
}


int print_student(Student *s)
{
    printf("======\n");
    printf("ID: %d\nName: %s\nLast name: %s\nCourse: %d\nGroup: %s\nGrades: ",
            (*s).id, (*s).name, (*s).last_name, (*s).course, (*s).group);

    int i;
    for (i = 0; i < 5; ++i)
    {
        printf("%d ", *((*s).grades + i));
    }
    printf("\n======\n");

    return 0;
}




int student_copy(Student *from, Student *to)
{
    (*to).id = (*from).id;
    (*to).name = (char *) malloc(sizeof(char) * strlen((*from).name));
    if (NULL == (*to).name)
    {
        return 1;
    }
    strcpy((*to).name, (*from).name);

    (*to).last_name = (char *) malloc(sizeof(char) * strlen((*from).last_name));
    if (NULL == (*to).last_name)
    {
        return 1;
    }
    strcpy((*to).last_name, (*from).last_name);

    (*to).course = (*from).course;
    (*to).group = (char *) malloc(sizeof(char) * strlen((*from).group));
    if (NULL == (*to).group)
    {
        return 1;
    }
    strcpy((*to).group, (*from).group);

    (*to).grades = (short *) malloc(sizeof(char) * 5);
    if (NULL == (*to).group)
    {
        return 1;
    }

    int i;
    for (i = 0; i < 5; ++i)
    {
        *((*to).grades + i) = *((*from).grades + i);
    }

    return 0;
}


int free_student(Student *stud)
{
    free(stud->grades);
    free(stud->name);
    free(stud->last_name);
    free(stud->group);

    return 0;
}


int free_students(Student *studs, int count)
{
    int i;
    for (i = 0; i < count; ++i)
    {
        free_student(studs + i);
        free_student(studs + i);
        free_student(studs + i);
        free_student(studs + i);
    }
    free(studs);

    return 0;
}


int cmp_id(const void *a, const void *b) {
    const Student *a1 = (const Student *)a;
    const Student *b1 = (const Student *)b;
    return (*a1).id > (*b1).id ? 1 : -1;
}

int cmp_course(const void *a, const void *b) {
    const Student *a1 = (const Student *)a;
    const Student *b1 = (const Student *)b;
    return (*a1).course > (*b1).course;
}

int cmp_name(const void *a, const void *b) {
    const Student *a1 = (const Student *)a;
    const Student *b1 = (const Student *)b;
    return strcmp((*a1).name, (*b1).name) > 0 ? 1 : -1;
}

int cmp_last_name(const void *a, const void *b) {
    const Student *a1 = (const Student *)a;
    const Student *b1 = (const Student *)b;
    return strcmp((*a1).last_name, (*b1).last_name) > 0 ? 1 : -1;
}

int cmp_group(const void *a, const void *b) {
    const Student *a1 = (const Student *)a;
    const Student *b1 = (const Student *)b;
    return strcmp((*a1).group, (*b1).group) > 0 ? 1 : -1;
}