#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/**
 * read_line - reads a line a time from input
 * @fd: file descriptor
 * @eof: end of file
 *
 * Return: read line
*/
char *read_line(int fd, char *eof)
{
	int bufsize, position;
	char *buffer;
	char c;

	bufsize = BUFSIZE;
	position = 0;
	buffer = malloc(sizeof(char) * bufsize);
	if (!buffer)
	{
		fprintf(stderr, "Error: allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		c = readchar(fd);
		if (c == EOF)
		{
			buffer[position] = '\0';
			eof[0] = EOF;
			return (buffer);
		}
		else if (c == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}
		buffer[position++] = c;
		if (position >= bufsize)
		{
			bufsize += BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				fprintf(stderr, "Error: Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * readchar - Reads a character at a time
 * @fd: file descriptor
 *
 * Return: read character
*/
char readchar(int fd)
{
	char ch;
	ssize_t bytesRead;

	while ((bytesRead = read(fd, &ch, 1)) == 1)
	{
		return (ch);
	}

	if (bytesRead == -1)
	{
		perror("Error reading from input");
		exit(EXIT_FAILURE);
	}

	return (EOF);
}

/**
 * split_line - splits a line into tokens
 * @line: line to split
 *
 * Return: array of tokens
*/
char **split_line(char *line)
{
	int bufsize, position;
	char **tokens;
	char *token;

	bufsize = TOK_BUFSIZE;
	position = 0;
	tokens = malloc(bufsize * sizeof(char *));

	if (!tokens)
	{
		fprintf(stderr, "Error: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "Error: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}
