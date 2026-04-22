CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -Wstrict-prototypes -Iinclude
DEBUG_CFLAGS = $(CFLAGS) -O0 -g
SANITIZE_CFLAGS = $(DEBUG_CFLAGS) -fsanitize=address,undefined

# Keep runner and cleanup commands portable between the Linux CI path
# and local MinGW/PowerShell usage on Windows.
ifeq ($(OS),Windows_NT)
RUN_TEST = powershell -Command ".\\$(TARGET).exe"
RM = del /Q
else
RUN_TEST = ./$(TARGET)
RM = rm -f
endif

# Main test executable for the core ring buffer artifact.
TARGET = test_ring_buffer
SRC = src/ring_buffer.c
TEST = tests/test_ring_buffer.c

# Good examples are intentionally buildable; bad examples are for inspection only.
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

.PHONY: all test debug sanitize examples clean

# Default review path: build the core artifact, run tests, and ensure examples compile.
all: test examples

test: $(TARGET)
	$(RUN_TEST)

# Debug build keeps symbols and disables optimization for easier local inspection.
debug: $(SRC) $(TEST) include/ring_buffer.h
	$(CC) $(DEBUG_CFLAGS) $(SRC) $(TEST) -o $(TARGET)
	$(RUN_TEST)

# Sanitizers provide lightweight runtime checks for memory and undefined behavior.
sanitize: $(SRC) $(TEST) include/ring_buffer.h
	$(CC) $(SANITIZE_CFLAGS) $(SRC) $(TEST) -o $(TARGET)
	$(RUN_TEST)

$(TARGET): $(SRC) $(TEST) include/ring_buffer.h
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(TARGET)

examples: $(GOOD_BINS)

examples/%: examples/%.c
	$(CC) $(CFLAGS) $< -o $@

# Remove generated binaries and restore a clean working tree for the build outputs.
clean:
	-$(RM) $(TARGET) $(TARGET).exe $(GOOD_BINS) examples\*.exe
