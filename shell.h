#ifndef SHELL_H
#define SHELL_H

/**
 * struct builtin_s - Struct builtin
 *
 * @name: Function name
 * @f: The function associated
 */
typedef struct builtin_s
{
	char *name;
	void (*f)(__attribute__((unused)) char **argv);
} builtin_t;

char *_getline(int fd, char **buffer);
char **split(char *str);
void readline(int fd, int mode, char *envp[]);
char *which(char *file);
void cd(char **argv);
void exit_shell(char **argv);
int exec(char *argv[], char *envp[]);

#endif /* SHELL_H */
