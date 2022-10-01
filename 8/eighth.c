#include <stdio.h>

#include "arguments.c"
#include "array.c"

#define START_LEN 8
#define ABS 1000


int is_space(char c)
{
    return c == '\n' || c == ' ' || c == '\t' || c == EOF;
}


int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("You must enter size of array!\n");
        return 1;
    }

    if (argc > 4)
    {
        printf("Too many arguments!\n");
        return 1;
    }

    if (!is_flag(argv[2]))
    {
        printf("Flag is incorrect!\n");
        return 1;
    }

    char *flag = argv[2];
    ++flag;
    int index;

    if ((*flag == 'a' || *flag == 'b') && argc > 3)
    {
        printf("Too many arguments!\n");
        return 1;
    }
    else if (*flag == 'c' || *flag == 'd' || *flag == 'e')
    {
        if (argc < 4)
        {
            printf("Wrong count of arguments!\n");
            return 1;
        }

        if (!is_integer(argv[3]))
        {
            printf("Index must be number!\n");
            return 1;   
        }
        index = atoi(argv[3]);
        if (index < 1)
        {
            printf("Index must be positive integer number!\n");
            return 1;
        }
    }
    
    
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("This file doesn't exists!\n");
    }

    int arr[128];
    int size = 0;

    int it = 0;
    int cur_len = START_LEN;
    char c = ' ', _c;
    char *num = (char *) malloc(sizeof(char) * START_LEN);


    while (_c != EOF)
    {
        if (!is_space(c))
        {
            if (it == cur_len)
            {
                cur_len *= 2;
                num = realloc(num, cur_len);
                if (num == NULL)
                {
                    printf("Not enough memory!\n");
                    return 1;
                }
            }
            *(num + it++) = c;
        }
        else if (it != 0)
        {
            *(num + it) = '\0';
            if (!is_number(num))
            {
                printf("%s is not a number!\n", num);
                return 1;
            }
            arr[size++] = atoi(num);
            it = 0;
        }

        _c = c;
        c = fgetc(file);
    }
    free(num);
    

    int success = 0;

    if (*flag == 'a' || *flag == 'b')
    {
        int *new_arr = (int *) malloc(sizeof(int) * size);

        if (*flag == 'a' ? odd_indexes(arr, new_arr, &size) == 0
                         : even_nums(arr, new_arr, &size) == 0)
        {
            success = 1;
        }

        int i;
        for (i = 0; i < size; ++i)
        {
            printf("%d ", new_arr[i]);
        }
    }
    
    else if (*flag == 'c' || *flag == 'd' || *flag == 'e')
    {
        int answer = 0;
        if (size < index + 1)
        {
            printf("Index must be lower than array size\n");
        }

        switch (*flag) {
            case 'c':
                if (furthest(arr, &answer, index, size) == 0)
                {
                    success = 1;
                }
                break;

            case 'd':
                if (sum_before_index(arr, &answer, index) == 0)
                {
                    success = 1;
                }
                break;

            case 'e':
                if (sum_lower_than_index(arr, &answer, index, size) == 0)
                {
                    success = 1;
                }
                break;
        }
        printf("%d", answer);
    }
    else
    {
        printf("There is not such flag!\n");
        return 1;
    }

    if (!success)
    {
        printf("Error\n");
        return -1;
    }

    printf("\n");

    return 0;
}