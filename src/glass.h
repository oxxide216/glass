#ifndef GLASS_H
#define GLASS_H

#include "shl_defs.h"
#include "shl_str.h"
#include "shl_defs.h"

typedef enum {
  GlassAttributeKindFloat = 0,
  GlassAttributeKindDouble,
  GlassAttributeKindInt,
  GlassAttributeKindUInt,
  GlassAttributeKindShort,
  GlassAttributeKindUShort,
  GlassAttributeKindByte,
  GlassAttributeKindUByte,
} GlassAttributeKind;

typedef struct {
  GlassAttributeKind kind;
  u32                len;
} GlassAttribute;

typedef Da(GlassAttribute) GlassAttributes;

typedef struct {
  u32 program;
  u32 vertex_array;
  u32 attributes_count;
} GlassShader;

typedef struct {
  u32         vertex_buffer;
  u32         index_buffer;
  u32         vertex_size;
  u32         indices_count;
  GlassShader shader;
} GlassObject;

void            glass_init(void);
void            glass_resize(u32 width, u32 height);
void            glass_clear_screen(f32 r, f32 g, f32 b, f32 a);
void            glass_push_attribute(GlassAttributes *attributes,
                                     GlassAttributeKind kind, u32 len);
GlassShader     glass_init_shader(Str vertex_src, Str fragment_src,
                                  GlassAttributes *attributes);
GlassObject     glass_init_object(void *vertices, u32 vertices_size, u32 vertex_size,
                                  u32 *indices, u32 indices_size, u32 indices_count,
                                  GlassShader shader, bool is_mutable);
void            glass_render_object(GlassObject *object);

#endif // GLASS_H
