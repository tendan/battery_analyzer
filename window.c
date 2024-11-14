#include "window.h"

#define VERSION "1.0.0"

int draw_top_bar(int tick) {
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);
	
	mvprintw(0, 0, "Battery Analyzer %s %d", VERSION, tick);
	int pos = max_x - 1;

	switch (tick) {
	case 0:
		mvprintw(0, pos, "/");
		break;
	case 1:
		mvprintw(0, pos, "-");
		break;
	case 2:
		mvprintw(0, pos, "\\");
		break;
	case 3:
		mvprintw(0, pos, "|");
		break;
	}
	++tick;
	tick %= 4;

	return tick;
}
