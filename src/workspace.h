#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <string>
#include <vector>

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
	std::vector<Window*> windows;
	std::vector<Window*> windows_floating;

	Workspace(std::string, Screen* screen);
	// Window handling
	void add_window(Window* window);
	void remove_window(Window* window);
	void show_all();
	void hide_all();
	Window* focus_next();
	int count();
	int count_tiling();

	// Layout handling
	void arrange();
	void next_layout();
};

#endif
