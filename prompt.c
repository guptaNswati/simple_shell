#include "shell.h"

void excute(char **tokens, hstory **head)
{
	pid_t pid, wpid;
	int status, i;
	char *path, *tokn, *concat, *p;

	if (tokens[0][0] != '/')
	{
		if (_strcmp(tokens[0], "history") == 0)
		{
			printHistory(head);
			return;
		}

		if (find_builtins(tokens) == 0)
		{
			_free(tokens);
			return;
		}
	}

	pid = fork();
	if (pid == -1)
	{
 		dprintf(STDERR_FILENO, "Forking Error\n");
		ext(NULL);
	}
	if (pid == 0)
	{
		/* Create a special node at beginning of child.. */
		/* After child is done, free up all nodes until this node */
		/* NOTE: because nodes were prepended */

		if (tokens[0][0] != '/')
			check_path(tokens, p);

		else if (execve(tokens[0], tokens, NULL) == -1)
			dprintf(STDERR_FILENO, "No such file or directory\n");
 		_ref_mem(&p, "remove child");
	}
	else
		waitpid(pid, &status, 0);
}

void promptUser()
{
	char *input, **tokens;
	int hstryCount, *hstryPtr;
	const char *file;
	static hstory *head = NULL;

	hstryPtr = &hstryCount;
	file = _strcat(_getenv("HOME"), "simple_shell/.simple_shell_history", '/');
	/* read history from file */
	readFromFile(file, &head, hstryPtr);

	/* ignore cntrl+C */
	signal(SIGINT, SIG_IGN);
	_puts("$ ");
	while (_getline(&input, STDIN_FILENO) != 0)
	{
		addHistory(&head, input, hstryPtr);
/* add command separator */
		tokens = tokenize(input, ' ');
		if (tokens)
		{
			excute(tokens, &head);
			_free(tokens);
		}
		_puts("$ ");
		writeHstorytofile(file, &head);
	}
	/* need to read history before exit */
	ext(NULL);
}
