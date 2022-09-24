#ifndef WAY_HOME_H
#define WAY_HOME_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

bool mx_isspace(char);
int mx_strlen(const char*);
int mx_atoi(const char*);
void mx_printerr(const char*);
char *mx_file_to_str(const char*);
void mx_find_error(int argc, char* argv[]);
void mx_printchar(char);
void mx_printstr(const char*);
void mx_printint(int);

typedef struct s_point {
	int x;
	int y;
}		t_point;

typedef struct s_cell {
	t_point position;
	bool isWall;
	bool isPath;
	int wave;
}		t_cell;

#endif

