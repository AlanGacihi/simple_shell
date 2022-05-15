#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * readline - reads and executes commands
 * @fd: file descriptor
 * @mode: 0 for interactive mode and 1 for non-interactive mode
 * @envp: environment
 */
void readline(int fd, int mode, char *envp[])
{
	char *line;
	char **argv;

	if (mode == 0)
	{
		if (_getline(0, &line))
		{
			argv = split(line);
			exec(argv, envp);
			free(line);
			free(argv);
		}
		else
		{
			free(line);
		}
	}
	else if (mode == 1)
	{
		while (_getline(fd, &line))
		{
			argv = split(line);
			exec(argv, envp);
			free(argv);
		}
		free(line);
	}
	else
	{
		fprintf(stderr, "Wrong mode\n");
	}
}
