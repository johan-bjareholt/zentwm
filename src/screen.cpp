#include "screen.h"
#include "layout.h"

Screen::Screen(swc_screen* swc, const swc_screen_handler* screen_handler){
        this->swc = swc;
        this->num_windows = 0;
        wl_list_init(&windows);
        swc_screen_set_handler(swc, screen_handler, this);
    }
void Screen::add_window(Window* window)
{
	window->screen = this;
	wl_list_insert(&windows, &window->link);
	num_windows++;
	swc_window_show(window->swc);
	arrange(this);
}