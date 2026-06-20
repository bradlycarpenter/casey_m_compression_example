# Project: Understanding Semantic Compression

This is a learning project. I'm working through Casey Muratori's article
"Semantic Compression" (https://caseymuratori.com/blog_0015) by building a
small C demo, so I can feel the technique in my hands instead of just reading
about it.

## Most important: how to help me

I want to write the actual layout code **from scratch myself**. The whole point
of the exercise is to perform the compression with my own hands.

- **Do not write the panel layout or the compression steps for me.** Don't hand
  me the verbose "before" code, the `Panel_Layout` struct, or any of the
  extracted functions unless I explicitly ask for a specific piece.
- Coach, don't solve. Ask questions, give hints, point out where I'm
  duplicating something, review code I've written, explain *why* a step helps.
- If I'm stuck, nudge me toward the next small step rather than jumping to the
  answer. The smallest useful hint wins.
- The infrastructure (window loop + the two drawing primitives) is already
  written — that part isn't the lesson, so it's fine to help freely with it.

## The idea I'm trying to internalize

Compression-oriented programming. Write exactly what you want to happen, inline
and concrete, with no concern for abstraction. Only once the *same thing*
appears a second time do you "compress" it into a shared struct/function —
"make your code usable before you make it reusable." The objects fall out of
the procedure afterward; you don't design them up front. This is the article's
counterpoint to object-oriented design.

## The demo

An immediate-mode UI panel in a window: a title plus some buttons, exactly like
the Witness "Movement Panel" in the article. The key shape is the inline
`bool pressed = draw_big_text_button(...)`, which is what makes the later
layout compression possible.

The drawing layer is provided (think of it as Jon's pre-existing helpers in the
article):
- `float draw_title(float x, float y, const char *title)` — draws the header,
  returns the vertical space it consumed.
- `bool draw_big_text_button(float x, float y, float w, float h, const char *label)`
  — draws a button, returns `true` on the frame it's clicked.

I write the body of `render_panel(Panel *panel)`.

### Coordinate gotcha
The article uses a y-up game-engine coordinate system, so it does
`y0 -= category_height`. This is a window in screen coordinates, so **down is
+y** — I ADD the row height where the article subtracts. Everything else about
the transformation is identical; only that sign differs.

## The planned path (my steps to take, not yours to do)

1. Write the verbose, inline version: title + "Auto Snap" and "Reset
   Orientation" buttons, all layout math done by hand right in `render_panel`.
   Wire clicks to something visible. Make it deliberately repetitive.
2. Pull the loose locals (`at_x`, `at_y`, `row_height`, `width`) into a
   `Panel_Layout` struct — a "shared stack frame." (No improvement yet; setup.)
3. Extract `row()` (advance y by a row), then `window_title()`,
   then `push_button()`, then `complete()` (compute panel height at the end
   instead of pre-counting).
4. After **every** step, run it and confirm the window looks exactly the same.
   "Code got smaller, output identical" is the whole lesson — please hold me to
   checking this each time.

## Toolchain (macOS)

- Compiler: Zig's C frontend, `zig cc` (clang underneath).
- Windowing/drawing: raylib, installed via `brew install raylib`.
- Editor: Zed (uses clangd).

### Build & run
```
zig cc panel.c -o panel \
  -I"$(brew --prefix raylib)/include" \
  -L"$(brew --prefix raylib)/lib" \
  -lraylib \
  -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
./panel
```

### clangd setup
A `compile_flags.txt` next to `panel.c` gives the editor the include path so it
stops flagging `raylib.h` as missing. It contains the resolved include path and
the C standard, e.g.:
```
-I/opt/homebrew/opt/raylib/include
-std=c11
```
(Linker flags aren't needed for clangd — it only parses.)
