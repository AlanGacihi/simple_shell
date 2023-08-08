#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * loop - Reads lines from standard input, parses them, and executes commands
 *        in a loop until the exit command is given.
 * @env: Program environment.
 */
void loop(char **env)
{
	char *line;
	char eof;
	char **args;
	int status;
	int prev_status;

	eof = 'a';

	do {
		printf("> ");
		fflush(stdout);
		line = read_line(STDIN_FILENO, &eof);
		args = split_line(line);
		status = parse(args, env);

		free(line);
		free(args);
		prev_status = status;

		if (strcmp(args[0], "exit") == 0)
		{
			if (args[1] != NULL)
			{
				exit(atoi(args[1]));
			}
			else
			{
				exit(prev_status);
			}
		}
	} while (eof != EOF);
}

/**
 * process_input - Reads lines from a file, parses them, and executes commands.
 * @fd: File descriptor to read input from.
 * @env: Program envronment.
 */
void process_input(int fd, char **env)
{
	int status;
	char eof;
	char *line;
	char **args;

	eof = 'a';

	do {
		line = read_line(fd, &eof);
		args = split_line(line);
		status = parse(args, env);

		free(line);
		free(args);
	} while (eof != EOF && status);
}
