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

Based on the current walkthroughs, the project progression covers:

- debugger-assisted reverse engineering (`gdb`, `objdump`, decompiler output) and control-flow reading
- stack overflow exploitation with direct `EIP` control (`gets`, unsafe concatenation paths)
- offset discovery and payload shaping (cyclic patterns, stack position discovery, `%x` probing)
- shellcode delivery, including environment-variable placement with NOP sled landing
- format string exploitation (`%n`) for arbitrary writes, global variable manipulation, and GOT overwrite
- control-flow hijacking via ret2func-style redirection and function pointer overwrite
- heap-oriented exploitation (adjacent chunk corruption, pointer redirection, allocator-behavior abuse)
- C++ object abuse on heap (vtable pointer overwrite and fake vtable redirection)
- integer/logic weaknesses (integer underflow in size computation, input-validation bypasses)

## Level highlights

| Challenge | Main concept | Key technique / takeaway |
| --- | --- | --- |
| `level0` | Control-flow logic check | Reverse condition and trigger hardcoded `/bin/sh` path via expected numeric input |
| `level1` | Stack overflow (`gets`) | Overwrite return address to jump to existing `run()` shell function (ret2func) |
| `level2` | Stack overflow with stack-address filter | Inject shellcode and return into heap buffer (`strdup`) to bypass stack-address check |
| `level3` | Format string vulnerability | Use `%n` to write `0x40` into global variable and unlock privileged path |
| `level4` | Advanced format string write | Large controlled print width + positional `%n` to set target global value |
| `level5` | Format string to GOT overwrite | Rewrite `exit@GOT` to privileged function address for control-flow hijack |
| `level6` | Heap overflow | Overflow first chunk into next object and overwrite function pointer |
| `level7` | Heap overflow + GOT targeting | Corrupt pointer chain, then indirect write to `puts@GOT` with address of hidden function |
| `level8` | Heap state manipulation / logic abuse | Command sequence (`auth`/`service`/`login`) makes checked heap field non-zero to spawn shell |
| `level9` | C++ heap object corruption | Overflow annotation buffer, overwrite vtable pointer, execute controlled function entry |
| `bonus0` | Stack overflow under input-size constraints | Split-input overwrite + environment shellcode + NOP sled targeting |
| `bonus1` | Integer underflow | Negative integer bypass influences `memcpy` size and enables controlled overwrite to pass check |
| `bonus2` | Stack overflow with locale-dependent layout | `LANG`-dependent greeting length changes offset, enabling full `EIP` overwrite + env shellcode |
| `bonus3` | Input-validation logic bypass | Empty-string argument drives `atoi`/null-write behavior to satisfy `strcmp` condition |

## Public portfolio note

Challenge secrets and progression artifacts (`flag` values, passwords) are removed
or redacted in this public repository version.
