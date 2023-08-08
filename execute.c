#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_PATH_LEN 1024

/**
 * parse - Interpret the input.
 * @args: An array of strings containing the command and its arguments.
 * @env: Program environment.
 *
 * Return: exit status.
 */
int parse(char **args, char **env)
{
	if (args[0] == NULL)
	{
		return (0);
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		return (my_exit(args));
	}
	else if (strcmp(args[0], "help") == 0)
	{
		return (help());
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		return (cd(args));
	}
	else if (strcmp(args[0], "env") == 0)
	{
		return (print_env(env));
	}

	return (execute(args, env));
}

/**
 * execute - Create a new process and execute the specified command.
 * @args: An array of strings containing the command and its arguments.
 * @env: Program environment.
 *
 * Return: Always return 1 to continue the shell loop.
 */
int execute(char **args, char **env)
{
	pid_t pid;
	char *path;
	int status;

	path = malloc(sizeof(char) * MAX_PATH_LEN);

	if (which(args[0], path))
	{
		fprintf(stderr, "simple_shell: %s: command not found.\n", args[0]);
		return (0);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, env) == -1)
		{
			perror("Error");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Error");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(path);
	return (0);
}

/**
 * which - Find full path to command.
 * @cmd: Given command.
 * @path: Write the full path found.
 *
 * Return: Always return status.
 */
int which(const char *cmd, char *path)
{
	char *path_env, *path_copy, *dir;

	if (access(cmd, X_OK) == 0)
	{
		strcpy(path, cmd);
		return (0);
	}

	path_env = getenv("PATH");
	if (!path_env)
	{
		fprintf(stderr, "Error getting PATH environment variable.\n");
		return (0);
	}

	path_copy = strdup(path_env);
	if (!path_copy)
	{
		fprintf(stderr, "Memory allocation error.\n");
		return (1);
	}

	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(path, MAX_PATH_LEN, "%s/%s", dir, cmd);
		if (access(path, X_OK) == 0)
		{
			free(path_copy);
			return (0);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (1);
}
