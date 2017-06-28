#include <stdio.h>
#include <time.h>
#include "file.h"

int get_write_file_name()
{
	// Get timestamp
	time_t raw_time;
	struct tm *timeinfo;
	char buffer[STRFTIME_BUFF_LEN];
	time (&raw_time);
	timeinfo = localtime (&raw_time);
	strftime (buffer, STRFTIME_BUFF_LEN, "ServerLog_%Y-%m-%d_%H-%M-%S.txt", timeinfo);
	memset(write_file_name, 0, sizeof(write_file_name));
	strcpy(write_file_name, buffer);

	return 0;
}

int write_data_to_file(char *data)
{
	// Try to open file
	FILE *f = fopen(write_file_name, "a");
	if (f == NULL) {
		printf("%s can not be opened.\n", write_file_name);
		write_file_name[0] = '\0';
		return -1;
	}

	// Get timestamp
	time_t raw_time;
	struct tm *timeinfo;
	char buffer[STRFTIME_BUFF_LEN];
	time (&raw_time);
	timeinfo = localtime (&raw_time);
	strftime (buffer, STRFTIME_BUFF_LEN, "%Y-%m-%d %H:%M:%S", timeinfo);

	// Write data to file
	fprintf(f, "%s\t%s\n", buffer, data);

	// Close file
	fclose(f);
	return 0;
}
