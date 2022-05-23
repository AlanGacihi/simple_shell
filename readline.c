#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void free_grid(char **grid, int height);
/**
 * readline - reads and executes commands
 * @fd: file descriptor
 * @mode: 0 for interactive mode and 1 for non-interactive mode
 */
void readline(int fd, int mode)
{
	char *line;
	char **argv;

	if (mode == 0)
	{
		if (_getline(0, &line))
		{
			argv = split(line);
			exec(argv);
			free_grid(argv, 1);
		}
		free(line);
	}
	else if (mode == 1)
	{
		while (_getline(fd, &line))
		{
			argv = split(line);
			exec(argv);
			free(argv);
		}
		free(line);
	}
	else
	{
		fprintf(stderr, "Wrong mode\n");
	}
}


/**
 * free_grid - frees an array of strings
 *
 */
void free_grid(char **grid, int height)
{
	if (grid != NULL && height != 0)
	{
		for (; height >= 0; height--)
			free(grid[height]);
		free(grid);
	}
}
