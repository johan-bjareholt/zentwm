#include <xkbcommon/xkbcommon.h>

#include "config.h"
#include "util.h"
#include "layout.h"

uint32_t border_width = 1;
uint32_t border_color_active = 0xff333388;
uint32_t border_color_normal = 0xff888888;

int panelreservation = 0;
int padding=0;

static const char * terminal_command[] = { "st-wl", NULL };
static const char * dmenu_command[] = { "dmenu_run-wl", NULL };
static int workspaces[] = {1,2,3,4,5,6,7,8,9,10};

void setup_hotkeys(){
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_q,
                    &close_focused_window, NULL);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_Return,
                    &spawn, terminal_command);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_r,
                    &spawn, dmenu_command);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_Escape,
                    &quit, NULL);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_space,
    				&next_layout, NULL);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_Tab,
                    &focus_next, NULL);

    // Workspace
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_1,
                    &switch_workspace, &workspaces[0]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_2,
                    &switch_workspace, &workspaces[1]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_3,
                    &switch_workspace, &workspaces[2]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_4,
                    &switch_workspace, &workspaces[3]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_5,
                    &switch_workspace, &workspaces[4]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_6,
                    &switch_workspace, &workspaces[5]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_7,
                    &switch_workspace, &workspaces[6]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_8,
                    &switch_workspace, &workspaces[7]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_9,
                    &switch_workspace, &workspaces[8]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_0,
                    &switch_workspace, &workspaces[9]);
}

void setup_layout() {
    // Reserve space for panel
    set_panelreserve(20);
    // Adds padding to layout
    set_padding(5);

    // Add available layouts
	add_layout(masterslavelayout);
	add_layout(evenlayout);
}