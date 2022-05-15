#include "shell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define NCHAR 64

/**
 * _getline - read one line until EOF
 * @fd: input
 * @buffer: pointer to output in memory
 *
 * Return: string
 */
char *_getline(int fd, char **buffer)
{
	char ch;
	char *tmp;
	size_t buflen = 0, nchar = NCHAR;

	*buffer = malloc(nchar);
	if (!*buffer)
	{
		perror("Error:");
		return (NULL);
	}

	while (read(fd, &ch, sizeof(ch)) > 0 && ch != '\n')
	{
		(*buffer)[buflen++] = ch;

		if (buflen + 1 >= nchar)
		{
			tmp = realloc(*buffer, nchar * 2);
			if (!tmp)
			{
				perror("Error:");
				(*buffer)[buflen] = 0;
				return (*buffer);
			}
			*buffer = tmp;
			nchar *= 2;
		}
	}
	(*buffer)[buflen] = 0;

	if (buflen == 0)
	{
		free(*buffer);
		*buffer = NULL;
	}

	return (*buffer);
}
