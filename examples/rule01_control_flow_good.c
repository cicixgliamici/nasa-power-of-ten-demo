#include <stddef.h>

int find_first_positive_good(const int *values, size_t size)
{
    size_t i;

    if (values == NULL)
    {
        return -1;
    }

    for (i = 0U; i < size; i++)
    {
        if (values[i] > 0)
        {
            return (int)i;
        }
    }

    return -1;
}

int main(void)
{
    return 0;
}
