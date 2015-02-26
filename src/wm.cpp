extern "C" {

    #include <stdlib.h>
    #include <swc.h>
    #include <unistd.h>
    #include <wayland-server.h>
    #include <xkbcommon/xkbcommon.h>

}

#include "wm.h"
#include "config.h"
#include "screen.h"
#include "window.h"


Screen * active_screen;
Window * focused_window;
struct wl_display * display;
struct wl_event_loop * event_loop;


void focus(Window * window)
{
    if (focused_window)
    {
        swc_window_set_border(focused_window->swc,
                              border_color_normal, border_width);
    }

    if (window)
    {
        swc_window_set_border(window->swc, border_color_active, border_width);
        swc_window_focus(window->swc);
    }
    else
        swc_window_focus(NULL);

    focused_window = window;
}

void screen_usable_geometry_changed(void * data)
{
    Screen * screen = (Screen*)data;

    /* If the usable geometry of the screen changes, for example when a panel is
     * docked to the edge of the screen, we need to rearrange the windows to
     * ensure they are all within the new usable geometry. */
    screen->arrange();
}

void screen_entered(void * data)
{
    Screen * screen = (Screen*)data;

    active_screen = screen;
}

const swc_screen_handler screen_handler {
    .destroy = NULL,
    .geometry_changed = NULL,
    .usable_geometry_changed = &screen_usable_geometry_changed,
    .entered = &screen_entered,
};

void window_destroy(void * data)
{
    Window * window = (Window *)data, * next_focus;

    if (focused_window == window)
    {
        /* Try to find a new focus nearby the old one. */
        next_focus = wl_container_of(window->link.next, window, link);

        if (&next_focus->link == &window->screen->windows)
        {
            next_focus = wl_container_of(window->link.prev,
                                         window, link);

            if (&next_focus->link == &window->screen->windows)
                next_focus = NULL;
        }

        focus(next_focus);
    }

    window->screen->remove_window(window);
    free(window);
}

void window_entered(void * data)
{
    Window * window = (Window *)data;

    focus(window);
}

const struct swc_window_handler window_handler = {
    .destroy = &window_destroy,
    .title_changed = NULL,
    .appid_changed = NULL,
    .parent_changed = NULL,
    .entered = &window_entered,
    .move = NULL,
    .resize = NULL,
};


void new_screen(struct swc_screen * swc)
{
    Screen * screen = new Screen(swc, &screen_handler);
    active_screen = screen;
}

void new_window(struct swc_window * swc)
{
    Window * window;

    window = new Window(swc, &window_handler);

    active_screen->add_window(window);
    focus(window);
}

const struct swc_manager manager = { &new_screen, &new_window };

void spawn(void * data, uint32_t time, uint32_t value, uint32_t state)
{
    char * const * command = (char * const *)data;

    if (state != WL_KEYBOARD_KEY_STATE_PRESSED)
        return;

    if (fork() == 0)
    {
        execvp(command[0], command);
        exit(EXIT_FAILURE);
    }
}

void quit(void * data, uint32_t time, uint32_t value, uint32_t state)
{
    if (state != WL_KEYBOARD_KEY_STATE_PRESSED)
        return;

    wl_display_terminate(display);
}

// Should i keep this function?
void close_focused_window(void * data, uint32_t time, uint32_t value, uint32_t state){
    if (state != WL_KEYBOARD_KEY_STATE_PRESSED &&
        focused_window != NULL)
        swc_window_close(focused_window->swc);
}

int main(int argc, char * argv[])
{
    display = wl_display_create();

    if (!display)
        return EXIT_FAILURE;
    if (wl_display_add_socket(display, NULL) != 0)
        return EXIT_FAILURE;
    if (!swc_initialize(display, NULL, &manager))
        return EXIT_FAILURE;

    // Reserve space for panel
    set_panelreserve(20);
    // Add hotkeys
    setup_hotkeys();

    event_loop = wl_display_get_event_loop(display);
    wl_display_run(display);
    wl_display_destroy(display);

    return EXIT_SUCCESS;
}

