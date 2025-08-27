#include "shl_log.h"

#include "winx/src/winx.h"
#include "winx/src/event.h"
#include "glass.h"
#include "params.h"
#define STBI_NO_LINEAR
#define STBI_NO_HDR
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shl_str.h"
#include "io.h"

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

static Str texture_vertex_shader = STR_LIT(
  "#version 330 core\n"
  "uniform vec2 u_resolution;\n"
  "layout (location = 0) in vec2 i_pos;\n"
  "layout (location = 1) in vec2 i_uv;"
  "out vec2 o_uv;\n"
  "void main(void) {\n"
  "  float x = i_pos.x / u_resolution.x * 2.0 - 1.0;\n"
  "  float y = 1.0 - i_pos.y / u_resolution.y * 2.0;\n"
  "  gl_Position = vec4(x, y, 0.0, 1.0);\n"
  "  o_uv = i_uv;\n"
  "}\n"
);

static Str texture_fragment_shader = STR_LIT(
  "#version 330 core\n"
  "uniform sampler2D u_texture;\n"
  "in vec2 o_uv;\n"
  "out vec4 frag_color;\n"
  "void main(void) {\n"
  "  frag_color = texture(u_texture, o_uv);\n"
  "}\n"
);

u32 get_texture_object_vertices(Vec2 **vertices, u32 window_width, u32 window_height) {
  if (*vertices)
    free(*vertices);

  u32 size = 8 * sizeof(Vec2);

  *vertices = malloc(size);
  (*vertices)[0] = vec2(0.0, 0.0);
  (*vertices)[1] = vec2(0.0, 0.0);
  (*vertices)[2] = vec2((f32) window_width, 0.0);
  (*vertices)[3] = vec2(1.0, 0.0);
  (*vertices)[4] = vec2(0.0, (f32) window_height);
  (*vertices)[5] = vec2(0.0, 1.0);
  (*vertices)[6] = vec2((f32) window_width, (f32) window_height);
  (*vertices)[7] = vec2(1.0, 1.0);

  return size;
}

bool process_event(WinxEvent *event, GlassObject *object,
                   GlassShader *shader, Vec2 **vertices) {
  if (event->kind == WinxEventKindQuit) {
    return false;
  } else if (event->kind == WinxEventKindResize) {
    u32 width = event->as.resize.width;
    u32 height = event->as.resize.height;

    u32 vertices_size = get_texture_object_vertices(vertices, (f32) width, (f32) height);
    u32 indices[] = { 0, 1, 2, 2, 1, 3 };

    glass_object_put_data(object, *vertices, vertices_size,
                          indices, sizeof(indices), 6, false);

    glass_set_param_2f(shader, "u_resolution",
                       vec2((f32) width, (f32) height));

    glass_resize(width, height);
  }

  return true;
}

int main(void) {
  Winx winx = winx_init();
  WinxWindow window = winx_init_window(&winx, STR_LIT("Glass test"),
                                       640, 480, WinxGraphicsModeOpenGL,
                                       NULL);
  glass_init();

  i32 width, height;
  u8 *texture_data = stbi_load("tests/textures/textures/test-texture.jpg",
                               &width, &height, NULL, 4);

  GlassTexture texture = glass_init_texture(texture_data, (u32) width, (u32) height,
                                            GlassTextureFilteringModeNearest);

  stbi_image_free(texture_data);

  GlassAttributes attributes = {0};
  glass_push_attribute(&attributes, GlassAttributeKindFloat, 2);
  glass_push_attribute(&attributes, GlassAttributeKindFloat, 2);

  GlassShader texture_shader = glass_init_shader(texture_vertex_shader,
                                                 texture_fragment_shader,
                                                 &attributes);
  glass_set_param_2f(&texture_shader, "u_resolution",
                     vec2(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT));
  glass_set_param_1i(&texture_shader, "u_texture", 0);

  Vec2 *texture_vertices = NULL;
  u32 texture_vertices_size = get_texture_object_vertices(&texture_vertices,
                                                          DEFAULT_WINDOW_WIDTH,
                                                          DEFAULT_WINDOW_HEIGHT);
  u32 texture_indices[] = { 0, 1, 2, 2, 1, 3 };

  GlassObject texture_object = glass_init_object(&texture_shader);
  glass_object_put_data(&texture_object, texture_vertices, texture_vertices_size,
                        texture_indices, sizeof(texture_indices), 6, false);
  glass_push_texture(&texture_object, &texture);

  bool is_running = true;
  while (is_running) {
    WinxEvent event;
    while ((event = winx_get_event(&window, false)).kind != WinxEventKindNone) {
      is_running = process_event(&event, &texture_object,
                                 &texture_shader, &texture_vertices);
      if (!is_running)
        break;
    }

    glass_clear_screen(0.1, 0.1, 0.1, 0.75);
    glass_render_object(&texture_object);
    winx_draw(&window);
  }

  winx_destroy_window(&window);
  winx_cleanup(&winx);
  return 0;
}
