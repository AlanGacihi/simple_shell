#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <linux/limits.h>
/**
* _change_dir - Function to handle the cd builtin.
* @path: Path to go.
* @new_envs: New environment variables array.
*/
void _change_dir(char *path, char *new_envs[])
{
	int chdir_res = 0, i = 0, j = 0;
	char ptr_dir[ARG_MAX], home_ptr[ARG_MAX], old_ptr[ARG_MAX];

	while (environ[i] && (strncmp(environ[i], "HOME=", 5)))
		i++;

	while (environ[j] && (strncmp(environ[j], "OLDPWD=", 7)))
		j++;

	strcpy(old_ptr, environ[j] + 7);
	strcpy(home_ptr, environ[i] + 5);
	getcwd(ptr_dir, ARG_MAX);
	if (!path)
		chdir_res = chdir(home_ptr);
	else if (!strcmp("-", path))
		chdir_res = chdir(old_ptr);
	else
		chdir_res = chdir(path);
	if (chdir_res)
	{
		perror("cd");
		return;
	}
	set_var("OLDPWD", ptr_dir, new_envs);
	getcwd(ptr_dir, ARG_MAX);
	set_var("PWD", ptr_dir, new_envs);
}
