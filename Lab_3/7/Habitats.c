#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text_functions.c"

#define START_LEN 15


enum gender
{
    m,
    w,
};

typedef struct Habitat
{
    char *last_name;
    char *name;
    char *middle_name;
    char *birth_date;
    enum gender gender;
    double income;
} Habitat;


int free_habitat(Habitat *hab)
{
    free(hab->last_name);
    free(hab->name);
    free(hab->middle_name);
    free(hab->birth_date);

    return 0;
}


int set_last_name(Habitat *hab, char *in)
{
    if (is_right_string(in, 1) && strlen(in) > 0)
    {
        hab->last_name = (char *) malloc(sizeof(char) * strlen(in));
        if (NULL == hab->last_name)
        {
            return 1;
        }
        strcpy(hab->last_name, in);

        return 0;
    }

    return 1;
}


int set_name(Habitat *hab, char *in)
{
    if (is_right_string(in, 1) && strlen(in) > 0)
    {
        hab->name = (char *) malloc(sizeof(char) * strlen(in));
        if (NULL == hab->name)
        {
            return 1;
        }
        strcpy(hab->name, in);

        return 0;
    }

    return 1;
}


int set_middle_name(Habitat *hab, char *in)
{
    if (is_right_string(in, 1) && strlen(in) > 0)
    {
        hab->middle_name = (char *) malloc(sizeof(char) * strlen(in));
        if (NULL == hab->middle_name)
        {
            return 1;
        }
        strcpy(hab->middle_name, in);

        return 0;
    }

    return 1;
}


int set_birth_date(Habitat *hab, char *in)
{
    int day, month, year;
    if (is_date(in, &day, &month, &year))
    {
        hab->birth_date = (char *) malloc(sizeof(char) * strlen(in));
        if (NULL == hab->birth_date)
        {
            return 1;
        }
        strcpy(hab->birth_date, in);

        return 0;
    }

    return 1;
}


int set_gender(Habitat *hab, char *in)
{
    if (*in == 'm')
    {
        hab->gender = m;

        return 0;
    }

    if (*in == 'w')
    {
        hab->gender = w;

        return 0;
    }

    return 1;
}


int set_income(Habitat *hab, char *in)
{
    double income;

    if (is_double(in, &income, 0))
    {
        hab->income = income;

        return 0;
    }

    return 1;
}


int print_habitat(Habitat *hab, int num)
{
    if (num) {
        printf("=== %d ===\n", num);
    }
    else
    {
        printf("=====\n");
    }
    printf("Last name: %s\nName: %s\nMiddle name: %s\nBirth date: %s\nGender: %u\nIncome: %.3lf\n",
            (*hab).last_name, (*hab).name, (*hab).middle_name,
            (*hab).birth_date,
            (*hab).gender, (*hab).income);
    printf("=====\n");

    return 0;
}


int file_print_habitat(FILE *f, Habitat *hab)
{
    fprintf(f, "%s %s %s %s %u %.3lf\n",
            (*hab).last_name, (*hab).name, (*hab).middle_name,
            (*hab).birth_date,
            (*hab).gender, (*hab).income);

    return 0;
}


int is_younger(Habitat *h1, Habitat *h2)
{
    int day_1, day_2, month_1, month_2, year_1, year_2;
    if (is_date(h1->birth_date, &day_1, &month_1, &year_1) && is_date(h2->birth_date, &day_2, &month_2, &year_2))
    {
        if (year_1 > year_2)
        {
            return 1;
        }
        else if (year_1 < year_2)
        {
            return 0;
        }

        if (month_1 > month_2)
        {
            return 1;
        }
        else if (month_1 < month_2)
        {
            return 0;
        }

        if (day_1 > day_2)
        {
            return 1;
        }
        return 0;
    }

    return -1;
}