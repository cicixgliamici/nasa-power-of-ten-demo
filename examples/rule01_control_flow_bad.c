#include <stddef.h>

int find_first_positive_bad(const int *values, size_t size)
{
    size_t i = 0U;
    int result = -1;

    if (values == NULL)
    {
        goto end;
    }

    while (i < size)
    {
        if (values[i] > 0)
        {
            result = (int)i;
            goto end;
        }

        i++;
    }

end:
    return result;
}
