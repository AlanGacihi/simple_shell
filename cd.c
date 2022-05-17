#include "shell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cd_prev(void);
int cd_home(void);
int cd_dir(char *dir);
int argc(char **argv);

/**
 * cd - change the working directory
 * @argv: list of arguments
 *
 * Return: 0 if successful, -1 otherwise
 */
int cd(char **argv)
{
	if (argc(argv) > 2)
	{
		fprintf(stderr, "Usage: cd [directory]\n");
		return (-1);
	}
	else if (argv[1] == NULL)
	{
		return (cd_home());
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		return (cd_prev());
	}
	else if (strcmp(argv[1], "~") == 0)
	{
		return (cd_home());
	}
	else
	{
		return (cd_dir(argv[1]));
	}
}

/**
 * cd_prev - change to the prevoius dir
 *
 * Return: 0 if successful, -1 otherwise
 */
int cd_prev(void)
{
	char *oldpwd;
	char pwd[PATHSIZE];
	char curdir[PATHSIZE];

	getcwd(pwd, PATHSIZE);

	oldpwd = getenv("OLDPWD");
	if (oldpwd)
	{
		printf("%s\n", oldpwd);
		if (chdir(oldpwd) == 0)
		{
			getcwd(curdir, PATHSIZE);
			setenv("PWD", curdir, 1);
			setenv("OLDPWD", pwd, 1);
			return (0);
		}
		else
		{
			fprintf(stderr, "bash: cd: %s: %s\n", oldpwd,
				strerror(errno));
			return (-1);
		}
	}
	else
	{
		fprintf(stderr, "Error: cd: OLDPWD not set\n");
		return (-1);
	}
}

/**
 * cd_home - change the wd to home
 *
 * Return: 0 if sucessful, -1 otherwise
 */
int cd_home(void)
{
	char oldpwd[PATHSIZE];
	char *home = getenv("HOME");

	getcwd(oldpwd, PATHSIZE);

	if (chdir(home) == 0)
	{
		setenv("PWD", home, 1);
		setenv("OLDPWD", oldpwd, 1);
		return (0);
	}
	else
	{
		fprintf(stderr, "bash:  cd: %s: %s\n", home, strerror(errno));
		return (-1);
	}
}

/**
 * cd_dir - changes wd to a dir
 * @dir: target directory
 *
 * Return: 0 if successful, -1 otherwise
 */
int cd_dir(char *dir)
{
	char oldpwd[PATHSIZE];
	char pwd[PATHSIZE];

	getcwd(oldpwd, PATHSIZE);

	if (chdir(dir) == 0)
	{
		getcwd(pwd, PATHSIZE);
		setenv("PWD", pwd, 1);
		setenv("OLDPWD", oldpwd, 1);
		return (0);
	}
	else
	{
		fprintf(stderr, "bash: cd: %s: %s\n", dir, strerror(errno));
		return (-1);
	}
}

/**
 * argc - counts number of arguments in argv
 * @argv: list of arguments
 *
 * Return: 0 if successful, -1 otherwise
 */
int argc(char **argv)
{
	int i = 0;

	while (argv[i])
		i++;

	return (i);
}
