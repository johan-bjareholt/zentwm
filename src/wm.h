#ifndef WM_H
#define WM_H

#include "screen.h"
#include "window.h"

extern Screen * active_screen;
extern Window * focused_window;
extern struct wl_display * display;
extern struct wl_event_loop * event_loop;

void focus(Window * window);
void screen_usable_geometry_changed(void * data);
void screen_entered(void * data);
void window_destroy(void * data);
void window_entered(void * data);

void new_screen(struct swc_screen * swc);
void new_window(struct swc_window * swc);

void spawn(void * data, uint32_t time, uint32_t value, uint32_t state);

void quit(void * data, uint32_t time, uint32_t value, uint32_t state);

void close_focused_window(void * data, uint32_t time, uint32_t value, uint32_t state);

#endif