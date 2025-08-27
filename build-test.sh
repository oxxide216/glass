#!/usr/bin/sh

CFLAGS="-Wall -Wextra -Isrc -Ilibs/winx -Ilibs"
LDFLAGS="-z execstack -lX11 -lGL -lGLEW"
BUILD_FLAGS="${@:1}"
SRC="$(find src -name "*.c")"
WINX_SRC="$(find libs/winx/src -name "*.c")"

cc -o glass-test $CFLAGS $LDFLAGS $BUILD_FLAGS $SRC $WINX_SRC
