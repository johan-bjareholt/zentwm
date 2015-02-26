
#include "layout.h"
#include "config.h"

/* This is a basic grid arrange function that tries to give each window an
 * equal space. */
void evenlayout(Screen * screen)
{
    Window * window = NULL;
    unsigned num_columns, num_rows, column_index, row_index;
    struct swc_rectangle geometry;
    struct swc_rectangle * screen_geometry = &screen->swc->usable_geometry;

    if (screen->num_windows == 0) return;

    //screen_geometry.height -= 200;
    //geometry.y += panelreservation;

    num_columns = ceil(sqrt(screen->num_windows));
    num_rows = screen->num_windows / num_columns + 1;
    window = wl_container_of(screen->windows.next, window, link);

    for (column_index = 0; &window->link != &screen->windows; ++column_index)
    {
        geometry.x = screen_geometry->x + border_width
            + screen_geometry->width * column_index / num_columns;
        geometry.width = screen_geometry->width / num_columns
            - 2 * border_width;

        if (column_index == screen->num_windows % num_columns)
            --num_rows;

        for (row_index = 0; row_index < num_rows; ++row_index)
        {
            geometry.y = screen_geometry->y + border_width
                + screen_geometry->height * row_index / num_rows;
            geometry.height = screen_geometry->height / num_rows
                - 2 * border_width;

            swc_window_set_geometry(window->swc, &geometry);
            window = wl_container_of(window->link.next, window, link);
        }
    }
}
