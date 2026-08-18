# libcomal-sound

C++20 sound library implementing the COMAL `TONE` and `PLAY` statements via FluidSynth.

## Responsibilities

- Execute `TONE freq, duration` — plays a pure tone at a given frequency and duration
- Execute `PLAY mml$` — plays a sequence of notes described in Music Macro Language (MML)
- Provide an abstract `ComalAbc` interface so the runtime can call sound without depending on FluidSynth directly

## Status

| Feature | Status |
|---------|--------|
| `TONE` | ✅ Working |
| `PLAY` (basic notes) | ✅ Working |
| `PLAY` (full MML) | ⏳ Partial — octave, length, tempo supported; advanced articulation TODO |

## Architecture

- `comal_sound.h` — public API (`tone()`, `play()`)
- `comal_abc.h` — abstract backend interface for dependency injection
- FluidSynth is used as the MIDI synthesis engine; the library links against `libfluidsynth`

## Building

Requires `libfluidsynth-dev` (Debian/Ubuntu) or `fluidsynth-devel` (Fedora).

```bash
cd build && cmake .. && make comal-sound -j$(nproc)
```

## See Also

- [`libcomal-runtime`](../libcomal-runtime/README.md) — calls this library for `TONE`/`PLAY` statements
- [`docs/PROJECT_STATUS.md`](../docs/PROJECT_STATUS.md) — overall project status
