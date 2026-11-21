# Assignment 5 – CO5: Runtime Polymorphism and Exceptions

**Repository:** `DSA01-RegisterNumber-Assignment5` (replace `RegisterNumber` with your register number).

This repository is organized into all nine assignment tasks: A1–A5 and B1–B4. Every task folder contains `code.cpp`, `output.txt`, and `screenshots/output.png`. Design tasks also contain `design.md` with the required design reasoning, pseudocode, hierarchy diagrams and complexity discussion.

## Student details
- Name: Replace with your name
- Register number: Replace with your register number
- Compiler: g++ 14.2.0 (GNU)
- Standard: C++17

## Compile command
```bash
g++ -std=c++17 -Wall -Wextra -O2 code.cpp -o app
./app
```
Run the commands from the relevant task folder. For sanitizer testing, see Task09_B4_Engineering_Decision/README.md. Task08 contains timing measurements; results vary with hardware, compiler and system load.

## Task index
1. A1 – Design the polymorphic bill hierarchy
2. A2 – Understand runtime binding
3. A3 – Design with abstract classes
4. A4 – Design the exception strategy
5. A5 – Design recovery and rethrowing
6. B1 – Implement and validate polymorphic billing
7. B2 – Engineer error conditions
8. B3 – Compare dispatch and exception costs
9. B4 – Final engineering decision

## Important submission notes
- Replace the student details above before submission.
- Review every output and explanation, and make sure you understand the code.
- The screenshots are images rendered from the actual captured program output in this repository; they are not photographs of a physical terminal.
- The B2 allocation-failure test safely throws `std::bad_alloc` deliberately; it does not request unbounded memory from the machine.
- Add at least one meaningful Git commit per task, as required by the assignment.
