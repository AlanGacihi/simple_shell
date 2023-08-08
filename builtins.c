#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * cd - Change the current working directory of the program.
 * @args: An array of arguments.
 *
 * Return: Always 1 to continue the shell loop.
 */
int cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Error: expected argument to cd\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("Error");
		}
	}
	return (1);
}
