#include "shell.h"

/**
 * main - Super simple shell
 *
 * Return: Always 0.
 */
int main()
{
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			printf("> ");
			fflush(stdout);

			read_and_exec(0, 0);
		}
	}
	else
	{
		read_and_exec(0, 1);
	}

	return(0);
}
