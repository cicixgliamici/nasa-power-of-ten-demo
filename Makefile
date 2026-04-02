## `Makefile`

```make
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Iinclude

TARGET = test_ring_buffer
SRC = src/ring_buffer.c
TEST = tests/test_ring_buffer.c

GOOD_EXAMPLES = \
	examples/rule01_control_flow_good.c \
	examples/rule02_loop_bounds_good.c \
	examples/rule03_dynamic_memory_good.c \
	examples/rule04_small_functions_good.c \
	examples/rule05_assertions_good.c \
	examples/rule06_scope_good.c \
	examples/rule07_return_checks_good.c \
	examples/rule08_macros_good.c \
	examples/rule09_pointers_good.c \
	examples/rule10_warnings_good.c

GOOD_BINS = $(GOOD_EXAMPLES:.c=)

all: test examples

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC) $(TEST) include/ring_buffer.h
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(TARGET)

examples: $(GOOD_BINS)

examples/%: examples/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET) $(GOOD_BINS)
