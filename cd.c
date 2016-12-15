#include "shell.h"

void chng_dr(char **str)
{
	char *curnt_dir, *newcd;

	curnt_dir = getcwd(curnt_dir, 102);

	newcd = str[1];
	if (newcd == NULL)
		newcd = _getenv("HOME");
	else if (newcd[0] == '-')
 		newcd = _getenv("OLDPWD");
	int res = chdir(newcd);
	printf("res %d\n", res);
	printf("curnt %s\n", getcwd(NULL, 102));
	if (res == -1)
	{
		printf("%s\n", strerror(errno));
		free(curnt_dir);
		return;
	}
	_setenv("PWD", newcd, 1);
	_setenv("OLDPWD", curnt_dir, 1);
	free(curnt_dir);
}
