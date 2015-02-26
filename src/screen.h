#ifndef SCREEN_H
#define SCREEN_H

extern "C" {
	#include <swc.h>
}

class Screen;

#include "window.h"

void set_panelreserve(int);

class Screen {
	void (*arrangefunc)(Screen*);
public:
    struct swc_screen * swc;
    struct wl_list windows;
    unsigned num_windows;
    Screen(swc_screen* swc, const swc_screen_handler* screen_handler);
   	void add_window(Window* window);
   	void remove_window(Window* window);
   	void arrange();
};


#endif