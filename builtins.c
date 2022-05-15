#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * cd - change the working directory
 * @argv: list of arguments
 *
 */
void cd(__attribute__((unused)) char **argv)
{
	if (argv[1] == NULL)
	{
		fprintf(stderr, "kash: cd: missing argument\n");
	} else
	{
		if (chdir(argv[1]) != 0)
		{
			perror("Error:");
		}
	}
}


/**
 * exit_shell - exits the shell
 * @argv: list of arguments
 *
 */
void exit_shell(__attribute__((unused)) char **argv)
{
	exit(EXIT_SUCCESS);
}
