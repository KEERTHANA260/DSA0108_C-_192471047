# Task A1 – Polymorphic bill hierarchy

## Common interface and data
Every bill stores the patient name and provides `total()`, `type()` and `print()`. `total()` and `type()` are pure virtual; `print()` is virtual and uses those functions.

## UML (text form)
```text
                 Bill (abstract)
          patient: string
          + total() const: double {pure virtual}
          + type() const: string {pure virtual}
          + print() const: void {virtual}
          + ~Bill() {virtual}
             /      |       |       \
 OutPatient  InPatient DayCare Emergency
```
Each derived class overrides `total()` and `type()`.

## Pseudocode – total all bills
```text
sum ← 0
FOR EACH Bill pointer b IN bills
    sum ← sum + b.total()
END FOR
PRINT sum
```

## Alternative: tagged structure and switch
A single structure could store a type tag and fields for every bill kind; `total()` would use `switch(type)`. Both approaches process n bills in O(n) time. The tagged structure may reserve space for fields that a particular bill does not use. With virtual functions, each object typically stores a vptr and derived-specific fields. Adding a new type requires a new derived class; with a switch, the central switch must also be edited. The polymorphic design keeps type-specific calculations separated.
