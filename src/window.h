#ifndef WINDOW_H
#define WINDOW_H

extern "C" {
	#include <swc.h>
}

class Window;

#include "screen.h"

class Window {
public:
    struct swc_window * swc;
    Screen* screen;
    struct wl_list link;    
    Window(swc_window* swc, const swc_window_handler* window_handler);
};

#endif