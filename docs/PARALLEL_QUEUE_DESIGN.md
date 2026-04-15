# OpenCOMAL Parallel Program Communication Design

## Purpose
Enable multiple Comal programs (running in separate IDE tabs) to communicate via named queues, providing an intuitive and safe model for teaching and demonstrating parallelism and inter-program communication.

## Phase 1 Decision (Approved Scope)

This document now defines **Phase 1 only**.

- Parallelism model: **separate programs in separate IDE tabs** (separate interpreter instances).
- Communication model: **named queues using QUEUE-first syntax** (`OPEN QUEUE`, `PRINT QUEUE`, `INPUT QUEUE`, `CLOSE QUEUE`).
- Blocking behavior: `INPUT QUEUE <chan>: var` on a queue opened for `READ` is a **blocking wait point** when the queue is empty.

The following are **explicitly out of Phase 1** and must not be implemented without a new teaching-value review:

- Non-blocking queue reads and timeout variants.
- In-program threading via `SPAWN` (for `PROC`) and related task lifecycle APIs.
- Any broader concurrency/runtime changes not required for tab-to-tab queue communication.

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

**Queue Syntax (Preferred):**

```
OPEN QUEUE 2, "Q$", WRITE
PRINT QUEUE 2: "Hello"
CLOSE QUEUE 2

OPEN QUEUE 3, "Q$", READ
INPUT QUEUE 3: A$
CLOSE QUEUE 3
```

- `OPEN QUEUE <chan>, "<name>", WRITE` — Open named queue for writing (enqueue).
- `OPEN QUEUE <chan>, "<name>", READ` — Open named queue for reading (dequeue).
- `PRINT QUEUE <chan>: expr` — Enqueue one message to queue.
- `INPUT QUEUE <chan>: var$` — Dequeue one message from queue (blocking by default, matches existing Comal INPUT behaviour).
- `CLOSE QUEUE <chan>` — Close queue channel.

Compatibility aliases are also accepted:

- `PRINT FILE <chan>: ...`
- `INPUT FILE <chan>: ...`
- `CLOSE FILE <chan>`

Use `QUEUE` in teaching materials to keep the mental model explicit.

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
PRINT QUEUE 2: "Hello from Tab 1!"
CLOSE QUEUE 2
```

**Tab 2 (Consumer):**
```
OPEN QUEUE 3, "Q$", READ
INPUT QUEUE 3: A$
PRINT "Received: ", A$
CLOSE QUEUE 3
```

---

## Implementation Notes

- **Backend:**
  - Implement queue registry as a singleton or shared object in the IDE backend.
  - Use mutex/lock for thread/process safety.
  - Support blocking queue dequeue for `INPUT QUEUE` on queue channels.
- **Interpreter:**
  - Parse `OPEN QUEUE` and queue channel I/O (`PRINT/INPUT/CLOSE QUEUE`).
  - Accept `FILE` spellings as compatibility aliases for queue channels.
  - Route queue operations to the backend registry.
- **IDE:**
  - Allow each tab to launch a separate interpreter instance.
  - Provide UI feedback for queue activity (optional).

---

## Phase 1 Acceptance Criteria

1. Two programs running in different tabs can exchange text messages through the same named queue.
2. `INPUT QUEUE` on an empty read queue blocks only that program instance until data arrives.
3. Queue operations do not expose shared mutable memory between programs.
4. Queue lifecycle (`OPEN QUEUE`/`CLOSE QUEUE`) follows predictable behavior and errors are user-friendly.
5. Documentation and examples teach queue communication without introducing thread terminology.

---


## Extensions & Future Work

These items are intentionally deferred until after a dedicated teaching-value review:

- Support for more data types (numeric queues, etc.).
- Non-blocking `INPUT` queue behavior and timeout variants.
- Broadcast/multicast queues.
- Inter-IDE or networked queue support.
- `SPAWN`/`PROC` threading model and task management semantics.
- **SLEEP function:** Allow a program to pause execution for a specified duration (useful for demonstrating waiting, pacing, or timeouts in queue operations).
- **Sound command:** Add a command to make a sound (e.g., BEEP or SOUND), useful for signaling events or user feedback in parallel programs.

---

## Summary
This design enables intuitive, safe, and visible parallelism in OpenCOMAL by allowing separate programs (tabs) to communicate via named queues. It is ideal for teaching and demonstration, and can be extended for more advanced concurrency features.
