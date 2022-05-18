#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>
/**
* prepare_command - Parses the command in order to check for quotes && || etc.
* @command: Command that the user entered.
* @argv: Argument vector for main.
* @envp: Environment.
* @alias: Alias vector.
* @filename: Name of the history file.
* @new_envs: New environment variables array.
* @status: status of previous command.
*/
void prepare_command(char *command, char *argv[], char *envp[], char *alias[],
char *filename, char *new_envs[], int *status)
{
	short i = 0, j = 0, quote_flag = 0, idx = 0, checks = -1, tok_res;
	char *exec_comm, new_command[ARG_MAX], *av[100];

	while (command[i])
	{
		if (command[i + 1] && (command[i] == '\n' || command[i] == ';'))
		{
			new_command[j++] = ' ', new_command[j++] = '\n';
			new_command[j++] = ' ', i++;
			continue;
		}
		else if (command[i] == '\'' || command[i] == '"')
		{
			quote_flag = ~quote_flag;
			i++;
			continue;
		}
		else if (command[i] == ' ' && quote_flag)
		{
			new_command[j++] = '\'';
			i++;
			continue;
		}
		new_command[j] = command[i], i++, j++;
	}
	free(command), new_command[j] = '\0';
	new_command[strlen(new_command) - 1] = '\0', exec_comm = new_command;
	do {
		exec_comm += idx;
		checks = check_newlines(exec_comm, &idx);
		tok_res = tokenize(exec_comm, av, alias, filename, status, new_envs);
		if (tok_res)
		{
			for (i = 0; av[i]; i++)
				free(av[i]);
			continue;
		}
		exec_command(filename, av, argv[0], envp, status);
	} while (!checks || (checks == 1 && !*status) || (checks == 2 && *status));
}
