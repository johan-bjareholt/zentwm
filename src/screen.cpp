#include "wm.h"
#include "screen.h"
#include "layout.h"

/*

	Setup functions

*/

void set_panelreserve(int px){
	struct swc_rectangle * screen_geometry = &active_screen->swc->usable_geometry;
	screen_geometry->y -= panelreservation;
	screen_geometry->height += panelreservation;
	panelreservation = px;
	screen_geometry->y += panelreservation;
	screen_geometry->height -= panelreservation;
}

void set_padding(int px){
	padding = px;
	active_screen->arrange();
}

/*

	Commands

*/
void next_layout(void * data, uint32_t time, uint32_t value, uint32_t state){
	if (state != WL_KEYBOARD_KEY_STATE_PRESSED)
		active_screen->next_layout();
}

/*

	Screen handler hooks

*/

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


/*

	Screen class functions

*/

Screen::Screen(swc_screen* swc, const swc_screen_handler* screen_handler)
{
	this->swc = swc;
	this->currentlayout = get_layout();
	this->num_workspace = 10;
	this->workspaces = new Workspace*[num_workspace];
	for (int i=0; i<num_workspace; i++){
		this->workspaces[i] = new Workspace(std::to_string(i+1), this);
	}
    this->current_workspace = workspaces[0];
	swc_screen_set_handler(swc, screen_handler, this);
}

Screen::~Screen(){
	delete current_workspace;
}

void Screen::arrange(){
	this->currentlayout->layoutfunc(this->current_workspace);
}

/*

	This function is very dirty, should be fixed!

*/
void Screen::hide(Workspace* workspace){
    // Initialize variables
    Window * window = NULL;
    struct swc_rectangle geometry;

    if (workspace->num_windows == 0) return;

    // Iterate over columns
    geometry.x = 10000;
    geometry.y = 10000;
    geometry.width = 0;
    geometry.height = 0;

    window = wl_container_of(workspace->windows.next, window, link);
    for (int window_index = 0; &window->link != &workspace->windows; window_index++)
    {
        // Apply window position and size
        swc_window_set_geometry(window->swc, &geometry);
        // Get next window
        window = wl_container_of(window->link.next, window, link);
    }
}

void Screen::change_workspace(int workspace_index){
	if (workspace_index < 1 || workspace_index > num_workspace)
		return;
	hide(current_workspace);
	current_workspace = workspaces[workspace_index-1];
	arrange();
}

void Screen::change_workspace(Workspace* workspace){
	if (workspace->screen != this)
		return;
	hide(current_workspace);
	current_workspace = workspace;
	arrange();
}

void Screen::next_layout(){
	this->currentlayout = this->currentlayout->next;
	arrange();
}