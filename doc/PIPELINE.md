OpenCOMAL: piping programs and stdin/stdout usage

This repository includes a plain-IO mode for `opencomalrun` so plain-text
COMAL listings and standard input/output can be used in Unix pipelines.

Quick examples

- Run a plain-text COMAL program file (no curses / pipe-friendly):

  ```bash
  bin/opencomalrun samples/filter_pipe.lst
  ```

- Read the program listing from stdin (use `-` to mean stdin):

  ```bash
  cat samples/filter_pipe.lst | bin/opencomalrun -
  ```

- Use `opencomalrun` inside a Unix pipe. Example — echo file contents through
  a COMAL program that echoes input lines (see `samples/filter_pipe.lst`):

  ```bash
  cat data.txt | bin/opencomalrun samples/filter_pipe.lst
  ```

- Explicit plain-mode flag: instead of relying on the program name or `-`,
  you can force pipe-friendly plain mode with `--plain`:

  ```bash
  printf 'hello\n\n' | bin/opencomalrun --plain samples/filter_pipe.lst
  ```

Behavior notes

- Automatic format detection: `opencomalrun` prefers the saved binary
  format (SqAsH) when present. If the header is missing the file is
  parsed as a plain-text COMAL listing.

- Plain (pipe) mode differences:
  - `opencomalrun` runs without `ncurses`/readline so it's suitable for
    pipes and non-interactive use.
  - The usual startup banner is suppressed when running in plain mode.
  - `INPUT` prompts are suppressed; when reading string inputs an
    unquoted `INPUT` value consumes the entire line so spaces are kept.
  - EOF on stdin causes the running program to terminate quietly (no
    error message).

Example filter program

Create `samples/filter_pipe.lst` (compatible with this COMAL version):

```
10 WHILE 1 DO
20   INPUT a$
30   IF a$ = "" THEN END
40   PRINT a$
50 ENDWHILE
```

Piped-test example:

```bash
printf 'hello world\n\n' | bin/opencomalrun samples/filter_pipe.lst
# prints "hello world" then exits
```

Want an automated test? I can add a small shell test that runs the pipe
command and asserts the output. Tell me whether to add it under
`tests/` or `samples/tests/` and I'll create it.