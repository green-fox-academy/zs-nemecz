#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#include <time.h>

#define MAX_FILENAME_LEN    1024
#define STRFTIME_BUFF_LEN   100
#define READ_BUFFER_LEN     1024

char write_file_name[MAX_FILENAME_LEN];

int get_file_name(char *file_name);
int get_write_file_name();
int write_data_to_file(char *data);
int save_to_file();

#endif // FILE_H_INCLUDED
