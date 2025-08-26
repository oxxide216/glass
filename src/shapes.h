#ifndef SHAPES_H
#define SHAPES_H

#include "glass.h"
#include "math.h"

typedef enum {
  GlassShapeKindTriangle = 0,
  GlassShapeKindQuad,
  GlassShapeKindCircle
} GlassShapeKind;

typedef struct {
  GlassShapeKind kind;
  GlassObject    object;
} GlassShapeObject;

typedef Da(GlassShapeObject) GlassShapeObjects;
typedef Da(Vec4)             GlassColors;

typedef struct {
  Vec2              resolution;
  GlassShader       default_shader;
  GlassShader       circle_shader;
  GlassShapeObjects objects;
  GlassColors       colors;
} GlassShapes;

GlassShapes glass_init_shapes(void);
void        glass_resize_shapes(GlassShapes *shapes, f32 width, f32 height);
void        glass_init_triangle(GlassShapes *shapes, Vec2 a, Vec2 b, Vec2 c, Vec4 color);
void        glass_init_quad(GlassShapes *shapes, Vec2 pos, Vec2 size, Vec4 color);
void        glass_init_circle(GlassShapes *shapes, Vec2 pos, f32 radius, Vec4 color);
void        glass_render_shapes(GlassShapes *shapes);

#endif // SHAPES_H
