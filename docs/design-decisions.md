# Design Decisions

## Why a fixed-size ring buffer
Chosen because it is small, stateful, bounded, and easy to audit.

## Why no dynamic allocation
To reflect the paper's preference for predictable memory behavior.

## Why return status codes
To make failures explicit and testable.

## Why assertions are still used
To capture internal invariants that should never be violated.

## Why the project stays intentionally small
The goal is traceability and disciplined implementation, not feature breadth.
