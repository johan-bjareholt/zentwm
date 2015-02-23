#include "window.h"

Window::Window(swc_window* swc, const swc_window_handler* window_handler)
{
    this->swc = swc;
    this->screen = NULL;
    swc_window_set_handler(swc, window_handler, this);
    swc_window_set_tiled(swc);
}