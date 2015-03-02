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
    Window * window = (Window *)data, * next_focus;
    window->workspace->focused_window = NULL;

    if (active_screen->current_workspace->focused_window == window)
    {
        /* Try to find a new focus nearby the old one. */
        next_focus = wl_container_of(window->link.next, window, link);

        if (&next_focus->link == &window->workspace->windows)
        {
            next_focus = wl_container_of(window->link.prev,
                                         window, link);

            if (&next_focus->link == &window->workspace->windows)
                next_focus = NULL;
        }
        // Needs to be added when proper c++ equivalent is implemented
        //focus(next_focus);
        next_focus->focus();
        //swc_window_focus(next_focus);
    }

    window->workspace->remove_window(window);
    free(window);
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
    this->workspace->add_window(this);
    swc_window_set_handler(swc, window_handler, this);
    swc_window_set_tiled(swc);
}

void Window::focus()
{
    if (active_screen->current_workspace->focused_window)
    {
        swc_window_set_border(active_screen->current_workspace->focused_window->swc,
                              border_color_normal, border_width);
    }

    swc_window_set_border(this->swc, border_color_active, border_width);
    swc_window_focus(this->swc);

    this->workspace->focused_window = this;
    active_screen->current_workspace = this->workspace;
}

bool Window::operator==(Window& other){
    bool result = false;
    if (this->swc == other.swc)
        result = true;
    return result;
}