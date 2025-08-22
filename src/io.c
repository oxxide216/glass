#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "shl_log.h"
#define SHL_ARENA_IMPLEMENTATION
#include "shl_arena.h"

Str read_file(char *path) {
  FILE *file = fopen(path, "r");
  if (!file) {
    ERROR("Could not open input file: %s\n", path);
    exit(1);
  }

  Str content;

  fseek(file, 0, SEEK_END);
  content.len = ftell(file);
  content.ptr = aalloc(content.len + 1);
  fseek(file, 0, SEEK_SET);
  fread(content.ptr, 1, content.len, file);
  content.ptr[content.len] = '\0';
  fclose(file);

  return content;
}
