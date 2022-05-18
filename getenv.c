#include "shell.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/**
* getenvtok - Get environment variable as tokens.
* @envp: Environment variables.
* @var: Variable to find.
* @token: Array to save the tokens.
* Return: String that must be free'd.
*/
char *getenvtok(char *envp[], char *var, char *token[])
{
	short i = 0;
	char *path_str = NULL;

	while (strncmp(envp[i], var, strlen(var)))
		i++;
	path_str = malloc(strlen(envp[i]) + 1);
	if (!path_str)
		exit(-1);
	strcpy(path_str, envp[i]);
	if (*(path_str + 5) == ':')
		*(path_str + 4) = '.', *(path_str + 3) = '=';
	i = 0;
	_strtok(path_str, "=");
	while ((token[i++] = _strtok(NULL, ":")))
		;
	return (path_str);
}
