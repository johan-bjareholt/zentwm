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
	active_screen->current_workspace->arrange();
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
    screen->current_workspace->arrange();
}

void screen_entered(void * data)
{
	// Will this function work with multi-monitor setups?
    Screen * screen = (Screen*)data;
    active_screen = screen;
}


/*

	Screen class functions

*/

Screen::Screen(swc_screen* swc, const swc_screen_handler* screen_handler)
{
	this->swc = swc;
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

/*

	This function is very dirty, should be fixed!

*/

void Screen::change_workspace(int workspace_index){
	if (workspace_index < 1 || workspace_index > num_workspace)
		return;
	// Get new workspace
	Workspace* workspace = workspaces[workspace_index-1];
	change_workspace(workspace);
}

void Screen::change_workspace(Workspace* workspace){
	if (workspace->screen != this)
		return;
	current_workspace->hide_all();
	// Get new workspace
	current_workspace = workspace;
	current_workspace->show_all();
	if (current_workspace->focused_window)
		current_workspace->focused_window->focus();
	current_workspace->arrange();
}

bool Screen::operator==(Screen& other){
	bool result=false;
	if (this->swc == other.swc)
		result = true;
	return result;
}
