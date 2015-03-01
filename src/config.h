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
extern int panelreservation;
extern int padding;

void setup_hotkeys();

void setup_layout();

#endif