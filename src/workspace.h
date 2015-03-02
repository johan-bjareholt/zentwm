#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <string>

class Workspace;

#include "screen.h"

// Commands
void switch_workspace(void * data, uint32_t time, uint32_t value, uint32_t state);
void focus_next(void * data, uint32_t time, uint32_t value, uint32_t state);
void next_layout(void * data, uint32_t time, uint32_t value, uint32_t state);


class Workspace {
private:
	struct layout* currentlayout;
public:
	std::string name;
	Screen* screen;
	Window* focused_window;
    struct wl_list windows;
    unsigned num_windows;
	Workspace(std::string, Screen* screen);
	void add_window(Window* window);
	void remove_window(Window* window);
	void arrange();
	void next_layout();
	void hideAll();
};

#endif