#include "shell.h"

int _strlen(const char *str)
{
	int len;

	for (len = 0; str[len] != '\0'; len++)
		;
	return (len);
}

char *_getenv(const char *name)
{
	extern char **environ;
	char *token;

	while (*environ != NULL)
	{
		token = strtok(*environ, "=");
		if (*token == *name)
		{
			return (strtok(NULL, "="));
		}
 		environ++;
	}
	return (NULL);
}

int _setenv(const char *name, const char *value, int overwrite)
{
	extern char **environ;
	char *token, *new;
	int i, j;

	new = malloc(sizeof(char) * (_strlen(name) + _strlen(value) + 2));
	if (new == NULL)
		return (-1);
	/* copy the strings */

	for (i = 0; name[i] != '\0'; i++)
		new[i] = name[i];

	new[i] = '=';

	i++;
	for (j = 0; value[j] != '\0'; j++, i++)
		new[i] = value[j];

	new[i] = '\0';

	while (*environ != NULL)
	{
		token = strtok(*environ, "=");
		if (*token == *name && overwrite != 0)
		{
			*environ = new;
			/*change value to given value and return 0 */
			return (0);
		}
		environ++;
	}
	*environ = new;
	printf("new env: %s\n", *environ);
	environ++;
	*environ = NULL;
	return (0);
}
int main(void)
{
	char *match, *token;

	match = _getenv("PWD");
	if (match)
	{
		printf("PATH=%s\n", match);
		/* printing all directories of path  */
		printf("\nPrinting Path Directories:\n");
		token = strtok(match, ":");
		while (token)
		{
			printf("%s\n", token);
			token = strtok(NULL, ":");
		}
	}
	else
		printf("could not find the variable\n");

	_setenv("ZNB", "world", 1);
	return (0);
}
