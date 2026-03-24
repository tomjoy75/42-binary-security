# Rainfall

Rainfall is a 42 educational binary exploitation and reverse engineering project.
This folder contains a curated portfolio version of my work on the challenge path,
kept close to the original level-by-level structure.

## Scope

- `level0` to `level9`: main progression
- `bonus0` to `bonus3`: bonus challenges
- each challenge folder includes a `resources/` directory with analysis artifacts

## Folder organization

- `resources/walkthrough.md`: exploitation notes and command traces
- `resources/source.c` or `resources/source.cpp`: recovered or provided source context
- `resources/exploit.py`: exploit script when a scripted exploit is useful
- `tools/`: reusable helper scripts shared across multiple levels
- `run.sh`: optional local helper to boot a Rainfall VM environment with QEMU

## Techniques explored

Based on the current walkthroughs and artifacts in this folder, the project covers:

- binary reconnaissance and disassembly-driven analysis (GDB / decompiler workflow)
- stack-based overflow analysis and EIP control
- shellcode injection patterns (including environment-variable placement)
- payload construction and offset discovery helpers
- heap corruption concepts in C++ challenge code (including vtable pointer abuse)

## Public portfolio note

Challenge secrets and progression artifacts (`flag` values, passwords) are removed
or redacted in this public repository version.
