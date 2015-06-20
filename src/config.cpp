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
static const char * dmenu_command[] = { "dmenu_run", NULL };
static int workspaces[] = {1,2,3,4,5,6,7,8,9,10};

void setup_hotkeys(){
	/*
		Sets the default hotkeys
	*/

    // Close focused window, SUPER+Q
	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_q,
                    &close_focused_window, NULL);
	// Open terminal, SUPER+Enter
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_Return,
                    &spawn, terminal_command);
	// Open dmenu, SUPER+r
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_r,
                    &spawn, dmenu_command);
	// Kill zentwm, SUPER+SHIFT+Esc
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO|SWC_MOD_SHIFT, XKB_KEY_Escape,
                    &quit, NULL);
	// Change layout, SUPER+Space
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_space,
    				&next_layout, NULL);
	// Focus next window, SUPER+Tab
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_Tab,
                    &focus_next, NULL);

	// Changing window types
	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_z,
					&make_focused_window_tiling, NULL);
	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_x,
					&make_focused_window_floating, NULL);
	swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO, XKB_KEY_c,
					&make_focused_window_background, NULL);

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

    // Moving windows between workspaces
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO|SWC_MOD_SHIFT, XKB_KEY_1,
                    &move_window_to_workspace, &workspaces[0]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO|SWC_MOD_SHIFT, XKB_KEY_2,
                    &move_window_to_workspace, &workspaces[1]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO|SWC_MOD_SHIFT, XKB_KEY_3,
                    &move_window_to_workspace, &workspaces[2]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO|SWC_MOD_SHIFT, XKB_KEY_4,
                    &move_window_to_workspace, &workspaces[3]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO|SWC_MOD_SHIFT, XKB_KEY_5,
                    &move_window_to_workspace, &workspaces[4]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO|SWC_MOD_SHIFT, XKB_KEY_6,
                    &move_window_to_workspace, &workspaces[5]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO|SWC_MOD_SHIFT, XKB_KEY_7,
                    &move_window_to_workspace, &workspaces[6]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO|SWC_MOD_SHIFT, XKB_KEY_8,
                    &move_window_to_workspace, &workspaces[7]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO|SWC_MOD_SHIFT, XKB_KEY_9,
                    &move_window_to_workspace, &workspaces[8]);
    swc_add_binding(SWC_BINDING_KEY, SWC_MOD_LOGO|SWC_MOD_SHIFT, XKB_KEY_0,
                    &move_window_to_workspace, &workspaces[9]);
}

void setup_layout() {
	/*
		Initializes the linked layout list
	*/

    // Adds padding to layout
    set_padding(5);

    // Add available layouts
	add_layout(masterslavelayout);
    add_layout(fulllayout);
	add_layout(evenlayout);
}
