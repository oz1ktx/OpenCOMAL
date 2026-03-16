# OpenCOMAL Parallel Program Communication Design

## Purpose
Enable multiple Comal programs (running in separate IDE tabs) to communicate via named queues, providing an intuitive and safe model for teaching and demonstrating parallelism and inter-program communication.

---

## Motivation
- **Educational clarity:** Running separate programs in different tabs is more intuitive for learners than simulating threads with procedures.
- **Safe concurrency:** Named queues provide message-passing without shared memory bugs.
- **Extensibility:** Lays groundwork for more advanced parallel and distributed Comal features.

---

## High-Level Architecture

### 1. Interpreter Instances
- Each code tab runs its own Comal interpreter (process or thread).
- Each interpreter is isolated except for access to the shared queue registry.

### 2. Queue Registry
- A global registry (in the IDE backend) manages all named queues.
- Each queue is a FIFO buffer, identified by a name (e.g., Q$).
- Registry ensures thread-safe access (mutex/lock or message-passing).

### 3. Communication Primitives

**Queue File Syntax (Preferred):**

```
OPEN QUEUE 2, "Q$", WRITE
PRINT #2, "Hello"
CLOSE 2

OPEN QUEUE 3, "Q$", READ
INPUT #3, A$
CLOSE 3
```

- `OPEN QUEUE <chan>, "<name>", WRITE` — Open named queue for writing (enqueue).
- `OPEN QUEUE <chan>, "<name>", READ` — Open named queue for reading (dequeue).
- `PRINT #<chan>, expr` — Enqueue value to queue.
- `INPUT #<chan>, var$` — Dequeue value from queue (blocking by default, matches existing Comal INPUT behaviour).

This syntax is clear, extensible, and consistent with Comal’s file I/O model, while making queues a first-class resource.

### 4. UI/IDE Integration
- Each tab can run/stop its own program independently.
- Optional: UI indicator for queue status (e.g., message count).
- Error handling for queue operations (e.g., non-existent queue, type mismatch).

---


## Example Usage

**Tab 1 (Producer):**
```
OPEN QUEUE 2, "Q$", WRITE
PRINT #2, "Hello from Tab 1!"
CLOSE 2
```

**Tab 2 (Consumer):**
```
OPEN QUEUE 3, "Q$", READ
INPUT #3, A$
PRINT "Received: ", A$
CLOSE 3
```

---

## Implementation Notes

- **Backend:**
  - Implement queue registry as a singleton or shared object in the IDE backend.
  - Use mutex/lock for thread/process safety.
  - Support blocking and non-blocking INPUT QUEUE.
- **Interpreter:**
  - Add new statement types for PRINT QUEUE and INPUT QUEUE.
  - Route queue operations to the backend registry.
- **IDE:**
  - Allow each tab to launch a separate interpreter instance.
  - Provide UI feedback for queue activity (optional).

---


## Extensions & Future Work

- Support for more data types (numeric queues, etc.).
- Non-blocking INPUT QUEUE with timeout.
- Broadcast/multicast queues.
- Inter-IDE or networked queue support.
- **SLEEP function:** Allow a program to pause execution for a specified duration (useful for demonstrating waiting, pacing, or timeouts in queue operations).
- **Sound command:** Add a command to make a sound (e.g., BEEP or SOUND), useful for signaling events or user feedback in parallel programs.

---

## Summary
This design enables intuitive, safe, and visible parallelism in OpenCOMAL by allowing separate programs (tabs) to communicate via named queues. It is ideal for teaching and demonstration, and can be extended for more advanced concurrency features.
