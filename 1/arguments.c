int arg_to_int(char *arg)
{
    char *ptr = arg;

    int num = 0;
    int factor = 1;
    
    if (*ptr == '-')
    {
        factor = -1;
        ++ptr;
    }

    while (*ptr)
    {
        if ('0' - 1 < *ptr && *ptr < '9' + 1)
        {
            num = num * 10 + (*ptr - '0');
        }
        ++ptr;
    }
    num *= factor;

    return num;
}

int is_number(char const*arg)
{
    char *ptr = arg;
    int dot = 0;

    if (*ptr == '-')
    {
        ++ptr;
    }

    while (*ptr)
    {
        if (*ptr == '.')
        {
            if (dot > 0)
            {
                return 0;
            }
            ++dot;
            
        }
        else if ('0' > *ptr || *ptr > '9')
        {
            return 0;
        }
        ++ptr;
    }

    return 1;
}

int is_integer(char const* arg)
{
    char *ptr = arg;
    
    if (*arg == '-')
    {
        ++ptr;
    }

    while (*ptr)
    {
        if ('0' > *ptr || *ptr > '9')
        {
            return 0;
        }
        ++ptr;
    }
    return 1;
}

int is_flag(char const* arg)
{
    return arg[0] == '-' || arg[0] == '/';
}