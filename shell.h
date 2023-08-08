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

#endif /* SHELL_H */
