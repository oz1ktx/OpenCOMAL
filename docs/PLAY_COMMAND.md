PLAY command — syntax and behavior

Overview

`PLAY` plays music (MIDI/ABC/MML) through the embedded synth (libfluidsynth) by default. The default behaviour is blocking (the interpreter waits until playback finishes). Use `ASYNC`/`NOWAIT` to run playback in background.

Grammar (informal)

PLAY-stmt := PLAY <format> <source> [options]

- <format> := MIDI | ABC | MML | RAW
- <source> := quoted-string (inline data) | filepath
- options := (VOL <0-100>) | (SF2 "<path>") | LOOP | DUR <ms> | CH <n> | INST <prog> | ASYNC | NOWAIT

Examples

- Blocking play a MIDI file (default):
  PLAY MIDI "songs/theme.mid" VOL 90 SF2 "/usr/share/sounds/GeneralUser.sf2"

- Play ABC inline, block until end:
  PLAY ABC "X:1\nT:Title\nK:C\nCDEF GABc" VOL 80

- Non-blocking (background) play:
  PLAY MIDI "loop.mid" ASYNC

Behavior & implementation notes

- Default: blocking. The interpreter waits for playback to complete unless `ASYNC` or `NOWAIT` is specified.
- Engine API: `PlaySpec` will include fields for `format`, `source`, `volume`, `sf2Path`, `loop`, `durationMs`, and `async` (bool).
- Blocking implementation: the interpreter will wait on a condition variable or future which the sound engine signals at playback end.
- Async implementation: `PLAY` schedules playback and returns immediately. Multiple async plays are allowed; `STOP` will stop active playback (recommendation: `STOP` stops all active playback instances).
- Implemented runtime shortcut: `PLAY "STOP"` stops active playback through the in-process sound service.
- ABC → MIDI: conversion is required. Options:
  - Prefer an embedded ABC→MIDI converter (if available).
  - Fallback: call `abc2midi` externally.
- FluidSynth integration (embedded path): link `libfluidsynth`, load SF2, render into a buffer (`fluid_synth_write_float` or similar) and stream into `QAudioSink` via a `QIODevice` for consistent Qt audio handling.
- SoundFonts: require an SF2 file. If none provided, prefer a bundled default SF2 or surface a runtime error for blocking `PLAY`.
- Threading: perform audio rendering on a dedicated audio thread. Synchronize control operations (load/unload SF2, program changes).
- Packaging: add `libfluidsynth` to CMake dependencies and packaging manifests (LGPL — ensure packaging notes are included).

Error handling

- Blocking `PLAY` reports errors (missing SF2, conversion failure) as runtime errors to the interpreter.
- Async `PLAY` should emit a warning or runtime message via the IO subsystem if playback fails.

Notes for follow-up implementation

- Parser: accept `ASYNC`/`NOWAIT` token in `PLAY` production and populate `PlaySpec.async`.
- Executor: if `PlaySpec.async == false`, wait on engine completion; otherwise return immediately.
- Engine: expose a mechanism to wait for playback completion and to cancel playback on `STOP`.

References

- FluidSynth: https://www.fluidsynth.org/ (link for packaging/build configuration)
- abcmidi / abc2midi (for ABC→MIDI conversion)

---

Progress snapshot (2026-03-30)

- ABC parser: added a lightweight, token-based ABC→ToneEvent parser (libcomal-sound/include/comal_abc.h, src/abc_parser.cpp) and unit test. (done)
- `TONE` implemented in the Qt engine and routes to a Qt-based `ToneIODevice`. (existing)
- FluidSynth backend: added a FluidSynth-based midi player wrapper (src/midi_player.cpp) and CMake detection for FluidSynth; `Engine::play` is wired to call FluidSynth for ABC strings in fallback and Qt builds when FluidSynth is available. (done)
- Packaging: CPack metadata updated to recommend `fluid-soundfont-gm` and depend on `fluidsynth` where appropriate. (done)

Progress snapshot (2026-04-07)

- Sound engine refactored to an in-process service-thread model (command queue + worker loop). (done)
- Added queued `StopAll` command semantics via `Engine::stopActive()`. (done)
- Runtime `PLAY` now supports `PLAY "STOP"` and routes to `stopActive()`. (done)
- Runtime sound usage unified to one shared engine instance (consistent volume/control/shutdown). (done)
- Qt tone playback cleanup race hardened using playback IDs with synchronized ownership. (done)

What worked during testing

- CLI FluidSynth (`fluidsynth`) loads the system SF2 and plays notes when connected to an audible sink.
- The IDE (comal-ide) can emit note events via the in-process FluidSynth when the system sink routing allowed audio to the speakers. The lack of sound earlier was due to sink routing (USB headset vs built-in speakers).

Outstanding follow-ups (next session)

- Add `SF2=` parameter parsing in `execPlay` so callers can select a SoundFont per `PLAY` call. (planned)
- Add verbose FluidSynth logs and an environment override `COMAL_FLUIDSYNTH_DRIVER` to force the audio driver (`pulseaudio`, `alsa`, etc.). (planned)
- Improve scheduling: replace sleep-based note scheduling with a proper event scheduler and add polyphony/mixer. (planned)
- Extend stop control from global stop to per-playback handle stop (queue command by playback id). (planned)
- Optionally include a default SF2 in `packaging/` (requires license confirmation) and wire packaging to install it under `/usr/share/soundfonts/`. (planned)
- Add automated tests (CI-friendly) that exercise the ABC parser and verify `Engine::play` behavior using the fallback ready-future in headless builds. (planned)

If you want to pick up from here next time, recommended first actions:

1. Implement `SF2=` support in `execPlay` and a small runtime test program under `tests/programs/`.
2. Add `COMAL_FLUIDSYNTH_DRIVER` support and verbose logging so in-process playback is diagnosable across audio backends.
3. Implement per-playback stop command support (ID-based), then add one or two small polyphony/mixer unit tests.

