PLAY and TONE in OpenCOMAL

This file is the single source of truth for current behavior and near-term design.

## What Is Implemented Now

### Runtime commands

- `TONE`:
  - Syntax today: `TONE <freq>, <duration_ms> [, ASYNC|NOWAIT]`
  - First two numeric args are required.
  - `ASYNC`/`NOWAIT` can be passed as identifier or string token.
  - Blocking is default (runtime waits for completion future).

- `PLAY`:
  - Syntax today: `PLAY <string> [, options...]`
  - First argument must be a string.
  - Special command: `PLAY "STOP"` stops active playback.
  - Options currently recognized:
    - `ASYNC` or `NOWAIT`
    - `VOL=<n>` (string option) or `VOL, <n>` (identifier + numeric)
    - `DUR=<ms>` (string option) or `DUR, <ms>` (identifier + numeric)
  - Additional numeric args are forwarded in `PlaySpec.params`.
  - Blocking is default unless async option is present.

### Engine behavior

- Engine uses an internal service thread and command queue.
- `Engine::play(...)` returns a shared completion future.
- `Engine::stopActive()` enqueues a stop-all command and waits for completion.
- Runtime and IDE shut down engines via `shutdownAllEngines()` on exit.

### Backend behavior by build configuration

- Qt Multimedia enabled:
  - `TONE` uses generated audio (`ToneIODevice`) through `QAudioSink`.
  - Non-`tone` `PLAY` inputs are:
    - routed to FluidSynth when `USE_FLUIDSYNTH` is enabled
    - otherwise completed as unsupported/no-op

- Qt Multimedia disabled:
  - Fallback engine returns a ready future (no audio) unless FluidSynth path is enabled.

### PLAY content currently supported

- `PLAY` is currently treated as a string payload.
- With FluidSynth enabled, payload is parsed through the lightweight ABC parser (`parseABCToTones`) and rendered as note events.
- This is not yet a full ABC standard implementation and not a full file-format matrix (`MIDI|ABC|MML|RAW`).

### Current ABC subset (implemented)

- Notes: `A B C D E F G`
- Accidentals prefix: `^` (sharp), `_` (flat), `=` (natural marker)
- Rests: `z` or `Z`
- Directives:
  - `L=<beats>` or `L:<beats>` default note length
  - `Q=<bpm>` or `Q:<bpm>` tempo in beats per minute (plain integer, e.g. `Q:120`)
  - `Q:<unit>=<bpm>` beat-unit form, e.g. `Q:1/4=123` means 123 quarter-note beats per minute
    — beat unit is parsed and applied correctly; omit it and `beatUnit` defaults to 1
- Octave handling:
  - lowercase note letter raises by one octave (`c` vs `C`)
  - `,` lowers one octave per symbol (`C,`)
  - `'` raises one octave per symbol (`c'`)
  - explicit octave digits override shifts (`C5`, `C3`)
- Length suffixes:
  - `A2` explicit beat length
  - `A/2` fraction of default length
  - `A/` shorthand for half default length
- Rest lengths:
  - `z2`, `z/2`, `z/` use the same length rules as notes
- Common bar separators are ignored:
  - `|`, `||`, `|]`, `[|`
- Comments (ignored to end of line):
  - `% This is a comment`
- Note ties (ignored):
  - `-` joins notes, not needed for simple playback
- Input style tolerance:
  - Supports compact body text without spaces between events (for example `E/2z^E/2`).
  - Accepts multiline pasted snippets with common ABC headers (`X:`, `T:`, `M:`, `L:`, `Q:`, `K:`); unknown headers are ignored.
  - Tuplet markers like `(3` are tolerated (marker is skipped, notes still parsed).

Example:

```comal
PLAY "L=1 Q=120 C D E F G A B z C2 C/2 c C, c' C5"
```

Full COMAL DATA/READ example (multiline ABC pasted as DATA rows):

- `tests/programs-nonum/abc_data_play.lst` — simple 3-line scale demo, confirmed working
- `tests/programs-nonum/pinkpanther_play.lst` — Pink Panther theme (9 DATA lines); plays at
  correct tempo after beat-unit fix. Minor timing issues remain in some dense passages
  (e.g. multi-tuplet and tied-note sequences). Not included in automated test suite
  (runtime ~3 min); run manually.

### DATA/READ + PLAY pattern

The sound engine keeps `ABCState` (tempo `Q:`, note length `L:`, beat unit) across
successive `PLAY` calls. Send the header once; body lines inherit the state:

```comal
PLAY "L:1/8 Q:1/4=123"   // set state once
FOR i := 1 TO n
  READ line$
  PLAY line$              // uses inherited L:1/8 Q:1/4=123
NEXT i
```

`PLAY "STOP"` resets the state to defaults (L=1 beat, Q=120 BPM) in addition to
stopping active playback. Directives embedded in a body line update the state for
that call and all subsequent ones (standard ABC behaviour).

User-facing hover/help text for `PLAY` and other keywords is maintained in:

- `docs/comal-keyword-docs.tsv`

## Minimal Mental Model

1. Runtime builds a `PlaySpec` from command args.
2. Runtime submits to shared `Engine`.
3. Engine queues work on service thread.
4. Runtime waits on future unless async was requested.
5. `PLAY "STOP"` stops active playback.

## Planned Features (Not Implemented Yet)

### Waveform support

- Goal: let `TONE` use named custom waveforms, not only sine.
- Proposed direction:
  - `WAVEFORM name, [v0, v1, ...]` to register one-cycle data
  - `TONE f, d, WAVEFORM=name`
- Implementation sketch:
  - add waveform registry to sound engine
  - generate samples via phase accumulator + interpolation

### Sample playback

- Goal: play PCM sample data and short files.
- Proposed direction:
  - `SAMPLE name, "file.wav"` (start with PCM WAV)
  - later allow in-memory sample registration
- Implementation sketch:
  - sample loader + streaming source
  - optional mixer for overlap/polyphony

### PLAY evolution

- **Beat unit (`Q:X/Y=BPM`) now parsed correctly** (2026-04-13). Prior to this fix all
  `Q:1/4=BPM`-style ABC files played 4× too fast because the beat-unit fraction was dropped.
- Remaining known gaps in complex ABC:
  - Tuplet timing (triplets `(3`, quintuplets `(5`) — markers currently skipped, notes play
    at unmodified durations rather than compressed time values.
  - Tied notes (`-`) across bar lines are silently dropped; this is correct for simple cases
    but note durations for tied chords are not extended.
  - Chord notation `[CEG]` is not yet supported; notes inside `[` ... `]` are parsed
    individually and played sequentially rather than together.
- Improve ABC subset coverage and diagnostics.
- Consider richer scheduling/polyphony instead of sleep-based sequencing.
- Optional SF2/per-playback controls and backend diagnostics.

## Notes

- This document intentionally describes actual behavior first, then roadmap.
- Keep design details here; avoid duplicating in other PLAY docs.

