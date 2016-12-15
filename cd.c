#include "shell.h"

int chng_dr(char **str)
{
	char *home, *curnt_dir, *oldcd;

	curnt_dir = getcwd(curnt_dir, 1024);
	if (str[1] == NULL)
	{
		home = _getenv("HOME");
		if (chdir(home) != 0)
		{
			printf("%s\n", strerror(errno));
			return (-1);
		}
		_setenv("PWD", home, 1);
		_setenv("OLDPWD", curnt_dir, 1);
		free(curnt_dir);
		return (0);
	}
	if (str[1] == "-")
	{
		oldcd = _getenv("OLDPWD");
		if (oldcd != NULL)
		{
			if (chdir(oldcd) != 0)
			{
				printf("%s\n", strerror(errno));
				return (-1);
			}
			_setenv("PWD", oldcd, 1);
			_setenv("OLDPWD", curnt_dir, 1);
			free(curnt_dir);
			return (0);
		}
		return (-1);
	}
	if (chdir(str[1]) != 0)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	_setenv("PWD", str[1], 1);
	_setenv("OLDPWD", curnt_dir, 1);
	free(curnt_dir);
	return (0);
}
