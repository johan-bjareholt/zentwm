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
    if (state == WL_KEYBOARD_KEY_STATE_PRESSED)
        active_screen->current_workspace->focus_next();
}

void next_layout(void * data, uint32_t time, uint32_t value, uint32_t state){
	if (state == WL_KEYBOARD_KEY_STATE_PRESSED)
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

void Workspace::add_window(Window* window){
    window->workspace = this;
    windows.push_back(window);
    if (active_screen->current_workspace == this){
       swc_window_show(window->swc);
    }
    window->focus();
	arrange();
}

void Workspace::remove_window(Window* window){
    windows.erase(windows.begin()+window->getWorkspaceIndex());
    swc_window_hide(window->swc);
	this->focus_next();
    window->workspace = NULL;
    arrange();
}

void Workspace::arrange(){
	this->currentlayout->layoutfunc(this);
}

Window* Workspace::focus_next(){
    Window* window=nullptr;
    if (this->windows.size() > 0){
        if (this->focused_window->getWorkspaceIndex() >= (int)this->windows.size()-1)
            window = this->windows[0];
        else
            window = this->windows[this->focused_window->getWorkspaceIndex()+1];

        if (window != nullptr)
            window->focus();
        else
            this->focused_window = nullptr;
    }
    else {
        swc_window_focus(NULL);
        this->focused_window = nullptr;
    }
    return window;
}

void Workspace::next_layout(){
	this->currentlayout = this->currentlayout->next;
    this->showAll();
	this->arrange();
}

void Workspace::showAll(){
    // Initialize variables
    if (this->windows.size() == 0) return;

    for (int i=0; i<(int)this->windows.size(); i++)
        swc_window_show(this->windows[i]->swc);    
}

void Workspace::hideAll(){
    // Initialize variables
    if (this->windows.size() == 0) return;

    for (int i=0; i<(int)this->windows.size(); i++)
        swc_window_hide(this->windows[i]->swc);
}

int Workspace::count(){
	return windows.size();
}

int Workspace::count_tiling(){
	int count = 0;
	for (int i=0; i<this->count(); i++){
		if (windows[i]->type == WINDOW_TILING)
			count++;
	}
	return count++;
}
