# Task B2 – Engineer error conditions

The program checks negative amounts, claims above cover, invalid numeric text and a controlled `std::bad_alloc` exception. The allocation-failure case deliberately throws `std::bad_alloc` rather than requesting unbounded memory, which could destabilize the machine. A resource object prints from its destructor to show cleanup during stack unwinding. A top-level `catch(...)` demonstrates a final safety net.

## Expected behavior
- A valid claim is approved.
- A claim above cover is logged and rethrown with `throw;`, preserving `ClaimError`.
- A negative amount is caught as `std::exception` by the caller.
- Invalid text is rejected by `std::stod` with `std::invalid_argument`.
- The controlled allocation exception is caught as `std::bad_alloc`.

## Alternative: std::optional
`approve` could return `optional<double>`; an empty optional represents rejection. For one million claims, both designs do O(n) work. Optional avoids exception-unwinding costs and is often attractive when failures are expected. Exceptions keep the normal success path uncluttered when failures are unusual. Optional results carry a value/presence state; exceptions carry an exception object and message only on failure.
