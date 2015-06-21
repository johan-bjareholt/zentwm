#ifndef WINDOW_H
#define WINDOW_H

extern "C" {
	#include <swc.h>
}

class Window;

#include "workspace.h"
#include "screen.h"

// Commands
void close_focused_window(void * data, uint32_t time, uint32_t value, uint32_t state);
void move_window_to_workspace(void * data, uint32_t time, uint32_t value, uint32_t state);
void make_focused_window_tiling(void * data, uint32_t time, uint32_t value, uint32_t state);
void make_focused_window_floating(void * data, uint32_t time, uint32_t value, uint32_t state);
void make_focused_window_background(void * data, uint32_t time, uint32_t value, uint32_t state);
void move_window_begin(void * data, uint32_t time, uint32_t value, uint32_t state);
void move_window_end(void * data, uint32_t time, uint32_t value, uint32_t state);

// Window handler hooks
void window_destroy(void * data);
void window_entered(void * data);

// Window handler
const struct swc_window_handler window_handler = {
    .destroy = &window_destroy,
    .title_changed = NULL,
    .app_id_changed = NULL,
    .parent_changed = NULL,
    .entered = &window_entered,
    .move = NULL,
    .resize = NULL,
};

// Window types
const int WINDOW_TILING		= 0;
const int WINDOW_FLOATING	= 1;
const int WINDOW_BACKGROUND	= 2;

// Window class
class Window {
public:
	Workspace* workspace;
    struct swc_window * swc;
	int type;

	// Border colors
	uint32_t default_border_color;
	uint32_t current_border_color;

	/*
		Functions
	*/
    Window(swc_window* swc, Workspace*, const swc_window_handler* window_handler);
    ~Window();
	void focus();
	void change_type(int);
	void begin_move();
	void end_move();
	int get_index();
    bool operator==(Window&);
};

#endif
