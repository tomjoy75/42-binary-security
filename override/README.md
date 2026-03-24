# OverRide

`override/` is a 42 educational project focused on binary exploitation and reverse engineering on Linux (x86 and x86-64 in later levels). This folder is organized like `snowcrash/`: one directory per level (`level00` through `level09`), with a single writeup file and optional supporting code.

Each level includes:

- `solution.md` — analysis and exploitation notes from the lab environment
- `artifacts/` — helper or reference code when it clarifies the level (decoders, shellcode, small C utilities, etc.)

Challenge secrets (`flag` files and similar progression tokens) are **not** kept in this public portfolio copy; any secrets that still appear inside historical command transcripts in `solution.md` should be treated as redacted or lab-only.

`run.sh` is kept as the original-style helper for booting the project VM with QEMU when working locally.

## What this project explores

Grounded in the existing `solution.md` writeups, the levels cover:

- Static and dynamic analysis (`gdb`, disassembly, decompiler-oriented reading)
- Logic and credential checks (hardcoded values, algorithm replication)
- Stack buffer overflows, return-address control, and **ret2libc**-style chains
- Unsafe `printf` usage for **information leaks** and **format-string** writes (including GOT targeting and `%hn` short writes)
- **Shellcode** development and use under constraints (e.g. avoiding `execve` when the parent traces syscalls)
- Environment-based shellcode placement and **NOP sled** landing
- **Ptrace**-mediated syscall monitoring as a constraint on exploit design
- XOR / arithmetic password derivation and small helper programs to mirror binary logic
- Out-of-bounds / **integer overflow** tricks to reach saved return addresses through an indexed store
- Application-level abuse (backup path behavior combined with a writable working directory under `/tmp`)
- x86-64 stack corruption with an **off-by-one** loop bound affecting a later copy size, then redirecting execution to a hidden function

## Level highlights

| Level | Main concept explored |
| --- | --- |
| `level00` | Decompiler-driven recovery of hardcoded password check leading to `system("/bin/sh")` |
| `level01` | Stack overflow from oversized read; **ret2libc** with `system`, `exit`, and `/bin/sh` |
| `level02` | Unsafe `printf` on user input → stack **information leak** to recover protected material |
| `level03` | XOR-based password derivation; helper program to search the valid key |
| `level04` | Child process overflow; **ptrace** blocks `execve` → custom **read-file shellcode** in the environment |
| `level05` | Format string → **GOT overwrite** of `exit` with `%hn`; environment shellcode |
| `level06` | Login/serial verification mirrored with a small **decrypt** helper |
| `level07` | “Storage” service with weak index checks; **integer overflow** on index + **ret2libc** |
| `level08` | Backup utility writing under a user-controlled relative tree → read target file via `/tmp` layout |
| `level09` | x86-64 message path; **off-by-one** username copy widens message; overflow to reach **hidden function** |
