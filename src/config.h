#ifndef CONFIG_H
#define CONFIG_H

extern "C" {
    #include <swc.h>
}

#include "screen.h"
#include "window.h"
#include "wm.h"



extern uint32_t border_width;
extern uint32_t border_color_active;
extern uint32_t border_color_normal;
extern int padding;

// Sets the default hotkeys
void setup_hotkeys();

// Initializes the linked layout list
void setup_layout();

#endif
