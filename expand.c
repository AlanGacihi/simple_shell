#include "shell.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
/**
* expand_vars - Function to expand variables.
* @av: Tokens of command.
* @status: status of execution of previous command.
*/
void expand_vars(char *av[], int *status)
{
	short i, j, m = 0, space_flag = 0;
	char not_expanded[100];

	for (i = 0; av[i]; i++)
	{
		for (j = 0, m = 0, not_expanded[0] = '\0'; av[i][j]; j++)
		{
			if (av[i][j] == ' ')
			{
				space_flag = 1, not_expanded[0] = '\0';
				break;
			}
			if (av[i][j] != '$')
				not_expanded[m++] = av[i][j], not_expanded[m] = '\0';
			else if (av[i][j + 1] != '\0')
			{
				if (expand1(av, &i, &j, &m, status, not_expanded))
				{
					j++;
					continue;
				}
				else if (expand2(av, &i, &j, not_expanded, &space_flag))
					break;
			}
		}
		if (not_expanded[0])
		{
			free(av[i]), av[i] = malloc(strlen(not_expanded) + 1);
			strcpy(av[i], not_expanded), not_expanded[0] = '\0';
		}
	}
}
short expand1(char *av[], short *i, short *j, short *m, int *status,
char *not_expanded)
{
	char *num2str_res;

	if (av[*i][*j + 1] == '?')
	{
		num2str_res = _num2str(*status >> 8), strcat(not_expanded, num2str_res);
		*m += strlen(num2str_res), free(num2str_res);
		return (1);
	}
	else if (av[*i][*j + 1] == '$')
	{
		num2str_res = _num2str(getpid()), strcat(not_expanded, num2str_res);
		*m += strlen(num2str_res), free(num2str_res);
		return (1);
	}
	return (0);
}
short expand2(char *av[], short *i, short *j, char *not_expanded,
short *space_flag)
{
	char varname[100];
	short k, l = 0, replaced = 0;

	for (k = *j + 1; av[*i][k]; k++)
	{
		if (av[*i][k] == ' ')
		{
			*space_flag = 1;
			return (2);
		}
		varname[l++] = av[*i][k];
	}
	if (*space_flag)
	{
		*space_flag = 0;
		return (2);
	}
	varname[l++] = '=';
	for (k = 0; environ[k]; k++)
		if (!strncmp(varname, environ[k], l))
		{
			free(av[*i]);
			av[*i] = malloc(strlen(not_expanded) + strlen(environ[k] + l) + 1);
			strcpy(av[*i], not_expanded), not_expanded[0] = '\0';
			strcat(av[*i], environ[k] + l), replaced = 1, l = 0;
			return (1);
		}
	if (replaced)
	{
		replaced = 0;
		return (1);
	}
	else
	{
		free(av[*i]), av[*i] = malloc(strlen(not_expanded) + 1);
		strcpy(av[*i], not_expanded), not_expanded[0] = '\0';
	}
	return (0);
}
/**
* _num2str - Converts a number into a string.
* @num: Number to convert.
* Return: string of the number.
*/
char *_num2str(int num)
{
	char *str = malloc(20);
	short i = 0, j;

	for (i = 0; num / 10; i++, num /= 10)
		str[i] = num % 10 + '0';
	str[i++] = num % 10 + '0';
	str[i] = '\0';
	for (i = 0, j = strlen(str) - 1; i < j; i++, j--)
	{
		str[i] += str[j];
		str[j] = str[i] - str[j];
		str[i] -= str[j];
	}
	return (str);
}
