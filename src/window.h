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

// Window handler hooks
void window_destroy(void * data);
void window_entered(void * data);

// Window handler
const struct swc_window_handler window_handler = {
    .destroy = &window_destroy,
    .title_changed = NULL,
    .appid_changed = NULL,
    .parent_changed = NULL,
    .entered = &window_entered,
    .move = NULL,
    .resize = NULL,
};

// Window class
class Window {
public:
    struct swc_window * swc;
    Workspace* workspace;
    struct wl_list link;    

    Window(swc_window* swc, Workspace*, const swc_window_handler* window_handler);
    void focus();
    bool operator==(Window&);
};

#endif