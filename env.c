#include "shell.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
/**
* set_var - Function to handle the setenv.
* @arg1: Name of the variable to be set.
* @arg2: Value for the variable.
* @new_envs: New environment variables array.
*/
void set_var(char *arg1, char *arg2, char *new_envs[])
{
	char *new_var, var_to_set[ARG_MAX];
	short i = 0, j = 0;

	if (!arg1 || !arg2)
	{
		write(STDERR_FILENO, "setenv: parameters not found\n", 29);
		return;
	}

	strcpy(var_to_set, arg1);
	strcat(var_to_set, "=");

	while (environ[i] && strncmp(environ[i], var_to_set, strlen(var_to_set)))
		i++;

	strcat(var_to_set, arg2);
	if (environ[i])
		strcpy(environ[i], var_to_set);
	else
	{
		new_var = malloc(100);
		strcpy(new_var, var_to_set);
		while (new_envs[j])
			j++;
		new_envs[j] = new_var;
		new_envs[j + 1] = NULL;
		environ[i++] = new_var;
		environ[i] = NULL;
	}
}

/**
 * unset_var - function that unsets an environment variable (locally)
 * @var_name: name of the variable to unset
 * @new_envs: New environment variables array.
 * Return: void
 */

void unset_var(char *var_name, char *new_envs[])
{
	short i = 0, j = 0;
	char var_to_rm[ARG_MAX];

	if (!var_name)
	{
		write(STDERR_FILENO, "unsetenv: parameter not found\n", 30);
		return;
	}

	strcpy(var_to_rm, var_name);
	strcat(var_to_rm, "=");

	while (environ[i] && strncmp(environ[i], var_to_rm, strlen(var_to_rm)))
		i++;
	for (j = 0; new_envs[j]; j++)
		if (!strcmp(new_envs[j], environ[i]))
			break;
	if (!environ[i])
	{
		write(STDERR_FILENO, "unsetenv: Variable not found\n", 29);
		return;
	}
	else
	{
		free(environ[i]);
	}
	while (environ[i])
	{
		environ[i] = environ[i + 1];
		new_envs[j] = new_envs[j + 1];
		i++;
		j++;
	}
}
