#include "shell.h"

int main()
{
	char *input, **tokens;
	static alias *head = NULL;

	_puts("$ ");
	while (_getline(&input, STDIN_FILENO) != 0)
	{
		tokens = tokenize(input, ' ');
		if (tokens)
		{
			if (_strcmp(tokens[0], "alias") == 0)
				whichAlias(tokens, &head);
		}
	}
	return (0);
}
