#include <stdio.h>
#include <stdlib.h>

#include "student.c"

#define START_LEN 15


int read_file(FILE *f, Student **studs, int *count_notes, int *line_corrupt)
{
    int err = 0, n, commas = 0, counter = 0, it = 0, len = START_LEN;
    char *in = (char *) malloc(sizeof(char) * len);
    if (NULL == in)
    {
        return 1;
    }
    char c;
    char c_prev = ' ';

    c = fgetc(f);
    while (c_prev != EOF)
    {
        if (c == EOF && c_prev != '\n')
        {
            c = '\n';
        }
        
        if (!is_comma(c) && !is_newline(c))
        {
            if (it == len)
            {
                len *= 2;
                char *ptr = realloc(in, sizeof(char) * len);
                if (ptr == NULL)
                {
                    free(in);
                    return 1;
                }

                in = ptr;
            }

            *(in + it++) = c;
        }
        else
        {
            *(in + it) = '\0';
            it = 0;
            

            if (is_comma(c))
            {
                switch (commas)
                {
                    case 0:
                        err = set_id(in, *studs + counter) == 0 ? 0 : 4;
                        break;
                    case 1:
                        err = set_name(in, *studs + counter) == 0 ? 0 : 5;
                        break;
                    case 2:
                        err = set_last_name(in, *studs + counter) == 0 ? 0 : 6;
                        break;
                    case 3:
                        err = set_course(in, *studs + counter) == 0 ? 0 : 7;
                        break;
                    case 4:
                        err = set_group(in, *studs + counter) == 0 ? 0 : 8;
                        break;
                    default:
                        err = set_grade(in, *studs + counter, commas - 5) == 0 ? 0 : 9;
                        break;
                }

                if (err)
                {
                    free(in);
                    *line_corrupt = counter + 1;
                    return err;
                }

                ++commas;
            }
            else
            {
                err = set_grade(in, *studs + counter, commas - 5);
                if (err || commas < 9)
                {
                    free(in);
                    *line_corrupt = counter + 1;
                    return 9;
                }
                
                ++counter;

                if (*count_notes == counter)
                {
                    Student *ptr = realloc(*studs, sizeof(Student) * (*count_notes * 2));
                    if (NULL == ptr)
                    {
                        free(in);
                        return 1;
                    }

                    *count_notes *= 2;
                    *studs = ptr;
                }

                commas = 0;
            }
        }

        c_prev = c;
        if (c != EOF)
        {
            c = fgetc(f);
        }
    }
    free(in);

    if (counter == 0)
    {
        *count_notes = 0;
        free(*studs);
    }
    else if (counter < *count_notes)
    {
        Student *ptr = realloc(*studs, sizeof(Student) * counter);
        if (NULL == ptr)
        {
            return 1;
        }

        *count_notes = counter;
        *studs = ptr;
    }

    return 0;
}


int find_students(Student *studs, Student *found, int by, int count_notes, int *count, char *num)
{
    char *str = (char *) malloc(sizeof(char) * START_LEN);
    if (NULL == str)
    {
        return 1;
    }

    int i, not_copy = 1, err = 0;
    for (i = 0; i < count_notes; ++i)
    {
        switch (by)
        {
            case 1:
                sprintf(str, "%d", (studs + i)->id);
                not_copy = strcmp(str, num);
                break;
            case 2:
                not_copy = strcmp((studs + i)->name, num);
                break;
            case 3:
                not_copy = strcmp((studs + i)->last_name, num);
                break;
            case 4:
                sprintf(str, "%d", (studs + i)->course);
                not_copy = strcmp(str, num);
                break;
            case 5:
                not_copy = strcmp((studs + i)->group, num);
                break;
        }

        if (!not_copy)
        {
            err = student_copy(studs + i, found + *count);
            if (err == 1)
            {
                return 1;
            }
            ++(*count);
        }
    }
    free(str);

    Student *ptr = (Student *) malloc(sizeof(Student) * *count);
    if (NULL == ptr)
    {
        return 1;
    }

    found = ptr;

    return 0;
}


int student_out(Student *st)
{
    printf("=====\nNL: %s %s\nCourse: %d\nGroup: %s\nAverage: ",
            (*st).name, (*st).last_name, (*st).course, (*st).group);

    double average = 0;
    int i;
    for (i = 0; i < 5; ++i)
    {
        average += *((*st).grades + i);
    }
    printf("%lf\n=====\n", average / 5);

    return 0;
}


int student_to_file(Student *s, FILE *f)
{
    printf("======\n");
    fprintf(f, "======\n");
    fprintf(f, "ID: %d\nName: %s\nLast name: %s\nCourse: %d\nGroup: %s\nGrades: ",
            (*s).id, (*s).name, (*s).last_name, (*s).course, (*s).group);

    printf("ID: %d\nName: %s\nLast name: %s\nCourse: %d\nGroup: %s\nGrades: ",
            (*s).id, (*s).name, (*s).last_name, (*s).course, (*s).group);

    int i;
    for (i = 0; i < 5; ++i)
    {
        fprintf(f, "%d ", *((*s).grades + i));
    }
    fprintf(f, "\n======\n");

    return 0;
}


double get_average(Student *stud)
{
    int average = 0, i;
    for (i = 0; i < 5; ++i)
    {
        average += *((*stud).grades + i);
    }

    return (double) average / 5;
}


int trace(Student *studs, int count, char* name)
{
    double *all_averages = (double *) malloc(sizeof(double) * count);
    if (NULL == all_averages)
    {
        return 1;
    }
    double *course_averages = (double *) malloc(sizeof(double) * 4);
    if (NULL == course_averages)
    {
        free(all_averages);
        return 1;
    }
    int *course_counts = (int *) malloc(sizeof(int) * 4);
    if (NULL == course_counts)
    {
        free(all_averages);
        free(course_averages);
        return 1;
    }

    int i, j;
    for (i = 0; i < count; ++i)
    {
        *(course_averages + (*(studs + i)).course - 1) = 0;
        *(course_counts + (*(studs + i)).course - 1) = 0;
    }
    

    for (i = 0; i < count; ++i)
    {
        *(all_averages + i) = get_average(studs + i);
        *(course_averages + (*(studs + i)).course - 1) += *(all_averages + i);
        ++(*(course_counts + (*(studs + i)).course - 1));
    }

    char *filename = (char *) malloc(sizeof(char) * (strlen(name) + 3));
    if (NULL == filename)
    {
        free(all_averages);
        free(course_averages);
        free(course_counts);
        return 1;
    }


    for (i = 0; i < 4; ++i)
    {
        if (*(course_counts + i) != 0)
        {
            *(course_averages + i) /= *(course_counts + i);
        }
    }


    for (j = 1; j <= 4; ++j)
    {
        sprintf(filename, "%s_%d", name, j);
        *(filename + strlen(name) + 2) = '\0';
        
        FILE *f = fopen(filename, "w");
        if (NULL == f)
        {
            free(all_averages);
            free(course_averages);
            free(course_counts);
            return 2;
        }

        for (i = 0; i < count; ++i)
        {
    printf("jsidngbuhgi");
            if (j == (*(studs + i)).course && (*(course_averages + j - 1) < *(all_averages + i)))
            {
                student_to_file(studs + i, f);
            }
        }

        fclose(f);
    }

    free(course_averages);
    free(course_counts);

    return 0;
}


Student_list *by_course(Student *studs, int count)
{
    Student_list *list_of_students = (Student_list *) malloc(sizeof(Student_list) * 4);
    
    int i;
    for (i = 0; i < 4; ++i)
    {
        (*(list_of_students + i)).length = 0;
        (*(list_of_students + i)).first = NULL;
    }

    for (i = 0; i < count; ++i)
    {
        insert_student(list_of_students + (*(studs + i)).course - 1, studs + i);
    }

    return list_of_students;
}