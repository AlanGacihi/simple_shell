#ifndef SHELL_H
#define SHELL_H
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <signal.h>
extern char **environ;

void my_exit(char *av[], char *alias[], char *filename, char *new_envs[], int);
int _atoi(char *);
short _getline(char **command, int *size, int fd);
void (*signal(int, void (*)(int)))(int);
void _change_dir(char *path, char *new_envs[]);
short check_newlines(char *av, short *idx);
char *getenvtok(char *envp[], char *var, char *token[]);
void set_var(char *arg1, char *arg2, char *new_envs[]);
void unset_var(char *var_to_rm, char *new_envs[]);
char *_strtok(char *base, char *delims);
short check_builtins(char *av[], char *alias[], char *filename,
char *new_envs[], int status);
int print_alias(char *av[], char *alias[]);
short set_alias(char *new_alias, char *alias[]);
int check_new_alias(char *new_alias);
void alias_expansion(char *av[], char *alias[]);
void expand_vars(char *av[], int *status);
char *_num2str(int num);
void copy_array(char *av[], char *alias_exp[]);
short get_filename(char **filename, char *envp[]);
short create_write_file(const char *filename, char *content_to_wr);
void print_history(char *filename);
void print_number(int n);
void print_loop_his(char *, int *, int *, int *);
void prepare_command(char *command, char *argv[], char *envp[], char *alias[],
char *filename, char *new_envs[], int *status);
void exec_command(char *filename, char *av[], char *prog_name, char *envp[],
int *status);
short tokenize(char *command, char *av[], char *alias[], char *filename,
int *status, char *new_envs[]);
short get_input(char *av[], char **command, int *args);
short expand2(char *av[], short *i, short *j, char *not_expanded,
short *space_flag);
short expand1(char *av[], short *i, short *j, short *m, int *status,
char *not_expanded);
void print_env(void);
short remove_spaces(char *command);

#endif  /* SHELL_H */
