#include "winx/winx.h"
#include "winx/event.h"
#include "glass.h"
#include "shapes.h"
#include "shl_log.h"
#include "shl_str.h"
#include "io.h"

bool process_event(WinxEvent *event, GlassShapes *shapes) {
  if (event->kind == WinxEventKindQuit) {
    return false;
  } else if (event->kind == WinxEventKindResize) {
    u32 width = event->as.resize.width;
    u32 height = event->as.resize.height;

    glass_resize_shapes(shapes, (f32) width, (f32) height);
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

  GlassShapes shapes = glass_init_shapes();
  glass_init_triangle(&shapes, vec2(0.0, window.height),
                      vec2(window.width / 2.0, 0.0),
                      vec2(window.width, window.height),
                      vec4(1.0, 0.0, 0.0, 1.0));
  glass_init_quad(&shapes, vec2(0.0, 0.0), vec2(50.0, 50.0),
                  vec4(0.0, 1.0, 0.0, 1.0));
  glass_init_circle(&shapes, vec2(50.0, 50.0), 50.0,
                    vec4(0.0, 0.0, 0.5, 1.0));

  bool is_running = true;
  while (is_running) {
    WinxEvent event;
    while ((event = winx_get_event(&window, false)).kind != WinxEventKindNone) {
      is_running = process_event(&event, &shapes);
      if (!is_running)
        break;
    }

    glass_clear_screen(0.1, 0.1, 0.1, 0.75);
    glass_render_shapes(&shapes);
    winx_draw(&window);
  }

  winx_destroy_window(&window);
  winx_cleanup(&winx);
  return 0;
}
