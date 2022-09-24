#ifndef FILE_TO_STR_H
#define FILE_TO_STR_H
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int mx_strlen(const char);
char *mx_strcpy(char*, const char*);
char *mx_strcat(char*, const char*);
char *mx_strnew(int);
char *mx_strdup(const char*);
char *mx_strjoin(char const*, char const*);

#endif

