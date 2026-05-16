# Design Decisions

## Why a fixed-size ring buffer
Chosen because it is small, stateful, bounded, and easy to audit.

The data structure is simple enough to inspect in one sitting, but still has
real safety-relevant behavior: empty/full states, wrap-around, null handling,
and FIFO ordering. That makes it a better demonstration artifact than a trivial
example with no meaningful state.

## Why no dynamic allocation
To reflect the paper's preference for predictable memory behavior.

All storage lives inside `ring_buffer_t`, so allocation failure, ownership
confusion, and heap fragmentation are outside the core artifact. This is a
deliberate trade-off: capacity is fixed, but analyzability improves.

## Why return status codes
To make failures explicit and testable.

The public API avoids hidden failure modes. Null pointers, empty reads, and full
writes are surfaced through `rb_status_t`, and tests assert the returned status
instead of assuming success.

## Why assertions are still used
To capture internal invariants that should never be violated.

Assertions are used for implementation assumptions, not as the public error
handling mechanism. Public misuse that can be expected, such as a null argument,
returns an explicit status code.

## Why ACSL contracts were added
The contracts make the API's assumptions, effects, and state transitions visible
to both reviewers and Frama-C.

The public header contains function contracts. The deeper logical helpers live
in `include/ring_buffer_contracts.h`, keeping the API readable while still
supporting a stronger FIFO-oriented model.

## Why the proof harness is separate
`proof/ring_buffer_fifo_harness.c` is not production code. It gives Frama-C
representative proof scenarios for push/pop, peek, and wrap-around behavior
without mixing proof-only sequences into the implementation.

This keeps the repository educational: the C artifact stays small, and the
formal-verification layer remains easy to find and discuss.

## Why the project stays intentionally small
The goal is traceability and disciplined implementation, not feature breadth.

A larger demo could show more APIs, but it would dilute the central point:
connect a safety-oriented guideline to code, tests, contracts, and reviewer
evidence in a compact repository.
