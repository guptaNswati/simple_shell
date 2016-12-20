#include "shell.h"

char **deepDupe(char **args)
{
	char **storage;
	int i, j, total;

	for (i = 0, total = 0; args[i] != NULL; i++)
	{
		j = _strlen(args[i]);
		total += j;
	}

	storage = _malloc(total * i);
	if (storage == NULL)
		return (NULL);

	for (i = 0; args[i] != NULL; i++)
	{
		j = _strlen(args[i]);
		storage[i] = _strcpy(args[i], j);
	}

	return (storage);
}
