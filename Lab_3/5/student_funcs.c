#include "student.c"
#include <stdio.h>
#include <stdlib.h>

#define START_LEN 15


int read_file(FILE *f, Student *studs, int *count_notes, int *line_corrupt)
{
    int err = 0, n, commas = 0, counter = 0, it = 0, len = START_LEN;
    char *in = (char *) malloc(sizeof(char) * len);
    char c;


    while ((c = fgetc(f)) != EOF)
    {
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
                        err = set_id(in, studs + counter) == 0 ? 0 : 4;
                        break;
                    case 1:
                        err = set_name(in, studs + counter) == 0 ? 0 : 5;
                        break;
                    case 2:
                        err = set_last_name(in, studs + counter) == 0 ? 0 : 5;
                        break;
                    case 3:
                        err = set_course(in, studs + counter) == 0 ? 0 : 7;
                        break;
                    case 4:
                        err = set_group(in, studs + counter) == 0 ? 0 : 8;
                        break;
                    default:
                        err = set_grade(in, studs + counter, commas - 5) == 0 ? 0 : 9;
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
                err = set_grade(in, studs + counter, commas - 5);
                if (err || commas < 9)
                {
                    free(in);
                    *line_corrupt = counter + 1;
                    return 9;
                }

                if (*count_notes == counter)
                {
                    *count_notes *= 2;
                    Student *ptr = realloc(studs, sizeof(Student) * *count_notes);
                    if (NULL == ptr)
                    {
                        free(in);
                        return 1;
                    }

                    studs = ptr;
                }

                ++counter;
                commas = 0;
            }
        }
    }
    free(in);

    if (counter < *count_notes)
    {
        Student *ptr = realloc(studs, sizeof(Student) * counter);
        if (NULL == ptr)
        {
            return 1;
        }

        *count_notes = counter;
        studs = ptr;
    }

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
                printf("-%s- -%s-\n", num, str);
                // printf("+%d+\n", strcmp(str, num));
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
            printf("Copied\n");
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
}