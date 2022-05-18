#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
/**
 * my_exit - function that exits the program with specified state
 * @av: pointer to the array of arguments
 * @alias: array of aliases
 * @filename: Memory used on history.
 * @new_envs: New environment variables array.
 * @status: Exit status of previous command.
 * Return: void
 */

void my_exit(char *av[], char *alias[], char *filename, char *new_envs[],
int status)
{
	unsigned char exit_st;
	int i = 0, j = 0;

	if (av[1])
	{
		exit_st = (unsigned char) _atoi(av[1]);
		if (i < 0 || *av[1] < 49 || *av[1] > 57)
		{
			write(STDERR_FILENO, "hsh: 1: exit: Illegal number:\n", 30);
			if (!isatty(STDIN_FILENO))
				exit(2);
		}
		else
		{
			while (alias[j])
				free(alias[j++]);
			j = 0;
			while (new_envs[j])
				free(new_envs[j++]);
			j = 0;
			while (av[j])
				free(av[j++]);
			free(filename);
			exit(exit_st);
		}
	}
	else
	{
		while (alias[i])
			free(alias[i++]);
		i = 0;
		while (new_envs[i])
			free(new_envs[i++]);
		while (av[j])
			free(av[j++]);
		free(filename);
		exit(status);
	}
}
