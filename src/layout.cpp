#include "layout.h"
#include "config.h"


/*
    Layout handling
*/

typedef void(*layoutfunc)(Screen*);


layout* firstlayout = nullptr;

void add_layout(layout& layout){
    if (firstlayout == nullptr){
        firstlayout = &layout;
        firstlayout->next = firstlayout;
    }
    else {
        layout.next = firstlayout->next;
        firstlayout->next = &layout;
    }
}

layout* get_layout(){
    if (firstlayout == nullptr){
        firstlayout = &masterslavelayout;
        firstlayout->next = &masterslavelayout;
    }
    return firstlayout;
}



/*
    The actual layout functions
*/



/* 
    
    Ëvenlayout

    This is a basic grid arrange function that tries to give each window an
    equal space. 

*/

struct layout evenlayout {
    .name = "even",
    .layoutfunc = evenlayoutfunc,
    .next = nullptr,
};

void evenlayoutfunc(Screen * screen)
{
    // Initialize variables
    Window * window = NULL;
    unsigned num_columns, num_rows, column_index, row_index;
    struct swc_rectangle geometry;
    struct swc_rectangle * screen_geometry = &screen->swc->usable_geometry;

    if (screen->num_windows == 0) return;

    num_columns = ceil(sqrt(screen->num_windows));
    num_rows = screen->num_windows / num_columns + 1;
    window = wl_container_of(screen->windows.next, window, link);

    // Iterate over columns
    for (column_index = 0; &window->link != &screen->windows; ++column_index)
    {
        geometry.x = screen_geometry->x + border_width + padding
            + screen_geometry->width * column_index / num_columns;
        geometry.width = screen_geometry->width / num_columns
            - 2 * border_width - 2*padding;

        // If the window count isn't evenly dividable by number of columns, fix that
        if (column_index == screen->num_windows % num_columns)
            --num_rows;

        // Iterate over rows in column
        for (row_index = 0; row_index < num_rows; ++row_index)
        {
            geometry.y = screen_geometry->y + border_width + padding
                + screen_geometry->height * row_index / num_rows;
            geometry.height = screen_geometry->height / num_rows
                - 2 * border_width - 2*padding;

            // Apply window position and size
            swc_window_set_geometry(window->swc, &geometry);
            // Get next window
            window = wl_container_of(window->link.next, window, link);
        }
    }
}

/*

    Master-slave layout

    An layout with one window being the master has one half of the left side of the screen, 
    while the others are rowed on the right side of the screen

*/

struct layout masterslavelayout {
    .name = "masterslave",
    .layoutfunc = masterslavelayoutfunc,
    .next = nullptr,
};

void masterslavelayoutfunc(Screen * screen)
{
    // Initialize variables
    Window * window = NULL;
    int num_rows, row_index;
    struct swc_rectangle geometry;
    struct swc_rectangle * screen_geometry = &screen->swc->usable_geometry;

    if (screen->num_windows == 0) return;

    window = wl_container_of(screen->windows.next, window, link);

    // If there is only one window, make it reserve the full screen
    if (screen->num_windows == 1){
        geometry.x = screen_geometry->x + border_width + padding;
        geometry.y = screen_geometry->y + border_width + padding;
        geometry.width = screen_geometry->width - 2*border_width - 2*padding;
        geometry.height = screen_geometry->height - 2*border_width - 2*padding;
        swc_window_set_geometry(window->swc, &geometry);
    }
    else {
        // Master window
        geometry.x = screen_geometry->x + border_width + padding;
        geometry.width = screen_geometry->width/2 - 2*padding - 2*border_width;
        geometry.y = screen_geometry->y + border_width + padding;
        geometry.height = screen_geometry->height - 2*padding - 2*border_width;

        swc_window_set_geometry(window->swc, &geometry);
        window = wl_container_of(window->link.next, window, link);

        // The other windows
        geometry.x = screen_geometry->x + screen_geometry->width/2 + padding + border_width;

        num_rows = screen->num_windows - 1;
        for (row_index = 0; &window->link != &screen->windows; ++row_index)
        {
            geometry.y = screen_geometry->y + border_width + padding
                + screen_geometry->height * row_index / num_rows;
            geometry.height = screen_geometry->height / num_rows
                - 2 * border_width - 2*padding;

            swc_window_set_geometry(window->swc, &geometry);
            window = wl_container_of(window->link.next, window, link);
        }
    }
}