#include "battery.h"

int read_raw_from_file(char *filepath, char *result_raw_value[]) {
	int status_code = 0;
	int fd = open(filepath, O_RDONLY);

	char* raw_value = NULL;
	raw_value = malloc(CHAR_LEN);

	if (fd == -1) {
		perror(filepath);
		status_code = -1;
		goto cleanup;
	}

	if (read(fd, raw_value, CHAR_LEN) == -1) {
		perror("Failed to read from sysfs file");
		status_code = -1; // TODO Make it different
		goto cleanup;
	}

	// Include scenario where result_raw_value is not NULL
	*result_raw_value = realloc(*result_raw_value, strlen(filepath) + sizeof(char));

	if (*result_raw_value == NULL) {
		perror("Failed to allocate read value");
		status_code = -1; // TODO Make it different
		goto cleanup;
	}
	strncpy(*result_raw_value, raw_value, CHAR_LEN);

cleanup:
	close(fd);
	free(raw_value);
	return status_code;
}

int get_file_path(char **dest_path, char *battery_name, char *module_name) {
	char *path = "/sys/class/power_supply";
	int str_size = strlen(path) + sizeof(char);
	str_size += strlen(battery_name) + sizeof(char);
	str_size += strlen(module_name);

	// Include scenario where dest_path is not NULL
	*dest_path = realloc(*dest_path, str_size + sizeof(char)); // Include terminating \0s

	if (*dest_path == NULL) {
		perror("Failed to allocate destination path");
		return -1;
	}

	snprintf(*dest_path, str_size + sizeof(char), "%s/%s/%s", path, battery_name, module_name);

	return 0;
}

int get_parsed_module_value(char *battery_name, char *module_name) {
	char *module_full_path = NULL;	
	int file_status = get_file_path(&module_full_path, battery_name, module_name);
	
	if (file_status != 0) {
		return -1;
	}

	char *raw_module_value = NULL;
	int status = read_raw_from_file(module_full_path, &raw_module_value);
	
	free(module_full_path);

	if (status != 0) {
		return -1; // TODO Make it different
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
