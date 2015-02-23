#include "config.h"

const uint32_t border_width = 1;
const uint32_t border_color_active = 0xff333388;
const uint32_t border_color_normal = 0xff888888;

static const char * terminal_command[] = { "st-wl", NULL };
static const char * dmenu_command[] = { "dmenu_run-wl", NULL };

void setup_hotkeys(){
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_q,
                    &close_focused_window, NULL);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_Return,
                    &spawn, terminal_command);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_r,
                    &spawn, dmenu_command);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_Escape,
                    &quit, NULL);
}