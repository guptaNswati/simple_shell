#include "shell.h"

void chng_dr(char **str)
{
	char *curnt_dir, *newcd, **setPwd, **setOwd;

	curnt_dir = NULL;
	newcd = NULL;
	setPwd = NULL;
	setOwd = NULL;

	curnt_dir = getcwd(curnt_dir, 102);
/*	_ref_mem(curnt_dir, "create");*/
	newcd = str[1];

	if ((newcd == NULL) || (_strcmp(newcd, "~") == 0) ||
	    (_strcmp(newcd, "$HOME") == 0))
		newcd = _getenv("HOME");
	else if (_strcmp(newcd, "-") == 0)
 		newcd = _getenv("OLDPWD");

	if (chdir(newcd) == -1)
	{
		printf("%s\n", strerror(errno));
		_free(curnt_dir);
		return;
	}
	setPwd = _malloc (sizeof (char *) * (3 + _strlen(newcd)));
	if (setPwd == NULL)
		return;
	setPwd[0] = "PWD", setPwd[1] = newcd;
	_setenv(setPwd);

	setOwd = _malloc (sizeof (char *) * (3 + _strlen(curnt_dir)));
        if (setOwd == NULL)
                return;
	setOwd[0] = "OLDPWD", setOwd[1] = curnt_dir;
	_setenv(setOwd);
	_free(curnt_dir);
	_free(setPwd);
	_free(setOwd);
}

void ext(char **str)
{
	printf("In exit\n");
	_free(NULL);
	_exit(10);
}

void hlp(char **str)
{
	printf("In help\n");
}
