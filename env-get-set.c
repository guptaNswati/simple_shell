#include "shell.h"

int checkEnv(const char *name)
{
	int i;

	if (name == NULL || *name == '\0')
		return (0);
	for (i = 0; name[i] != '\0'; i++)
	{
		if (name[i] == '=')
			return (0);
	}
	return (i);
}

int _strlen(const char *str)
{
	int len;

	for (len = 0; str[len] != '\0'; len++)
		;
	return (len);
}

void printEnv(void)
{
	extern char **environ;

	while (*environ)
	{
		printf("%s\n", *environ);
		environ++;
	}
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

	i = checkEnv(name);
	if (i == 0)
		return (-1);
	new = _strcat(name, value, '=');
	if (new == NULL)
		return (-1);
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

int _unsetenv(const char *name)
{
	extern char **environ;
	char **newenv;
	int i;
	char *token;

	i = checkEnv(name);
	if (i == 0)
		return (-1);
	while (*environ)
	{
		token = strtok(*environ, "=");
		/* delete variable name from environment */
		if (*token == *name)
		{
			for (newenv = environ; *newenv != NULL; newenv++)
				*newenv = *(newenv + 1);
			*newenv = NULL;
			return (0);
		}
		environ++;
	}
/* name does not exist in the environment, function succeeds */
	printf("No such environment variable exists\n");
	return (0);
}
