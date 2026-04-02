typedef struct
{
    int count;
} counter_t;

void increment_bad(counter_t *counter)
{
    counter->count++;
}
