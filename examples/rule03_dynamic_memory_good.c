#include <stddef.h>

#define STATIC_BUFFER_SIZE 32U

typedef struct
{
    int data[STATIC_BUFFER_SIZE];
    size_t count;
} static_buffer_t;

void init_buffer_good(static_buffer_t *buffer)
{
    if (buffer == NULL)
    {
        return;
    }

    buffer->count = 0U;
}

int main(void)
{
    static_buffer_t buffer;
    init_buffer_good(&buffer);
    return 0;
}
