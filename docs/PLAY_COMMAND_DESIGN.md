# PLAY and TONE Command Design for OpenCOMAL

## Overview
The PLAY command enables users to play musical notes and melodies from within COMAL programs. The design aims to be accessible for beginners while providing advanced features for users familiar with MIDI and music programming. The implementation leverages the Qt Multimedia framework for audio and MIDI support.
The TONE command enables users to generate a sine wave at any frequency and duration.

## Goals
- Allow beginners to play simple melodies with minimal syntax.
- Support advanced users with access to MIDI features (instrument, channel, volume, etc.).
- Use Qt Multimedia for cross-platform audio and MIDI playback.
- Maintain compatibility with classic BASIC/MML-style music strings by using the ABC format.

## User-Facing Syntax
### Basic Usage
```
PLAY "C D E F"
```
- Plays notes C, D, E, G .
- Octave, note, and duration follow ABC conventions.

### ABC Subset (initial)

- The first implementation will accept a small, well-defined subset of ABC notation to provide a "PLAY \"A B C D\"" experience without pulling in external tools.
- Supported features (initial):
	- Notes A–G, accidentals `^` (sharp), `_` (flat), and `=` (natural).
	- Octave markers via commas/quotes (`,` for lower, `'` for higher) or implicit octave from a starting `L:` value.
	- Note lengths as integers or fractions (e.g. `A`, `A2`, `A/2`).
	- Rests `z`.
	- Default unit length `L:` and tempo `Q:` directives to set duration-to-ms conversion.
- This subset is intentionally small so it can be converted 1:1 into timed note events (pitch + duration) and then into MIDI note-on/note-off messages or fed to an internal mixer.
- Full ABC features (voices, ornaments, complex tuplets, repeats) are out of scope for the initial implementation and can be added later or handled by an optional `abc2midi` bridge.

### Advanced Usage
- ABC commands are transferred to the MIDI backend.
- Advanced options can be inline (in the string) or as separate arguments.

## Parsing and Translation
- The PLAY string is parsed into a sequence of note events (pitch, duration, octave, tempo, instrument, etc.).
- Events are translated into MIDI note-on/note-off messages or a MIDI sequence.
- Instrument, channel, and other parameters are set via MIDI control messages.

Notes on conversion: for the initial subset, conversion is deterministic — resolve `L:` and `Q:` to a base milliseconds-per-beat, convert ABC length tokens to milliseconds, map note+octave+accidental to MIDI note numbers, and emit note-on/note-off at computed times.

## Playback Implementation
- Use Qt Multimedia (QMediaPlayer, QAudioOutput, or QMidiOut) to play the generated MIDI sequence.
- For simple tones (TONE command), generate sine waves using QAudioOutput and a custom QIODevice.
- For PLAY, prefer MIDI playback for polyphony, instrument support, and timing accuracy.

## Extensibility
- Future: support for loading/saving MIDI files, real-time playback control.
- Future: Extend the TONE wave playback with commands WAVEFORM and SAMPLE: Instead of a sine wave, the TONE could use a user-supplied set of samples representing a single period of the sound. This would allow experiments with wave forms.
- Future: Extend with a SAMPLE command that plays back a dataset of PCM format samples, for example from a file or from DATA in the program.
- Future: Extend the TONE command with ASDR (attack, sustain, delay, release) envelope. 

## Summary

- This design provides a beginner-friendly PLAY command with a clear path to advanced MIDI features, leveraging Qt Multimedia for robust, cross-platform audio and music support.
- Adding MIDI support adds an extra dependency to the final package.
---

## Roadmap: PLAY, TONE, WAVEFORM, SAMPLE

This roadmap describes an incremental, testable plan to implement the following responsibilities:
- `PLAY` — musical note playback using an ABC subset → MIDI/event stream
- `TONE` — single-frequency playback, extended to accept named waveforms
- `WAVEFORM` — registration API for one-period waveforms (used by `TONE`)
- `SAMPLE` — play raw PCM from memory or file (WAV) via streaming

Principles
- Keep `PLAY` focused on musical notation; do not conflate it with raw sample playback.
- Reuse the `Engine` audio sink and the `QIODevice`-based model used for `TONE` so all playback paths funnel through the same output pipeline.
- Implement a minimal, well-documented subset first, then expand features (ABC advanced features, WAV variants, higher-quality resampling, mixer improvements).

Phases & Milestones
1. Design & docs (this change)
	- Finalise the ABC subset for `PLAY` and document conversion rules (done in this doc).
	- Document `WAVEFORM` and `SAMPLE` APIs so they are stable before implementation.

2. Waveform registration + `TONE` integration
	- Add `WAVEFORM` command/API: `WAVEFORM name, [v0,v1,...]` where values are floats in [-1.0,1.0]. Store small arrays in `Engine`.
	- Implement `WaveformIODevice` (QIODevice) that loops the registered single-period samples, resampling as needed to produce requested pitch and sample rate. Use phase accumulator and linear interpolation.
	- Extend `TONE` to accept an optional waveform name: `TONE freq,duration[,WAVEFORM=name]`.
	- Tests: unit test for waveform registration; integration test `tone_waveform_test.lst` plays a named waveform.

3. SAMPLE streaming (file & memory)
	- Decide on formats: start with 16-bit PCM WAV (RIFF) because it's simple to parse; later add AIFF/FLAC via libs.
	- Implement a minimal WAV loader (header parsing) and `SampleIODevice` that streams samples from file or in-memory buffer, performing conversion to the engine's output format (16-bit stereo interleaved) as required.
	- Add `SAMPLE` command/API: `SAMPLE name, "file.wav"` or `SAMPLE name = DATA [ <raw PCM numbers> ]` (in-memory). Expose playback as `PLAY SAMPLE=name` or a dedicated `PLAY_SAMPLE name` command if preferred.
	- Tests: small WAV fixtures + integration tests that play short samples.

4. Envelope & safety
	- Add optional per-source ADSR envelope parameters for `TONE` and `SAMPLE` to reduce clicks and support expressive sounds.
	- Default short fade-in/out when a source stops (to avoid abrupt waveform deletion).

5. Mixer / polyphony
	- Implement a software mixer that accepts multiple active sources (Tone, Waveform, Sample) and produces a single interleaved output stream consumed by the persistent `QAudioSink`.
	- Mixer responsibilities: sample rate conversion (simple linear), channel mapping, per-source volume/gain, mixing with clipping protection (soft clip / normalization), and per-source envelope application.
	- API: `Engine::startSource(std::unique_ptr<Source>)` returns a handle; `Engine::stopSource(handle)` requests stop; mixer handles scheduling and resource cleanup.
	- Tests: polyphony test that plays overlapping notes/samples and verifies no clicks and reasonable loudness.

6. MIDI backend / ABC→MIDI bridge (optional)
	- Provide an optional path for full ABC compatibility: call out to system `abc2midi` (documented) or integrate a third-party ABC parser to generate MIDI files or events.
	- Keep the internal ABC → note-event converter small and deterministic for the documented subset; optionally allow `PLAY "@FILE.abc"` to invoke `abc2midi` for full-featured files.

7. Documentation, examples, and UX polish
	- Document `WAVEFORM` and `SAMPLE` usage with examples in `docs/` and add example programs under `tests/programs/`.
	- Add runtime error handling and helpful messages when a named waveform or sample is missing.

API / Command proposals
- `WAVEFORM name, [v0,v1,...]` — registers a named waveform (values -1.0..1.0). Stored in `Engine`.
- `TONE freq, duration [, WAVEFORM=name] [, ADSR=a,s,d,r]` — play a tone at `freq` Hz for `duration` ms using optional waveform and envelope.
- `SAMPLE name, "file.wav"` — register sample from file.
- `SAMPLE name = DATA [n1,n2,...]` — register in-memory 16-bit signed PCM data (interpreted as mono unless channel metadata present).
- `PLAY "ABC string"` — unchanged: musical notation playback (ABC subset). `PLAY` remains for notes only.

Internal design notes
- Use `QIODevice` subclasses for all real-time sources (`ToneIODevice`, `WaveformIODevice`, `SampleIODevice`). Create them and manage on Qt thread; schedule `deleteLater()` after playback ends.
- For initial implementation (before mixer), allow the persistent `QAudioSink` to accept a single `QIODevice` (current model); later refactor to have the mixer present a single `QIODevice` to `QAudioSink` and mix N sources internally.
- Implement simple linear resampling inside each `Source` or centrally in the mixer.
- Use phase accumulators plus small cross-fade on start/stop for click-free transitions.
- Keep all heavy I/O (file reading) asynchronous or streaming; avoid large allocations for long samples.

Testing and validation
- Unit tests for parsers and loaders (WAV header, ABC subset parsing, waveform registration).
- Integration tests that run short programs exercising `TONE`+`WAVEFORM` and `SAMPLE` playback (non-blocking), run under test harness (automated run that verifies process exit without error). Manual listening required to judge sound quality.

Timeline (example minimal schedule)
- Week 1: WAVEFORM register + `WaveformIODevice` + integrate with `TONE`.
- Week 2: SIMPLE SAMPLE loader (WAV) + `SampleIODevice` + tests.
- Week 3: Envelope (ASDR) + basic mixer for 4-8 voice polyphony + integration tests.
- Week 4: Documentation, examples, and polish + optional `abc2midi` bridge.

Risks & mitigations
- Playback clicks and pops: mitigate with phase accumulators and short cross-fades; prefer event-loop cleanup over abrupt sink stops (done earlier).
- Resampling quality vs CPU: start with linear interpolation; profile and replace with higher-quality resampler if needed.
- Licensing: calling `abc2midi` brings GPL dependency; keep it optional and documented.

----------------
Update the roadmap tasks in the repository TODOs (or project board) when ready so development can proceed incrementally.

## Implementation Status (progress update)

- **libcomal-sound**: new subproject added providing a sound `Engine` and `PlaySpec` API. Implemented in `libcomal-sound/` with Qt Multimedia guarded by `USE_QTMULTIMEDIA`.
- **TONE command**: implemented in `libcomal-runtime/src/executor.cpp` and backed by `libcomal-sound/src/sound_engine.cpp`. Accepts `TONE freq,duration` and generates a sine wave (non-blocking playback).
- **PLAY command**: parsing and full ABC/MIDI playback not yet implemented. Minimal runtime support added: `PLAY "VOL=nn"` sets persistent engine volume. More PLAY features are planned.
- **Playback details**: uses Qt Multimedia when available; playback is non-blocking and engine state includes an atomic volume. Background playback threads are tracked and joined on shutdown to ensure graceful cleanup.
- **Tests & cleanup**: a basic integration test `tests/programs/tone_play_test.lst` and helper `tests/test_tone_play.sh` were added; debug output removed from the sound engine.
- **Packaging**: packaging deps updated to include Qt Multimedia (DEB/RPM) in `CMakeLists.txt` for generated packages.

## Next Implementation Steps

- Implement full PLAY string parsing (ABC → event sequence) and MIDI translation.
- Move `Engine` into per-interpreter state (isolation) — planned optimisation.
- Add richer tests for non-blocking playback, Engine shutdown, and PLAY semantics.
- Implement the software mixer for overlapping tones, or
- Add tests for TONE playback.
