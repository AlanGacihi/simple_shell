#ifndef SHELL_H
#define SHELL_H

#define PATHSIZE 128

extern char **environ;

/**
 * struct builtin_s - Struct builtin
 *
 * @name: Function name
 * @f: The function associated
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv);
} builtin_t;

void shellPrompt(void);
char *_getline(int fd, char **buffer);
char **split(char *str);
void readline(int fd, int mode);
char *which(char *file);
int cd(char **argv);
int exit_shell(char **argv);
int env(char **argv);
int exec(char *argv[]);
int _setenv(char **argv);
int _unsetenv(char **argv);
int set_var(char *variable, char *value);
int unset_var(char *variable);

#endif /* SHELL_H */
