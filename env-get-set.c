#include "shell.h"

/* for accesing environmental variables */
extern char **environ;

/**
* checkEnv - checks if environmenta variable name is null or contains '='
* @name: pointer to variable name
* Return: if name is valid returns its length, else 0
**/
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

/**
* _getenv - finds an environmental variable
* @name: pointer to variable name
* Return: pointer to found value or null
**/
char *_getenv(char *name)
{
	char **dupeenv, **token;

	dupeenv = deepDupe(environ);
	if (dupeenv == NULL)
		return (NULL);
	while (*dupeenv)
	{
		token = tokenize(*dupeenv, '=');
		if (_strcmp(token[0], name) == 0)
			return (token[1]);
 		dupeenv++;
	}
	return (NULL);
}

/**
* _setenv - sets an environment variable based on user input
* @tokens: pointer to user input
* Return: nothing
**/
void _setenv(char **tokens)
{
	char **token, *new, **dupeenv;
	int i;

	i = checkEnv(tokens[1]);
	if (i == 0)
		return;
	new = _strcat(tokens[1], tokens[2], '=');
	if (new == NULL)
		return;
	i = 0;
	dupeenv = deepDupe(environ);
	if (dupeenv == NULL)
                return;
	for (i = 0; dupeenv[i]; i++)
	{
		token = tokenize(dupeenv[i], '=');
		if (_strcmp(token[0], tokens[1]) == 0)
		{
			environ[i] = new;
			/*change value to given value and return 0 */
			return;
		}
	}
	environ[i] = new;
	environ[++i] = NULL;
}

/**
* _unsetenv - unsets an envriornment variable
* @tokens: pointer to user input
* Return: nothing
**/
void _unsetenv(char **tokens)
{
	char **dupeenv;
	int i;
	char **token;

	i = checkEnv(tokens[1]);
	if (i == 0)
		return;

        dupeenv = deepDupe(environ);
	if (dupeenv == NULL)
                return;
	for (i = 0; dupeenv[i]; i++)
	{
		token = tokenize(dupeenv[i], "=");
		/* delete variable name from environment */
		if (_strcmp(token[0], tokens[1]) == 0)
		{
			for (; environ[i] != NULL; i++)
				environ[i] = environ [i + 1];
			environ[i] = NULL;
			return;
		}
	}
/* name does not exist in the environment, function succeeds */
	_puts("No such environment variable exists\n");
}

/**
* printEnv - prints list of all environment variables
* @tokens: pointer to user input as part of builtin prototype
* Return: nothing
**/
void printEnv(char **tokens)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}
}
