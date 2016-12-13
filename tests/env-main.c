#include "shell.h"

int main(int ac, char **av, char **env)
{
	extern char **environ;

	while (*environ != NULL)
	{
		printf("%s\n", *environ);
		environ++;
	}
	return (0);
}
