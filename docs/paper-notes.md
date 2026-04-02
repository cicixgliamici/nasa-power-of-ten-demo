# Paper Notes

This repository is inspired by the NASA/JPL paper
"The Power of Ten: Rules for Developing Safety-Critical Code".

## Main idea

The paper proposes a small set of simple, checkable rules
to reduce code complexity and improve verifiability.

## The ten rules in short

1. Avoid complex flow of control.
2. Give all loops a fixed upper bound.
3. Do not use dynamic memory allocation after initialization.
4. Keep functions small.
5. Use assertions to check invariants.
6. Declare data objects at the smallest possible scope.
7. Check return values and validate parameters.
8. Limit use of the preprocessor.
9. Limit pointer use.
10. Compile with strong warnings and use static analysis.

## Takeaway

The strength of the paper is not only in each individual rule,
but in the fact that the rules are simple, local, and enforceable.
