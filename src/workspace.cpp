#include "workspace.h"
#include "screen.h"

#include <algorithm>
#include <iostream>

/*
	Commands
*/

void switch_workspace(void * data, uint32_t time, uint32_t value, uint32_t state){
    int* workspace_num = (int*)data;
    active_screen->change_workspace(*workspace_num);
}


void focus_next(void * data, uint32_t time, uint32_t value, uint32_t state){
    if (state == WL_KEYBOARD_KEY_STATE_RELEASED)
        active_screen->current_workspace->focus_next();
}

void next_layout(void * data, uint32_t time, uint32_t value, uint32_t state){
	if (state == WL_KEYBOARD_KEY_STATE_RELEASED)
		active_screen->current_workspace->next_layout();
}



/*
	Workspace class
*/

Workspace::Workspace(std::string name, Screen* screen){
	this->name = name;
	this->screen = screen;
	this->currentlayout = get_layout();
    this->focused_window = nullptr;
}


/*

    Window Handling

*/

void Workspace::add_window(Window* window){
    window->workspace = this;
    if (window->type == WINDOW_TILING)
        windows_tiling.push_back(window);
    else if (window->type == WINDOW_FLOATING)
        windows_floating.push_back(window);
    if (active_screen->current_workspace == this){
       swc_window_show(window->swc);
    }
    window->focus();
	arrange();
}

void Workspace::remove_window(Window* window){
    // Get window index of the window type
    int window_index = this->get_index(window);
    std::vector<Window*>* container = nullptr;
    if (window->type == WINDOW_TILING){
        container = &windows_tiling;
    }
    else if (window->type == WINDOW_FLOATING){
        container = &windows_floating;
        window_index -= windows_tiling.size();
    }
    // Remove it from the workspace
    container->erase(window_index+container->begin());

    swc_window_hide(window->swc); // Hide window until it is added onto another workspace
	this->focus_next();           // Focus next window in the workspace, to avoid crashing the wm
    window->workspace = NULL;     // Unassign the window from the workspace
    arrange();                    // Rearrange the windows so empty space gets reserved by the other windows
}

void Workspace::show_all(){
    // Initialize variables
    if (this->windows_tiling.size() == 0) return;
    // Show all tiling windows
    for (int i=0; i<(int)this->windows_tiling.size(); i++)
        swc_window_show(this->windows_tiling[i]->swc);
    // Show all floating windows
    for (int i=0; i<(int)this->windows_floating.size(); i++)
        swc_window_show(this->windows_floating[i]->swc);
}

void Workspace::hide_all(){
    // Initialize variables
    if (this->windows_tiling.size() == 0) return;
    // Hide all tiling windows
    for (int i=0; i<(int)this->windows_tiling.size(); i++)
        swc_window_hide(this->windows_tiling[i]->swc);
    // Hide all floating windows
    for (int i=0; i<(int)this->windows_floating.size(); i++)
        swc_window_hide(this->windows_floating[i]->swc);
}

Window* Workspace::focus_next(){
    Window* window=nullptr;
    if (this->windows_tiling.size() > 0){
        if (this->focused_window != nullptr && this->focused_window->get_index() >= (int)this->windows_tiling.size()-1)
            window = this->windows_tiling[0];
        else
            window = this->windows_tiling[this->focused_window->get_index()+1];

        if (window != nullptr)
            window->focus();
        else
            this->focused_window = nullptr;
    }
    else {
        // If there are no windows in the workspace, unfocus
        swc_window_focus(NULL);
        this->focused_window = nullptr;
    }
    return window;
}

Window* Workspace::get_window(int index){
    Window* window;
    if (index < (int)windows_tiling.size())
        window = windows_tiling[index];
    else
        window = windows_floating[index - windows_tiling.size()];
    return window;
}

int Workspace::get_index(Window* window){
    std::vector<Window*>* container = nullptr;
    int index = 0;
    if (window->type == WINDOW_TILING){
        container = &this->windows_tiling;
    }
    if (window->type == WINDOW_FLOATING){
        container = &this->windows_floating;
        index += windows_tiling.size();
    }
    index += std::find(container->begin(), container->end(), window) - container->begin();
    return index;
}

int Workspace::count(){
	return windows_tiling.size() + windows_floating.size();
}

int Workspace::count_tiling(){
	return windows_tiling.size();
}



/*

    Layout handling

*/

void Workspace::arrange(){
	this->currentlayout->layoutfunc(this);
}

void Workspace::next_layout(){
	this->currentlayout = this->currentlayout->next;
    this->show_all();
	this->arrange();
}
