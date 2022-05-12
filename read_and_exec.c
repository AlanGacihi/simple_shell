#include "shell.h"

/**
 * read_and_exec - reads and executes commands
 * @fd: file descriptor
 * @mode - 0 for interactive mode and 1 for non-interactive mode
 */
void read_and_exec(int fd, int mode)
{
	char *line;
	char *cmd;
	char **argv;

	if (mode == 0)
	{
		if(_getline(0, &line))
		{
			argv = split(line);

			cmd = which(argv[0]);
			if (cmd)
			{
				argv[0] = cmd;
				exec(argv);
			}
			else
			{
				printf("Command not found\n");
			}

			free(cmd);
			free(line);
			free(argv);
		}
		else
		{
			return;
		}
	}
	else if (mode == 1)
	{
		while(_getline(fd, &line))
		{
			argv = split(line);

			cmd = which(argv[0]);
			if (cmd)
			{
				argv[0] = cmd;
				exec(argv);
			}
			else
			{
				printf("Command not found\n");
			}
			
			free(cmd);
			free(line);
			line = NULL;
			free(argv);
		}
	}
	else
	{
		perror("Wrong mode");
	}
}
