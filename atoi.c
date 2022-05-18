#include "shell.h"
#include <stdio.h>
/**
 * _atoi - converts a string to an integer
 * @s: pointer to an array of characters
 * Return: integer if there is a number or (0) if not
 */
int _atoi(char *s)
{
	int i = 0, j = 0;

	unsigned int n = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			j++;
		if (s[i] >= '0' && s[i] <= '9')
			n = n * 10 + s[i] - '0';
		else if (n > 0)
			break;
		i++;
	}
	if (i == 0)
		return (0);
	if (j % 2 != 0)
		n = (int) -n;
	return (n);
}
