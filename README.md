# Semantic Compression Demo

A hands-on walk through Casey Muratori's [Semantic Compression](https://caseymuratori.com/blog_0015) article. The idea: write everything inline and concrete first, then compress duplicate code into structs and functions only *after* the duplication exists. Objects fall out of the procedure; they aren't designed up front.

The demo is an immediate-mode UI panel (title + buttons) rendered with raylib — the same "Movement Panel" shape from the article.

## Dependencies

- [Zig](https://ziglang.org/) (for `zig cc`, a clang frontend)
- [raylib](https://www.raylib.com/) via `brew install raylib`

## Build & run

```sh
just run
```

Or manually:

```sh
zig cc main.c -o ./build/main \
  -I"$(brew --prefix raylib)/include" \
  -L"$(brew --prefix raylib)/lib" \
  -lraylib \
  -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
./build/main
```

## Files

| File | Purpose |
|---|---|
| `main.c` | Everything: drawing primitives, panel struct, render loop |
| `compile_flags.txt` | clangd include path for editor tooling |
| `justfile` | Build and run recipes |
