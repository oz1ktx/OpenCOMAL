## Conversation Summary

*   **Goal.** Build a kid‑friendly programming environment with **simple drawing commands** that produce graphics on a canvas.
*   **APIs considered.**
    *   **HP‑GL** → too low‑level for kids.
    *   **Logo** → intuitive but **turtle‑centric** and limited for modern use.
    *   **Processing** → a great **model**: minimal, shape‑centric, stateful styles, easy animation.
*   **Architecture ideas.**
    *   A **graphics server** receiving commands (via IPC) from a separate scripting environment: Qt or Java/Processing possible.
    *   Qt is attractive (your familiarity, robust 2D/scene graph, IPC). Java/Processing would give perfect Processing parity but adds JVM.
*   **Prototype plan.**
    *   Start **without IPC**: a **Qt app** with a **multi‑line** text box for commands and a canvas to render.
    *   **Command format:** `name` followed by **numbers** only—simple line‑based parsing.
*   **QML vs Widgets.**
    *   **QWidget/QPainter** is great for the first prototype.
    *   **QML/Qt Quick** is better long‑term: GPU acceleration, declarative scene graph, **easy animations**, modern UI.
*   **Grouping model.**
    *   Adopt **Option 3 (dot notation)**: `GroupName.command args...`
    *   If **no group prefix**, command goes to **root** (the implicit canvas layer). **Root is not animated.**
    *   Supports **nesting** naturally: `Sprite.Part.Subpart.command …`.
*   **Reusability.**
    *   In a scene graph you can’t attach one object to two parents, but you **can** **copy/instantiate** definitions.
    *   Add a simple **template/define + spawn/use** mechanic later to create multiple **independent instances** (sprites).

***

# Design Document — Kid‑Friendly Graphics Language & Renderer (Qt/QML)

> **Version:** 0.1 (Prototype)  
> **Author:** Peter N. Andreasen (with design input from M365 Copilot)  
> **Status:** Draft

***

## 1) Objectives

*   **Instant visual payoff**: draw shapes with **minimal syntax**.
*   **Approachable language**: **line‑based**, `name + numbers`.
*   **Modern rendering & animation**: smooth, **GPU‑accelerated** (QML).
*   **Intuitive composition**: **groups** and **nested groups** (sprites).
*   **Extensible**: templates (reusable sprites), events, assets, IPC later.

**Non‑goals (v0.1):**

*   Full Processing compatibility.
*   Complex text or image effects.
*   Networking/IPC (post‑prototype).
*   Advanced physics or game engine features.

***

## 2) User‑Facing Command Language

### 2.1 Mental Model

*   You draw into a **scene** with an implicit **root** layer.
*   You can optionally **name groups** and draw inside them.
*   **Transforms/animations** applied to a group affect all of its children.

### 2.2 Syntax Rules (v0.1)

*   Each **line** is one command.
*   Tokens are **whitespace-separated**.
*   First token is either:
    *   `commandName` (acts on **root**), or
    *   `Group1[.Group2[.Group3…]].commandName`
*   All remaining tokens are **numbers** (float/double).
*   Lines starting with `#` are **comments**; blank lines are ignored.

### 2.3 Minimal Command Set (initial)

**Shapes**

*   `line x1 y1 x2 y2`
*   `rect x y w h`
*   `circle cx cy r`
*   (Optional later) `ellipse x y w h`, `poly x0 y0 x1 y1 ...`

**Styles (stateful)**

*   `stroke r g b [a]` (0–255)
*   `fill r g b [a]`
*   `noFill`
*   `lineWidth w`

**Canvas**

*   `background r g b [a]`  → sets background color for the frame
*   `clear` → clears drawing area to current background

**Transforms (group‑level)**

*   `translate dx dy` *(applies to group)*
*   `rotate deg` *(applies to group)*
*   `scale s` or `scale sx sy`

> For v0.1, you can implement transforms either immediately (as “apply now” to the group’s `x/y/rotation/scale` properties) or later with a proper transform stack.

**Animation (group‑level)**

*   `animate property to value over durationMs [easing] [loop|yoyo]`  
    Examples:
    *   `Kevin.animate x to 400 over 2000`
    *   `Kevin.animate rotation to 360 over 3000 loop`
    *   `Kevin.animate scale to 2 over 1000 yoyo`

*(Animation syntax can be iterated later; start with `x`, `y`, `rotation`, `scale`, `opacity`.)*

**Grouping**

*   Omit group prefix → command targets **root**.
*   Include group prefix → command targets **that group**, created on first use.
*   Nested groups via dot notation: `Sprite.Head.circle …`

**Reusability (planned v0.2)**

*   `define Name { … }` → defines a template.
*   `<Group>.spawn Name` or `<Group>.use Name` → instantiates a copy inside `<Group>`.

### 2.4 Grammar (EBNF, prototype)

```ebnf
line        = [qualifiedCommand] { number } ;
qualifiedCommand
            = ( identifier "." )* identifier ;   (* zero or more groups, then command *)
identifier  = letter { letter | digit | "_" } ;
number      = ["-"] digit { digit } [ "." digit { digit } ] ;

(* Semantics:
   If there is no dot, the identifier is a command on root.
   If there is at least one dot, all but the final identifier form the group path,
   final identifier is the command name. *)
```

***

## 3) Examples

### 3.1 Root‑level drawing

    background 240 240 255
    stroke 0 0 0
    fill 0 128 255 128
    lineWidth 3

    rect 40 40 200 120
    circle 200 200 80
    line 20 20 300 80

### 3.2 Grouped drawing & animation

    Kevin.circle 100 100 40
    Kevin.line 0 0 200 200

    # Move Kevin to the right over 2 seconds
    Kevin.animate x to 600 over 2000

    # Spin Kevin forever
    Kevin.animate rotation to 360 over 5000 loop

### 3.3 Nested groups (sprite parts)

    Spaceship.Body.rect 10 10 200 60
    Spaceship.Engine.rect 180 30 30 20
    Spaceship.Flame.triangle 195 50 205 90 215 50

    # Animate the entire spaceship
    Spaceship.animate x to 800 over 3000

    # Make engine rotate quickly (silly but illustrative)
    Spaceship.Engine.animate rotation to 360 over 1000 loop

***

## 4) System Architecture

### 4.1 Phases

*   **Phase A (now)**: Qt app, no IPC
    *   **Editor**: `QTextEdit` for multi‑line commands
    *   **Parser**: C++ line parser → OP list + model updates
    *   **Renderer**: initially `QWidget/QPainter` for simplicity or jump to **QML**
*   **Phase B (later)**: Move renderer to **QML/Qt Quick** (GPU, animations)
*   **Phase C (later)**: Add **IPC** (local socket/FIFO) so the renderer becomes a server

### 4.2 Core Components

*   **Command Editor**: `QTextEdit`, Run button, error panel
*   **Parser/Validator**
    *   Tokenizes per line
    *   Extracts `groupPath` (array of identifiers) and `commandName`
    *   Validates **arity** (number of numeric args) against a **command registry**
    *   Accumulates errors with line numbers
*   **Command Registry**
    *   Maps `commandName` → metadata: `{minArgs, maxArgs, fn(kind)}`
    *   Style commands flagged as **stateful**
    *   Animation commands flagged as **group‑level**
*   **Scene Model**
    *   **Root** node (non‑animatable canvas)
    *   Dictionary of **Group** nodes created on first use, supporting nesting
    *   Each group has properties: `x, y, rotation, scale, opacity, z`
*   **Renderer**
    *   **QML scene graph**: create one `Item` per group; children for shapes
    *   Mapping:
        *   `circle` → `Rectangle { radius: w/2 }` or a custom `Circle` component
        *   `line` → `Canvas` drawing or a small `PathView` / `Shape` (QtQuick.Shapes)
        *   `rect` → `Rectangle`
    *   Styles: `fill` → `color`, `stroke` → `border.color`, `lineWidth` → `border.width`
*   **Animation Engine**
    *   Create `NumberAnimation`/`PropertyAnimation` in QML targeting group items
    *   Support `loop`, `yoyo`, `easing`
*   **Error Reporting**
    *   Inline status label and error list
    *   Highlight lines (optional later)

### 4.3 Data Structures (C++ side, concept)

```cpp
struct CmdSpec {
  int minArgs, maxArgs;
  enum Kind { Shape, Style, Canvas, Transform, Animation } kind;
};

struct ParsedLine {
  QVector<QString> groupPath;  // ["Spaceship","Engine"]
  QString command;             // "circle"
  QVector<double> args;        // numeric args
  int lineNo;
};
```

***

## 5) QML Mapping (Renderer)

*   **Root** → `Item { id: root }` (no transforms applied)
*   **Groups** → nested `Item`s:
        Item { id: Spaceship
          Item { id: Engine
            Rectangle { ... }    // shapes
          }
        }
*   **Shapes**
    *   `rect` → `Rectangle`
    *   `circle` → `Rectangle { width:h; radius: width/2 }` or `Shape` from `QtQuick.Shapes`
    *   `line` → `Shape { ShapePath { moveTo; lineTo; strokeWidth; strokeColor } }` (preferred)
*   **Styles** (stateful per target)
    *   Maintain style state during parsing or explicitly attach styles to created items.
*   **Animations**
    *   Generated as `PropertyAnimation` blocks, or use `Behavior on x { ... }` to auto‑animate.

***

## 6) IPC (Future)

*   **Protocol**: reuse the **same line‑based text format** (or JSON if needed).
*   **Transport**: `QLocalSocket` (same machine), fallback to `QTcpServer`.
*   **Messages**
    *   `reset`, `run`, `append`, `preview`, `export`, `ping`.
*   **Replay/Recording**: keep command log to support **undo/replay**.

***

## 7) Validation & Errors

*   Unknown command → `Line N: unknown command 'foo'`
*   Wrong arity → `Line N: 'circle' expects 3 args, got 2`
*   Non‑numeric arg → `Line N: expected numbers after 'rect'`
*   Color bounds → clamp 0–255
*   Group name rules → `[A-Za-z][A-Za-z0-9_]*` (enforced on parse)

***

## 8) Performance Considerations

*   Prefer **QML + QtQuick.Shapes** for vector shapes—hardware accelerated.
*   Reuse items when re‑running to avoid churn (optional optimization).
*   For many lines/shapes, use `Shape`/`Path` batching instead of `Canvas`.
*   Avoid animating thousands of items simultaneously; animate parent groups.

***

## 9) Reusability / Templates (v0.2)

**Copy semantics** (not shared references):

*   `define Kevin { ... }` — store Kevin’s **shape/commands** as a template.
*   `<Group>.spawn Kevin` — create a **new instance** (independent `Item` subtree).
*   Instances can be animated independently and styled post‑spawn.

Alternative lightweight syntax:

*   `template Kevin.circle 0 0 40`
*   `A.use Kevin`, `B.use Kevin`

***

## 10) Extensibility Roadmap

*   **More shapes**: `ellipse`, `arc`, `poly`, `path`
*   **Transforms**: `push`, `pop`, `translate`, `rotate`, `scale` (stack)
*   **Layers / z‑order**: `z index`
*   **Color names / hex**: `strokeName red`, `fillHex #FF8800CC`
*   **Events**: `onClick`, `onFrame`, `onKey`
*   **Assets**: `image path x y`, `spriteSheet`, sound playback
*   **Export**: `savePNG path`, `saveSVG path` (Qt SVG generator or custom)
*   **Inspector UI**: select and edit items visually (QML tooling)
*   **Education UX**: examples gallery, “Try it” buttons, live preview debounce
*   **Security**: sandbox if/when user code is executed as scripts

***

## 11) Incremental Milestones

1.  **M1 — Local Prototype (Widgets or QML)**
    *   Multi‑line editor, parser, minimal commands (`line`, `rect`, `circle`, `stroke`, `fill`, `noFill`, `lineWidth`, `background`, `clear`)
    *   Root rendering works
2.  **M2 — Groups (dot‑notation)**
    *   Auto‑create groups on first use
    *   Apply transforms at group level
3.  **M3 — Animations**
    *   `animate property to value over duration [loop]`
    *   Basic easing
4.  **M4 — Nested Groups / Sprites**
    *   `A.B.C.command …`
    *   Couple of demo sprites with independent animations
5.  **M5 — Templates (Reusability)**
    *   `define` / `spawn` or `template` / `use`
6.  **M6 — IPC**
    *   Local socket server
    *   Command streaming from external client

***

## 12) Test Plan (Examples)

*   **Happy paths**
    *   Minimal script draws shapes, no errors
    *   Grouped commands render at expected coordinates
    *   Animation moves exactly over specified duration
*   **Errors**
    *   Unknown command, bad arity, bad numbers
    *   Invalid group names
*   **State**
    *   `stroke/fill/lineWidth` persist within a target
    *   Re‑running script resets scene correctly
*   **Hierarchy**
    *   Nested groups inherit transforms from parents
    *   Animating parent affects children; animating child is local
*   **Templates (later)**
    *   Spawned instances are independent (style & animation)

***

## 13) Example End‑to‑End Demo Script

    # Scene setup
    background 250 250 255
    stroke 20 20 20
    fill  0 160 255 128
    lineWidth 3

    # Root shapes
    rect 30 30 160 100
    circle 200 200 60
    line 0 0 320 60

    # Kevin sprite
    Kevin.circle 100 100 40
    Kevin.line 0 0 200 200

    # Animate Kevin
    Kevin.animate x to 600 over 2000
    Kevin.animate rotation to 360 over 5000 loop

    # Nested spaceship
    Spaceship.Body.rect 50 50 200 60
    Spaceship.Engine.rect 230 60 20 20
    Spaceship.Flame.triangle 240 80 250 120 260 80

    # Move whole spaceship
    Spaceship.animate x to 800 over 3000

***

## 14) Open Questions

*   Do we want **time units** in seconds (`over 2s`) instead of milliseconds?
*   Should **styles** be per‑group state or per‑shape immediate attributes?
*   How to handle **partial updates** (append vs reset) when running scripts?
*   Preferred **easing** names and defaults (e.g., `InOutQuad`)?
*   Should we support **named colors** and **hex** in v0.1?

***

### Final Notes

*   Your current approach—**dot‑notation groups with an implicit non‑animatable root**—is simple, intuitive, and scales naturally to nested sprites.
*   Start small with the **local prototype**, then migrate rendering to **QML** for animation and performance, and only then add **IPC** when you’re ready.

If you want, I can turn this spec into:

*   a **Qt Quick (QML) skeleton** wired to the C++ parser, or
*   a **Widget prototype** you already started, with the new **group** and **animate** commands added.

