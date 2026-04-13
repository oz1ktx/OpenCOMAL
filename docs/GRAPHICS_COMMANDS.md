# OpenCOMAL Graphics Commands

The `DRAW` statement is an OpenCOMAL extension — it is **not** part of the
original COMAL language.  It provides a simple, immediate-mode 2D drawing
API that renders to the IDE's Graphics panel.

## The DRAW Statement

```
DRAW command-name [, arg, arg, ...]
```

There are three calling forms:

| Form | Example |
|------|---------|
| **Bare name** — command name without quotes (preferred) | `DRAW circle, 200, 150, 50` |
| **Quoted name** — command name as a string | `DRAW "circle", 200, 150, 50` |
| **Single-string** — entire command packed into one string | `DRAW "circle 200 150 50"` |

The bare-name form is preferred — the parser automatically treats the
first identifier as a string command name:

```comal
x := 100
y := 200
r := 30 + offset
DRAW circle, x, y, r
DRAW noFill
DRAW stroke, 255, 0, 0
```

The quoted form is required for **grouped commands** that contain a dot
(e.g. `DRAW "Spaceship.rect", x, y, w, h`) because the dot is not part
of COMAL identifier syntax.  Command names are **case-insensitive**
(`DRAW CIRCLE`, `DRAW circle`, and `DRAW Circle` all work).

### Group notation quick guide

Grouped command names follow this rule:

```
Group1.Group2....command
```

- Everything before the final `.` is the group path.
- The final token is the command name.

Examples:

```comal
DRAW "HUD.text", 10, 10, "Score: 42"
DRAW "Ship.Engine.rect", 100, 120, 40, 18
DRAW "Ship.Engine.fill", 255, 120, 0
```

This makes it easier to organize scene elements into logical subtrees.
In the IDE, hovering the command token in grouped form (for example
`Ship.Engine.rect`) now resolves to the same command help as `rect`.

---

## Coordinate System

The default canvas is **640 × 480** pixels.  The origin (0, 0) is at the
**top-left** corner; X increases to the right, Y increases downward.

---

## Shape Commands

These commands add a shape to the current group (or the root canvas).
The shape inherits the current stroke, fill, and line-width style.

### line

Draw a straight line from (x1, y1) to (x2, y2).

```
line x1 y1 x2 y2
```

| Arg | Description |
|-----|-------------|
| x1, y1 | Start point |
| x2, y2 | End point |

```comal
DRAW line, 0, 0, 300, 200
```

### rect

Draw an axis-aligned rectangle.

```
rect x y w h
```

| Arg | Description |
|-----|-------------|
| x, y | Top-left corner |
| w | Width |
| h | Height |

```comal
DRAW rect, 10, 20, 100, 50
```

### circle

Draw a circle.

```
circle cx cy r
```

| Arg | Description |
|-----|-------------|
| cx, cy | Centre point |
| r | Radius |

```comal
DRAW circle, 200, 200, 80
```

### ellipse

Draw an axis-aligned ellipse defined by its bounding box.

```
ellipse x y w h
```

| Arg | Description |
|-----|-------------|
| x, y | Top-left corner of bounding box |
| w | Width |
| h | Height |

```comal
DRAW ellipse, 100, 300, 120, 60
```

### text

Draw a text string at a position.  The text uses the current stroke color
and the current `fontSize` (see Style Commands).  The position is the
**top-left corner** of the text bounding box, consistent with `rect` and
`ellipse`.

```
text x y "string"
```

| Arg | Description |
|-----|-------------|
| x, y | Top-left position |
| "string" | The text to draw (must be quoted if it contains spaces) |

The text color is taken from the current stroke color.  The font size is
taken from the current `fontSize` style (default 12 pt).

```comal
DRAW text, 100, 50, "Hello World"

// Variable string
label$ := "Score: " + STR$(score)
DRAW text, 10, 10, label$

// Grouped text
DRAW "HUD.text", 5, 5, "Lives: 3"
```

**Future extensions:** optional trailing rotation angle (degrees) will be
added as a trailing argument in a later version.  Font family and style
are set via the separate `font` style command, which is not yet
implemented.

---

## Style Commands

Style commands change the drawing state for **all subsequent** shapes
until the style is changed again.

### stroke

Set the stroke (outline) color.  Enables stroking if it was disabled.

```
stroke r g b [a]
```

| Arg | Description | Range |
|-----|-------------|-------|
| r, g, b | Red, green, blue components | 0–255 |
| a | Alpha (opacity), optional, default 255 | 0–255 |

```comal
DRAW stroke, 255, 0, 0         // red outline
DRAW stroke, 0, 0, 0, 128      // semi-transparent black
```

### fill

Set the fill (interior) color.  Enables filling if it was disabled.

```
fill r g b [a]
```

Arguments are the same as `stroke`.

```comal
DRAW fill, 0, 128, 255, 200
```

### noStroke

Disable the stroke for subsequent shapes.  Takes no arguments.

```comal
DRAW noStroke
```

### noFill

Disable the fill for subsequent shapes.  Takes no arguments.

```comal
DRAW noFill
```

### lineWidth

Set the stroke width in pixels.

```
lineWidth w
```

| Arg | Description |
|-----|-------------|
| w | Line width (positive number) |

```comal
DRAW lineWidth, 3
```

### fontSize

Set the font size (in points) for subsequent `text` commands.  Acts like
`lineWidth` — stateful, affects all text drawn after this call until
changed again.

```
fontSize size
```

| Arg | Description |
|-----|-------------|
| size | Font size in points (must be positive) |

Default is 12.0 pt.

```comal
DRAW fontSize, 24          // big heading
DRAW text, 100, 50, "Title"

DRAW fontSize, 12          // back to normal
DRAW text, 100, 100, "Body text"
```

**Future extension:** a `font` style command (not yet implemented) will
allow selecting the font family and style (bold, italic).

---

## Canvas Commands

### background

Set the canvas background color.

```
background r g b [a]
```

Arguments are the same as `stroke`.  Default is (240, 240, 255).

```comal
DRAW background, 0, 0, 0       // black background
```

### clear

Remove all shapes and groups from the scene.

```comal
DRAW clear
```

---

## Transform Commands

Transform commands modify the position, rotation, or scale of the
**target group**.  Without a group prefix they affect the root canvas.
Transforms are **cumulative** — each call adds to the existing value.

### translate

Move the group origin by (dx, dy).

```
translate dx dy
```

```comal
DRAW "Spaceship.translate", 10, -5
```

### rotate

Rotate the group by the given angle in degrees.

```
rotate degrees
```

```comal
DRAW "Spaceship.rotate", 45
```

### scale

Scale the group.  With one argument, scales uniformly; with two,
scales X and Y independently.

```
scale factor
scale sx sy
```

```comal
DRAW "Spaceship.scale", 2          // double size
DRAW "Spaceship.scale", 1.5, 0.8  // stretch
```

---

## Groups (Sprites)

Commands can target a **named group** by prefixing the command name
with a dot-separated path.  Groups are created automatically on first
use.  This allows building composite objects ("sprites") that can be
transformed as a unit.

```
GroupName.command args...
```

Groups can be nested:

```
Parent.Child.command args...
```

### Example — a grouped spaceship

```comal
// Set up the body
DRAW "Spaceship.fill", 128, 128, 128
DRAW "Spaceship.rect", 0, 0, 80, 30

// Add an engine (child group of Spaceship)
DRAW "Spaceship.Engine.fill", 255, 100, 0
DRAW "Spaceship.Engine.circle", -10, 15, 12

// Move the whole spaceship (body + engine move together)
DRAW "Spaceship.translate", 200, 100
```

---

## Comments in the Graphics Language

When using the single-string form, lines beginning with `#` are treated
as comments and ignored:

```comal
DRAW "# This is a comment"
```

This is primarily useful in the internal command parser; in normal COMAL
code, use the standard `//` comment syntax instead.

---

## Default Style State

When the scene is first created (or after `clear`), the defaults are:

| Property | Default |
|----------|---------|
| Stroke color | Black (0, 0, 0, 255) |
| Stroke enabled | Yes |
| Fill color | White (255, 255, 255, 255) |
| Fill enabled | Yes |
| Line width | 1.0 |
| Font size | 12.0 |
| Background color | (240, 240, 255, 255) |

---

## IDE Features

In the OpenCOMAL IDE, the Graphics panel provides:

- **Toolbar** — Clear button, Save PNG, Save SVG
- **Right-click context menu** — Clear, Save as PNG, Save as SVG
- **Persistent scene** — In direct (interactive) mode, successive DRAW
  commands accumulate on the same canvas.  Running a full program clears
  the canvas first.

---

## Complete Example

```comal
// Draw a simple scene
DRAW background, 135, 206, 235
// Green ground
DRAW fill, 34, 139, 34
DRAW noStroke
DRAW rect, 0, 350, 640, 130
// House body
DRAW stroke, 0, 0, 0
DRAW fill, 200, 100, 50
DRAW rect, 200, 250, 150, 100
// Roof
DRAW fill, 139, 69, 19
DRAW line, 200, 250, 275, 180
DRAW line, 275, 180, 350, 250
// Sun
DRAW noStroke
DRAW fill, 255, 255, 0
DRAW circle, 550, 80, 40
PRINT "Scene drawn"
END
```
