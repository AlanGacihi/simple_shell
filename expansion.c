#include "shell.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
/**
 * alias_expansion - function that performs alias expansions
 * @av: array of arguments passed to the program
 * @alias: array of aliases stored in the program
 * Return: void
 */
void alias_expansion(char *av[], char *alias[])
{
	int i = 0, j = 0, eq_len, len;
	char checker[1000], *token, new_args[1000], *alias_exp[100];

	if (!alias || !alias[0])
		return;
	strcpy(checker, alias[i]), token = _strtok(checker, "=");
	while (token && alias[i])
	{
		eq_len = strlen(token);
		if (!strcmp(token, av[0]) && alias[i][eq_len] == '=')
			break;
		i++;
		if (alias[i])
			strcpy(checker, alias[i]), token = _strtok(checker, "=");
	}
	if (!alias[i])
		return;
	token = _strtok(NULL, "="), strcpy(new_args, token);
	token = _strtok(new_args, " ");
	for (i = 0; token; i++)
	{
		eq_len = strlen(token);
		if (token[0] == '\'' && token[1] != '\'')
			alias_exp[i] = malloc(eq_len), strcpy(alias_exp[i], token + 1);
		else if (token[0] == '\'' && token[1] == '\'')
			alias_exp[i] = malloc(1), strcpy(alias_exp[i], "");
		else
			alias_exp[i] = malloc(eq_len + 1), strcpy(alias_exp[i], token);
		token = _strtok(NULL, " ");
	}
	if (strcmp(alias_exp[i - 1], ""))
		len = strlen(alias_exp[i - 1]), alias_exp[i - 1][len - 1] = '\0';

	for (j = 1; av[j]; j++, i++)
	{
		alias_exp[i] = malloc(strlen(av[j]) + 1);
		 strcpy(alias_exp[i], av[j]), free(av[j]);
	}
	free(av[0]), alias_exp[i] = NULL, copy_array(av, alias_exp);
	alias_expansion(av, alias);
}

/**
 * copy_array - function that initializes/copies a *arr[] and frees the origin
 * @av: destination
 * @alias_exp: array to be copied
 * Return: void
 */
void copy_array(char *av[], char *alias_exp[])
{
	int i;

	for (i = 0; alias_exp[i]; i++)
	{
		av[i] = malloc(strlen(alias_exp[i]) + 1);
		strcpy(av[i], alias_exp[i]), free(alias_exp[i]);
	}
	av[i] = NULL;
}
