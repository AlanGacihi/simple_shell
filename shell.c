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
int main(void)
{
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			shellPrompt();
			fflush(stdout);

			readline(0, 0);
		}
	}
	else
	{
		readline(0, 1);
	}

	return (0);
}
