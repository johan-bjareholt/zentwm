#include "window.h"

/*

	Commands

*/
void close_focused_window(void * data, uint32_t time, uint32_t value, uint32_t state){
    if (state != WL_KEYBOARD_KEY_STATE_PRESSED &&
        active_screen->current_workspace->focused_window != NULL)
        swc_window_close(active_screen->current_workspace->focused_window->swc);
}


/*

	Window Handler hooks

*/

void window_destroy(void * data)
{
    Window * window = (Window *)data;
    window->workspace->remove_window(window);
    delete window;
}

void window_entered(void * data)
{
    Window * window = (Window *)data;
    if (window){
        window->focus();

    }
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
    this->workspace->add_window(this);
    swc_window_set_handler(swc, window_handler, this);
    swc_window_set_tiled(swc);
}

void Window::focus()
{
    if (this->workspace->focused_window != nullptr)
    {
        swc_window_set_border(this->workspace->focused_window->swc,
                              border_color_normal, border_width);
    }
    swc_window_set_border(this->swc, border_color_active, border_width);
    swc_window_focus(this->swc);
    active_screen->current_workspace = this->workspace;
    this->workspace->focused_window = this;
    this->workspace->arrange();
}

bool Window::operator==(Window& other){
    bool result = false;
    if (this->swc == other.swc)
        result = true;
    return result;
}