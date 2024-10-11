#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int get_battery_full(char *battery_name);
int get_battery_full_design(char *battery_name); 
float get_battery_health(char *battery_name); 
int get_battery_level(char *battery_name);
float get_battery_percentage(char *battery_name);
