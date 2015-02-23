#ifndef CONFIG_H
#define CONFIG_H

#include "screen.h"
#include "window.h"



extern const uint32_t border_width;
extern const uint32_t border_color_active;
extern const uint32_t border_color_normal;

extern Screen * active_screen;
extern Window * focused_window;
extern struct wl_display * display;
extern struct wl_event_loop * event_loop;

#endif