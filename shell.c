#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Super simple shell
 * @ac: number of arguments
 * @argv: list of arguments
 * @envp: environment
 * Return: Always 0.
 */
int main(__attribute__((unused)) int ac, __attribute__((unused)) char *argv[],
	 char *envp[])
{
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			printf("> ");
			fflush(stdout);

			readline(0, 0, envp);
		}
	}
	else
	{
		readline(0, 1, envp);
	}

	return (0);
}
