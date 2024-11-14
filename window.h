#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

// Not safe with MT, be careful
int draw_top_bar(int tick);

#endif
