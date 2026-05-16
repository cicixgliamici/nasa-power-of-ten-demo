# Reflection

## What remains highly relevant today
- warning-clean compilation
- bounded state
- explicit error handling
- simplicity of control flow
- contracts that make assumptions and side effects explicit

## What would be complemented by modern practice
- sanitizers
- static analysis
- CI pipelines
- coverage tooling
- formal methods used with clear scope and limitations

## What is intentionally restrictive
Some rules reduce convenience and generality,
but this is part of the pedagogical value of the exercise.

In this repository, the fixed capacity and narrow API are not accidental
shortcomings. They make the artifact easier to reason about and easier to
connect back to the paper.

## What the Frama-C layer adds
The ACSL contracts make the ring buffer's API discipline explicit:
preconditions, side effects, null behavior, state validity, and FIFO-oriented
logical preservation are visible beside the code.

The proof harness adds a useful middle ground between unit tests and a full
industrial formal model. It demonstrates how formal verification can support
review without pretending that a small educational repository is certified
safety-critical software.

## What still should not be overstated
The repository is more reviewer-ready after adding contracts, but it is still a
study project. It does not include certification process evidence, coverage
reports as committed evidence, MISRA compliance records, tool qualification, or
a complete formal model of all possible histories.

That limitation is part of the honest story: the project demonstrates strong
engineering habits in a small scope, not production aerospace assurance.

## What I learned from implementing the paper
The rules are more useful when treated as engineering constraints
rather than as slogans.
