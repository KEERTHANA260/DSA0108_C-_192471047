# Task A5 – Recovery and rethrowing

## Catch, log and rethrow
A low-level function should normally throw when it cannot complete. A layer that can add useful context may catch, log and use `throw;` to rethrow the same exception. The top-level application catches the error, reports it to the user and decides whether to continue.

## Stack unwinding and RAII
When an exception leaves a scope, automatic objects in that scope are destroyed in reverse construction order. A `Guard`, `std::vector`, `std::string`, file stream or `std::unique_ptr` releases its resource through its destructor. This is RAII and avoids manually writing `delete` in every catch block.

## Output prediction
The `service` guard is destroyed first, then the `billing` guard, then `main` guard after the catch completes. The normal statement after the throwing call is skipped. The program catches at the top level and continues to its recovery message.

## Alternative: manual delete in catch blocks
Manual cleanup can work, but every error path must release every resource. If new catch paths are added, each must be audited. RAII keeps cleanup tied to object lifetime; both approaches have O(1) cleanup per resource, but RAII reduces duplicated cleanup code and leak risk.
