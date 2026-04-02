#include <stddef.h>

int count_positive_bad(const int *values, size_t size)
{
    size_t i;
    int count;
    int current;
    int is_positive;

    count = 0;
    current = 0;
    is_positive = 0;

    if (values == NULL)
    {
        return 0;
    }

    for (i = 0U; i < size; i++)
    {
        current = values[i];
        is_positive = (current > 0);

        if (is_positive)
        {
            count++;
        }
    }

    return count;
}
