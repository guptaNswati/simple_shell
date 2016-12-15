#include "shell.h"

extern char **environ;

int checkEnv(char *name)
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

void printEnv(char **tokens)
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

void _setenv(char **tokens)
{
	char *token, *new, **dupeenv;
	int i;

	i = checkEnv(tokens[0]);
	if (i == 0)
		return;
	new = _strcat(tokens[0], tokens[1], '=');
	if (new == NULL)
		return;
	i = 0;
	dupeenv = deepDupe(environ);
	for (i = 0; dupeenv[i]; i++)
	{
		token = strtok(dupeenv[i], "=");
		if (_strcmp(token, tokens[0]) == 0)
		{
			environ[i] = new;
			/*change value to given value and return 0 */
			return;
		}
	}
	environ[i] = new;
	environ[++i] = NULL;
}

void _unsetenv(char **tokens)
{
	char **newenv, **dupeenv;
	int i;
	char *token;

	i = checkEnv(tokens[1]);
	if (i == 0)
		return;

        dupeenv = deepDupe(environ);
	for (i = 0; dupeenv[i]; i++)
	{
		token = strtok(dupeenv[i], "=");
		/* delete variable name from environment */
		if (_strcmp(token, tokens[1]) == 0)
		{
			for (newenv = environ; *newenv != NULL; newenv++)
				*newenv = *(newenv + 1);
			*newenv = NULL;
			return;
		}
	}
/* name does not exist in the environment, function succeeds */
	printf("No such environment variable exists\n");
}
