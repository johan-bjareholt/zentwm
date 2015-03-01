#include "layout.h"
#include "config.h"


/*
    Layout handling
*/

typedef void(*layoutfunc)(Workspace*);


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

void evenlayoutfunc(Workspace * workspace)
{
    // Initialize variables
    Window * window = NULL;
    unsigned num_columns, num_rows, column_index, row_index;
    struct swc_rectangle geometry;
    struct swc_rectangle * workspace_geometry = &workspace->screen->swc->usable_geometry;

    if (workspace->num_windows == 0) return;

    num_columns = ceil(sqrt(workspace->num_windows));
    num_rows = workspace->num_windows / num_columns + 1;
    window = wl_container_of(workspace->windows.next, window, link);

    // Iterate over columns
    for (column_index = 0; &window->link != &workspace->windows; ++column_index)
    {
        geometry.x = workspace_geometry->x + border_width + padding
            + workspace_geometry->width * column_index / num_columns;
        geometry.width = workspace_geometry->width / num_columns
            - 2 * border_width - 2*padding;

        // If the window count isn't evenly dividable by number of columns, fix that
        if (column_index == workspace->num_windows % num_columns)
            --num_rows;

        // Iterate over rows in column
        for (row_index = 0; row_index < num_rows; ++row_index)
        {
            geometry.y = workspace_geometry->y + border_width + padding
                + workspace_geometry->height * row_index / num_rows;
            geometry.height = workspace_geometry->height / num_rows
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

    An layout with one window being the master has one half of the left side of the workspace, 
    while the others are rowed on the right side of the workspace

*/

struct layout masterslavelayout {
    .name = "masterslave",
    .layoutfunc = masterslavelayoutfunc,
    .next = nullptr,
};

void masterslavelayoutfunc(Workspace * workspace)
{
    // Initialize variables
    Window * window = NULL;
    int num_rows, row_index;
    struct swc_rectangle geometry;
    struct swc_rectangle * workspace_geometry = &workspace->screen->swc->usable_geometry;

    if (workspace->num_windows == 0) return;

    window = wl_container_of(workspace->windows.next, window, link);

    // If there is only one window, make it reserve the full workspace
    if (workspace->num_windows == 1){
        geometry.x = workspace_geometry->x + border_width + padding;
        geometry.y = workspace_geometry->y + border_width + padding;
        geometry.width = workspace_geometry->width - 2*border_width - 2*padding;
        geometry.height = workspace_geometry->height - 2*border_width - 2*padding;
        swc_window_set_geometry(window->swc, &geometry);
    }
    else {
        // Master window
        geometry.x = workspace_geometry->x + border_width + padding;
        geometry.width = workspace_geometry->width/2 - 2*padding - 2*border_width;
        geometry.y = workspace_geometry->y + border_width + padding;
        geometry.height = workspace_geometry->height - 2*padding - 2*border_width;

        swc_window_set_geometry(window->swc, &geometry);
        window = wl_container_of(window->link.next, window, link);

        // The other windows
        geometry.x = workspace_geometry->x + workspace_geometry->width/2 + padding + border_width;

        num_rows = workspace->num_windows - 1;
        for (row_index = 0; &window->link != &workspace->windows; ++row_index)
        {
            geometry.y = workspace_geometry->y + border_width + padding
                + workspace_geometry->height * row_index / num_rows;
            geometry.height = workspace_geometry->height / num_rows
                - 2 * border_width - 2*padding;

            swc_window_set_geometry(window->swc, &geometry);
            window = wl_container_of(window->link.next, window, link);
        }
    }
}