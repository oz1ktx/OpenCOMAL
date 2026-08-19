# libcomal-cpm

C++20 library for OpenCOMAL's Z80 assembly and CP/M-compatible execution path.

## Responsibilities

- **`.COM` image loading** — load binaries at `0100h` with CP/M-style warm-boot and BDOS vectors
- **Z80 execution** — run `.COM` programs on the vendored `redcode/Z80` core
- **BDOS shim** — minimal CP/M-compatible console, DMA, and FCB-backed file operations
- **Assembly integration** — assemble `.asm` / `.z80` / `.s` via the `sjasmplus` adapter
- **Source-level debug snapshots** — registers, flags, memory windows, and disassembly rows for paused execution

## Key Files

| File | Purpose |
|------|---------|
| `include/comal_cpm_backend.h` | Public backend, assembler, and debug snapshot interfaces |
| `include/z80_com_loader.h` | `.COM` image loader and memory layout |
| `src/comal_cpm_backend.cpp` | Z80 execution loop, BDOS shim, source mapping, assembler adapter |
| `src/z80_com_loader.cpp` | `.COM` loader implementation |

## Building

```bash
cd build && cmake .. && make comal-cpm -j$(nproc)
```

## See Also

- [`comal-ide`](../comal-ide/README.md) — Qt IDE that consumes this library for assembly workflows
- [`libcomal-runtime`](../libcomal-runtime/README.md) — COMAL runtime, kept separate from CP/M/Z80 handling
