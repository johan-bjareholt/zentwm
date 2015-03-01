#include "workspace.h"
#include "screen.h"

/*
	Commands
*/

void switch_workspace(void * data, uint32_t time, uint32_t value, uint32_t state){
    int* workspace_num = (int*)data;
    active_screen->change_workspace(*workspace_num);
}


void focus_next(void * data, uint32_t time, uint32_t value, uint32_t state){
	// Find current focused window
}

void next_layout(void * data, uint32_t time, uint32_t value, uint32_t state){
	if (state != WL_KEYBOARD_KEY_STATE_PRESSED)
		active_screen->current_workspace->next_layout();
}



/*
	Workspace class
*/

Workspace::Workspace(std::string name, Screen* screen){
	this->name = name;
	this->screen = screen;
	num_windows = 0;
	this->currentlayout = get_layout();
	wl_list_init(&windows);
}

void Workspace::add_window(Window* window){
	window->screen = this;
	wl_list_insert(&windows, &window->link);
	num_windows++;
	swc_window_show(window->swc);
	arrange();
}

void Workspace::remove_window(Window* window){
    window->screen = NULL;
    wl_list_remove(&window->link);
    num_windows--;
    swc_window_hide(window->swc);
    arrange();
}

void Workspace::arrange(){
	this->currentlayout->layoutfunc(this);
}

void Workspace::next_layout(){
	this->currentlayout = this->currentlayout->next;
	arrange();
}

void Workspace::hideAll(){
    // Initialize variables
    Window * window = NULL;
    struct swc_rectangle geometry;

    if (this->num_windows == 0) return;

    // Iterate over columns
    geometry.x = 10000;
    geometry.y = 10000;
    geometry.width = 0;
    geometry.height = 0;

    window = wl_container_of(this->windows.next, window, link);
    for (int window_index = 0; &window->link != &this->windows; window_index++)
    {
        // Apply window position and size
        swc_window_set_geometry(window->swc, &geometry);
        // Get next window
        window = wl_container_of(window->link.next, window, link);
    }
}