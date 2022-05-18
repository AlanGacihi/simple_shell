#include "shell.h"
/**
* check_newlines - Checks for newlines in command.
* @av: vector of arguments for the command.
* @idx: Pointer to variable to save the index if found.
* Return: 0 if \n or ; 1 if &&, 2 if ||, and 3 if #.
*/
short check_newlines(char *av, short *idx)
{
	short i = 0, retv = -1;

	while (av[i])
	{
		if (av[i] == '\n' || av[i] == ';' || (av[i] == '&' && av[i + 1] == '&') ||
			(av[i] == '|' && av[i + 1] == '|') || av[i] == '#')
		{
			switch (av[i])
			{
				case '&':
					retv = 1;
					av[i] = '\0';
					i++;
					break;
				case '|':
					retv = 2;
					av[i] = '\0';
					i++;
					break;
				case '#':
					retv = 3;
					break;
				default:
					retv = 0;
					break;
			}
			av[i] = '\0';
			*idx = ++i;
			break;
		}
		i++;
	}
	return (retv);
}
