#ifndef SHELL_H
#define SHELL_H

void loop(char **);
char *read_line(int, char *);
char **split_line(char *);
void process_input(int, char **);
int execute(char **, char **);
int which(const char *, char *);
char readchar(int);
int execute(char **, char **);
int parse(char **, char **);
int cd(char **);
int my_exit(char **);
int print_env(char **);
int help();

#endif /* SHELL_H */
