#include "window.h"

#define VERSION "1.0.0"

int draw_top_bar(int tick) {
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	//WINDOW* top_bar_win = newwin(1, max_x, 0, 0);
	
	mvprintw(/*top_bar_win,*/ 0, 0, "Battery Analyzer %s", VERSION);
	//refresh();
	//wrefresh(top_bar_win);
	int pos = max_x - 1;

	switch (tick) {
	case 0:
		mvprintw(/*top_bar_win,*/ 0, pos, "/");
		break;
	case 1:
		mvprintw(/*top_bar_win,*/ 0, pos, "-");
		break;
	case 2:
		mvprintw(/*top_bar_win,*/ 0, pos, "\\");
		break;
	case 3:
		mvprintw(/*top_bar_win,*/ 0, pos, "|");
		break;
	}
	++tick;
	tick %= 4;

	return tick;
}
