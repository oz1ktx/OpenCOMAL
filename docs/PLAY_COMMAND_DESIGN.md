# PLAY Command Design for OpenCOMAL

## Overview
The PLAY command enables users to play musical notes and melodies from within COMAL programs. The design aims to be accessible for beginners while providing advanced features for users familiar with MIDI and music programming. The implementation leverages the Qt Multimedia framework for audio and MIDI support.

## Goals
- Allow beginners to play simple melodies with minimal syntax.
- Support advanced users with access to MIDI features (instrument, channel, volume, etc.).
- Use Qt Multimedia for cross-platform audio and MIDI playback.
- Maintain compatibility with classic BASIC/MML-style music strings.

## User-Facing Syntax
### Basic Usage
```
PLAY "O4C4D4E4G4"
```
- Plays notes C, D, E, G in octave 4, each as a quarter note.
- Octave, note, and duration follow BASIC/MML conventions.

### Advanced Usage
```
PLAY "T120 I5 O4C4D4E4", INST=5, VOL=100, CHAN=2
```
- "T120" sets tempo to 120 BPM.
- "I5" or INST=5 sets MIDI instrument (e.g., Electric Piano).
- VOL and CHAN set volume and MIDI channel.
- Advanced options can be inline (in the string) or as separate arguments.

## Parsing and Translation
- The PLAY string is parsed into a sequence of note events (pitch, duration, octave, tempo, instrument, etc.).
- Events are translated into MIDI note-on/note-off messages or a MIDI sequence.
- Instrument, channel, and other parameters are set via MIDI control messages.

## Playback Implementation
- Use Qt Multimedia (QMediaPlayer, QAudioOutput, or QMidiOut) to play the generated MIDI sequence.
- For simple tones (TONE command), generate sine waves using QAudioOutput and a custom QIODevice.
- For PLAY, prefer MIDI playback for polyphony, instrument support, and timing accuracy.

## Extensibility
- The parser can be extended to support additional MML/BASIC features (e.g., rests, ties, volume changes, tempo changes mid-string).
- Future: support for loading/saving MIDI files, real-time playback control, and graphical piano roll display.

## Example
```
PLAY "T140 I10 O5C4E4G4C5"
// Plays a C major arpeggio at 140 BPM using instrument 10 (e.g., Glockenspiel)
```

## Summary
This design provides a beginner-friendly PLAY command with a clear path to advanced MIDI features, leveraging Qt Multimedia for robust, cross-platform audio and music support.

---

## Implementation Status (progress update)

- **libcomal-sound**: new subproject added providing a sound `Engine` and `PlaySpec` API. Implemented in `libcomal-sound/` with Qt Multimedia guarded by `USE_QTMULTIMEDIA`.
- **TONE command**: implemented in `libcomal-runtime/src/executor.cpp` and backed by `libcomal-sound/src/sound_engine.cpp`. Accepts `TONE freq,duration` and generates a sine wave (non-blocking playback).
- **PLAY command**: parsing and full MML/MIDI playback not yet implemented. Minimal runtime support added: `PLAY "VOL=nn"` sets persistent engine volume. More PLAY features are planned.
- **Playback details**: uses Qt Multimedia when available; playback is non-blocking and engine state includes an atomic volume. Background playback threads are tracked and joined on shutdown to ensure graceful cleanup.
- **Tests & cleanup**: a basic integration test `tests/programs/tone_play_test.lst` and helper `tests/test_tone_play.sh` were added; debug output removed from the sound engine.
- **Packaging**: packaging deps updated to include Qt Multimedia (DEB/RPM) in `CMakeLists.txt` for generated packages.

## Next Implementation Steps

- Implement full PLAY string parsing (MML → event sequence) and MIDI translation.
- Move `Engine` into per-interpreter state (isolation) — planned optimisation.
- Add richer tests for non-blocking playback, Engine shutdown, and PLAY semantics.

