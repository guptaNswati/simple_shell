#include "shell.h"

/* if its just alias, print alias */
/* if alias and some chars, findAlias */
/* if alias chars = value, add alias */

/* returns pointer to appropriate function */
whichAlias(char **tokens)
{
	char **newTokens;
	/* if theres only 1 token, call printAlias, tokens based on space */
	if (tokens[1] == NULL)
		return (printAlias);
	newTokens = tokenize(tokens[1], "=");
	if (newTokens[1] == NULL)
		return (findAlias);
	return addAlias(, newTokens[0], newTokens[1]);
}

alias *addAlias(alias **head, char *key, char *value)
{
	alias *new, *temp;

	new = _malloc(sizeof(alias));
	if (new == NULL)
		return (NULL);

	new->key = _strcpy(key, _strlen(key));
	if (new->key == NULL)
	{
		_free(new);
		return (NULL);
	}
	new->value = _strcpy(value, _strlen(value));
	if (new->value == NULL)
	{
		_free(new->key);
		_free(new);
		return (NULL);
	}
	new->next = NULL;

	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (new);
}

void printAlias(alias **head)
{
	int i;
	alias *start;


	if (head == NULL)
	{
		_puts("No alias found\n");
		return;
	}
	start = *head;
	while (*head)
	{
		_puts("alias ");
		_puts((*head)->key);
		_puts("='");
		_puts((*head)->value);
		_puts("'");
		*head = (*head)->next;
	}
	/* return the head after iterating */
	*head = start;
}

alias *findAlias(alias **head, char *key)
{
	if (head == NULL)
	{
		_puts("alias: ");
		_puts(key);
		_puts(": not found\n");
		return (NULL);
	}
	while (*head)
	{
		if (_strcmp((*head)->key, key) == 0)
			return ((*head)->value);
		*head = *head->next;
	}
	return (NULL);
}
