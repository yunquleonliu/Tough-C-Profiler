# Tough C — MVP Planning Document

## Goal of the MVP

Deliver a **working Tough C profiler** that:

- runs before standard compilation
- enforces hard safety rules
- rejects non-compliant code
- integrates with existing C/C++ toolchains
- demonstrates clear value for memory and concurrency safety

The MVP does **not** aim for completeness or formal proofs.

---

## Scope Definition

### In Scope (MVP)

1. Ownership rules
2. Lifetime safety rules
3. Explicit concurrency constraints
4. File-level Tough C declaration
5. Hard failure on violation

### Out of Scope (MVP)

- Full borrow checker
- Formal verification
- Whole-program correctness proofs
- Automatic code rewriting

---

## File Declaration Mechanism

Supported mechanisms:
- File extension: `.tcc`
- Or header annotation:
  ```cpp
  // @tcc
  // concurrency: required
