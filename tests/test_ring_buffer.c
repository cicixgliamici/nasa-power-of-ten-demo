#include "ring_buffer.h"

#include <assert.h>
#include <stdio.h>

static void test_init(void)
{
    ring_buffer_t rb;

    assert(rb_init(&rb) == RB_OK);
    assert(rb_is_empty(&rb));
    assert(!rb_is_full(&rb));
    assert(rb_size(&rb) == 0U);
    assert(rb_capacity() == RING_BUFFER_CAPACITY);
}

static void test_push_pop_fifo(void)
{
    ring_buffer_t rb;
    int value = 0;

    assert(rb_init(&rb) == RB_OK);

    assert(rb_push(&rb, 10) == RB_OK);
    assert(rb_push(&rb, 20) == RB_OK);
    assert(rb_push(&rb, 30) == RB_OK);
    assert(rb_size(&rb) == 3U);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 10);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 20);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 30);

    assert(rb_is_empty(&rb));
    assert(rb_size(&rb) == 0U);
}

static void test_full_buffer(void)
{
    ring_buffer_t rb;
    size_t i;

    assert(rb_init(&rb) == RB_OK);

    for (i = 0U; i < RING_BUFFER_CAPACITY; i++)
    {
        assert(rb_push(&rb, (int)i) == RB_OK);
    }

    assert(rb_is_full(&rb));
    assert(rb_size(&rb) == RING_BUFFER_CAPACITY);
    assert(rb_push(&rb, 99) == RB_ERROR_FULL);
}

static void test_empty_buffer(void)
{
    ring_buffer_t rb;
    int value = 0;

    assert(rb_init(&rb) == RB_OK);
    assert(rb_pop(&rb, &value) == RB_ERROR_EMPTY);
    assert(rb_peek(&rb, &value) == RB_ERROR_EMPTY);
}

static void test_null_checks(void)
{
    ring_buffer_t rb;
    int value = 0;

    assert(rb_init(&rb) == RB_OK);

    assert(rb_init(NULL) == RB_ERROR_NULL);
    assert(rb_push(NULL, 1) == RB_ERROR_NULL);
    assert(rb_pop(NULL, &value) == RB_ERROR_NULL);
    assert(rb_pop(&rb, NULL) == RB_ERROR_NULL);
    assert(rb_peek(NULL, &value) == RB_ERROR_NULL);
    assert(rb_peek(&rb, NULL) == RB_ERROR_NULL);
    assert(rb_clear(NULL) == RB_ERROR_NULL);
}

static void test_peek(void)
{
    ring_buffer_t rb;
    int value = 0;

    assert(rb_init(&rb) == RB_OK);
    assert(rb_push(&rb, 42) == RB_OK);

    /* Peek should not remove the element. */
    assert(rb_peek(&rb, &value) == RB_OK);
    assert(value == 42);
    assert(rb_size(&rb) == 1U);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 42);
    assert(rb_is_empty(&rb));
}

static void test_clear(void)
{
    ring_buffer_t rb;
    int value = 0;

    assert(rb_init(&rb) == RB_OK);
    assert(rb_push(&rb, 1) == RB_OK);
    assert(rb_push(&rb, 2) == RB_OK);
    assert(rb_push(&rb, 3) == RB_OK);

    assert(rb_clear(&rb) == RB_OK);
    assert(rb_is_empty(&rb));
    assert(rb_size(&rb) == 0U);
    assert(rb_pop(&rb, &value) == RB_ERROR_EMPTY);
}

static void test_wrap_around(void)
{
    ring_buffer_t rb;
    int value = 0;
    size_t i;

    assert(rb_init(&rb) == RB_OK);

    for (i = 0U; i < RING_BUFFER_CAPACITY; i++)
    {
        assert(rb_push(&rb, (int)i) == RB_OK);
    }

    for (i = 0U; i < 3U; i++)
    {
        assert(rb_pop(&rb, &value) == RB_OK);
        assert(value == (int)i);
    }

    assert(rb_push(&rb, 100) == RB_OK);
    assert(rb_push(&rb, 101) == RB_OK);
    assert(rb_push(&rb, 102) == RB_OK);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 3);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 4);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 5);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 6);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 7);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 100);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 101);

    assert(rb_pop(&rb, &value) == RB_OK);
    assert(value == 102);

    assert(rb_is_empty(&rb));
}

int main(void)
{
    test_init();
    test_push_pop_fifo();
    test_full_buffer();
    test_empty_buffer();
    test_null_checks();
    test_peek();
    test_clear();
    test_wrap_around();

    printf("All ring buffer tests passed.\n");
    return 0;
}
