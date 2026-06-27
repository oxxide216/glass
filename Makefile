.RECIPEPREFIX = >

PLATFORM = LINUX

ifeq ($(PLATFORM), LINUX)
  CC = cc
else ifeq ($(PLATFORM), WINDOWS)
  CC = x86_64-w64-mingw32-gcc
endif
override CFLAGS += -Wall -Wextra -Iinclude -Ilibs/winx/include -Ilibs/glad/include
ifeq ($(PLATFORM), LINUX)
  override LDFLAGS += -z execstack -L. -Llibs/winx \
                      -l:libwinx.a -l:libglass.a -lX11 -lGL
else ifeq ($(PLATFORM), WINDOWS)
  override LDFLAGS += -L. -Llibs/winx -l:libwinx.lib \
                      -l:libglass.lib -lopengl32 -lgdi32 \
                      -static
endif
BUILD_DIR = build

SRC = $(wildcard src/*.c)

TRIANGLES_TEST_SRC = $(wildcard tests/triangles/*.c)
TEXTURES_TEST_SRC = $(wildcard tests/textures/*.c)

ifeq ($(PLATFORM), LINUX)
  OBJ = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRC))
else ifeq ($(PLATFORM), WINDOWS)
  OBJ = $(patsubst src/%.c,$(BUILD_DIR)/%.obj,$(SRC))
endif

ifeq ($(PLATFORM), LINUX)
  TESTS_EXECS = $(BUILD_DIR)/tests/triangles $(BUILD_DIR)/tests/textures
else ifeq ($(PLATFORM), WINDOWS)
  TESTS_EXECS = $(BUILD_DIR)/tests/triangles.exe $(BUILD_DIR)/tests/textures.exe
endif

ifeq ($(PLATFORM), LINUX)
libglass.a: $(OBJ)
> ar rcs libglass.a $(OBJ)
else ifeq ($(PLATFORM), WINDOWS)
libglass.lib: $(OBJ)
> x86_64-w64-mingw32-ar rcs libglass.lib $(OBJ)
endif

tests: $(TESTS_EXECS)

$(BUILD_DIR)/%.o: src/%.c
> mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.obj: src/%.c
> mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/tests/triangles: $(TRIANGLES_TEST_SRC) libglass.a libs/winx/libwinx.a
> mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -o $@ $(TRIANGLES_TEST_SRC) $(LDFLAGS)

$(BUILD_DIR)/tests/textures: $(TEXTURES_TEST_SRC) libglass.a libs/winx/libwinx.a
> mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -o $@ $(TEXTURES_TEST_SRC) $(LDFLAGS)

$(BUILD_DIR)/tests/triangles.exe: $(TRIANGLES_TEST_SRC) libs/winx/libwinx.lib libglass.lib
> mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -o $@ $(TRIANGLES_TEST_SRC) $(LDFLAGS)

$(BUILD_DIR)/tests/textures.exe: $(TEXTURES_TEST_SRC) libs/winx/libwinx.lib libglass.lib
> mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -o $@ $(TEXTURES_TEST_SRC) $(LDFLAGS)

libs/winx/libwinx.a:
> $(MAKE) -C libs/winx

libs/winx/libwinx.lib:
> $(MAKE) -C libs/winx PLATFORM=WINDOWS

clean:
> rm -rf $(BUILD_DIR) libglass.a libglass.lib
