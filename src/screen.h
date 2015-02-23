#ifndef SCREEN_H
#define SCREEN_H

extern "C" {
	#include <swc.h>
}

class Screen {
public:
    struct swc_screen * swc;
    struct wl_list windows;
    unsigned num_windows;
    Screen(swc_screen* swc, const swc_screen_handler* screen_handler){
        this->swc = swc;
        this->num_windows = 0;
        wl_list_init(&windows);
        swc_screen_set_handler(swc, screen_handler, this);
    }
};


#endif