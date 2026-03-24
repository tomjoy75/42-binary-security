# 42-binary-security

## 1. Intro

This repository groups several **42 school** curriculum projects in **binary analysis**, **reverse engineering**, and **low-level Linux security**. The material is **educational and lab-oriented**: structured writeups, recovered context, and small helpers that show how each challenge was approached in a controlled environment—not a claim of professional offensive-security experience.

![OverRide challenge environment](assets/images/override-environment.png)

*Example challenge environment and binary protection context from the OverRide track.*

## 2. What this repository covers

Across the three projects, the common threads are:

- **Linux privilege escalation and trust boundaries** (permissions, SUID, cron, services)
- **Binary analysis and reverse engineering** (static reading, disassembly/decompiler use, reasoning about control flow)
- **Memory-corruption exploitation** on the stack and heap, including **format-string** abuse where it appears in the levels
- **Shellcode and payload shaping** under layout and syscall constraints (including environment placement and NOP sleds where relevant)
- **Debugger-assisted analysis** (`gdb` and related workflows)
- **Low-level security reasoning**: tracing how a program checks input, where assumptions break, and how mitigations or quirks change the exploit path

## 3. Projects

### `snowcrash`

Progressive **Linux privilege-escalation** challenges from `level00` through `level14`, each with a `solution.md` and optional `artifacts/` when something clarifies the path.

**Demonstrates:** recon on binaries and scripts, common local misconfiguration and injection patterns, and **gdb**-based bypasses in a structured, level-by-level writeup style.

### `rainfall`

**Binary exploitation and reverse engineering** on a level path (`level0`–`level9`, plus `bonus0`–`bonus3`), with `resources/` walkthroughs, source context, exploit scripts where useful, and shared `tools/`.

**Demonstrates:** stack and heap overflows, **format strings** (including GOT-oriented writes), shellcode delivery, heap and C++ vtable abuse, and related integer/logic pitfalls—documented with traces and artifacts.

### `override`

**Binary exploitation on Linux** (x86 and x86-64 in later levels), organized per level (`level00`–`level09`) with `solution.md` and optional `artifacts/` (similar spirit to `snowcrash/`).

**Demonstrates:** ret2libc-style chains, **format-string** leaks and writes, shellcode under **ptrace** constraints, integer overflow tricks, and application-level abuse paths—grounded in the existing writeups.

## 4. Repository structure

```
42-binary-security/
├── snowcrash/    # privilege escalation track (levels + solution.md / artifacts)
├── rainfall/     # binary exploitation track (levels + resources/, tools/)
└── override/     # binary exploitation track (levels + solution.md / artifacts)
```

## 5. Portfolio note

This is **educational, lab, and CTF-style** work from the 42 curriculum. **Challenge secrets and progression artifacts** (flags, passwords, and similar tokens) are **removed or redacted** in this public version so the repo stays a readable portfolio sample without spoiling or leaking challenge material.
