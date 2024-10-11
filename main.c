#include <stdio.h>
#include "battery.h"

int main(void) {
	float battery_health = get_battery_health("BAT1");
	float battery_level = get_battery_percentage("BAT1");

	printf("Battery level is: %.2f%%\n", battery_level);
	printf("Battery health is: %.2f%%\n", battery_health);
	return 0;
}
