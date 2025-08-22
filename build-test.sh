#!/usr/bin/sh

CFLAGS="-Wall -Wextra -Isrc -Ilibs/winx -Ilibs"
LDFLAGS="-z execstack"
SRC="$(find src -name "*.c")"
WINX_SRC_PATH="../winx/src"
WINX_LIBS_PATH="libs/winx"
LIBS="-lX11 -lGL -lGLEW"

if [ "$1" == "--rebuild-libs" ]; then
  BUILD_FLAGS="${@:2}"
  if [ -d "libs" ]; then
    rm -r libs
  fi
else
  BUILD_FLAGS="${@:1}"
fi

if [ ! -d libs ]; then
  mkdir libs
fi

if [ ! -d $WINX_LIBS_PATH ]; then
  cp -r $WINX_SRC_PATH $WINX_LIBS_PATH
fi

LIBS_SRC="$(find libs -name "*.c")"

cc -o glass-test $CFLAGS $LIBS $LDFLAGS $BUILD_FLAGS $SRC $LIBS_SRC
