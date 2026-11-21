# Task B3 – Cost comparison

This executable benchmarks switch-based dispatch against virtual dispatch at 1,000, 1,000,000 and 10,000,000 bills, then compares return-code validation with exception validation for one million claims at 0%, 1% and 50% invalid rates. Compile with `-O2` for the requested optimized measurements.

## Complexity
Both switch and virtual approaches perform O(n) total work; each bill calculation/dispatch is O(1). The virtual representation stores polymorphic objects (typically including a vptr) and incurs allocation/indirection in this simple benchmark. The tagged structure stores a type field and common payload fields. Exception success paths are typically inexpensive, while throwing/catching becomes more costly as the invalid percentage rises. Return-code validation uses ordinary branches and is often preferable when rejection is frequent.

## Interpretation
Timings are machine-dependent. Use the measured values in `output.txt` as evidence from this run, not as universal performance claims. The program reports the first pair's correctness check and includes a timing caveat.

## Alternative: std::variant
A `variant<OutPatient, InPatient>` stores one of the alternatives inline, with storage at least as large as the largest alternative plus a discriminator. `std::visit` dispatches based on the active alternative. It can avoid per-object heap allocation and virtual pointers, while keeping heterogeneous values in one container. Add a third alternative to the variant and update visitors as needed.
