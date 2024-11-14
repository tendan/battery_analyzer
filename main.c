#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include "battery.h"
#include "window.h"

static int raw_main();

int main(void) {
	//raw_main();
	int ch;

	initscr();

	refresh();
	int tick = 1;
	do {
		clear();
		tick = draw_top_bar(tick);
		move(2, 1);
		float battery_level = get_battery_percentage("BAT1");
		printw("Battery level is: %.2f%%", battery_level);

		move(4, 1);
		float battery_health = get_battery_health("BAT1");
		printw("Battery health is: %.2f%%", battery_health);
		refresh();
		sleep(1);
	} while ((ch = getch()) != 'q');
	endwin();
	return 0;
}

int raw_main() {
	float battery_health = get_battery_health("BAT1");
	float battery_level = get_battery_percentage("BAT1");

	printf("Battery level is: %.2f%%\n", battery_level);
	printf("Battery health is: %.2f%%\n", battery_health);
	
	return 0;
}
