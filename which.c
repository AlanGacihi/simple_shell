#include "shell.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int _assert(char *file);
char **path_sep(void);

/**
 * which - checks if a command exists
 *@file - name of command
 *
 * Return: path if command exits, NULL otherwise
 */
char *which(char *file)
{
	char **path;
	char *real_path;
	int i = 0;

	if (strchr(file, '/'))
	{
	    if (_assert(file))
		    return (file);
	    else
		    return (NULL);
	}
	else
        {
		path = path_sep();
		while(path[i])
		{
		        real_path = strcat(path[i], file);
			if (_assert(real_path))
			{
				while(path[++i])
					free(path[i]);
				free(path);
				return (real_path);
			}
			free(path[i++]);
			real_path = NULL;
		}
		free(path);
		return (NULL);
	}
}

/**
 * assert - checks if command is excecutable
 * @file: command name
 *
 * Return: 1 if true and 0 otherwise
 */
int _assert(char *file)
{
	struct stat st;

	if (stat(file, &st) == 0)
	{
		if (access(file, X_OK))
			return (0);
		else
			return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * path_sep - separates PATH into dirs
 *
 */
char **path_sep(void)
{
	char **dirs;
	char *path;
	char *dir;
	char cp[PATHSIZE];
	int i = 0;
	int j = 0;
	int count = 1;

	path = getenv("PATH");

	while(path[i])
	{
		if (path[i] == ':')
			count++;
		i++;
	}

	dirs = (char **)malloc((count * sizeof(char *)) + 1);
	if (dirs == NULL)
		return (NULL);

	while ((dir = strsep(&path, ":")) != NULL)
	{
		strcpy(cp, dir);
		strcat(cp, "/");
		dirs[j++] = strdup(cp);
	}
	dirs[j] = NULL;

	return (dirs);
}
