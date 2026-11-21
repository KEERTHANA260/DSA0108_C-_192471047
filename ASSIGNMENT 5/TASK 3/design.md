# Task A3 – Abstract payer classes

`Payer` is an abstract interface with the pure virtual operation `amountCovered(const Bill&)`. `SelfPay`, `Insurance`, and `GovernmentScheme` implement it. Insurance stores a cover limit and co-payment percentage; GovernmentScheme stores a fixed package rate.

## Extension
A new payer such as `CorporatePayer` derives from `Payer` and implements `amountCovered()`. Existing payer classes and the code that iterates over `Payer` pointers do not need to change.

## Alternative: function objects
A `std::function<double(const Bill&)>` can hold a selected policy function. The policy can capture data such as a cover limit. A call is O(1) in the usual model, like virtual dispatch. A function object stores callable state (and may allocate depending on its size); a class-based payer stores its policy data in named members and offers a clear interface. Both approaches support run-time selection.
