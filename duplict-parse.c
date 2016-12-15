#include "shell.h"

strLL *parsePath(char *path, char *delim)
{
	strLL *head, *tmp, *newnode;
	char *str;
	int i, j, d, x;

	if (path == NULL)
		return (NULL);

	tmp = head;

	for (i = 0, j = 0; path[i]; i++)
	{
		for (d = 0; delim[d]; d++)
		{
			if (path[i] == delim[d])
			{
				str = malloc(i - j + 1);
				for (x = 0; x < (i - j); x++)
				{
					str[x] = path[j + x];
				}
				j = i + 1;
			}
		}
		newnode = malloc(sizeof(strLL));
		newnode->str = str;
		newnode->next = NULL;
		if (tmp == NULL)
			tmp = newnode;
		else
		{
			tmp->next = newnode;
			tmp = tmp->next;
		}
	}

	return (head);
}

char **deepDupe(char **args)
{
	char **storage;
	int i, j, total;

	for (i = 0, total = 0; args[i] != NULL; i++)
	{
		for (j = 0; args[i][j]; j++)
			;
		total += j;
	}

	storage = malloc(total * i);

	for (i = 0; args[i] != NULL; i++)
	{
		for (j = 0; args[i][j]; j++)
			;
		storage[i] = _strcpy(args[i], j);
	}

	return (storage);
}
