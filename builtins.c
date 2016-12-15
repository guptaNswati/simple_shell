#include "shell.h"

void find_builtins(char **tokens)
{
	if (_strcmp(tokens[0], "cd") == 0)
	{
		chng_dr(tokens);
		return;
	}
	if (_strcmp(tokens[0], "env") == 0 ||
	    _strcmp(tokens[0], "printenv") == 0)
	{
		printEnv();
		return;
	}
}

void check_path(char **tokens)
{
	char *path, *tokn, *concat;

	path = _getenv("PATH");
	tokn = strtok(path, ":");
	while (tokn)
	{
		concat = _strcat(tokn, tokens[0], '/');
		if (concat)
		{
			if (execve(concat, tokens, NULL) != -1)
				break;
			tokn = strtok(NULL, ":");
		}
	}
}
