#include "shell.h"

void chng_dr(char **str)
{
	char *curnt_dir, *newcd, **setPwd, **setOwd;

	curnt_dir = NULL;
	newcd = NULL;
	setPwd = NULL;
	setOwd = NULL;

	curnt_dir = getcwd(curnt_dir, 102);
	_ref_mem(curnt_dir, "create");
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
	int code;
	hstory **head;
	const char *file;

	printf("In exit\n");

	head = getHistoryHead();
	file = _strcat(_getenv("HOME"), ".simple_shell_history", '/');
	writeHstorytofile(file);
	_free(NULL);

	if (str == NULL)
	{
		/* default exit code 10 */
		_exit(10);
	}
	else
	{
		/* exit code given in index 1 of array */
		code = _atoi(str[0]);  /* change according to how we want this */
		if (code > 0)
			_exit(code);
		else
			_exit(10);
	}

}

void hlp(char **str)
{
	int i, trigger;
	help_struct storage[] = {
		{"cd", "cd [dir]", cd_data},
		{"env", "env", env_data},
		{"exit", "exit", exit_data},
		{"help", "help [pattern ...]", help_data},
		{"printenv", "printenv", env_data},
		{"setenv", "setenv name value", setenv_data},
		{"unsetenv", "unsetenv name", unsetenv_data},
		{NULL, NULL, NULL}
	};

	if (str[1])
	{
		for (i = 0, trigger = 1; storage[i].cmd != NULL; i++)
		{
			if (_strcmp(str[1], storage[i].cmd) >= 0)
			{
				storage[i].func(storage[i].cmd);
				trigger = 0;
			}
		}
		if (trigger)
		{
			printf("simple_shell: help: no help topics match `%s`."
			       " Try `help`.\n", str[1]);
		}
		return;
	}

	printf(BBLU"\nSimple Shell"RESET
	       ", version 0.01-release (x86_64-pc-linux-gnu)\n\n"
	       "These shell commands are defined interally."
	       "Type `help` to see this list.\n"
	       "Type `help name` to find out more about the "
	       "function `name`.\n\n");

	printf("-----\n");
	for (i = 0; storage[i].cmd; i++)
	{
		printf(" %s\n", storage[i].synopsis);
		printf("-----\n");
	}
}
