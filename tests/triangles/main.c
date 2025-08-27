#include "winx/src/winx.h"
#include "winx/src/event.h"
#include "glass.h"
#include "shl_log.h"
#include "shl_str.h"
#include "io.h"

bool process_event(WinxEvent *event) {
  if (event->kind == WinxEventKindQuit) {
    return false;
  } else if (event->kind == WinxEventKindResize) {
    glass_resize(event->as.resize.width,
                 event->as.resize.height);
  }

  return true;
}

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

int main(void) {
  Winx winx = winx_init();
  WinxWindow window = winx_init_window(&winx, STR_LIT("Glass test"),
                                       640, 480, WinxGraphicsModeOpenGL,
                                       NULL);
  glass_init();

  Str vertex_shader_str = read_file("tests/triangles/shaders/default-vertex.glsl");
  Str fragment_shader_str = read_file("tests/triangles/shaders/default-fragment.glsl");

  GlassAttributes attributes = {0};
  glass_push_attribute(&attributes, GlassAttributeKindFloat, 3);
  GlassShader shader = glass_init_shader(vertex_shader_str,
                                         fragment_shader_str,
                                         &attributes);

  GlassObject triangle0 = glass_init_object(vertices0, sizeof(vertices0), 3,
                                            indices0, sizeof(indices0),
                                            ARRAY_LEN(indices0),
                                            shader, false);
  GlassObject triangle1 = glass_init_object(vertices1, sizeof(vertices1), 3,
                                            indices1, sizeof(indices1),
                                            ARRAY_LEN(indices1),
                                            shader, false);

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
