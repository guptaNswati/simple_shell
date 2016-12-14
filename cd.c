#include "shell.h"

int chng_dr(char **str)
{
	if (str[1] == NULL)
	{
		dprintf(STDERR_FILENO, "No directory specified, \
expects arguements to cd\n");
		return (-1);
	}
	if (chdir(str[1]) != 0)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	return (0);
}
