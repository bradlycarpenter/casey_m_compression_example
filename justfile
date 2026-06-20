build:
    zig cc main.c -o ./build/main \
    -I"$(brew --prefix raylib)/include" \
    -L"$(brew --prefix raylib)/lib" \
    -lraylib \
    -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL

run: build
    ./build/main
