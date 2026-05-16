# Lightweight Safety Case

This file gives reviewers a compact claim/evidence/limit view of the project.
It is not a certification argument. It is a small educational safety case that
shows how the repository connects intent, code, tests, and verification.

## Claim 1: The core artifact has bounded state

**Evidence**

- `ring_buffer_t` stores all data in a fixed internal array.
- No heap allocation is used in the core artifact.
- Tests and examples operate within `RING_BUFFER_CAPACITY`.

**Limit**

- Capacity is compile-time fixed. This is intentional for analyzability, not a
  general-purpose container design.

## Claim 2: Public operations make error states explicit

**Evidence**

- Public functions return `rb_status_t`.
- Tests check null, empty, full, and normal paths.
- ACSL contracts document success and failure behaviors.

**Limit**

- Callers still need to check return values. The repository demonstrates that
  discipline through tests and examples.

## Claim 3: FIFO behavior is specified beyond representative tests

**Evidence**

- `include/ring_buffer_contracts.h` defines logical helpers for ring indices
  and logical FIFO ranges.
- Public contracts preserve logical ranges across `push`, `pop`, and `peek`.
- `proof/ring_buffer_fifo_harness.c` exercises representative proof sequences
  for push/pop, peek, and wrap-around behavior.

**Limit**

- The proof harness is intentionally bounded and educational. It strengthens
  evidence for the stated model, but does not claim industrial certification.

## Claim 4: The verification story is layered

**Evidence**

- Compiler warnings are treated as a quality gate.
- Unit tests cover concrete behavior.
- Sanitizers provide an optional runtime hardening path.
- Frama-C/WP checks ACSL contracts where the toolchain is available.
- `cppcheck` is available as an optional static-analysis target.
- `make coverage` is available as optional GCC/gcov evidence when supported.

**Limit**

- Tool availability differs by platform. Frama-C is expected mainly on Linux,
  CI, or Docker.
- Coverage reports and proof logs are generated evidence, not committed
  certification records.
