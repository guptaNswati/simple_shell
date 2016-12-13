#include "shell.h"

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

int main(void)
{
	char *match;

	match = _getenv("PWD");
	if (match)
		printf("PATH=%s\n", match);
	else
		printf("could not find the variable\n");
	return (0);
}
