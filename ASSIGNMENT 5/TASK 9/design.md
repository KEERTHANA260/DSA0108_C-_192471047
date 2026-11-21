# Task B4 – Final engineering decision

## Extension
The program adds `CorporatePackageBill` and `CorporateTieUp` as new derived classes. The existing `Bill` and `Payer` interfaces remain unchanged, and earlier bill types continue to work through base-class pointers.

## Resource safety
All objects are owned by `std::unique_ptr`; base classes have virtual destructors. The program can be compiled with AddressSanitizer using:
```bash
g++ -std=c++17 -Wall -Wextra -O1 -g -fsanitize=address -fno-omit-frame-pointer code.cpp -o app
./app
```
A clean run should finish without AddressSanitizer memory-error reports. Sanitizer availability depends on the compiler/runtime environment.

## Production decision
A polymorphic design is suitable when new bill and payer types are added regularly: each new type implements a stable interface, while processing code remains unchanged. Exceptions are appropriate for unusual failures; expected high-frequency validation failures may be better represented by status/optional results. A production hospital system also needs persistent storage, audit logging, authentication, transaction boundaries, input validation, tests and operational monitoring; this assignment is a design demonstration, not a deployable billing system.

## Alternative: configuration-driven plug-ins
Rates and simple policies could be loaded from validated configuration files. Rule interpretation adds lookup/interpretation work per bill and requires schema/version management. It reduces code changes for rate-only updates, but complex new behavior still needs code. C++ classes provide stronger compile-time checking; configuration is more flexible but introduces parsing and configuration-risk concerns.
