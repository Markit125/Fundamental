#include "employee.c"


int get_note(FILE *f, char *line);


int read_file(char *file_name, char *flag)
{
    FILE *f = fopen(file_name, "r");
    if (NULL == f)
    {
        return FILE_NOT_FOUND;
    }

    employee *employees;
    int err;

    err = add_employees(&employees, f);
    if (err)
    {
        return err;
    }

    return SUCCESS;
}
