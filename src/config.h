#ifndef CONFIG_H
#define CONFIG_H

extern "C" {

    #include <stdlib.h>
    #include <swc.h>
    #include <unistd.h>
    #include <wayland-server.h>
    #include <xkbcommon/xkbcommon.h>

}

#include "screen.h"
#include "window.h"
#include "wm.h"



extern uint32_t border_width;
extern uint32_t border_color_active;
extern uint32_t border_color_normal;
extern int panelreservation;

void setup_hotkeys();

#endif