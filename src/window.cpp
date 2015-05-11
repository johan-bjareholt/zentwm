#include "window.h"

#include <algorithm>

/*

	Commands

*/
void close_focused_window(void * data, uint32_t time, uint32_t value, uint32_t state){
    if (state == WL_KEYBOARD_KEY_STATE_RELEASED &&
        active_screen->current_workspace->focused_window != NULL)
        swc_window_close(active_screen->current_workspace->focused_window->swc);
}

void move_window_to_workspace(void * data, uint32_t time, uint32_t value, uint32_t state){
    if (state == WL_KEYBOARD_KEY_STATE_RELEASED &&
        active_screen->current_workspace->focused_window != NULL){

        Window* window_to_move = active_screen->current_workspace->focused_window;
        active_screen->current_workspace->remove_window(window_to_move);
        int* target_workspace = (int*) data;
        active_screen->workspaces[*target_workspace-1]->add_window(window_to_move);
    }
}

void make_focused_window_tiling(void * data, uint32_t time, uint32_t value, uint32_t state){
	Window* window = active_screen->current_workspace->focused_window;
	if (state == WL_KEYBOARD_KEY_STATE_RELEASED &&
		window != NULL){
		window->change_type(WINDOW_TILING);
	}
}

void make_focused_window_floating(void * data, uint32_t time, uint32_t value, uint32_t state){
	Window* window = active_screen->current_workspace->focused_window;
	if (state == WL_KEYBOARD_KEY_STATE_RELEASED &&
		window != NULL){
		window->change_type(WINDOW_FLOATING);
	}
}

void make_focused_window_static(void * data, uint32_t time, uint32_t value, uint32_t state){
	Window* window = active_screen->current_workspace->focused_window;
	if (state == WL_KEYBOARD_KEY_STATE_RELEASED &&
		window != NULL){
		window->change_type(WINDOW_STATIC);
	}
}

/*

	Window Handler hooks

*/

void window_destroy(void * data)
{
    Window * window = (Window *)data;
    delete window;
}

void window_entered(void * data)
{
    Window * window = (Window *)data;
    if (window)
        window->focus();
    else
        swc_window_focus(NULL);
}


/*

	Window class functions

*/

Window::Window(swc_window* swc, Workspace* workspace, const swc_window_handler* window_handler)
{
    this->swc = swc;
    this->workspace = workspace;
    // This sets both Workspace* and workspace_index
    swc_window_set_handler(this->swc, window_handler, this);
    swc_window_set_tiled(this->swc);
	this->type = WINDOW_TILING;
	this->workspace->add_window(this);
}

Window::~Window(){
	swc_window_hide(this->swc);
	if (this->workspace)
		this->workspace->remove_window(this);
}

void Window::focus()
{
	if (this->type != WINDOW_STATIC){
	    if (this->workspace->focused_window != nullptr)
	    {
	        swc_window_set_border(this->workspace->focused_window->swc,
	                              border_color_normal, border_width);
	    }
	    swc_window_set_border(this->swc, border_color_active, border_width);

    	if (this->workspace == active_screen->current_workspace){
    	    swc_window_focus(this->swc);
    	}
    	this->workspace->focused_window = this;
    	this->workspace->arrange();
	}
}

void Window::change_type(int type){
	// Deinitialize old type
	if (this->type == WINDOW_TILING){
		active_screen->current_workspace->remove_window(this);
	}
	else if (this->type == WINDOW_FLOATING){
		// Has yet to be implemented
	}
	else if (this->type == WINDOW_STATIC){
		swc_window_hide(this->swc);
	}

	// Set new type
	this->type = type;

	// Apply new type
	if (this->type == WINDOW_TILING){
		active_screen->current_workspace->add_window(this);
	}
	else if (this->type == WINDOW_FLOATING){
		// Has yet to be implemented
	}
	else if (this->type == WINDOW_STATIC){
		swc_window_show(this->swc);
	}
}

int Window::get_index(){
	return std::find(this->workspace->windows.begin(), this->workspace->windows.end(), this) - this->workspace->windows.begin();
}

bool Window::operator==(Window& other){
    bool result = false;
    if (this->swc == other.swc)
        result = true;
    return result;
}
