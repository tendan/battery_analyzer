#include "battery.h"

int read_raw_from_file(char *filepath, char *result_raw_value[]) {
	int fd = open(filepath, O_RDONLY);
	if (fd == -1) {
		perror(filepath);
		return -1;
	}
	//struct stat file_stat;
	//int stat_status = fstat(fd, &file_stat);
	//if (stat_status != 0) {
	//	perror("Couldn't read sysfs file");
	//	return -1;
	//}
	//size_t char_len = file_stat.st_size * sizeof(char);
	size_t char_len = 15;
	char* raw_value = NULL;
	raw_value = malloc(char_len);
	if (read(fd, raw_value, char_len) == -1) {
		perror("Failed to read from sysfs file");
		return -1;
	}
	//raw_value = 0;
	close(fd);
	*result_raw_value = malloc(strlen(filepath) + sizeof(char));
	strncpy(*result_raw_value, raw_value, char_len);

	raw_value = 0;
	free(raw_value);
	return 0;	
}

int get_file_path(char **dest_path, char *battery_name, char *module_name) {
	char *path = "/sys/class/power_supply";
	int str_size = strlen(path) + sizeof(char);
	str_size += strlen(battery_name) + sizeof(char);
	str_size += strlen(module_name);

	*dest_path = malloc(str_size + sizeof(char)); // Include terminating \0
	snprintf(*dest_path, str_size + sizeof(char), "%s/%s/%s", path, battery_name, module_name);

	return 0;
}

int get_parsed_module_value(char *battery_name, char *module_name) {
	char *module_full_path;	
	int file_status = get_file_path(&module_full_path, battery_name, module_name);
	
	if (file_status != 0) {
		return -1;
	}

	char *raw_module_value;
	int status = read_raw_from_file(module_full_path, &raw_module_value);
	
	free(module_full_path);

	if (status != 0) {
		return -1;
	}

	int parsed_value = atoi(raw_module_value);
	free(raw_module_value);

	return parsed_value;
}

int get_battery_full(char *battery_name) {
	return get_parsed_module_value(battery_name, "charge_full");	
}

int get_battery_full_design(char *battery_name) {
	return get_parsed_module_value(battery_name, "charge_full_design");
}

float get_battery_health(char *battery_name) {
	float battery_full_value = (float)get_battery_full(battery_name);
	float battery_full_design_value = (float)get_battery_full_design(battery_name);

	if (battery_full_value == -1 || battery_full_design_value == -1) {
		printf("Failed to get battery health");	
		return -1.;
	}
	return battery_full_value / battery_full_design_value * 100;	
}

int get_battery_level(char *battery_name) {
	return get_parsed_module_value(battery_name, "charge_now");
}

float get_battery_percentage(char *battery_name) {
	return (float)get_battery_level(battery_name) / (float)get_battery_full(battery_name) * 100;
}
