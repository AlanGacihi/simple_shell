#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

int argc(char **argv);
int isNumber(char *str);

/**
 * exit_shell - exits the shell
 * @argv: list of arguments
 *
 * Return: 0 if sucessful, -1 otherwise
 */
int exit_shell(char **argv)
{
	if (argc(argv) > 2)
	{
		fprintf(stderr, "Usage: exit [status]\n");
		return (-1);
	}
	else if (argv[1] == NULL)
	{
		exit(EXIT_SUCCESS);
		return (0);
	}
	else if (isNumber(argv[1]) == 0)
	{
		exit(atoi(argv[1]));
		return (0);
	}
	else
	{
		fprintf(stderr, "Usage: exit [status]\n");
		return (-1);
	}

	return (-1);
}

/**
 * isNumber - checks if a string is a number
 * @str: input string
 *
 * Return: 0 if true, -1 otherwise
 */
int isNumber(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!(isdigit(str[i])))
			return (-1);
	}
	return (0);
}

/**
 * env - prints the environment
 * @argv: list of arguments
 *
 * Return: 0 Always
 */
int env(__attribute__((unused)) char **argv)
{
	int i = 0;

	while (environ[i])
		printf("%s\n", environ[i++]);

	return (0);
}

/**
 * _setenv - initialize a new environment variable, or modify an existing one
 * @argv: list of arguments
 *
 * Return: 0 if successful, -1 otherwise
 */
int _setenv(char **argv)
{
	if (argc(argv) != 3 || strchr(argv[1], '=') != NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}

	if (set_var(argv[1], argv[2]) != 0)
	{
		perror("Error");
		return (-1);
	}

	return (0);
}

/**
 * _unsetenv - deletes a variable from the environment
 * @argv: list of arguments
 *
 * Return: 0 if successful, -1 otherwise
 */
int _unsetenv(char **argv)
{
	int unset;

	if (argc(argv) != 2 || strchr(argv[1], '=') != NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (-1);
	}

	unset = unset_var(argv[1]);

	if (unset == -1)
	{
		perror("Error:");
		return (-1);
	}
	else if (unset == 1)
	{
		return (-1);
	}

	return (0);
}
