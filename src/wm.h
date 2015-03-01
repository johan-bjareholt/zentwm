#ifndef WM_H
#define WM_H

#include "screen.h"
#include "window.h"

// Global variables
extern Screen* active_screen;
extern Window* focused_window;
extern struct wl_display * display;
extern struct wl_event_loop * event_loop;

// Swc_manager hooks
void new_screen(struct swc_screen * swc);
void new_window(struct swc_window * swc);

// Swc manager
const struct swc_manager manager = { 
	&new_screen, 
	&new_window
};

// Main function
int main(int, char**);

// Quit command
void quit(void * data, uint32_t time, uint32_t value, uint32_t state);

#endif