#include "shell.h"

extern char **environ;

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

void printEnv(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
}

char *_getenv(char *name)
{
	char **dupeenv, *token;

	dupeenv = deepDupe(environ);
	while (*dupeenv)
	{
		token = strtok(*dupeenv, "=");
		if (_strcmp(token, name) == 0)
			return (strtok(NULL, "="));
 		dupeenv++;
	}
	return (NULL);
}

int _setenv(const char *name, const char *value, int overwrite)
{
	char *token, *new, **dupeenv;
	int i;

	i = checkEnv(name);
	if (i == 0)
		return (-1);
	new = _strcat(name, value, '=');
	if (new == NULL)
		return (-1);
	i = 0;
	dupeenv = deepDupe(environ);
	for (i = 0; dupeenv[i]; i++)
	{
		token = strtok(dupeenv[i], "=");
		if (_strcmp(token, name) == 0 && overwrite != 0)
		{
			environ[i] = new;
			/*change value to given value and return 0 */
			return (0);
		}
	}
	environ[i] = new;
	environ[++i] = NULL;
	return (0);
}

int _unsetenv(const char *name)
{
	char **newenv, **dupeenv;
	int i;
	char *token;

	i = checkEnv(name);
	if (i == 0)
		return (-1);

        dupeenv = deepDupe(environ);
	for (i = 0; dupeenv[i]; i++)
	{
		token = strtok(dupeenv[i], "=");
		/* delete variable name from environment */
		if (_strcmp(token, name) == 0)
		{
			for (newenv = environ; *newenv != NULL; newenv++)
				*newenv = *(newenv + 1);
			*newenv = NULL;
			return (0);
		}
	}
/* name does not exist in the environment, function succeeds */
	printf("No such environment variable exists\n");
	return (0);
}
