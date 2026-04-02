#include <stddef.h>

int count_positive_good(const int *values, size_t size)
{
    size_t i;
    int count = 0;

    if (values == NULL)
    {
        return 0;
    }

    for (i = 0U; i < size; i++)
    {
        int current = values[i];

        if (current > 0)
        {
            count++;
        }
    }

    return count;
}

int main(void)
{
    return 0;
}
