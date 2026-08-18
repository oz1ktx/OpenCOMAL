# libcomal-graphics

C++20 graphics library implementing the COMAL `DRAW` command set via a retained scene model.

## Responsibilities

- Parse and execute all 13 `DRAW` sub-commands from COMAL programs
- Maintain a scene graph of drawing primitives that can be rendered by any front-end
- Support group nesting (`DRAW GROUP` / `DRAW ENDGROUP`) for logical object hierarchies
- Provide style controls: colour, line width, fill, font

## Supported DRAW Commands

| Command | Description |
|---------|-------------|
| `DRAW CLEAR` | Clear the scene |
| `DRAW MOVE x,y` | Move pen to absolute position |
| `DRAW LINE x,y` | Draw line to position |
| `DRAW CIRCLE r` | Draw circle at current position |
| `DRAW RECT w,h` | Draw rectangle |
| `DRAW TEXT s$` | Render text string |
| `DRAW COLOR r,g,b` | Set drawing colour |
| `DRAW FILL r,g,b` | Set fill colour |
| `DRAW WIDTH w` | Set line width |
| `DRAW FONT name$,size` | Set font |
| `DRAW GROUP` | Begin a named group |
| `DRAW ENDGROUP` | End current group |
| `DRAW IMAGE file$` | Place an image |

## Architecture

- `comal_graphics.h` / `src/` — command parser and scene model controller
- `comal_scene_model.h` — scene graph node types (lines, circles, text, groups, …)
- `comal_graphics_commands.h` — command enum and parameter types
- The library is rendering-backend agnostic; the Qt IDE renders via `QGraphicsScene`

## Building

```bash
cd build && cmake .. && make comal-graphics -j$(nproc)
```

## See Also

- [`comal-ide`](../comal-ide/README.md) — Qt front-end that renders this scene model
- [`docs/PROJECT_STATUS.md`](../docs/PROJECT_STATUS.md) — overall project status
