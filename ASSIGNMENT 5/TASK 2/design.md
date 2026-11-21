# Task A2 – Runtime binding

## Early vs late binding
A non-virtual call is selected using the pointer's static type at compile time (early binding). A virtual call such as `b->total()` is selected at run time using the actual object type (`OPBill`), so it calls `OPBill::total()`.

## Conceptual vtables
```text
Bill vtable:       total -> pure virtual entry; destructor -> Bill::~Bill
OPBill vtable:     total -> OPBill::total;      destructor -> OPBill::~OPBill
```
The `Bill*` points to an `OPBill`; its vptr leads to the derived vtable, and the virtual call selects `OPBill::total()`.

## Why virtual destructor?
Deleting a derived object through `Bill*` must run the derived destructor and then the base destructor. A virtual base destructor makes that behavior correct. Without it, deleting through the base pointer is undefined behavior.

## Program prediction
Expected output: `500 ~OPBill ~Bill` followed by a newline. `show()` itself is non-virtual, but it calls the virtual `total()` internally, so the derived override is selected.

## Alternative: dynamic_cast chain
Without virtual `total()`, code could test each possible derived type using `dynamic_cast` and call its calculation. For k types, one bill may require up to k checks; processing n bills can take O(nk) type checks in the worst case. A virtual call is O(1) dispatch per bill. A polymorphic object typically carries one vptr, while a cast-chain design adds branching and must be updated when types are added.
