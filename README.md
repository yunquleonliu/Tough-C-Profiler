# Tough C (TCC)

**Tough C** is a pre-compilation profiler that enforces memory and concurrency
safety rules for C/C++ *before* code is allowed to exist.

Tough C does not replace C or C++.  
It **completes the C++ federation promise**.

> *C Federation always covers your butt.*

---

## What Is Tough C?

Tough C is **not**:
- a new programming language
- a new compiler
- a style guide or lint tool

Tough C **is**:
- a **pre-compilation verifier**
- with **hard rejection power**
- enforcing a **Tough C profile**
- while preserving **full C/C++ escape hatches**

If code fails Tough C rules, it **does not get compiled**.

---

## Why Tough C Exists

Programmers choose C/C++ not because they ignore danger,
but because C++ makes a unique promise:

> **You can do anything.**

That promise matters when:
- performance suddenly becomes critical
- hardware-level control is required
- concurrency models must change
- no higher-level abstraction fits

Languages that restrict capability *too early*
trap engineers when their initial judgment turns out wrong.

C++ never traps you.

Tough C extends this promise by adding **reversible safety**.

---

## Core Philosophy

- Safety is **opt-in**
- Power is **never removed**
- Escape hatches always exist

If Tough C becomes too restrictive:
- move the file out of Tough C
- drop to raw C/C++
- use pointer arithmetic, bit tricks, or hardware primitives

No capability is lost.
It is only **postponed until truly needed**.

---

## Designed for the AI Era

In an age where:
- large amounts of code are AI-generated
- humans no longer inspect every line
- correctness matters more than elegance

The real question becomes:

> **Should this code be allowed to exist at all?**

Tough C answers that question.

---

## What Tough C Enforces (MVP Scope)

- Ownership discipline
- Lifetime safety
- Explicit concurrency models

Tough C does **not** try to prove programs correct.
It defines **what is acceptable to write**.

---

## Project Status

🚧 **Early-stage / MVP design**

Current focus:
- rule definition
- profiler architecture
- minimal viable enforcement set

---

## License

TBD (likely permissive, e.g. Apache-2.0 or MIT)

---

## Slogan

> **Tough C does not reduce what C/C++ can do.  
It only delays when you must do it.**
