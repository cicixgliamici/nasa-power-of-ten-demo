CC = gcc
FRAMAC ?= frama-c
FRAMAC_FLAGS = -wp -wp-rte
FRAMAC_FIFO_FLAGS = $(FRAMAC_FLAGS)
CPPCHECK ?= cppcheck
DOCKER ?= docker
GCOV ?= gcov
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -Wstrict-prototypes -Iinclude
DEBUG_CFLAGS = $(CFLAGS) -O0 -g
SANITIZE_CFLAGS = $(DEBUG_CFLAGS) -fsanitize=address,undefined
COVERAGE_CFLAGS = $(DEBUG_CFLAGS) --coverage
COVERAGE_LDFLAGS = --coverage

ifneq ($(WP_PROVER),)
FRAMAC_FLAGS += -wp-prover $(WP_PROVER)
endif

# Keep runner and cleanup commands portable between the Linux CI path
# and local MinGW/PowerShell usage on Windows.
ifeq ($(OS),Windows_NT)
RUN_TEST = powershell -Command ".\\$(TARGET).exe"
COVERAGE_RUN = powershell -Command ".\\$(COVERAGE_TARGET).exe"
RM = del /Q
else
RUN_TEST = ./$(TARGET)
COVERAGE_RUN = ./$(COVERAGE_TARGET)
RM = rm -f
endif

# Main test executable for the core ring buffer artifact.
TARGET = test_ring_buffer
COVERAGE_TARGET = coverage_ring_buffer
SRC = src/ring_buffer.c
TEST = tests/test_ring_buffer.c
CONTRACTS = include/ring_buffer.h include/ring_buffer_contracts.h
FIFO_PROOF = proof/ring_buffer_fifo_harness.c

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

.PHONY: all test debug sanitize coverage review review-optional verify verify-fifo verify-docker cppcheck examples clean

# Default review path: build the core artifact, run tests, and ensure examples compile.
all: test examples

test: $(TARGET)
	$(RUN_TEST)

# Debug build keeps symbols and disables optimization for easier local inspection.
debug: $(SRC) $(TEST) $(CONTRACTS)
	$(CC) $(DEBUG_CFLAGS) $(SRC) $(TEST) -o $(TARGET)
	$(RUN_TEST)

# Sanitizers provide lightweight runtime checks for memory and undefined behavior.
sanitize: $(SRC) $(TEST) $(CONTRACTS)
	$(CC) $(SANITIZE_CFLAGS) $(SRC) $(TEST) -o $(TARGET)
	$(RUN_TEST)

coverage: $(SRC) $(TEST) $(CONTRACTS)
	$(CC) $(COVERAGE_CFLAGS) $(SRC) $(TEST) $(COVERAGE_LDFLAGS) -o $(COVERAGE_TARGET)
	$(COVERAGE_RUN)
	$(GCOV) -b -c $(SRC) $(TEST)

review: all sanitize

review-optional: cppcheck verify verify-fifo

verify: $(SRC) $(CONTRACTS)
	$(FRAMAC) $(FRAMAC_FLAGS) -Iinclude $(SRC)

verify-fifo: $(SRC) $(CONTRACTS) $(FIFO_PROOF)
	$(FRAMAC) $(FRAMAC_FIFO_FLAGS) -Iinclude $(SRC) $(FIFO_PROOF)

verify-docker: $(SRC) $(CONTRACTS) $(FIFO_PROOF)
	$(DOCKER) run --rm -v "$(CURDIR):/work" -w /work framac/frama-c:latest frama-c $(FRAMAC_FIFO_FLAGS) -Iinclude $(SRC) $(FIFO_PROOF)

cppcheck:
	$(CPPCHECK) --enable=warning,style,performance,portability --error-exitcode=1 --std=c99 -Iinclude $(SRC) $(TEST) $(GOOD_EXAMPLES)

$(TARGET): $(SRC) $(TEST) $(CONTRACTS)
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(TARGET)

examples: $(GOOD_BINS)

examples/%: examples/%.c
	$(CC) $(CFLAGS) $< -o $@

# Remove generated binaries and restore a clean working tree for the build outputs.
clean:
	-$(RM) $(TARGET) $(TARGET).exe $(COVERAGE_TARGET) $(COVERAGE_TARGET).exe $(GOOD_BINS) examples\*.exe *.gcda *.gcno *.gcov
