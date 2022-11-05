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
                        // id
                        err = set_id(in, studs + counter) == 0 ? 0 : 4;
                        break;
                    case 1:
                        // name
                        err = set_name(in, studs + counter) == 0 ? 0 : 5;
                        break;
                    case 2:
                        // course
                        err = set_course(in, studs + counter) == 0 ? 0 : 6;
                        break;
                    case 3:
                        // group
                        err = set_group(in, studs + counter) == 0 ? 0 : 7;
                        break;
                    default:
                        // grade
                        err = set_grade(in, studs + counter, commas - 4) == 0 ? 0 : 8;
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
                err = set_grade(in, studs + counter, commas - 4);
                if (err || commas < 8)
                {
                    free(in);
                    *line_corrupt = counter + 1;
                    return 8;
                }

                if (*count_notes == counter)
                {
                    *count_notes *= 2;
                    Student *ptr = realloc(studs, sizeof(Student) * *count_notes);
                    if (NULL == ptr)
                    {
                        // do not forget about free grades dynamic array!
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