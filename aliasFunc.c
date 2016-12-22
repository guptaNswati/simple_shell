#include "shell.h"

/**
* whichAlias - given how an alias cmd is eneterd, calls right function
* @tokens: pointer to user input string
* @head: pointer to head of the alias list
* Return: nothing
**/
void whichAlias(char **tokens,)
{
	char **newTokens;
	alias **a_head, *temp;
	int i;

	a_head = getAliasHead();
	/* if theres only 1 token, call printAlias, tokens based on space */
	if (tokens[1] == NULL)
	{
		printAlias(a_head);
		return;
	}
	newTokens = tokenize(tokens[1], '=');
	if (newTokens[1] == NULL)
	{
		temp = findAlias(a_head, newTokens[0]);
		if (temp != NULL)
		{
			_puts("alias ");
			_puts(temp->key);
			_puts("='");
			_puts(temp->value);
			_puts("'");
		}
		else
		{
			_puts("alias: ");
			_puts(newTokens[0]);
			_puts(": not found\n");
		}
		return;
	}
	/* before craeting new alias check if there is space after key, if there is, it fails*/
	i = _strlen(newTokens[0]);
	if (newTokens[0][i - 1] == ' ')
	{
		_puts("alias: not found\n");
		return;
	}
	addAlias(a_head, newTokens[0], newTokens[1]);
}
