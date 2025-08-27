#include <GL/glew.h>

#include "shapes.h"
#include "params.h"

static Str default_vertex_shader = STR_LIT(
  "#version 330 core\n"
  "uniform vec2 u_resolution;\n"
  "layout (location = 0) in vec2 i_pos;\n"
  "void main(void) {\n"
  "  float x = i_pos.x / u_resolution.x * 2.0 - 1.0;\n"
  "  float y = 1.0 - i_pos.y / u_resolution.y * 2.0;\n"
  "  gl_Position = vec4(x, y, 0.0, 1.0);\n"
  "}\n"
);

static Str default_fragment_shader = STR_LIT(
  "#version 330 core\n"
  "uniform vec4 u_color;\n"
  "out vec4 frag_color;\n"
  "void main(void) {\n"
  "  frag_color = u_color;\n"
  "}\n"
);

static Str circle_vertex_shader = STR_LIT(
  "#version 330 core\n"
  "uniform vec2 u_resolution;\n"
  "layout (location = 0) in vec2 i_pos;\n"
  "layout (location = 1) in vec2 i_uv;\n"
  "out vec2 o_uv;\n"
  "void main(void) {\n"
  "  float x = i_pos.x / u_resolution.x * 2.0 - 1.0;\n"
  "  float y = 1.0 - i_pos.y / u_resolution.y * 2.0;\n"
  "  gl_Position = vec4(x, y, 0.0, 1.0);\n"
  "  o_uv = i_uv;\n"
  "}\n"
);

static Str circle_fragment_shader = STR_LIT(
  "#version 330 core\n"
  "uniform vec4 u_color;\n"
  "in vec2 o_uv;"
  "out vec4 frag_color;\n"
  "void main(void) {\n"
  "  float alpha = 1.0 - smoothstep(0.95, 1.0, length(o_uv));\n"
  "  frag_color = vec4(u_color.x, u_color.y, u_color.z, u_color.w * alpha);\n"
  "}\n"
);

#include "shl_log.h"

GlassShapes glass_init_shapes(void) {
  GlassShapes shapes = {0};

  GlassAttributes default_shader_attributes = {0};
  glass_push_attribute(&default_shader_attributes, GlassAttributeKindFloat, 2);
  shapes.default_shader = glass_init_shader(default_vertex_shader,
                                            default_fragment_shader,
                                            &default_shader_attributes);

  GlassAttributes circle_shader_attributes = {0};
  glass_push_attribute(&circle_shader_attributes, GlassAttributeKindFloat, 2);
  glass_push_attribute(&circle_shader_attributes, GlassAttributeKindFloat, 2);
  shapes.circle_shader = glass_init_shader(circle_vertex_shader,
                                           circle_fragment_shader,
                                           &circle_shader_attributes);

  return shapes;
}

void glass_resize_shapes(GlassShapes *shapes, f32 width, f32 height) {
  shapes->resolution = vec2(width, height);
}

void glass_init_triangle(GlassShapes *shapes, Vec2 a, Vec2 b, Vec2 c, Vec4 color) {
  Vec2 vertices[] = { a, b, c };
  u32 indices[] = { 0, 1, 2 };

  GlassObject triangle = glass_init_object(&shapes->default_shader);
  glass_object_put_data(&triangle, vertices, sizeof(vertices),
                        indices, sizeof(indices), 3, true);

  GlassShapeObject shape = { GlassShapeKindTriangle, triangle };

  DA_APPEND(shapes->objects, shape);
  DA_APPEND(shapes->colors, color);
}

void glass_init_quad(GlassShapes *shapes, Vec2 pos, Vec2 size, Vec4 color) {
  Vec2 vertices[] = {
    pos,
    vec2(pos.x + size.x, pos.y),
    vec2(pos.x, pos.y + size.y),
    vec2(pos.x + size.x, pos.y + size.y),
  };
  u32 indices[] = { 0, 1, 2, 2, 1, 3 };

  GlassObject quad = glass_init_object(&shapes->default_shader);
  glass_object_put_data(&quad, vertices, sizeof(vertices),
                        indices, sizeof(indices), 6, true);

  GlassShapeObject shape = { GlassShapeKindQuad, quad };

  DA_APPEND(shapes->objects, shape);
  DA_APPEND(shapes->colors, color);
}

void glass_init_circle(GlassShapes *shapes, Vec2 pos, f32 radius, Vec4 color) {
  Vec2 vertices[] = {
    vec2(pos.x - radius, pos.y - radius), vec2(-1.0, 1.0),
    vec2(pos.x + radius, pos.y - radius), vec2(1.0, 1.0),
    vec2(pos.x - radius, pos.y + radius), vec2(-1.0, -1.0),
    vec2(pos.x + radius, pos.y + radius), vec2(1.0, -1.0),
  };
  u32 indices[] = { 0, 1, 2, 2, 1, 3 };

  GlassObject circle = glass_init_object(&shapes->circle_shader);
  glass_object_put_data(&circle, vertices, sizeof(vertices),
                        indices, sizeof(indices), 6, true);

  GlassShapeObject shape = { GlassShapeKindCircle, circle };

  DA_APPEND(shapes->objects, shape);
  DA_APPEND(shapes->colors, color);
}

void glass_render_shapes(GlassShapes *shapes) {
  glass_set_param_2f(&shapes->default_shader, "u_resolution",
                     shapes->resolution);
  glass_set_param_2f(&shapes->circle_shader, "u_resolution",
                     shapes->resolution);

  for (u32 i = 0; i < shapes->objects.len; ++i) {
    glass_set_param_4f(&shapes->default_shader, "u_color",
                       shapes->colors.items[i]);
    glass_set_param_4f(&shapes->circle_shader, "u_color",
                       shapes->colors.items[i]);

    glass_render_object(&shapes->objects.items[i].object);
  }
}
