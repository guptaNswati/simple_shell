#include "shell.h"

int main()
{
	char *input, **tokens;
	alias *temp;
	static alias *head = NULL;

	_puts("$ ");
	while (_getline(&input, STDIN_FILENO) != 0)
	{
		tokens = tokenize(input, ' ');
		if (tokens)
		{
			if (_strcmp(tokens[0], "alias") == 0)
			       temp = findAlias(&head, input);
			if (temp != NULL)
			{
				temp = find_aliasToalias(&head, temp->value);
				input = temp->value;
			}
			whichAlias(tokens, &head);
		}
	}
	return (0);
}
