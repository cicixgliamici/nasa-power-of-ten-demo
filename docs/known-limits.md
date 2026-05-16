# Known Limits

This repository is intentionally honest about its scope.

## What This Project Does Not Claim

- It is not production safety-critical software.
- It is not certified against any aerospace, automotive, medical, or industrial
  safety standard.
- It does not claim MISRA C or CERT C compliance.
- It does not include tool qualification evidence.
- It does not include committed formal proof logs for every run.
- It does not include committed coverage reports.

## Tooling Limits

- Frama-C, cppcheck, coverage, sanitizers, and Docker are optional.
- Tool availability varies across Linux, Windows, and local developer machines.
- The formal-verification workflow is manual so normal CI remains lightweight.

## Model Limits

- The ACSL layer strengthens the FIFO story, but it remains educational.
- The proof harness covers representative formal scenarios, not a
  certification-grade model of every possible history.
- The fixed capacity is a deliberate design choice for reviewability, not a
  general-purpose container feature.

## Why These Limits Are Acceptable Here

The goal is to show disciplined translation from a safety-oriented paper into a
small C artifact with tests, contracts, review documentation, and explicit
trade-offs. The project is designed for portfolio and educational review, not
for deployment in a safety-critical system.
