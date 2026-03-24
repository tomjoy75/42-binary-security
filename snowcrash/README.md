# Snowcrash

`snowcrash/` is a 42 educational project focused on Linux privilege escalation, binary analysis, and low-level security reasoning.

This folder is organized by challenge level (`level00` to `level14`). Each level includes a `solution.md` writeup documenting the analysis and exploitation path followed in the lab environment.

To keep the repository readable, supporting files are included only when they materially clarify a level (for example, exploit or decoding helpers). These files are stored under that level's `artifacts/` directory.

This is CTF-style educational work intended to demonstrate structured methodology, technical curiosity, and core security fundamentals in a controlled context.

## What this project explores

- Linux user/group permissions, SUID behavior, and privilege boundaries
- Recon techniques on binaries and scripts (`strings`, source reading, basic decompilation)
- Common exploitation paths: command injection, environment/path abuse, symlink tricks, and race conditions
- Practical analysis workflows with command-line tooling, packet inspection (Wireshark), and debugger-assisted bypasses (`gdb`)

## Level highlights

| Level | Main concept explored |
| --- | --- |
| `level00` | User/file enumeration and Caesar-style decoding to recover credentials |
| `level01` | Password hash extraction and cracking with John the Ripper |
| `level02` | Network capture analysis (`.pcap`) and password recovery via TCP stream/hex inspection |
| `level03` | PATH injection against a SUID binary calling `env`/`echo` |
| `level04` | CGI command injection via unsanitized GET parameter in Perl |
| `level05` | Cron-executed script abuse through writable execution directory |
| `level06` | PHP `preg_replace` `/e` code execution injection |
| `level07` | Environment variable (`LOGNAME`) command injection in SUID context |
| `level08` | Access control bypass with symbolic link indirection |
| `level09` | Custom reversible encoding analysis and decoder implementation |
| `level10` | TOCTOU race condition exploitation using `access()` vs file use |
| `level11` | Lua service command injection through `io.popen` input concatenation |
| `level12` | Perl CGI command injection with input transformation/wildcard workaround |
| `level13` | `gdb` register manipulation to bypass UID check and reach protected path |
| `level14` | Advanced debugger-assisted bypass (`ptrace`/`getuid`) on `getflag` flow |
