#include "shell.h"
#include <stdio.h>
#include <unistd.h>

/**
 * _getline - function that reads input from stdin
 * @command: address of pointer to buffer
 * @size: count of chars to be read as a line
 * @fd: file descriptor for read function
 * Return: count of chars read including newline/ excluding terminating null
 */

short _getline(char **command, int *size, int fd)
{
	short read_bytes = 0;

	read_bytes = read(fd, *command, *size);

	if (read_bytes == 0)
		return (-1);
	else if (read_bytes == -1)
	{
		free(*command);
		perror("Could not read input");
		exit(-1);
	}

	(*command)[read_bytes] = '\0';
	return (read_bytes);
}
