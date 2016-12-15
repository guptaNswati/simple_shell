#include "shell.h"

void chng_dr(char **str)
{
	char *curnt_dir, *newcd, **setPwd, **setOwd;

	curnt_dir = getcwd(curnt_dir, 102);

	newcd = str[1];
	if ((newcd == NULL) || (_strcmp(newcd, "~") == 0) ||
	    (_strcmp(newcd, "$HOME") == 0))
		newcd = _getenv("HOME");
	else if (_strcmp(newcd, "-") == 0)
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
	setPwd[0] = "PWD", setPwd[1] = newcd;
	_setenv(setPwd);
	setOwd[0] = "OLDPWD", setOwd[1] = curnt_dir;
	_setenv(setOwd);
	free(curnt_dir);
}

void ext(char **str)
{
	printf("In exit\n");
}

void hlp(char **str)
{
	printf("In help\n");
}

void hstry(char **str)
{
	printf("In history\n");
}
