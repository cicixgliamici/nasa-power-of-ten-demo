#include "ring_buffer.h"

/*
 * Frama-C proof harness for representative FIFO scenarios.
 *
 * The production artifact remains src/ring_buffer.c. This file gives WP a
 * small, explicit set of proof-oriented call sequences that exercise the
 * stronger ACSL model without adding test-only code to the implementation.
 */

void proof_init_push_pop_fifo(void)
{
    ring_buffer_t rb;
    int value = 0;
    rb_status_t status;

    status = rb_init(&rb);
    //@ assert status == RB_OK;
    //@ assert rb_valid(&rb);
    //@ assert rb.count == 0;

    status = rb_push(&rb, 11);
    //@ assert status == RB_OK;
    //@ assert rb.count == 1;
    //@ assert rb_logical_value_at{Here}(&rb, 0, 11);

    status = rb_push(&rb, 22);
    //@ assert status == RB_OK;
    //@ assert rb.count == 2;
    //@ assert rb_logical_value_at{Here}(&rb, 0, 11);
    //@ assert rb_logical_value_at{Here}(&rb, 1, 22);

    status = rb_pop(&rb, &value);
    //@ assert status == RB_OK;
    //@ assert value == 11;
    //@ assert rb.count == 1;
    //@ assert rb_logical_value_at{Here}(&rb, 0, 22);

    status = rb_pop(&rb, &value);
    //@ assert status == RB_OK;
    //@ assert value == 22;
    //@ assert rb.count == 0;
}

void proof_peek_is_non_destructive(void)
{
    ring_buffer_t rb;
    int value = 0;
    rb_status_t status;

    status = rb_init(&rb);
    //@ assert status == RB_OK;

    status = rb_push(&rb, 7);
    //@ assert status == RB_OK;
    //@ assert rb.count == 1;

    status = rb_peek(&rb, &value);
    //@ assert status == RB_OK;
    //@ assert value == 7;
    //@ assert rb.count == 1;
    //@ assert rb_logical_value_at{Here}(&rb, 0, 7);

    status = rb_pop(&rb, &value);
    //@ assert status == RB_OK;
    //@ assert value == 7;
    //@ assert rb.count == 0;
}

void proof_wrap_around_preserves_fifo(void)
{
    ring_buffer_t rb;
    int value = 0;
    rb_status_t status;

    status = rb_init(&rb);
    //@ assert status == RB_OK;

    status = rb_push(&rb, 1);
    //@ assert status == RB_OK;
    status = rb_push(&rb, 2);
    //@ assert status == RB_OK;
    status = rb_push(&rb, 3);
    //@ assert status == RB_OK;

    status = rb_pop(&rb, &value);
    //@ assert status == RB_OK;
    //@ assert value == 1;

    status = rb_push(&rb, 4);
    //@ assert status == RB_OK;
    //@ assert rb_logical_value_at{Here}(&rb, 0, 2);
    //@ assert rb_logical_value_at{Here}(&rb, 1, 3);
    //@ assert rb_logical_value_at{Here}(&rb, 2, 4);

    status = rb_pop(&rb, &value);
    //@ assert status == RB_OK;
    //@ assert value == 2;
    status = rb_pop(&rb, &value);
    //@ assert status == RB_OK;
    //@ assert value == 3;
    status = rb_pop(&rb, &value);
    //@ assert status == RB_OK;
    //@ assert value == 4;
    //@ assert rb.count == 0;
}
