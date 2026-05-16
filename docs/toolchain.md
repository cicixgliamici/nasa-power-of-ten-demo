# Toolchain Notes

This repository keeps the required toolchain deliberately small. Optional tools
add evidence for reviewers, but they are not required to understand the code.

## Required Core Path

The normal review path expects:

- a C99-capable compiler, tested primarily with GCC,
- `make`,
- a shell environment that can run the generated test executable.

Run:

```bash
make review
```

This builds the core artifact, runs tests, builds examples, and runs the
sanitizer path when the local toolchain supports it.

## Linux Review Path

Linux is the simplest path for the full reviewer workflow:

```bash
sudo apt-get update
sudo apt-get install -y build-essential make cppcheck gcovr frama-c why3 z3
make review
make review-optional WP_PROVER=z3
make coverage
```

Package names may vary by distribution. `gcov` is normally provided by GCC.

## Windows Review Path

On Windows, use MSYS2/MinGW for the core path:

```bash
mingw32-make
mingw32-make test
mingw32-make examples
```

Sanitizer and coverage availability depends on the installed MinGW runtime.
Treat `sanitize` and `coverage` as optional on Windows.

## Frama-C Path

For local formal verification:

```bash
make verify WP_PROVER=z3
make verify-fifo WP_PROVER=z3
```

The manual GitHub Actions workflow also runs these checks on Linux.

## Docker Path

If Docker is available, the Frama-C container path is:

```bash
make verify-docker
```

This is optional and intended for reviewers who want formal-verification
evidence without installing Frama-C locally.

