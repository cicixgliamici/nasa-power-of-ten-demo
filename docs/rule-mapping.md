# Rule Mapping

This document maps the main ideas of the NASA/JPL *Power of Ten* paper
to the concrete choices made in this repository.

## Rule 1 — Restrict code to very simple control flow constructs

**Intent**  
Reduce hidden complexity and make control flow easier to inspect and reason about.

**Repository evidence**
- The ring buffer implementation uses direct, linear control flow.
- No recursion is used.
- No `goto` is used.
- No indirect control transfers are used.
- Example: `src/ring_buffer.c`
- Isolated example: `examples/rule01_control_flow_good.c`

**Trade-off**  
This reduces expressiveness, but improves predictability and reviewability.

---

## Rule 2 — Give all loops a fixed upper bound

**Intent**  
Support reasoning about worst-case execution time and termination.

**Repository evidence**
- Test loops iterate over `RING_BUFFER_CAPACITY`.
- Example loops are bounded explicitly.
- Isolated example: `examples/rule02_loop_bounds_good.c`

**Trade-off**  
This can make interfaces less flexible, but greatly improves analyzability.

---

## Rule 3 — Do not use dynamic memory allocation after initialization

**Intent**  
Avoid fragmentation, allocation failure, and unpredictable runtime behavior.

**Repository evidence**
- `ring_buffer_t` stores its data in a fixed-size internal array.
- No `malloc`, `calloc`, `realloc`, or `free` are used.
- Isolated example: `examples/rule03_dynamic_memory_good.c`

**Trade-off**  
Capacity is fixed at compile time, so scalability is intentionally limited.

---

## Rule 4 — Keep functions small

**Intent**  
Improve local reasoning, testing, and review.

**Repository evidence**
- The ring buffer API is split into small operations such as init, push, pop, full, and empty checks.
- Isolated example: `examples/rule04_small_functions_good.c`

**Trade-off**  
A larger number of small functions may create more surface area, but each unit becomes easier to test and audit.

---

## Rule 5 — Use assertions to check for anomalous conditions

**Intent**  
Document and enforce invariants that should always hold internally.

**Repository evidence**
- Assertions are used in `src/ring_buffer.c` to guard internal assumptions.
- Null arguments are handled with explicit return codes where appropriate.
- Isolated example: `examples/rule05_assertions_good.c`

**Trade-off**  
Assertions are not a replacement for runtime error handling; they complement it.

---

## Rule 6 — Declare data objects at the smallest possible scope

**Intent**  
Reduce accidental misuse and improve readability.

**Repository evidence**
- Local variables are introduced close to where they are used.
- Isolated example: `examples/rule06_scope_good.c`

**Trade-off**  
This can sometimes slightly increase verbosity, but reduces unnecessary coupling.

---

## Rule 7 — Check the return value of all non-void functions

**Intent**  
Prevent silent failures and make error handling explicit.

**Repository evidence**
- Ring buffer operations return `rb_status_t`.
- Tests explicitly check returned status codes.
- Isolated example: `examples/rule07_return_checks_good.c`

**Trade-off**  
This increases code verbosity, but failures become visible and testable.

---

## Rule 8 — Use the preprocessor only for simple inclusion and simple macros

**Intent**  
Avoid hidden logic, side effects, and debugging difficulty caused by macros.

**Repository evidence**
- The implementation relies on normal functions instead of function-like macros for logic.
- The header uses the preprocessor only for include guards and simple constants.
- Isolated example: `examples/rule08_macros_good.c`

**Trade-off**  
Functions are usually clearer and safer, though some low-level optimizations may be sacrificed.

---

## Rule 9 — Limit pointer use to a single dereference, and avoid complex expressions

**Intent**  
Reduce pointer-related bugs and make data access easier to inspect.

**Repository evidence**
- Pointer use in the ring buffer API is simple and direct.
- Null checks are explicit.
- Isolated example: `examples/rule09_pointers_good.c`

**Trade-off**  
This limits compact expression style, but improves safety and readability.

---

## Rule 10 — Compile with all warnings enabled and fix them all

**Intent**  
Treat compiler diagnostics as part of the verification process.

**Repository evidence**
- `Makefile` enables strict compilation flags such as `-Wall -Wextra -Werror -pedantic`.
- Example: `Makefile`

**Trade-off**  
This can slow down early iteration, but helps keep the codebase disciplined and warning-clean.

---

## Summary

The main project artifact is intentionally small.
Its value lies not in size, but in traceability:

- from paper rule
- to design constraint
- to implementation choice
- to tests and examples
- to reflection on trade-offs
