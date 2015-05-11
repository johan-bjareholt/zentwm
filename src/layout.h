#ifndef LAYOUT_H
#define LAYOUT_H

#include "workspace.h"
#include "config.h"

#include <string>

typedef void(*layoutfunc)(Workspace*);

// Base layout struct
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
void evenlayoutfunc(Workspace * workspace);
// Master-slave layout
extern struct layout masterslavelayout;
void masterslavelayoutfunc(Workspace * workspace);
// Full layout
extern struct layout fulllayout;
void fulllayoutfunc(Workspace* workspace);

#endif
