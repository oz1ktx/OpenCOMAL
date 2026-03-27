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
