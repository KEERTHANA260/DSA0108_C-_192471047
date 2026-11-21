# Task A4 – Exception strategy

## Error list and hierarchy
```text
std::exception
  └── std::runtime_error
       └── BillingError
            ├── InvalidCharge
            ├── ClaimError
            ├── UnknownPackage
            └── MissingPatient
```
Other standard failures include `std::bad_alloc` for allocation failure and `std::invalid_argument` / `std::out_of_range` for invalid numeric conversion.

## Exception specifications
Validation, parsing, bill creation and claim approval may throw. Functions that only release resources (destructors) should not throw; destructors are normally `noexcept`. Throwing during stack unwinding can terminate the program. A function should be marked `noexcept` only when it can genuinely guarantee not to throw.

## Alternative: status return
A function could return an enum status (or `bool`) and write an error message to an output parameter. The normal path avoids exception unwinding and has predictable branching. The caller must check every result and pass error details back explicitly, increasing plumbing and the risk of ignored status values. Exceptions cost more on the error path; return codes add little per-result state but more caller code.
