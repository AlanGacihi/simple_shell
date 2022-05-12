#include "shell.h"
#include <sys/wait.h>
#include <unistd.h>

/**
 * exec - creates a process and executes a command
 * @av - list of commands and arguments
 *
 * Return: none
 */
void exec(char **av)
{
	extern char **environ;
	int status;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if(execve(av[0], av, environ) == -1)
		{
			perror("Error:");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(child_pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
