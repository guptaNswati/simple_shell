#include "shell.h"

void excute(char **tokens)
{
	pid_t pid;
	int status;
	char *p;

	if (tokens[0][0] != '/')
	{
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

hstory **getHistoryHead(void)
{
	static hstory *head = NULL;

	return (&head);
}

void promptUser(void)
{
	char *input, **tokens;
	int hstryCount, *hstryPtr;
	char *file;
	alias *temp;
	static alias *head = NULL;

	hstryPtr = &hstryCount;
	file = _strcat(_getenv("HOME"), ".simple_shell_history", '/');
	/* read history from file */
	readFromFile(file, hstryPtr);

	/* ignore cntrl+C */
	signal(SIGINT, SIG_IGN);
	_puts("$ ");
	while (_getline(&input, STDIN_FILENO) != 0)
	{
		addHistory(input, hstryPtr);
		/* remove empty spaces from begining */
		/* add cyclic alias */
/*
		temp = findAlias(&head, input);
		if (temp != NULL)
		{
			temp = find_aliasToalias(head, temp->value);
			input = temp->value;
		}
*/
		/* alias */
		/* looking through aliases and call tokenize. */
/* add command separator */
		tokens = tokenize(input, ' ');
		if (tokens)
		{
			excute(tokens);
			_free(tokens);
		}
		_puts("$ ");
	}

	/* need to read history before exit */
	ext(NULL);
}
