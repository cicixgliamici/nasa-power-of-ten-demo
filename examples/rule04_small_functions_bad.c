#include <stddef.h>

int process_values_bad(const int *values, size_t size)
{
    size_t i;
    int sum = 0;
    int count = 0;
    int average = 0;
    int max = 0;
    int min = 0;

    if ((values == NULL) || (size == 0U))
    {
        return -1;
    }

    max = values[0];
    min = values[0];

    for (i = 0U; i < size; i++)
    {
        if (values[i] >= 0)
        {
            sum += values[i];
            count++;

            if (values[i] > max)
            {
                max = values[i];
            }

            if (values[i] < min)
            {
                min = values[i];
            }
        }
    }

    if (count > 0)
    {
        average = sum / count;
    }

    return average + max + min;
}
