# Static Analysis and Warning Discipline Notes

This repository is intentionally small, but it still benefits from a disciplined build and warning policy.

The goal of these notes is not to overstate the verification story,
but to make the current quality stance explicit and reviewable.

## Goals

The warning/static-analysis stance of this project is guided by three principles:

1. keep the code easy to inspect,
2. detect suspicious constructs early,
3. avoid relying on complex tooling to compensate for unclear code.

## Compiler Warning Intent

The repository aims to compile cleanly under a strict warning profile.

In this repository, the `Makefile` currently enables:

- `-Wall`
- `-Wextra`
- `-Werror`
- `-pedantic`
- `-Wconversion`
- `-Wshadow`
- `-Wstrict-prototypes`

This warning profile is intentionally strict for a project of this size:
the point is not to maximize compiler flag count, but to keep questionable
constructs visible and to support code review.

## Why this matters here

The value of this repository is not in performance or feature richness.

Its value is in disciplined implementation under explicit constraints.

For that reason, warning-clean compilation is not just a "nice to have":
it is part of making the artifact small, inspectable, and trustworthy.

## Current Quality Gates

The repository already includes a lightweight but concrete verification path:

- `make` builds the core artifact and examples
- `make test` builds and runs the unit tests
- `make sanitize` provides a sanitizer-oriented build mode
- GitHub Actions runs build, tests, and examples on push and pull request

These checks are intentionally modest, but they align with the scope of the project:
small codebase, explicit constraints, and reviewability over toolchain complexity.

## Platform Considerations

The repository's default verification path is exercised in Linux CI, which matches the simplest `make` workflow.

On Windows, the same project can be built with a MinGW-compatible toolchain using `mingw32-make`.
The core build, tests, and example compilation work with that setup, but sanitizer availability is toolchain-specific.

In particular, some MinGW distributions do not include the runtime libraries required for:

- `-fsanitize=address`
- `-fsanitize=undefined`

In those environments, the `sanitize` target should be treated as an optional capability rather than a guaranteed cross-platform check.

## Possible Lightweight Static-Analysis Tools

The following tools are natural fits for a repository of this kind:

- `cppcheck`
- `clang-tidy`
- compiler sanitizers in debug-oriented builds

These are not required for understanding the repository, but they are useful extensions for future hardening.

## Scope Note

This project does **not** attempt to reproduce the full industrial verification stack of a safety-critical environment.

Instead, it adopts a lighter but educationally meaningful stance:

- small codebase,
- explicit constraints,
- tests,
- warnings,
- optional sanitizers,
- and traceability documentation.

## Future Extension Ideas

Possible future improvements include:

- adding an optional `cppcheck` target,
- documenting example output or expected verification steps for reviewers,
- attaching warning/static-analysis results to CI artifacts,
- and expanding CI with additional compiler/toolchain variants when useful.
