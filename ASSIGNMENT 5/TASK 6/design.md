# Task B1 – Implement and validate polymorphic billing

The program implements four bill types and three payer types. All bills are processed through `Bill` pointers and all payer policies through `Payer` pointers. `std::unique_ptr` owns the objects and safely destroys them.

## Hand checks
- OP: 500 + 1,200 = 1,700
- IP: 3 × 2,500 + 40,000 = 47,500
- Day-care: 18,000
- Emergency: 2,000 + (750 × 4) = 5,000
- Grand total: 72,200

## Runtime binding evidence
`total()` and `type()` are virtual. Removing `virtual` from the base `total()` declaration makes the derived `override` declarations invalid and the compiler reports that they do not override. The base destructor is virtual so deleting through a base pointer destroys the complete derived object.

## Alternative: templates
Separate containers such as `vector<OutPatient>` and `vector<InPatient>` can use templates and avoid virtual dispatch. Each bill calculation remains O(1), and processing n bills is O(n). However, keeping different types together in one homogeneous list becomes harder; the caller must process separate containers or use a tagged/variant representation.
