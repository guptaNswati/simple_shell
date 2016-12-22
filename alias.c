#include "shell.h"

/* for tracking the last found alias match */
static alias *match = NULL;

/**
* resetAlias - resets an alias to given values, if found in the list
* @head: pointer to head of the alias list
* @key: key to look for
* @value: value to set to key
* Return: a pointer to found alias or null
**/
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

/**
 * addAlias - either add an alias to given value or adds new
 * @head: pointer to head of the alias list
 * @key: key to look for
 * @value: value to set to key
 * Return: a pointer to new alias
 **/
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

/**
 * printAlias - prints an alias list
 * @head: pointer to head of the alias list
 * Return: nothing
 **/
void printAlias(alias **head)
{
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

/**
 * findAlias - finds an alias to given key, if found in the list
 * @head: pointer to head of the alias list
 * @key: key to look for
 * Return: a pointer to found alias or null
 **/
alias *findAlias(alias **head, char *key)
{
	alias *start;

	start = *head;
	while (*head)
	{
		if (_strcmp((*head)->key, key) == 0)
		{
			match = *head;
			return (*head);
		}
		*head = (*head)->next;
	}
	*head = start;
	return (NULL);
}

/**
 * find_aliasToalias - checks recursively for an alais to an alias to an alias
 * @head: pointer to head of the alias list
 * @key: key to look for
 * Return: a pointer to found alias
 **/
alias *find_aliasToalias(alias **head, char *key)
{
	alias *temp;

	temp = findAlias(head, key);
	if (temp == NULL)
		return (match);
	/* check if its pointing to itself */
	if (_strcmp(temp->key, temp->value) == 0)
	{
		match = temp;
		return (temp);
	}
	/* recursively find the next match */
	return (find_aliasToalias(head, temp->value));
}
