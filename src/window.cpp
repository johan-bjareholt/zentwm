#include "window.h"

/*

	Commands

*/
void close_focused_window(void * data, uint32_t time, uint32_t value, uint32_t state){
    if (state != WL_KEYBOARD_KEY_STATE_PRESSED &&
        focused_window != NULL)
        swc_window_close(focused_window->swc);
}


/*

	Window Handler hooks

*/

void focus(Window * window)
{
    if (focused_window)
    {
        swc_window_set_border(focused_window->swc,
                              border_color_normal, border_width);
    }

    if (window)
    {
        swc_window_set_border(window->swc, border_color_active, border_width);
        swc_window_focus(window->swc);
    }
    else
        swc_window_focus(NULL);

    focused_window = window;
}

void window_destroy(void * data)
{
    Window * window = (Window *)data, * next_focus;

    if (focused_window == window)
    {
        /* Try to find a new focus nearby the old one. */
        next_focus = wl_container_of(window->link.next, window, link);

        if (&next_focus->link == &window->screen->windows)
        {
            next_focus = wl_container_of(window->link.prev,
                                         window, link);

            if (&next_focus->link == &window->screen->windows)
                next_focus = NULL;
        }

        focus(next_focus);
    }

    window->screen->remove_window(window);
    free(window);
}

void window_entered(void * data)
{
    Window * window = (Window *)data;

    focus(window);
}


/*

	Window class functions

*/

Window::Window(swc_window* swc, const swc_window_handler* window_handler)
{
    this->swc = swc;
    this->screen = NULL;
    swc_window_set_handler(swc, window_handler, this);
    swc_window_set_tiled(swc);
}

bool Window::operator==(Window& other){
    bool result = false;
    if (this->swc == other.swc)
        result = true;
    return result;
}