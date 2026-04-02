# NASA Power of Ten Demo

This repository is a small C project inspired by the NASA/JPL paper
*The Power of Ten: Rules for Developing Safety-Critical Code*.

The goal is simple: show the ability to read a technical paper,
extract practical rules, apply them to a small implementation,
and reflect on their value in modern software development.

The code implements a fixed-size ring buffer and follows a deliberately
restricted style: simple control flow, no dynamic memory allocation,
small functions, explicit error handling, and testable behavior.

## Project Structure

* `include/` - public header
* `src/` - implementation
* `tests/` - simple assert-based tests
* `docs/` - notes, mapping, reflection
* `examples/` - bad/good comparative examples for all ten rules

## Build

```bash
make
```

## Run tests

```bash
make test
```

## Build the good examples

```bash
make examples
```

## Why this repository exists

This project is not meant to be a full safety-critical software framework.
It is a compact study project designed to demonstrate:

* paper comprehension
* disciplined implementation
* clean project organization
* basic technical reflection beyond the original paper

---

.PHONY: all test examples clean
```
