# Evidence Matrix

This document is a reviewer-oriented summary of where each Power of Ten rule
shows up in the repository.

It is intentionally compact: the goal is to make it fast to connect
design intent, implementation evidence, test evidence, and known limits.

This is the best single-page document to open during a fast review:
it answers "where is the evidence?" without requiring a full repository tour first.

| Rule | Implementation evidence | Test evidence | Example files | Notes / limitations |
|---|---|---|---|---|
| 1. Simple control flow | `src/ring_buffer.c` uses direct, linear control flow with no recursion or `goto` | Core behavior tests exercise the main branches | `examples/rule01_control_flow_good.c`, `examples/rule01_control_flow_bad.c` | Demonstrated on a small artifact, not across a larger codebase |
| 2. Fixed loop bounds | Bounded state and fixed-capacity operations support predictable iteration | Tests iterate up to `RING_BUFFER_CAPACITY` | `examples/rule02_loop_bounds_good.c`, `examples/rule02_loop_bounds_bad.c` | Mostly shown through tests and examples rather than loop-heavy production code |
| 3. No dynamic allocation | `ring_buffer_t` stores data in a fixed internal array | Tests validate behavior without heap use | `examples/rule03_dynamic_memory_good.c`, `examples/rule03_dynamic_memory_bad.c` | Capacity is intentionally fixed at compile time |
| 4. Small functions | API is split into short operations such as init, push, pop, clear, peek | Tests target operations independently | `examples/rule04_small_functions_good.c`, `examples/rule04_small_functions_bad.c` | Demonstrated in a compact module rather than a large system |
| 5. Assertions for invariants | `assert` is used to defend internal ring-buffer validity assumptions | Indirectly supported by all behavioral tests | `examples/rule05_assertions_good.c`, `examples/rule05_assertions_bad.c` | Assertions complement, but do not replace, runtime error handling |
| 6. Smallest practical scope | Local variables are introduced near use in the implementation and tests | Test code follows the same style | `examples/rule06_scope_good.c`, `examples/rule06_scope_bad.c` | This is mostly a style/readability discipline |
| 7. Check return values | Public API returns `rb_status_t` and callers are expected to inspect it | Tests explicitly check return codes for success and failure paths | `examples/rule07_return_checks_good.c`, `examples/rule07_return_checks_bad.c` | Strongly demonstrated in the API and tests |
| 8. Simple preprocessor use | Header uses include guards and a simple capacity constant | Build/examples compile under strict flags | `examples/rule08_macros_good.c`, `examples/rule08_macros_bad.c` | No macro-heavy logic is present in the main artifact |
| 9. Simple pointer usage | Pointer handling is direct: null checks and straightforward dereferences | Null-handling tests exercise pointer-related error paths | `examples/rule09_pointers_good.c`, `examples/rule09_pointers_bad.c` | Demonstrated on a small API surface |
| 10. Warning-clean, tool-friendly code | `Makefile` enables strict warning flags; CI runs build/test/examples | CI checks the same commands expected of a reviewer | `examples/rule10_warnings_good.c`, `examples/rule10_warnings_bad.c` | Static analysis is documented, with room for future tooling expansion |

## Suggested Reviewer Path

1. Read `README.md`
2. Inspect `include/ring_buffer.h` and `src/ring_buffer.c`
3. Read `tests/test_ring_buffer.c`
4. Cross-check this table with `docs/rule-mapping.md`
5. Finish with `docs/reflection.md`
