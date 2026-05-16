# Verification Matrix

This matrix separates evidence types so reviewers can see what is tested,
specified, or left as a documented limitation.

| Area | Unit tests | ACSL / Frama-C | Static tooling | Limit |
|---|---|---|---|---|
| Initialization | `test_init` | `rb_init` postconditions | warnings, cppcheck | Does not clear payload bytes beyond logical state |
| FIFO ordering | direct FIFO tests and bounded shadow-model sequence | logical range preservation and proof harness | warnings, cppcheck | No claim of certification-grade full abstraction |
| Empty/full handling | empty, full, multiple-cycle tests | behavior clauses for empty/full cases | warnings, cppcheck | Caller must still check return values |
| Null handling | null argument tests | null behaviors and no-write guarantees | warnings, cppcheck | API intentionally returns errors instead of aborting |
| Wrap-around | wrap-around and multiple-cycle tests | logical index helper and harness scenario | warnings, cppcheck | Capacity remains fixed |
| Invariants | indirectly exercised by all tests and runtime assertions | `rb_valid` and `rb_valid_read` predicates | warnings, cppcheck | Assertions are development checks, not user-facing errors |
| Build discipline | CI build/test/examples | manual formal-verification workflow | strict compiler flags, optional sanitizers | Toolchain support varies by platform |
| Coverage evidence | Optional `make coverage` test run | Not applicable | GCC/gcov text reports | Optional, not committed as certification evidence |

## How to use this matrix

For normal review, run `make`, `make test`, and `make examples`.

For hardening review, also run:

```bash
make sanitize
make coverage
make cppcheck
make verify WP_PROVER=z3
make verify-fifo WP_PROVER=z3
```

When Frama-C is not installed locally, use Linux CI or the optional Docker path:

```bash
make verify-docker
```
