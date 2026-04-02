#include <stdlib.h>

int *create_buffer_bad(size_t count)
{
    return (int *)malloc(count * sizeof(int));
}
