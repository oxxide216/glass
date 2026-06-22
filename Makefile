.RECIPEPREFIX = >

CC = cc
override CFLAGS += -Wall -Wextra -Iinclude -Ilibs/winx/include
override LDFLAGS += -z execstack -lX11 -lGL -lGLEW
BUILD_DIR = build

SRC = $(wildcard src/*.c)

TRIANGLES_TEST_SRC = $(wildcard tests/triangles/*.c)
TEXTURES_TEST_SRC = $(wildcard tests/textures/*.c)

OBJ = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRC))

TESTS_EXECS = $(BUILD_DIR)/tests/triangles $(BUILD_DIR)/tests/textures

libglass.a: $(OBJ)
> ar rcs libglass.a $(OBJ)

tests: $(TESTS_EXECS)

$(BUILD_DIR)/%.o: src/%.c
> mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/tests/triangles: $(TRIANGLES_TEST_SRC) libglass.a libs/winx/libwinx.a
> mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -o $@ $(TRIANGLES_TEST_SRC) libglass.a libs/winx/libwinx.a $(LDFLAGS)

$(BUILD_DIR)/tests/textures: $(TEXTURES_TEST_SRC) libglass.a libs/winx/libwinx.a
> mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -o $@ $(TEXTURES_TEST_SRC) libglass.a libs/winx/libwinx.a $(LDFLAGS)

libs/winx/libwinx.a:
> $(MAKE) -C libs/winx

clean:
> rm -rf $(BUILD_DIR) libglass.a
