#include "shell.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
/**
 * print_alias - function that handles the alias built in
 * @av: array of arguments passed
 * @alias: two dimensional array malloc'ed for aliases
 * Return: continue status = 2
 */
int print_alias(char *av[], char *alias[])
{
	int i = 0, j = 1, len, flag = 0, set_res = 0, eq_len = 0;
	char al_name[ARG_MAX];

	if (!av[j])
	{
		while (alias[i])
		{
			len = strlen(alias[i]);
			write(STDOUT_FILENO, alias[i++], len);
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	while (av[j])
	{
		while (alias[i])
		{
			strcpy(al_name, alias[i]);
			_strtok(al_name, "=");
			eq_len = strlen(al_name);
			if (!strcmp(al_name, av[j]) && alias[i][eq_len] == '=')
			{
				len = strlen(alias[i]);
				write(STDOUT_FILENO, alias[i], len);
				write(STDOUT_FILENO, "\n", 1), flag++;
			}
			i++;
		}
		if (!flag)
		{
			set_res = set_alias(av[j], alias);
			if (!set_res)
			{
				len = strlen(av[j]);
				write(STDOUT_FILENO, av[j], len);
				write(STDOUT_FILENO, ": Not found\n", 12);
			}
		}
		flag = 0, j++, i = 0;
	}
	return (2);
}
/**
 * set_alias - set new aliases and modifies existing ones
 * @new_alias: new alias to store
 * @alias: array of aliases stored
 * Return: 0 on error, or 1 in success
 */
short set_alias(char *new_alias, char *alias[])
{
	int i = 0, len = 0, check_alias;
	char new_alias_cpy[ARG_MAX], *alias_name, *alias_value, al_cpy[ARG_MAX];
	char old_alias_cpy[ARG_MAX];

	check_alias = check_new_alias(new_alias);
	if (!check_alias)
		return (0);

	strcpy(al_cpy, new_alias);
	alias_name = _strtok(al_cpy, "=");
	alias_value = _strtok(NULL, "=");
	if (!alias_value)
		alias_value = "''";
	strcpy(new_alias_cpy, alias_name), strcat(new_alias_cpy, "=");
	if (alias_value[0] != '\'')
		strcat(new_alias_cpy, "'");
	strcat(new_alias_cpy, alias_value);

	len = strlen(alias_value);
	if (alias_value[len - 1] != '\'')
		strcat(new_alias_cpy, "'");

	i = 0;
	while (alias[i])
	{
		strcpy(old_alias_cpy, alias[i]);
		_strtok(old_alias_cpy, "=");
		if (!strcmp(old_alias_cpy, alias_name))
		{
			strcpy(alias[i], new_alias_cpy);
			return (1);
		}
		i++;
	}
	alias[i] = malloc(ARG_MAX);
	if (!alias[i])
		exit(-1);
	strcpy(alias[i++], new_alias_cpy);
	alias[i] = NULL;
	return (1);
}
/**
 * check_new_alias - checks if argument passes the required format
 * @new_alias: argument
 * Return: 1 on success or 0 on error
 */
int check_new_alias(char *new_alias)
{
	int i = 0, equals_count = 0;

	while (new_alias[i])
	{
		if (new_alias[i] == '=')
			equals_count++;
		i++;
	}
	if (!equals_count || (equals_count == 1 && new_alias[0] == '='))
		return (0);
	return (1);
}
