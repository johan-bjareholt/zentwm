#include "wm.h"
#include "screen.h"
#include "layout.h"

/*

	Setup functions

*/

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

	Commands

*/
void next_layout(void * data, uint32_t time, uint32_t value, uint32_t state){
	if (state != WL_KEYBOARD_KEY_STATE_PRESSED)
		active_screen->next_layout();
}

/*

	Screen handler hooks

*/

void screen_usable_geometry_changed(void * data)
{
    Screen * screen = (Screen*)data;

    /* If the usable geometry of the screen changes, for example when a panel is
     * docked to the edge of the screen, we need to rearrange the windows to
     * ensure they are all within the new usable geometry. */
    screen->arrange();
}

void screen_entered(void * data)
{
    Screen * screen = (Screen*)data;

    active_screen = screen;
}


/*

	Screen class functions

*/

Screen::Screen(swc_screen* swc, const swc_screen_handler* screen_handler)
{
	this->swc = swc;
	this->num_windows = 0;
	this->currentlayout = get_layout();
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
	this->currentlayout->layoutfunc(this);
}

void Screen::next_layout(){
	this->currentlayout = this->currentlayout->next;
	arrange();
}