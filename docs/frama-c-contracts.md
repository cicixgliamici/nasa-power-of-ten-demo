# Frama-C and ACSL Contracts

This repository uses ACSL contracts as an optional formal-verification layer for
the core ring-buffer artifact.

The goal is not to claim industrial certification. The goal is narrower:
show how a small safety-oriented C module can make its assumptions, effects,
and state invariants explicit enough for mechanical checking.

## Why Contracts Fit This Project

The ring buffer is intentionally small and bounded:

- it has fixed storage,
- it does not allocate dynamically,
- it has a compact public API,
- and it has clear structural invariants.

That makes it a good target for Frama-C. The contracts complement the existing
quality gates:

- compiler warnings check suspicious C constructs,
- unit tests check representative behavior,
- assertions defend internal assumptions during execution,
- ACSL contracts describe required preconditions, side effects, and
  postconditions for all allowed calls.

## Contract Scope

The public API in `include/ring_buffer.h` defines the function contracts.
Shared logical helpers live in `include/ring_buffer_contracts.h` so the API
stays readable while the deeper proof model has a dedicated place.

The current contract layer covers:

- valid ring-buffer structure:
  - `head < RING_BUFFER_CAPACITY`,
  - `tail < RING_BUFFER_CAPACITY`,
  - `count <= RING_BUFFER_CAPACITY`,
  - `tail == (head + count) % RING_BUFFER_CAPACITY`;
- null-pointer behavior for functions that accept nullable arguments;
- success, empty, and full behaviors for `push`, `pop`, and `peek`;
- assigned memory locations for each operation;
- basic state transitions such as count increment/decrement and index wrap;
- logical FIFO range preservation across `push`, `pop`, and `peek`.

This is still deliberately small, but it now goes beyond structural validity:
the contracts describe how the logical FIFO sequence is preserved by the main
operations.

## FIFO Proof Harness

The repository also includes:

```text
proof/ring_buffer_fifo_harness.c
```

The harness is not production code. It gives Frama-C representative proof
sequences for:

- push/pop FIFO order,
- non-destructive peek,
- wrap-around preservation.

This keeps proof-oriented scenarios out of the implementation while making the
formal-verification path more concrete for reviewers.

## Current Limits

The contracts now model FIFO preservation through logical ranges, but they do
not claim industrial certification or a fully developed abstract algebra of all
possible histories.

That stronger model would be possible, but it would add more logic machinery.
For this repository, the deeper layer is meant to be useful and reviewable
without drowning the educational C artifact.

## Running Frama-C

If Frama-C is installed and available in `PATH`, run:

```bash
make verify
```

The target expands to:

```bash
frama-c -wp -wp-rte -Iinclude src/ring_buffer.c
```

For the stronger FIFO harness path, run:

```bash
make verify-fifo WP_PROVER=z3
```

If Docker is available, the optional container path is:

```bash
make verify-docker
```

See `docs/toolchain.md` for toolchain setup notes and `docs/review-results.md`
for a lightweight place to record formal-verification outcomes.

To select a specific prover, pass `WP_PROVER`:

```bash
make verify WP_PROVER=z3
```

The `-wp` option asks Frama-C to prove the ACSL contracts using the WP plugin.
The `-wp-rte` option also generates runtime-error proof obligations, such as
array bounds and arithmetic checks.

## GitHub Actions

The repository includes a manual GitHub Actions workflow:

```text
.github/workflows/formal-verification.yml
```

It is intentionally triggered with `workflow_dispatch` rather than every push.
That keeps the normal C build/test CI lightweight while still giving reviewers
a repeatable way to run the formal-verification path when Frama-C evidence is
needed.

The workflow installs:

- `frama-c`,
- `why3`,
- `z3`.

The workflow runs both `make verify` and `make verify-fifo`.

WP can simplify some goals internally, but external provers are the practical
path for completing proof obligations in a real verification run.

## Reviewer Interpretation

A successful Frama-C run should be read as evidence that the implementation is
consistent with the stated contracts, not as evidence that every possible
safety property has been specified.

In other words:

- tests show selected executions,
- assertions check assumptions during execution,
- ACSL states the intended API contract,
- the FIFO proof harness exercises representative formal scenarios,
- Frama-C checks the implementation against the stated contracts.

The value is the combination: the repository becomes easier to audit because
the code, tests, and formal contracts all point at the same design intent.
