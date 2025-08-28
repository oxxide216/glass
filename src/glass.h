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
  u32             id;
  u32             vertex_size;
  GlassAttributes attributes;
} GlassShader;

typedef struct {
  u32 id;
  u32 width;
  u32 height;
} GlassTexture;

typedef Da(GlassTexture) GlassTextures;

typedef struct {
  u32           vertex_array;
  u32           vertex_buffer;
  u32           index_buffer;
  u32           indices_count;
  GlassShader   shader;
  GlassTextures textures;
} GlassObject;

typedef enum {
  GlassTextureFilteringModeNearest = 0,
  GlassTextureFilteringModeLinear,
} GlassTextureFilteringMode;

void            glass_init(void);
void            glass_resize(u32 width, u32 height);
void            glass_clear_screen(f32 r, f32 g, f32 b, f32 a);
void            glass_push_attribute(GlassAttributes *attributes,
                                     GlassAttributeKind kind, u32 len);
GlassShader     glass_init_shader(Str vertex_src, Str fragment_src,
                                  GlassAttributes *attributes);
GlassObject     glass_init_object(GlassShader *shader);
void            glass_put_object_data(GlassObject *object, void *vertices,
                                      u32 vertices_size, u32 *indices,
                                      u32 indices_size, u32 indices_count,
                                      bool is_mutable);
GlassTexture    glass_init_texture(u8 *data, u32 width, u32 height,
                                   GlassTextureFilteringMode filtering_mode);
void            glass_push_texture(GlassObject *object, GlassTexture *texture);
void            glass_render_object(GlassObject *object);

#endif // GLASS_H
