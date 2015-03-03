#ifndef SCREEN_H
#define SCREEN_H

/*

	ToDo

	- screen_usable_geometry_changed isn't applied and tested with screen_handler
    - hiding windows from other workspaces is very dirty

*/

extern "C" {
	#include <swc.h>
}

class Screen;

#include "window.h"
#include "layout.h"
// Setup functions
void set_panelreserve(int);
void set_padding(int);

// Screen handler hooks
void screen_usable_geometry_changed(void * data);
void screen_entered(void * data);

// Screen handler
const swc_screen_handler screen_handler {
    .destroy = NULL,
    .geometry_changed = NULL,
    .usable_geometry_changed = &screen_usable_geometry_changed,
    .entered = &screen_entered,
};

// Screen class
class Screen {
    int num_workspace;
public:
    struct swc_screen * swc;
    Workspace* current_workspace;
    Workspace** workspaces;
    Screen(swc_screen* swc, const swc_screen_handler* screen_handler);
    ~Screen();
    // Since this is a pointer to any workspace, does it fit into the screen class?
    void change_workspace(int workspace_index);
    void change_workspace(Workspace*);
    bool operator==(Screen&);
};


#endif