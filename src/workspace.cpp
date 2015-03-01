#include "workspace.h"
#include "screen.h"


void switch_workspace(void * data, uint32_t time, uint32_t value, uint32_t state){
    int* workspace_num = (int*)data;
    active_screen->change_workspace(*workspace_num);
}


Workspace::Workspace(std::string name, Screen* screen){
	this->name = name;
	this->screen = screen;
	num_windows = 0;
	wl_list_init(&windows);
}

void Workspace::add_window(Window* window){
	window->screen = this;
	wl_list_insert(&windows, &window->link);
	num_windows++;
	swc_window_show(window->swc);
	screen->arrange();
}

void Workspace::remove_window(Window* window){
    window->screen = NULL;
    wl_list_remove(&window->link);
    num_windows--;
    swc_window_hide(window->swc);
    screen->arrange();
}