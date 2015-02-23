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



extern const uint32_t border_width;
extern const uint32_t border_color_active;
extern const uint32_t border_color_normal;

void setup_hotkeys();

#endif