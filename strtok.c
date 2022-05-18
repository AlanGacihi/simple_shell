/**
* _strtok - Own implementation of strtok.
* @base: String to evaluate.
* @delims: Delimiters for tokens.
* Return: Pointer to next token.
*/
char *_strtok(char *base, char *delims)
{
	static char *copy;
	static int i;
	int j = 0, word_found = -1, blanks = 0;
	char *ret_str;

	if (base)
	{
		i = 0;
		copy = base;
	}
	while (copy[i])
	{
		while (delims[j])
		{
			if (copy[i] == delims[j])
			{
				blanks = 1;
				if (word_found >= 0)
				{
					copy[i++] = '\0';
					ret_str = copy + word_found;
					return (ret_str);
				}
			}
			j++;
		}
		j = 0;
		if (word_found == -1 && !blanks)
		{
			word_found = i;
		}
		blanks = 0;
		i++;
	}
	if (word_found == -1)
		return (0);
	ret_str = copy + word_found;
	return (ret_str);
}
