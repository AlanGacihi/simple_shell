#include "shell.h"
#include <string.h>
/**
* remove_spaces - Removes lines of spaces.
* @command: Command to review.
* Return: 1 if skip necessary, 0 otherwise.
*/
short remove_spaces(char *command)
{
	short i, sp = 0;

	for (i = 0; command[i]; i++)
		if (command[i] == ' ' || command[i] == '\n')
			sp++;
		else
			break;
	if (!*(command + sp) || !strcmp(command + sp, "\n"))
	{
		free(command);
		return (1);
	}
	strcpy(command, command + sp);
	return (0);
}
