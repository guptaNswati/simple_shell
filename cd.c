#include "shell.h"

/**
* chng_dr - changes directory and sets pwd and oldwpd
* @str: pointer to directory to be changed to
* Return: nothing
**/
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
		_puts(strerror(errno));
		_puts("\n");
		_free(curnt_dir);
		return;
	}
	setPwd = _malloc (sizeof (char *) * (3 + _strlen(newcd)));
	if (setPwd == NULL)
		return;
	setPwd[1] = "PWD", setPwd[2] = newcd;
	_setenv(setPwd);
	setOwd = _malloc (sizeof (char *) * (3 + _strlen(curnt_dir)));
        if (setOwd == NULL)
                return;
	setOwd[1] = "OLDPWD", setOwd[2] = curnt_dir;
	_setenv(setOwd);
	_free(curnt_dir);
	_free(setPwd);
	_free(setOwd);
}

/**
* ext - exits out of the program, with an exit status
* @str: pointer to string as part of builtins prototype
* Return: nothing
**/
void ext(char **str)
{
	int code;
	char *file;
	file = _strcat(_getenv("HOME"), ".simple_shell_history", '/');
	writeHstorytofile(file);
	_free(NULL);

	if (str == NULL)
	{
		/* default exit code 0 */
	  _exit(0);
	}
	else
	{
		_puts("Successfully exited!\n");
		/* exit code given in index 1 of array */
		code = _atoi(str[0]);  /* change according to how we want this */
		if (code > 0)
			_exit(code);
		else
			_exit(0);
	}
}

/**
* hlp - displays list of builtins and how to use them
* @str: pointer to string as a builtin prototype
* Return: nothing
**/
void hlp(char **str)
{
	int i, trigger;
	help_struct storage[] = {
		{"alias", "alias [key] [value]", alias_data},
		{"cd", "cd [dir]", cd_data},
		{"env", "env", env_data},
		{"exit", "exit", exit_data},
		{"help", "help [pattern ...]", help_data},
		{"history", "history", history_data},
		{"printenv", "printenv", env_data},
		{"setenv", "setenv name=value", setenv_data},
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
			_puts("simple_shell: help: no help topics match `");
			_puts(str[1]);
			_puts("`. Try `help`.\n");
		}
		return;
	}

	_puts(BBLU"\nSimple Shell"RESET);
	_puts(", version 0.01-release (x86_64-pc-linux-gnu)\n\n");
	_puts("These shell commands are defined interally.");
	_puts("Type `help` to see this list.\n");
	_puts("Type `help name` to find out more about the ");
	_puts("function `name`.\n\n");

	_puts("-----\n");
	for (i = 0; storage[i].cmd; i++)
	{
		_puts(" ");
		_puts(storage[i].synopsis);
		_puts("\n-----\n");
	}
}
