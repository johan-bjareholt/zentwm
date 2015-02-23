#include "config.h"

const uint32_t border_width = 1;
const uint32_t border_color_active = 0xff333388;
const uint32_t border_color_normal = 0xff888888;

Screen * active_screen;
Window * focused_window;
struct wl_display * display;
struct wl_event_loop * event_loop;