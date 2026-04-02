#include <stddef.h>

static int sum_non_negative(const int *values, size_t size)
{
    size_t i;
    int sum = 0;

    for (i = 0U; i < size; i++)
    {
        if (values[i] >= 0)
        {
            sum += values[i];
        }
    }

    return sum;
}

static int count_non_negative(const int *values, size_t size)
{
    size_t i;
    int count = 0;

    for (i = 0U; i < size; i++)
    {
        if (values[i] >= 0)
        {
            count++;
        }
    }

    return count;
}

static int compute_average(int sum, int count)
{
    if (count == 0)
    {
        return 0;
    }

    return sum / count;
}

int process_values_good(const int *values, size_t size)
{
    int sum;
    int count;

    if ((values == NULL) || (size == 0U))
    {
        return -1;
    }

    sum = sum_non_negative(values, size);
    count = count_non_negative(values, size);

    return compute_average(sum, count);
}

int main(void)
{
    return 0;
}
