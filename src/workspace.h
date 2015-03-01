#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <string>

class Workspace;

#include "screen.h"

void switch_workspace(void * data, uint32_t time, uint32_t value, uint32_t state);

class Workspace {
private:
public:
	std::string name;
	Screen* screen;
    struct wl_list windows;
    unsigned num_windows;
	Workspace(std::string, Screen* screen);
	void add_window(Window* window);
	void remove_window(Window* window);
};

#endif