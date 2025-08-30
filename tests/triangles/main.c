#include "winx/src/winx.h"
#include "winx/src/event.h"
#include "glass.h"
#include "shl_log.h"
#include "shl_str.h"

static Str triangle_vertex_shader = STR_LIT(
  "#version 330 core\n"
  "layout (location = 0) in vec3 i_pos;\n"
  "void main(void) {\n"
  "  gl_Position = vec4(i_pos.x, i_pos.y, i_pos.z, 1.0);\n"
  "}\n"
);

static Str triangle_fragment_shader = STR_LIT(
  "#version 330 core\n"
  "out vec4 frag_color;\n"
  "void main(void) {\n"
  "  frag_color = vec4(1.0, 0.5, 0.2, 1.0);\n"
  "}\n"
);

static f32 vertices0[] = {
  -1.0, -1.0, 0.0,
   0.0,  0.0, 0.0,
   1.0, -1.0, 0.0,
};

static u32 indices0[] = {
  0, 1, 2,
};

static f32 vertices1[] = {
  -1.0,  1.0, 0.0,
   1.0, 1.0, 0.0,
   0.0,  0.0, 0.0,
};

static u32 indices1[] = {
  0, 1, 2,
};

bool process_event(WinxEvent *event) {
  if (event->kind == WinxEventKindQuit) {
    return false;
  } else if (event->kind == WinxEventKindResize) {
    glass_resize(event->as.resize.width,
                 event->as.resize.height);
  }

  return true;
}

int main(void) {
  Winx winx = winx_init();
  WinxWindow window = winx_init_window(&winx, STR_LIT("Glass test"),
                                       640, 480, WinxGraphicsModeOpenGL,
                                       NULL);
  glass_init();

  GlassAttributes attributes = {0};
  glass_push_attribute(&attributes, GlassAttributeKindFloat, 3);
  GlassShader shader = glass_init_shader(triangle_vertex_shader,
                                         triangle_fragment_shader,
                                         &attributes);

  GlassObject triangle0 = glass_init_object(&shader);
  glass_put_object_data(&triangle0, vertices0,
                        sizeof(vertices0), indices0,
                        sizeof(indices0), 3, false);

  GlassObject triangle1 = glass_init_object(&shader);
  glass_put_object_data(&triangle1, vertices1,
                        sizeof(vertices1), indices1,
                        sizeof(indices1), 3, false);

  bool is_running = true;
  while (is_running) {
    WinxEvent event;
    while ((event = winx_get_event(&window, false)).kind != WinxEventKindNone) {
      is_running = process_event(&event);
      if (!is_running)
        break;
    }

    glass_clear_screen(0.0, 0.0, 0.0, 0.5);
    glass_render_object(&triangle0);
    glass_render_object(&triangle1);
    winx_draw(&window);
  }

  winx_destroy_window(&window);
  winx_cleanup(&winx);
  return 0;
}
