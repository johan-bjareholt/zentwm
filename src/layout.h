#ifndef LAYOUT_H
#define LAYOUT_H

#include "screen.h"
#include "config.h"

#include <string>

typedef void(*layoutfunc)(Screen*);

struct layout {
    std::string name;
    void (*layoutfunc)(Screen*);
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
void evenlayoutfunc(Screen * screen);
// Master-slave layout
extern struct layout masterslavelayout;
void masterslavelayoutfunc(Screen * screen);

#endif