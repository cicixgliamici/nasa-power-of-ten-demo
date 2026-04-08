# NASA Power of Ten Demo

This repository is a small C project inspired by the NASA/JPL paper
*The Power of Ten: Rules for Developing Safety-Critical Code*.

Its purpose is not to re-publish the paper, but to demonstrate the ability to:

* read a technical paper carefully
* extract concrete engineering rules from it
* translate those rules into implementation constraints
* design and test a small but disciplined software artifact
* reflect on the strengths and limitations of the paper in modern software practice

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

* `include/` — public API
* `src/` — implementation
* `tests/` — unit tests for the ring buffer
* `examples/` — isolated bad/good examples for each rule
* `docs/` — mapping from paper rules to design decisions, examples, and reflections

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
* testing beyond “happy path” scenarios

## Rule Traceability

A mapping between the paper's rules and this repository is provided in:

* `docs/rule-mapping.md`
* `docs/design-decisions.md`
* `docs/reflection.md`

## Build

```bash
make
```

## Run tests

```bash
make test
```

## Build examples

```bash
make examples
```

## Notes

This is not a production-ready safety-critical library.

It is a compact engineering study project whose goal is to demonstrate how a technical paper can be read, interpreted, implemented, and critically assessed.

## Quick Reviewer Guide

If you are visiting this repository to evaluate the project quickly, the best path is:

1. Read this README for the project goal and structure.
2. Open `docs/reviewer-guide.md` for a short guided tour.
3. Open `docs/rules-summary-table.md` for a compact overview of all ten rules.
4. Inspect `src/` and `tests/` for the main implementation artifact.
5. Read `docs/design-decisions.md` and `docs/reflection.md` for engineering rationale.

This repository is intentionally small: the focus is not feature breadth, but traceability from engineering guideline to implementation choice.

## Quality Gates

The repository uses a few simple quality gates to keep the artifact disciplined and auditable:

- `make` builds the core implementation
- `make test` runs the test suite
- `make examples` builds the example material
- CI runs these checks automatically on push and pull request
- `docs/static-analysis-notes.md` records the intended warning/static-analysis discipline

These checks are deliberately lightweight, consistent with the spirit of the project: keep the code small enough to understand, and strict enough to reason about.

## Additional Documentation

- `docs/reviewer-guide.md` — how to read the repository as an evaluator
- `docs/rules-summary-table.md` — compact status/mapping for the ten rules
- `docs/static-analysis-notes.md` — compiler warnings and static-analysis stance
