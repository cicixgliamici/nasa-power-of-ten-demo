# Rules Mapping

## Main component: ring buffer

| Rule | How it is applied |
|------|-------------------|
| 1 | No recursion, no goto, simple control flow |
| 2 | All loops in tests have fixed bounds |
| 3 | No malloc/free; fixed-size storage only |
| 4 | Functions are short and focused |
| 5 | Assertions check internal assumptions |
| 6 | Variables are declared in the smallest practical scope |
| 7 | Parameters are validated and return codes are checked |
| 8 | Only simple macros are used |
| 9 | Pointer usage is limited and explicit |
| 10 | Strict compiler flags are used in the Makefile |

## Comparative examples

The `examples/` directory contains bad/good pairs
for each rule, for educational purposes.
