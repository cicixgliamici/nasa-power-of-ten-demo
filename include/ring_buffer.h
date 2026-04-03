#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>
#include <stdbool.h>

#define RING_BUFFER_CAPACITY 8

typedef enum
{
    RB_OK = 0,
    RB_ERROR_NULL = 1,
    RB_ERROR_FULL = 2,
    RB_ERROR_EMPTY = 3
} rb_status_t;

typedef struct
{
    int data[RING_BUFFER_CAPACITY];
    size_t head;
    size_t tail;
    size_t count;
} ring_buffer_t;

rb_status_t rb_init(ring_buffer_t *rb);
rb_status_t rb_push(ring_buffer_t *rb, int value);
rb_status_t rb_pop(ring_buffer_t *rb, int *value);

size_t rb_size(const ring_buffer_t *rb);
size_t rb_capacity(void);
rb_status_t rb_peek(const ring_buffer_t *rb, int *value);
rb_status_t rb_clear(ring_buffer_t *rb);

bool rb_is_empty(const ring_buffer_t *rb);
bool rb_is_full(const ring_buffer_t *rb);

#endif
