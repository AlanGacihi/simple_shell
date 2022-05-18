#include "shell.h"
#include <string.h>
/**
* check_builtins - Checks if user entered a builtin.
* @av: Command in tokens.
* @alias: Array of aliases.
* @filename: file with history
* @new_envs: New environment variables array.
* @status: Exit status of previous command.
* Return: 0 if no builtin, 1 or 2 otherwise.
*/
short check_builtins(char *av[], char *alias[], char *filename,
char *new_envs[], int status)
{
	int alias_ret;

	if (!strcmp("history", av[0]))
	{
		print_history(filename);
		return (1);
	}
	if (!strcmp("exit", av[0]))
	{
		my_exit(av, alias, filename, new_envs, status);
		return (1);
	}
	if (!strcmp("cd", av[0]))
	{
		_change_dir(av[1], new_envs);
		return (1);
	}
	if (!strcmp("setenv", av[0]))
	{
		set_var(av[1], av[2], new_envs);
		return (1);
	}
	if (!strcmp("unsetenv", av[0]))
	{
		unset_var(av[1], new_envs);
		return (1);
	}
	if (!strcmp("alias", av[0]))
	{
		alias_ret = print_alias(av, alias);
		return (alias_ret);
	}
	return (0);
}
