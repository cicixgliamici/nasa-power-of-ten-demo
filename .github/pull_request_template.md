## Summary

- describe the change briefly
- explain why it is needed

## Validation

Required reviewer path:

- [ ] `make review`

Individual checks, when useful:

- [ ] `make`
- [ ] `make test`
- [ ] `make examples`
- [ ] `make sanitize`

Optional tool-dependent checks:

- [ ] `make verify` when Frama-C is available or contracts changed
- [ ] `make verify-fifo` when FIFO contracts or proof harness changed
- [ ] `make cppcheck` when cppcheck is available
- [ ] `make coverage` when GCC/gcov coverage is available

Documentation:

- [ ] docs updated when evidence, claims, or limitations changed

## Notes

- mention any platform-specific behavior
- mention any limitations or follow-up work
