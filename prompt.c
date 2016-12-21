#include "shell.h"

/**
* getHistoryHead - intializes static head to struct hstry
* for passing to functions
* Return: address of hstrory head
**/
hstory **getHistoryHead(void)
{
	static hstory *head = NULL;

	return (&head);
}

/**
* excute - forks a parent process and wait for child process
* to complete executing its child process
* @tokens: pointer to user input
* Return: nothing
**/
void excute(char **tokens)
{
	pid_t pid;
	int status;
	char *p;

	if (tokens[0][0] != '/')
	{
		if (find_builtins(tokens) == 0)
			return;
	}
	pid = fork();
	if (pid == -1)
	{
 		_puts("Forking Error\n");
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
			_puts("No such file or directory\n");
	}
	else
		waitpid(pid, &status, 0);
}


/**
* linep_withoutspaces - remove empty the spaces from begining of
* input string recursively
* @line: input string
* Return: pointer to first non space char
**/
char *linep_withoutspaces(char *line)
{
	/* no need to null check, as empty string will not be passed  */
	if (*line == ' ')
	{
		line++;
		return (linep_withoutspaces(line));
	}
	return (line);
}

/**
* promptUser - prompts user and recieves and input
* Return: nothing and exits when user enters cntrlD
**/
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
		/* discard the begining spaces */
		input = linep_withoutspaces(input);
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
