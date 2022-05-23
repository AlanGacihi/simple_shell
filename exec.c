#include "shell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_builtins(char **argv);

/**
 * exec - creates a process and executes a command
 * @argv: list of commands and arguments
 *
 * Return: 0 if success, -1 otherwise
 */
int exec(char *argv[])
{
	int status;
	char *cmd;
	pid_t child_pid;

	if (check_builtins(argv) == 0)
		return (0);

	cmd = which(argv[0]);
	if (cmd == NULL)
	{
		fprintf(stderr, "bash: %s: command not found\n", argv[0]);
		free(cmd);
		return (-1);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (-1);
	}
	if (child_pid == 0)
	{
		if (execve(cmd, argv, environ) == -1)
		{
			perror("Error:");
			free(cmd);
			return (-1);
		}
	}
	else
	{
		wait(&status);
	}
	/*free (cmd);*/

	return (-1);
}

/**
 * check_builtins - checks if a command is builtin
 * @argv: list of arguments
 *
 *
 * Return: 0 if successful, -1 otherwise
 *
 */
int check_builtins(char **argv)
{
	int i = 0, j;

	builtin_t builtins[] = {
		{"cd", cd},
		{"exit", exit_shell},
		{"env", env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv}
	};

	j = sizeof(builtins) / sizeof(builtin_t);
	for (i = 0; i < j; i++)
	{
		if (strcmp(argv[0], builtins[i].name) == 0)
		{
			builtins[i].f(argv);
			return (0);
		}
	}

	return (-1);
}

/**
 * shellPrompt - Displays the prompt for the shell
 *
 */
void shellPrompt(void)
{
	char pwd[PATHSIZE];

	printf("cisfun:%s# ", getcwd(pwd, PATHSIZE));
}
