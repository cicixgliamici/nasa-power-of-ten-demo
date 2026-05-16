#ifndef RING_BUFFER_CONTRACTS_H
#define RING_BUFFER_CONTRACTS_H

/*
 * ACSL contract helpers for the ring buffer.
 *
 * This file is intentionally separate from the public API declarations:
 * the API remains easy to read, while the stronger Frama-C model has a
 * dedicated home for predicates and logical helpers.
 */

/*@
  logic integer rb_index(integer head, integer offset) =
    (head + offset) % RING_BUFFER_CAPACITY;

  predicate rb_structurally_valid_read(const ring_buffer_t *rb) =
    \valid_read(rb) &&
    0 <= rb->head < RING_BUFFER_CAPACITY &&
    0 <= rb->tail < RING_BUFFER_CAPACITY &&
    rb->count <= RING_BUFFER_CAPACITY;

  predicate rb_valid_read(const ring_buffer_t *rb) =
    rb_structurally_valid_read(rb) &&
    rb->tail == rb_index(rb->head, rb->count);

  predicate rb_valid(ring_buffer_t *rb) =
    \valid(rb) &&
    0 <= rb->head < RING_BUFFER_CAPACITY &&
    0 <= rb->tail < RING_BUFFER_CAPACITY &&
    rb->count <= RING_BUFFER_CAPACITY &&
    rb->tail == rb_index(rb->head, rb->count);

  predicate rb_logical_range_equal{L1,L2}(
    const ring_buffer_t *rb,
    integer start1,
    integer start2,
    integer length
  ) =
    \forall integer k;
      0 <= k < length ==>
        \at(rb->data[rb_index(\at(rb->head, L1), start1 + k)], L1) ==
        \at(rb->data[rb_index(\at(rb->head, L2), start2 + k)], L2);

  predicate rb_logical_value_at{L}(
    const ring_buffer_t *rb,
    integer offset,
    integer value
  ) =
    0 <= offset < \at(rb->count, L) &&
    \at(rb->data[rb_index(\at(rb->head, L), offset)], L) == value;
*/

#endif
