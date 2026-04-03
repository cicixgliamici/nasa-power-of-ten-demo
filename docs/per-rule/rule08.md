# Rule 8 — Macros

## Intent
Avoid hidden behavior introduced by function-like macros.

## Bad example
`SQUARE(x)` expands textually and does not preserve intended grouping.

Example:
`SQUARE(1 + 2)` becomes `1 + 2 * 1 + 2`, which evaluates to `5`.

## Good example
A normal function preserves type checking, scoping, and evaluation clarity.

## Why this matters
The paper's point is not to ban every macro,
but to avoid using the preprocessor as a hidden programming language.
