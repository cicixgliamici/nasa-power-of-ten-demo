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

#include "ring_buffer_contracts.h"

/*@
  requires rb == \null || \valid(rb);

  behavior null_buffer:
    assumes rb == \null;
    assigns \nothing;
    ensures \result == RB_ERROR_NULL;

  behavior ok:
    assumes rb != \null;
    assigns rb->head, rb->tail, rb->count;
    ensures \result == RB_OK;
    ensures rb_valid(rb);
    ensures rb->head == 0;
    ensures rb->tail == 0;
    ensures rb->count == 0;

  complete behaviors;
  disjoint behaviors;
*/
rb_status_t rb_init(ring_buffer_t *rb);

/*@
  requires rb == \null || rb_valid(rb);

  behavior null_buffer:
    assumes rb == \null;
    assigns \nothing;
    ensures \result == RB_ERROR_NULL;

  behavior full_buffer:
    assumes rb != \null;
    assumes rb_valid(rb);
    assumes rb->count == RING_BUFFER_CAPACITY;
    assigns \nothing;
    ensures \result == RB_ERROR_FULL;

  behavior ok:
    assumes rb != \null;
    assumes rb_valid(rb);
    assumes rb->count < RING_BUFFER_CAPACITY;
    assigns rb->data[rb->tail], rb->tail, rb->count;
    ensures \result == RB_OK;
    ensures rb_valid(rb);
    ensures rb->data[\old(rb->tail)] == value;
    ensures rb_logical_range_equal{Pre,Here}(rb, 0, 0, \old(rb->count));
    ensures rb_logical_value_at{Here}(rb, \old(rb->count), value);
    ensures rb->tail == (\old(rb->tail) + 1U) % RING_BUFFER_CAPACITY;
    ensures rb->count == \old(rb->count) + 1U;

  complete behaviors;
  disjoint behaviors;
*/
rb_status_t rb_push(ring_buffer_t *rb, int value);

/*@
  requires rb == \null || rb_valid(rb);
  requires value == \null || \valid(value);

  behavior null_argument:
    assumes rb == \null || value == \null;
    assigns \nothing;
    ensures \result == RB_ERROR_NULL;

  behavior empty_buffer:
    assumes rb != \null && value != \null;
    assumes rb_valid(rb);
    assumes rb->count == 0;
    assigns \nothing;
    ensures \result == RB_ERROR_EMPTY;

  behavior ok:
    assumes rb != \null && value != \null;
    assumes rb_valid(rb);
    assumes rb->count > 0;
    assigns *value, rb->head, rb->count;
    ensures \result == RB_OK;
    ensures rb_valid(rb);
    ensures *value == \old(rb->data[rb->head]);
    ensures *value == \old(rb->data[rb_index(rb->head, 0)]);
    ensures rb_logical_range_equal{Pre,Here}(rb, 1, 0, rb->count);
    ensures rb->head == (\old(rb->head) + 1U) % RING_BUFFER_CAPACITY;
    ensures rb->count == \old(rb->count) - 1U;

  complete behaviors;
  disjoint behaviors;
*/
rb_status_t rb_pop(ring_buffer_t *rb, int *value);

/*@
  requires rb_valid_read(rb);
  assigns \nothing;
  ensures \result == rb->count;
*/
size_t rb_size(const ring_buffer_t *rb);

/*@
  assigns \nothing;
  ensures \result == RING_BUFFER_CAPACITY;
*/
size_t rb_capacity(void);

/*@
  requires rb == \null || rb_valid_read(rb);
  requires value == \null || \valid(value);

  behavior null_argument:
    assumes rb == \null || value == \null;
    assigns \nothing;
    ensures \result == RB_ERROR_NULL;

  behavior empty_buffer:
    assumes rb != \null && value != \null;
    assumes rb_valid_read(rb);
    assumes rb->count == 0;
    assigns \nothing;
    ensures \result == RB_ERROR_EMPTY;

  behavior ok:
    assumes rb != \null && value != \null;
    assumes rb_valid_read(rb);
    assumes rb->count > 0;
    assigns *value;
    ensures \result == RB_OK;
    ensures *value == rb->data[rb->head];
    ensures *value == rb->data[rb_index(rb->head, 0)];
    ensures rb_logical_range_equal{Pre,Here}(rb, 0, 0, rb->count);

  complete behaviors;
  disjoint behaviors;
*/
rb_status_t rb_peek(const ring_buffer_t *rb, int *value);

/*@
  requires rb == \null || \valid(rb);

  behavior null_buffer:
    assumes rb == \null;
    assigns \nothing;
    ensures \result == RB_ERROR_NULL;

  behavior ok:
    assumes rb != \null;
    assigns rb->head, rb->tail, rb->count;
    ensures \result == RB_OK;
    ensures rb_valid(rb);
    ensures rb->head == 0;
    ensures rb->tail == 0;
    ensures rb->count == 0;

  complete behaviors;
  disjoint behaviors;
*/
rb_status_t rb_clear(ring_buffer_t *rb);

/*@
  requires rb_valid_read(rb);
  assigns \nothing;
  ensures rb->count == 0 ==> \result != 0;
  ensures rb->count != 0 ==> \result == 0;
*/
bool rb_is_empty(const ring_buffer_t *rb);

/*@
  requires rb_valid_read(rb);
  assigns \nothing;
  ensures rb->count == RING_BUFFER_CAPACITY ==> \result != 0;
  ensures rb->count != RING_BUFFER_CAPACITY ==> \result == 0;
*/
bool rb_is_full(const ring_buffer_t *rb);

#endif
