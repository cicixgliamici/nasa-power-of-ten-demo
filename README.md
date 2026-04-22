# NASA Power of Ten Demo

[![CI](https://github.com/cicixgliamici/nasa-power-of-ten-demo/actions/workflows/ci.yml/badge.svg)](https://github.com/cicixgliamici/nasa-power-of-ten-demo/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

This repository is a small C project inspired by the NASA/JPL paper
*The Power of Ten: Rules for Developing Safety-Critical Code*.

It is designed as a compact, reviewable engineering artifact:

* small enough to inspect quickly
* disciplined enough to discuss as an example of safety-oriented C practice
* documented enough to show traceability from paper to code

Its purpose is not to re-publish the paper, but to demonstrate the ability to:

* read a technical paper carefully
* extract concrete engineering rules from it
* translate those rules into implementation constraints
* design and test a small but disciplined software artifact
* reflect on the strengths and limitations of the paper in modern software practice

## What A Reviewer Should Notice

If you only have a few minutes, focus on these points:

* the main artifact is intentionally small and auditable
* implementation choices are tied back to explicit engineering rules
* tests cover normal behavior plus key edge cases
* the repository includes reflection on trade-offs, not just rule-following

Quick entry points:

* Main artifact: `include/ring_buffer.h` and `src/ring_buffer.c`
* Test evidence: `tests/test_ring_buffer.c`
* Rule traceability: `docs/rule-mapping.md`

## Main Artifact

The main implementation is a fixed-size ring buffer written in C.

The ring buffer was chosen because it is small enough to remain auditable,
yet rich enough to demonstrate several of the paper's core ideas:

* simple control flow
* bounded memory usage
* no dynamic allocation
* explicit error handling
* assertions for internal invariants
* warning-clean compilation
* small, testable functions

## Repository Structure

* `include/` - public API
* `src/` - implementation
* `tests/` - unit tests for the ring buffer
* `examples/` - isolated bad/good examples for each rule
* `docs/` - mapping from paper rules to design decisions, examples, and reflections

## Why a Ring Buffer

A ring buffer is a useful demonstration target because it has:

* a small and bounded state space
* clear invariants
* no need for heap allocation
* meaningful edge cases such as wrap-around, full, and empty states

This makes it a good vehicle for showing disciplined implementation rather than accidental complexity.

## What This Repository Demonstrates

This repository is intended to show:

* paper comprehension
* disciplined C programming
* explicit design trade-offs
* traceability from guideline to implementation
* testing beyond "happy path" scenarios

## Implemented Rules At A Glance

| Rule | Repository interpretation | Main evidence |
|---|---|---|
| 1 | Keep control flow simple | Small linear ring-buffer operations in `src/` |
| 2 | Use bounded loops and predictable iteration | Fixed-capacity design and bounded test loops |
| 3 | Avoid dynamic allocation after initialization | No heap allocation in the core artifact |
| 4 | Keep functions small | Narrow API and short single-purpose functions |
| 5 | Assert internal invariants | `assert` checks in `src/ring_buffer.c` |
| 6 | Keep scope narrow | Local variables introduced close to use |
| 7 | Check return values explicitly | `rb_status_t` API and assert-based tests |
| 8 | Keep preprocessor use simple | Include guards and simple constants only |
| 9 | Keep pointer usage simple | Direct pointer checks and straightforward dereferences |
| 10 | Compile cleanly and keep the code tool-friendly | Strict warning flags, CI, and static-analysis notes |

## Rule Traceability

A mapping between the paper's rules and this repository is provided in:

* `docs/rule-mapping.md`
* `docs/design-decisions.md`
* `docs/reflection.md`
* `docs/evidence-matrix.md`

## Build

```bash
make
```

On Windows with MinGW/WinLibs, the equivalent command is typically:

```bash
mingw32-make
```

## Run tests

```bash
make test
```

On Windows with MinGW/WinLibs:

```bash
mingw32-make test
```

## Build examples

```bash
make examples
```

On Windows with MinGW/WinLibs:

```bash
mingw32-make examples
```

## Notes

This is not a production-ready safety-critical library.

It is a compact engineering study project whose goal is to demonstrate how a technical paper can be read, interpreted, implemented, and critically assessed.

## Quick Reviewer Guide

If you are visiting this repository to evaluate the project quickly, the best path is:

1. Read this README for the project goal and structure.
2. Open `docs/reviewer-guide.md` for a short guided tour.
3. Open `docs/evidence-matrix.md` for a one-page traceability view.
4. Open `docs/rules-summary-table.md` for a compact overview of all ten rules.
5. Inspect `src/` and `tests/` for the main implementation artifact.
6. Read `docs/design-decisions.md` and `docs/reflection.md` for engineering rationale.

This repository is intentionally small: the focus is not feature breadth, but traceability from engineering guideline to implementation choice.

## Quality Gates

The repository uses a few simple quality gates to keep the artifact disciplined and auditable:

- `make` builds the core implementation
- `make test` runs the test suite
- `make examples` builds the example material
- `make sanitize` provides an optional sanitizer-oriented build path
- CI runs these checks automatically on push and pull request
- `docs/static-analysis-notes.md` records the warning/static-analysis stance

These checks are deliberately lightweight, consistent with the spirit of the project: keep the code small enough to understand, and strict enough to reason about.

## Verification

The verification story is intentionally lightweight but explicit:

- strict compiler warnings are enabled in the `Makefile`
- unit tests cover FIFO behavior, empty/full handling, null checks, clear, and wrap-around
- example files provide small compliant/non-compliant comparisons for the paper rules
- CI runs build, tests, and example compilation automatically
- the repository documents how static-analysis and sanitizer-oriented checks fit into the project

## Platform Notes

The repository is designed around a simple `Makefile` workflow and is exercised in CI on Linux.

For local Windows use, a MinGW-compatible toolchain such as WinLibs can also build and run the project successfully with:

- `mingw32-make test`
- `mingw32-make examples`

The optional `sanitize` target is intended as a lightweight hardening path, but support depends on the local toolchain.
Some Windows MinGW distributions do not ship the AddressSanitizer and UndefinedBehaviorSanitizer runtime libraries required by `-fsanitize=address,undefined`.

## Additional Documentation

- `docs/reviewer-guide.md` - how to read the repository as an evaluator
- `docs/evidence-matrix.md` - one-page mapping from rule to code, tests, and examples
- `docs/rules-summary-table.md` - compact status/mapping for the ten rules
- `docs/static-analysis-notes.md` - compiler warnings and static-analysis stance

## Repository Hygiene

- `LICENSE` defines reuse permissions explicitly
- GitHub Actions validates Linux and Windows build paths
- `CODEOWNERS` and a pull request template make review expectations clearer
