Core Rule Sets
1. Ownership Rules (MVP)

Disallowed:

Raw owning pointers (T*)

new / delete

malloc / free

Allowed:

std::unique_ptr<T>

std::shared_ptr<T> (may be restricted)

not_null<T*>

span<T>

Function signatures must clearly express ownership transfer or borrowing.

2. Lifetime Rules (MVP)

Disallowed:

Returning references or pointers to local variables

Storing raw pointers in containers

Untracked reference members

Allowed:

Value semantics

Explicit ownership containers

Read-only borrows with clear scope

3. Concurrency Rules (MVP)

Disallowed:

Unsynchronized shared mutable state

Capturing non-const references in thread lambdas

Sharing raw pointers across threads

Allowed shared mechanisms:

std::atomic<T>

std::mutex with RAII locking

Message passing / channels

Concurrency correctness is enforced by allowed patterns, not inference.

Architecture Overview
.tcc file
   ↓
Tough C Profiler (AST-based)
   ↓
Pass / Fail
   ↓
Standard compiler (clang / gcc / msvc)

Implementation Strategy
Tooling

clang libTooling

AST + limited CFG analysis

Pattern-based rejection

Deterministic diagnostics

Output

Clear error messages

Rule identifier

Suggested escape path (e.g., move file out of TCC)

Milestones
Phase 1 — Rule Definition

Finalize MVP rule list

Write failing examples

Phase 2 — Profiler Core

File detection

AST parsing

Rule engine skeleton

Phase 3 — Ownership & Lifetime

Implement core checks

Validate on real code samples

Phase 4 — Concurrency

Implement restricted concurrency patterns

Reject unsafe thread usage

Phase 5 — Integration

CLI tool

CI-friendly exit codes

Documentation & examples

Definition of MVP Success

The MVP is successful if:

Common AI-generated C/C++ bugs are rejected

Violations fail the build deterministically

Engineers can opt in and out safely

No changes to existing compilers are required

Final Principle

Tough C is not about writing better C++.
It is about deciding which C++ is allowed to exist.