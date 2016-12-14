#include "shell.h"

typedef struct strLL
{
	char *str;
	struct strLL *next;
} strLL;


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

	printf("Deep Duping...\n");

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
