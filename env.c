#include "shell.h"
#include <linux/limits.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * set_var - Function to handle the setenv.
 * @variable: Name of the variable to be set.
 * @value: Value for the variable.
 *
 * Return: 0 if successful, -1 otherwise
 */
int set_var(char *variable, char *value)
{
	char *new_var, set[ARG_MAX];
	int i = 0;

	if (!variable || !value)
	{
		errno = EINVAL;
		return (-1);
	}

	strcpy(set, variable);
	strcat(set, "=");

	while (environ[i] && strncmp(environ[i], set, strlen(set)))
		i++;

	strcat(set, value);
	if (environ[i])
		strcpy(environ[i], set);
	else
	{
		new_var = malloc(100);
		strcpy(new_var, set);

		environ[i++] = new_var;
		environ[i] = NULL;
	}

	return (0);
}

/**
 * unset_var - function that unsets an environment variable (locally)
 * @variable: name of the variable to unset
 *
 * Return: 0 if successful, -1 otherwise
 */
int unset_var(char *variable)
{
	int i = 0;
	char rm[ARG_MAX];

	if (!variable)
	{
		errno = EINVAL;
		return (-1);
	}

	strcpy(rm, variable);
	strcat(rm, "=");

	while (environ[i] && strncmp(environ[i], rm, strlen(rm)))
		i++;

	if (!environ[i])
	{
		fprintf(stderr, "bash: unsetenv: %s: Variable not found\n",
			variable);
		return (1);
	}
	else
	{
		free(environ[i]);
	}
	while (environ[i])
	{
		environ[i] = environ[i + 1];
		i++;
	}

	return (0);
}
