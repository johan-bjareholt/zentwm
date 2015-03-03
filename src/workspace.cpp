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
    if (state != WL_KEYBOARD_KEY_STATE_PRESSED)
        active_screen->current_workspace->focus_next();
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
	this->currentlayout = get_layout();
    this->focused_window = nullptr;
}

void Workspace::add_window(Window* window){
    window->workspace_index = windowsv.size();
    windowsv.push_back(window);
    if (active_screen->current_workspace == this){
	   swc_window_show(window->swc);
       window->focus();
    }
	arrange();
}

void Workspace::remove_window(Window* window){
    window->workspace = NULL;
    windowsv.erase(windowsv.begin()+window->workspace_index);
    for (int i=window->workspace_index; i<(int)windowsv.size(); i++)
        windowsv[i]->workspace_index--;
    swc_window_hide(window->swc);
    this->focus_next();
    arrange();
}

void Workspace::arrange(){
	this->currentlayout->layoutfunc(this);
}

Window* Workspace::focus_next(){
    Window* window=nullptr;
    if (this->windowsv.size() > 0){
        if (this->focused_window->workspace_index >= (int)this->windowsv.size()-1)
            window = this->windowsv[0];
        else
            window = this->windowsv[this->focused_window->workspace_index+1];

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
	arrange();
}

void Workspace::showAll(){
    // Initialize variables
    if (this->windowsv.size() == 0) return;

    for (int i=0; i<(int)this->windowsv.size(); i++)
        swc_window_show(this->windowsv[i]->swc);    
}

void Workspace::hideAll(){
    // Initialize variables
    if (this->windowsv.size() == 0) return;

    for (int i=0; i<(int)this->windowsv.size(); i++)
        swc_window_hide(this->windowsv[i]->swc);
}