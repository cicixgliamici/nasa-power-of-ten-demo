# Review Results Template

Use this file as a lightweight review log when collecting evidence for a PR,
portfolio review, or external walkthrough. It is a template, not a permanent
claim that every tool was run on every machine.

## Review Metadata

- Date:
- Reviewer:
- Platform:
- Compiler:
- Frama-C version, if used:
- cppcheck version, if used:
- Notes:

## Required Review Path

| Command | Result | Notes |
|---|---|---|
| `make review` | Not run / Pass / Fail | Builds, tests, examples, and sanitizer path on supported toolchains |

## Individual Checks

| Command | Result | Notes |
|---|---|---|
| `make` | Not run / Pass / Fail | Core build plus examples |
| `make test` | Not run / Pass / Fail | Unit tests |
| `make examples` | Not run / Pass / Fail | Good examples compile |
| `make sanitize` | Not run / Pass / Fail | Requires sanitizer runtime support |

## Optional Evidence

| Command | Result | Notes |
|---|---|---|
| `make cppcheck` | Not run / Pass / Fail | Requires cppcheck |
| `make coverage` | Not run / Pass / Fail | Requires GCC/gcov coverage support |
| `make verify WP_PROVER=z3` | Not run / Pass / Fail | Requires Frama-C, Why3, and prover setup |
| `make verify-fifo WP_PROVER=z3` | Not run / Pass / Fail | Stronger FIFO proof harness path |
| `make verify-docker` | Not run / Pass / Fail | Requires Docker |

## Summary

- Overall result:
- Important findings:
- Follow-up work:

