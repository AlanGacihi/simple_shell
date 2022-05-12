#ifndef SHELL_H
#define SHELL_H

#define PATHSIZE 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

char *_getline(int fd, char **buffer);
char **split(char *str);
void exec(char **av);
void read_and_exec(int fd, int mode);
char *which(char *file);
int _assert(char *file);

#endif /* SHELL_H */
