extern "C" {
    #include <swc.h>
}
#include <wayland-server.h>

#include "wm.h"
#include "config.h"


Screen * active_screen;
Window * focused_window;
struct wl_display * display;
struct wl_event_loop * event_loop;


void new_screen(struct swc_screen * swc)
{
    Screen * screen = new Screen(swc, &screen_handler);
    active_screen = screen;
}

void new_window(struct swc_window * swc)
{
    Window * window;

    window = new Window(swc, &window_handler);

    active_screen->current_workspace->add_window(window);
    focus(window);
}


// Main function
int main(int argc, char * argv[])
{
    /*
        Initialize graphics and display
    */
    display = wl_display_create();
    if (!display)
        return EXIT_FAILURE;
    if (wl_display_add_socket(display, NULL) != 0)
        return EXIT_FAILURE;
    if (!swc_initialize(display, NULL, &manager))
        return EXIT_FAILURE;


    /*
        Setup configuration
    */

    // Reserve space for panel
    set_panelreserve(20);
    // Adds padding to layout
    set_padding(5);
    // Add hotkeys
    setup_hotkeys();
    // setup layout
    setup_layouts();

    // Get events
    event_loop = wl_display_get_event_loop(display);
    // Start session
    wl_display_run(display);
    // Destroy session after termination signal
    wl_display_destroy(display);

    return EXIT_SUCCESS;
}

// Quit command
void quit(void * data, uint32_t time, uint32_t value, uint32_t state)
{
    if (state != WL_KEYBOARD_KEY_STATE_PRESSED)
        return;

    wl_display_terminate(display);
}
