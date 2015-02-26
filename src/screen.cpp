#include "wm.h"
#include "screen.h"
#include "layout.h"

void set_panelreserve(int px){
	struct swc_rectangle * screen_geometry = &active_screen->swc->usable_geometry;
	screen_geometry->y -= panelreservation;
	screen_geometry->height += panelreservation;
	panelreservation = px;
	screen_geometry->y += panelreservation;
	screen_geometry->height -= panelreservation;
}

void set_padding(int px){
	padding = px;
	active_screen->arrange();
}

/*

	Screen class functions

*/

Screen::Screen(swc_screen* swc, const swc_screen_handler* screen_handler)
{
	this->swc = swc;
	this->num_windows = 0;
	this->arrangefunc = &evenlayout;
	wl_list_init(&windows);
	swc_screen_set_handler(swc, screen_handler, this);
}

void Screen::add_window(Window* window)
{
	window->screen = this;
	wl_list_insert(&windows, &window->link);
	num_windows++;
	swc_window_show(window->swc);
	arrange();
}

void Screen::remove_window(Window* window)
{
    window->screen = NULL;
    wl_list_remove(&window->link);
    num_windows--;
    swc_window_hide(window->swc);
    arrange();
}

void Screen::arrange(){
	arrangefunc(this);
}