#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

char *check_path(char *file, long int l, long int k);
int _assert(const char *file);

/**
 * which - executes a commands if it finds it
 * @file: name of file
 *
 * Return: -1 if it fails
 *
 */
char *which(char *file)
{
	char *path = getenv("PATH");
	long int l, k;

	errno = ENOENT;
	if (!*file)
		return (NULL);

	if (strchr(file, '/'))
	{
		if (_assert(file) == 0)
			return (file);
		else
			return (NULL);
	}

	if (!path)
		path = "/usr/local/bin:/bin:/usr/bin";
	k = strnlen(file, NAME_MAX + 1);

	l = strnlen(path, PATH_MAX - 1) + 1;

	return (check_path(file, l, k));
}

/**
 * check_path - looks for file in path directories
 * @file: name of file
 * @l: length of path
 * @k: lengh of file
 *
 * Return: -1 if it fails
 */
char *check_path(char *file, long int l, long int k)
{
	const char *path = getenv("PATH"), *p, *z;
	int seen_eacces = 0;
	char *b;

	b = malloc(sizeof(char) * (l + k + 1));
	for (p = path; ; p = z)
	{
		z = strchrnul(p, ':');
		if (z - p >= l)
		{
			if (!*z++)
				break;
			continue;
		}
		memcpy(b, p, z - p);
		b[z - p] = '/';
		memcpy(b + (z - p) + (z > p), file, k + 1);

		if (_assert(b) == 0)
			return (b);

		switch (errno)
		{
		case EACCES:
			seen_eacces = 1;
		case ENOENT:
		case ENOTDIR:
			break;
		default:
			return (NULL);
		}
		if (!*z++)
			break;
	}
	if (seen_eacces)
		errno = EACCES;
	return (NULL);
}

/**
 * _assert - checks if command is executable
 * @file:command name
 *
 * Return: 1 if true, 0 otherwise
 */
int _assert(const char *file)
{
	struct stat st;

	if (stat(file, &st) == 0)
		return (access(file, X_OK));
	else
		return (-1);
}
