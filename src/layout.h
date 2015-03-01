#ifndef LAYOUT_H
#define LAYOUT_H

#include "workspace.h"
#include "config.h"

#include <string>

typedef void(*layoutfunc)(Workspace*);

struct layout {
    std::string name;
    void (*layoutfunc)(Workspace*);
    layout* next;
};

// Layout handling functions
extern layout* firstlayout;
void add_layout(layout& layout);
layout* get_layout();

/*
	The actual layouts
*/

// Evenlayout
extern struct layout evenlayout;
void evenlayoutfunc(Workspace * screen);
// Master-slave layout
extern struct layout masterslavelayout;
void masterslavelayoutfunc(Workspace * screen);

#endif