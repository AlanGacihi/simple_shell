#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
/**
 * print_number - prints an integer as if it were a string
 * @n: integer to print
 * Return: void
 */
void print_number(int n)
{
	unsigned int k;
	char letter[1];

	k = n;
	if (k / 10)
	{
		print_number(k / 10);
	}
	letter[0] = k % 10 + '0';
	write(STDIN_FILENO, letter, 1);
}
