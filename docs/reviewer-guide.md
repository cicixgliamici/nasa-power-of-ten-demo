# Reviewer Guide

This repository is a compact engineering study inspired by the NASA/JPL paper  
*The Power of Ten: Rules for Developing Safety-Critical Code*.

It is not intended to be a production-grade safety-critical framework.  
Its purpose is narrower and more explicit:

- read a well-known engineering paper carefully,
- extract concrete rules,
- map those rules to implementation constraints,
- build a small artifact that can be audited,
- and reflect critically on what is gained and what is lost.

## What the main artifact is

The core artifact is a fixed-size ring buffer implemented in C.

A ring buffer is a good demonstration target because it is:

- small enough to inspect fully,
- bounded in memory usage,
- rich enough to contain non-trivial invariants,
- and simple enough to keep accidental complexity under control.

## How to read the repository

A good reading order is:

1. `README.md`  
   Project purpose, scope, and high-level structure.

2. `include/` and `src/`  
   Public API and implementation.

3. `tests/`  
   Evidence that normal and edge-case behavior are checked.

4. `docs/rule-mapping.md`  
   Traceability from paper rules to repository choices.

5. `docs/design-decisions.md`  
   Why the ring buffer was chosen and how constraints were interpreted.

6. `docs/reflection.md`  
   Critical discussion of strengths, trade-offs, and limitations.

7. `docs/rules-summary-table.md`  
   Compact overview of all ten rules and the repository’s current coverage.

## What this repository tries to demonstrate

This project is meant to demonstrate:

- careful reading of a technical paper,
- disciplined implementation under explicit constraints,
- bounded-state reasoning,
- test-oriented engineering,
- traceability from principle to code,
- and the ability to explain design choices clearly.

## What this repository does not claim

This repository does **not** claim to be:

- a certified safety-critical library,
- a full implementation of all practices used in aerospace software,
- or a substitute for formal verification, industrial toolchains, or process standards.

It is best understood as a compact, auditable, paper-to-code study project.

## What an evaluator may want to check

An evaluator reviewing this repository may want to ask:

- Is the implementation intentionally small and bounded?
- Are the design constraints visible in the code?
- Are invariants and error paths handled explicitly?
- Is there traceability between documented rule and concrete implementation?
- Are the tests aligned with the intended discipline?
- Does the reflection show understanding rather than blind rule-following?

Those are the main questions this repository is designed to support.
