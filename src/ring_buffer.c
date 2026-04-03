#include "ring_buffer.h"

#include <assert.h>

rb_status_t rb_init(ring_buffer_t *rb)
{
    if (rb == NULL)
    {
        return RB_ERROR_NULL;
    }

    rb->head = 0U;
    rb->tail = 0U;
    rb->count = 0U;

    return RB_OK;
}

bool rb_is_empty(const ring_buffer_t *rb)
{
    assert(rb != NULL);
    return (rb->count == 0U);
}

bool rb_is_full(const ring_buffer_t *rb)
{
    assert(rb != NULL);
    return (rb->count == RING_BUFFER_CAPACITY);
}

rb_status_t rb_push(ring_buffer_t *rb, int value)
{
    if (rb == NULL)
    {
        return RB_ERROR_NULL;
    }

    if (rb_is_full(rb))
    {
        return RB_ERROR_FULL;
    }

    assert(rb->tail < RING_BUFFER_CAPACITY);
    assert(rb->count < RING_BUFFER_CAPACITY);

    rb->data[rb->tail] = value;
    rb->tail = (rb->tail + 1U) % RING_BUFFER_CAPACITY;
    rb->count++;

    assert(rb->count <= RING_BUFFER_CAPACITY);

    return RB_OK;
}

rb_status_t rb_pop(ring_buffer_t *rb, int *value)
{
    if ((rb == NULL) || (value == NULL))
    {
        return RB_ERROR_NULL;
    }

    if (rb_is_empty(rb))
    {
        return RB_ERROR_EMPTY;
    }

    assert(rb->head < RING_BUFFER_CAPACITY);
    assert(rb->count > 0U);

    *value = rb->data[rb->head];
    rb->head = (rb->head + 1U) % RING_BUFFER_CAPACITY;
    rb->count--;

    return RB_OK;
}

static bool rb_is_valid(const ring_buffer_t *rb)
{
    if (rb == NULL)
    {
        return false;
    }

    if (rb->head >= RING_BUFFER_CAPACITY)
    {
        return false;
    }

    if (rb->tail >= RING_BUFFER_CAPACITY)
    {
        return false;
    }

    if (rb->count > RING_BUFFER_CAPACITY)
    {
        return false;
    }

    return true;
}
