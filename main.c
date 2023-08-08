#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * main - Entry point of the program.
 * @ac: The number of command-line arguments.
 * @av: An array of strings containing the command-line arguments.
 * @env: Environment variables.
 *
 * Return: The exit status of the program.
 */
int main(int ac, char **av, __attribute__((unused)) char **env)
{
	int fd;

	if (isatty(0) && ac == 1)
	{
		loop(env);
	}
	else if (isatty(0) && ac > 1)
	{
		fd = open(av[1], O_RDONLY);

		if (fd == -1)
		{
			fprintf(stderr, "Error opening file: %s\n", av[1]);
			exit(EXIT_FAILURE);
		}

		process_input(fd, env);
		close(fd);
	}
	else
	{
		process_input(STDIN_FILENO, env);
	}

	return (0);
}
