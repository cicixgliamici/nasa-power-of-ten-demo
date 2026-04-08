#include <assert.h>
#include <stddef.h>

typedef struct
{
    int count;
} counter_t;

void increment_good(counter_t *counter)
{
    assert(counter != NULL);
    assert(counter->count >= 0);

    counter->count++;

    assert(counter->count > 0);
}

int main(void)
{
    counter_t counter = {0};
    increment_good(&counter);
    return 0;
}
