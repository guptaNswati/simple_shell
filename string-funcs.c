#include "shell.h"

char *_strcpy(char *strng, int i)
{
	int j;
	char *res;

	res = malloc(sizeof(res) * (i + 1));
	if (res == NULL)
		return (NULL);
	for (j = 0; j < i; j++)
	{
		res[j] = *strng;
		strng++;
	}
	res[j] = '\0';

	return (res);
}

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

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

char *_strtok(char *str, const char *delim)
{
	strLL *head, *tmp;
	char *strg;
	int i;

	if (str == NULL)
		return (NULL);

	tmp = head;
	while (str[i] != '\0')
	{
		/* hit the first delimiter */
		if (str[i] == *delim)
		{
			strg = _strcpy(str, i);
			return (strg);
/*			head = malloc(sizeof(strLL));
			if (head == NULL)
				return (NULL);
			strg = _strcpy(str, i);
			printf("%s\n", strg);
			head->str = strg;
			head = head->next; */
			i = 0;
		}
		i++;
	}
	return (NULL);
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
