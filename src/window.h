#ifndef WINDOW_H
#define WINDOW_H

class Window {
public:
    struct swc_window * swc;
    Screen * screen;
    struct wl_list link;    
    Window(swc_window* swc, const swc_window_handler* window_handler){
        this->swc = swc;
        this->screen = NULL;
        swc_window_set_handler(swc, window_handler, this);
        swc_window_set_tiled(swc);
    }
};

#endif