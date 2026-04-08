# Rules Summary Table

This table is a compact overview of how the ten rules from  
*The Power of Ten: Rules for Developing Safety-Critical Code*  
are interpreted in this repository.

The goal is not to claim perfect or exhaustive compliance, but to make the repository easier to inspect and evaluate.

| Rule | Short Interpretation | Repository Evidence | Current Status |
|---|---|---|---|
| 1 | Keep control flow simple | Small implementation scope, straightforward ring-buffer operations, limited branching in core code | Partially demonstrated |
| 2 | Give loops fixed bounds | Bounded data structure and preference for predictable iteration | Partially demonstrated |
| 3 | Avoid dynamic memory allocation after initialization | Ring buffer chosen specifically to support bounded storage and no heap dependence in the core artifact | Demonstrated in design intent |
| 4 | Keep functions small | Core artifact intentionally kept compact and auditable | Partially demonstrated |
| 5 | Use assertions liberally for internal invariants | Assertions used as a mechanism for documenting and checking assumptions | Partially demonstrated |
| 6 | Keep data/control scope narrow | Small public API and limited state footprint in the main artifact | Partially demonstrated |
| 7 | Check return values / propagate errors explicitly | Error handling is treated as part of the design, not as an afterthought | Partially demonstrated |
| 8 | Limit preprocessor use / avoid complexity hidden by macros | Repository keeps the implementation intentionally direct and inspectable | Demonstrated in style intent |
| 9 | Prefer simple tool-friendly code | Small codebase, warning-clean intent, and static-analysis notes | Partially demonstrated |
| 10 | Keep code easy to audit | Repository structure, traceability docs, tests, and reflections all aim at auditability | Demonstrated at repository level |

## How to interpret the status column

The status labels are intentionally conservative.

- **Demonstrated in design intent** means the rule is clearly reflected in the repository’s design choices and scope.
- **Partially demonstrated** means there is visible evidence, but not yet a fully isolated or systematic demonstration for every aspect of the rule.
- **Demonstrated at repository level** means the repository structure and documentation clearly support the rule’s spirit, even if not every line of code is a direct example.

## Why this table exists

A small repository can be easy to read, but still hard to evaluate quickly.

This table exists to help a reviewer answer the question:

> “Where, concretely, do the paper’s ideas show up in this repository?”

For deeper discussion, see:

- `docs/rule-mapping.md`
- `docs/design-decisions.md`
- `docs/reflection.md`
- `docs/static-analysis-notes.md`
