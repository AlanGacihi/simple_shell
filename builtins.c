#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * cd - Change the current working directory of the program.
 * @args: An array of arguments.
 *
 * Return: Always 1 to continue the shell loop.
 */
int cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Error: expected argument to cd\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("Error");
		}
	}
	return (1);
}

/**
 * my_exit - Exit the program.
 * @args: An array of arguments.
 *
 * Return: Always one.
 */
int my_exit(char **args)
{
	int status;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
	}
	else
	{
		status = 1;
	}
	exit(status);

	return (1);
}

/**
 * help - Know what to do.
 *
 * Return: Always 1.
 */
int help(void)
{
	printf("SIMPLE SHELL\n");
	printf("Type program names and arguments, and hit enter.\n");

	return (1);
}

/**
 * env - Print the current environment.
 * @env: Program environment.
 *
 * Return: Always 1.
 */
int print_env(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		printf("%s\n", env[i]);
	}

	return (1);
}
