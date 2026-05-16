# Audit Checklist — NASA Power of Ten Demo

This checklist is meant to make the repository easier to review as a compact engineering artifact inspired by the NASA/JPL *Power of Ten* discipline.

It is not a claim of full safety-critical certification. Instead, it is a reviewer-oriented map showing where the repository demonstrates the intended design constraints.

---

## How to use this checklist

A reviewer can use this file together with:
- `README.md`
- `docs/rule-mapping.md`
- `docs/design-decisions.md`
- `docs/reviewer-readiness.md`
- `docs/toolchain.md`
- `docs/review-results.md`
- `docs/known-limits.md`
- `src/`
- `tests/`

The goal is to make it fast to verify that the implementation choices are not accidental, but connected to explicit engineering rules.

---

## Review checklist

| Area | What to verify | Where to inspect |
|---|---|---|
| Bounded memory use | No heap allocation in the core artifact; fixed-size data structure | `src/`, `include/` |
| Small auditable artifact | Main artifact remains intentionally compact and reviewable | `src/`, `tests/` |
| Explicit error handling | Error states are surfaced explicitly rather than hidden | `src/`, public API |
| Assertions / invariants | Internal assumptions are defended by checks where appropriate | `src/` |
| API contracts | Public API assumptions, side effects, and basic state transitions are written as ACSL contracts | `include/ring_buffer.h`, `docs/frama-c-contracts.md` |
| FIFO proof layer | Deeper ACSL helpers and proof harness describe representative FIFO preservation | `include/ring_buffer_contracts.h`, `proof/ring_buffer_fifo_harness.c` |
| Simple control flow | Functions avoid unnecessary complexity and remain easy to trace | `src/` |
| Warning discipline | Build is intended to remain clean under strict compiler warnings | `Makefile`, CI, `docs/static-analysis-notes.md` |
| Test coverage of edge cases | Empty/full buffer, wrap-around, invalid operations, boundary scenarios | `tests/` |
| Guideline traceability | Each important implementation choice can be connected back to a repository design rationale | `docs/rule-mapping.md`, `docs/design-decisions.md` |
| Reviewer readiness | Strengths and remaining review risks are stated explicitly | `docs/reviewer-readiness.md` |
| Review evidence capture | Reviewers have a lightweight place to record commands and outcomes | `docs/review-results.md` |
| Toolchain clarity | Required and optional tooling paths are documented | `docs/toolchain.md` |
| Scope honesty | Non-claims and limitations are explicit | `docs/known-limits.md` |
| Good vs bad examples | Examples illustrate why the disciplined style matters | `examples/` |
| Lightweight quality gates | Build, tests, and examples are all easy to run and inspect | `Makefile`, CI |

---

## Suggested fast review path

If you only have a few minutes:

1. Read `README.md`
2. Open `docs/rule-mapping.md`
3. Inspect the ring buffer implementation in `src/`
4. Read the tests in `tests/`
5. Check `docs/design-decisions.md`, `docs/static-analysis-notes.md`, and `docs/frama-c-contracts.md`
6. Check `docs/verification-matrix.md` and `docs/safety-case.md`
7. Check `docs/reviewer-readiness.md`
8. Check `docs/toolchain.md`, `docs/review-results.md`, and `docs/known-limits.md`

That is enough to understand the repository as a small but disciplined engineering study.

---

## What this repository is meant to demonstrate

This repository is mainly intended to demonstrate:
- careful reading of an engineering paper / guideline set
- disciplined translation from rules to implementation choices
- compact C code designed to remain auditable
- explicit API contracts that support mechanical checking
- a deeper FIFO proof harness that keeps proof code separate from production code
- testing and documentation that support reviewability
- engineering reflection rather than feature breadth

---

## Notes

This checklist is deliberately short. The point is not to bury the reviewer in process, but to make the repository faster to inspect and easier to trust.
