#include "plot.h"

static int draw_plot_axis(WINDOW* plot);

WINDOW* draw_plot(WINDOW* instance, int h, int w) {
	WINDOW *plot = NULL;
	if (instance == NULL) {
		plot = newwin(h, w, 5, 1);
	} else {
		plot = instance;
	}
	//box(plot, 0, 0);
	
	draw_plot_axis(plot);
	
	return plot;
}

static int draw_plot_axis(WINDOW* plot) {
	int max_x, max_y;
	getmaxyx(plot, max_y, max_x);
	
	for (int i = 0; i < max_y - 1; ++i)
		mvwprintw(plot, i, 0, "|");
	
	mvwprintw(plot, max_y - 1, 0, "+");
	
	for (int j = 1; j < max_x; ++j)
		mvwprintw(plot, max_y - 1, j, "-");
	return 0;
}
