#include "shell.h"

int find_builtins(char **tokens)
{
	int i;
	in_built list[] = {{"alias", },
			     {"cd", chng_dr},
			     {"env", printEnv},
			     {"exit", ext},
			     {"help", hlp},
			     {"history", hstry},
			     {"printenv", printEnv},
			     {"setenv", _setenv},
			     {"unsetenv", _unsetenv},
	};

	for (i = 0; i < 9; i++)
	{
		if (_strcmp(tokens[0], list[i].s) == 0)
		{
			if (_strcmp(list[i].s, "setenv") == 0)
				tokens++;
			list[i].func(tokens);
			return (0);
		}
	}
	return (-1);
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
	dprintf(STDERR_FILENO, "No such command found\n");
}
