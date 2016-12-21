#include "shell.h"

alias *resetAlias(alias **head, char *key, char *value)
{
	alias *start;

	start = *head;
	while (*head)
        {
                if (_strcmp((*head)->key, key) == 0)
		{
			(*head)->value = _strcpy(value, _strlen(value));
			return (*head);
		}
                *head = (*head)->next;
        }
	*head = start;
	return (NULL);
}


alias *addAlias(alias **head, char *key, char *value)
{
	alias *new, *temp;
	int valueLen;

	new = _malloc(sizeof(alias));
	if (new == NULL)
		return (NULL);

	new->key = _strcpy(key, _strlen(key));
	if (new->key == NULL)
	{
		_free(new);
		return (NULL);
	}
	valueLen = _strlen(value);

	if (value[0] == '"')
	{
		value++;
		value[valueLen - 1] = '\0';
		valueLen -= 2;
	}
	new->value = _strcpy(value, valueLen);
	if (new->value == NULL)
	{
		_free(new->key);
		_free(new);
		return (NULL);
	}
	new->next = NULL;

	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	/* check if it already exits in the list */
	temp = resetAlias(head, key, value);
	if (temp != NULL)
	{
		_free(new->key);
		_free(new->value);
		_free(new);
		return (temp);
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return (new);
}

void printAlias(alias **head)
{
	int i;
	alias *start;

	if (*head == NULL)
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
		_puts("'\n");
		*head = (*head)->next;
	}
	/* return the head after iterating */
	*head = start;
}

alias *findAlias(alias **head, char *key)
{
	alias *start;

	start = *head;
	while (*head)
	{
		if (_strcmp((*head)->key, key) == 0)
			return (*head);
		*head = (*head)->next;
	}
	*head = start;
	return (NULL);
}


void whichAlias(char **tokens, alias **head)
{
	char **newTokens;
	alias *temp;
	int i;

	/* if theres only 1 token, call printAlias, tokens based on space */
	if (tokens[1] == NULL)
	{
		printAlias(head);
		return;
	}
	newTokens = tokenize(tokens[1], '=');
	if (newTokens[1] == NULL)
	{
		temp = findAlias(head, newTokens[0]);
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
	addAlias(head, newTokens[0], newTokens[1]);
}
