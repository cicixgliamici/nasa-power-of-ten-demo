#include "ring_buffer.h"

#include <assert.h>

/*
 * Internal validity check for the ring buffer state.
 * This is used to validate invariants during development.
 */
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

rb_status_t rb_init(ring_buffer_t *rb)
{
    if (rb == NULL)
    {
        return RB_ERROR_NULL;
    }

    rb->head = 0U;
    rb->tail = 0U;
    rb->count = 0U;

    assert(rb_is_valid(rb));
    return RB_OK;
}

bool rb_is_empty(const ring_buffer_t *rb)
{
    assert(rb_is_valid(rb));
    return (rb->count == 0U);
}

bool rb_is_full(const ring_buffer_t *rb)
{
    assert(rb_is_valid(rb));
    return (rb->count == RING_BUFFER_CAPACITY);
}

size_t rb_size(const ring_buffer_t *rb)
{
    assert(rb_is_valid(rb));
    return rb->count;
}

size_t rb_capacity(void)
{
    return RING_BUFFER_CAPACITY;
}

rb_status_t rb_peek(const ring_buffer_t *rb, int *value)
{
    if ((rb == NULL) || (value == NULL))
    {
        return RB_ERROR_NULL;
    }

    assert(rb_is_valid(rb));

    if (rb_is_empty(rb))
    {
        return RB_ERROR_EMPTY;
    }

    *value = rb->data[rb->head];
    return RB_OK;
}

rb_status_t rb_clear(ring_buffer_t *rb)
{
    if (rb == NULL)
    {
        return RB_ERROR_NULL;
    }

    rb->head = 0U;
    rb->tail = 0U;
    rb->count = 0U;

    assert(rb_is_valid(rb));
    return RB_OK;
}

rb_status_t rb_push(ring_buffer_t *rb, int value)
{
    if (rb == NULL)
    {
        return RB_ERROR_NULL;
    }

    assert(rb_is_valid(rb));

    if (rb_is_full(rb))
    {
        return RB_ERROR_FULL;
    }

    /* tail always points to the next free slot. */
    rb->data[rb->tail] = value;

    /* Advance tail with wrap-around. */
    rb->tail = (rb->tail + 1U) % RING_BUFFER_CAPACITY;
    rb->count++;

    assert(rb_is_valid(rb));
    assert(rb->count <= RING_BUFFER_CAPACITY);

    return RB_OK;
}

rb_status_t rb_pop(ring_buffer_t *rb, int *value)
{
    if ((rb == NULL) || (value == NULL))
    {
        return RB_ERROR_NULL;
    }

    assert(rb_is_valid(rb));

    if (rb_is_empty(rb))
    {
        return RB_ERROR_EMPTY;
    }

    /* head points to the next readable element. */
    *value = rb->data[rb->head];

    /* Advance head with wrap-around. */
    rb->head = (rb->head + 1U) % RING_BUFFER_CAPACITY;
    rb->count--;

    assert(rb_is_valid(rb));
    return RB_OK;
}
