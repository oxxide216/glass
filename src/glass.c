#include <GL/glew.h>
#include <GL/gl.h>

#include "glass.h"
#include "shl_log.h"

typedef struct {
  GLenum gl_kind;
  u32    size;
} AttributeKindData;

static AttributeKindData attrib_kinds_data[] = {
  [GlassAttributeKindFloat] =  { GL_FLOAT, 4 },
  [GlassAttributeKindDouble] = { GL_DOUBLE, 8 },
  [GlassAttributeKindInt] =    { GL_INT, 4 },
  [GlassAttributeKindUInt] =   { GL_UNSIGNED_INT, 4 },
  [GlassAttributeKindShort] =  { GL_SHORT, 2 },
  [GlassAttributeKindUShort] = { GL_UNSIGNED_SHORT, 2 },
  [GlassAttributeKindByte] =   { GL_BYTE, 1 },
  [GlassAttributeKindUByte] =  { GL_UNSIGNED_BYTE, 1 },
};

void glass_init(void) {
  GLenum result = glewInit();
  if (GLEW_OK != result) {
    ERROR("%s\n", glewGetErrorString(result));
    exit(1);
  }

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void glass_resize(u32 width, u32 height) {
  glViewport(0, 0, width, height);
}

void glass_clear_screen(f32 r, f32 g, f32 b, f32 a) {
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void glass_print_shader_error(u32 shader) {
  i32 result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if (result)
    return;

  char message[128];
  glGetShaderInfoLog(shader, ARRAY_LEN(message), NULL, message);
  ERROR("Shader compilation error:\n%s\n", message);
  exit(1);
}

void glass_push_attribute(GlassAttributes *attributes, GlassAttributeKind kind, u32 len) {
  GlassAttribute attribute = { kind, len };
  DA_APPEND(*attributes, attribute);
}

GlassShader glass_init_shader(Str vertex_src, Str fragment_src, GlassAttributes attributes) {
  GlassShader shader = { glCreateProgram(), 0, attributes };

  for (u32 i = 0; i < attributes.len; ++i) {
    GlassAttribute *attribute = attributes.items + i;
    AttributeKindData *data = attrib_kinds_data + attribute->kind;

    shader.vertex_size += attribute->len * data->size;
  }

  u32 vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, (const GLchar* const*) &vertex_src.ptr, NULL);
  glCompileShader(vertex);
  glass_print_shader_error(vertex);

  u32 fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, (const GLchar* const*) &fragment_src.ptr, NULL);
  glCompileShader(fragment);
  glass_print_shader_error(fragment);

  glAttachShader(shader.program, vertex);
  glAttachShader(shader.program, fragment);
  glLinkProgram(shader.program);

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return shader;
}

GlassObject glass_init_object(GlassShader shader) {
  GlassObject object = {0};
  object.shader = shader;

  glGenBuffers(1, &object.vertex_buffer);
  glGenBuffers(1, &object.index_buffer);

  return object;
}

void glass_object_put_data(GlassObject *object, void *vertices,
                           u32 vertices_size, u32 *indices,
                           u32 indices_size, u32 indices_count,
                           bool is_mutable) {
  object->indices_count = indices_count;

  GLenum usage;
  if (is_mutable)
    usage = GL_DYNAMIC_DRAW;
  else
    usage = GL_STATIC_DRAW;

  if (object->vertex_array != 0)
    glDeleteVertexArrays(1, &object->vertex_array);

  glGenVertexArrays(1, &object->vertex_array);
  glBindVertexArray(object->vertex_array);

  glBindBuffer(GL_ARRAY_BUFFER, object->vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, usage);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, usage);

  void *offset = 0;
  for (u32 i = 0; i < object->shader.attributes.len; ++i) {
    GlassAttribute *attribute = object->shader.attributes.items + i;
    AttributeKindData *data = attrib_kinds_data + attribute->kind;

    glVertexAttribPointer(i, attribute->len, data->gl_kind,
                          GL_FALSE, object->shader.vertex_size, offset);
    glEnableVertexAttribArray(i);

    offset += attribute->len * data->size;
  }

  glBindVertexArray(0);
}

void glass_render_object(GlassObject *object) {
  glUseProgram(object->shader.program);
  glBindVertexArray(object->vertex_array);

  glDrawElements(GL_TRIANGLES, object->indices_count, GL_UNSIGNED_INT, NULL);
}
