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
* getAliasHead - intializes static head to struct alias
* for passing to functions
* Return: address of alias head
**/
alias **getAliasHead(void)
{
	static alias *head = NULL;

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
		p = NULL;
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
	char *input, **tokens, **cmds;
	int hstryCount, *hstryPtr, status;
	char *file;
	hstory **h_head;
	alias **a_head, *temp;

	h_head = getHistoryHead();
	a_head = getAliasHead();
	hstryCount = 0;
	hstryPtr = &hstryCount;
	file = _strcat(_getenv("HOME"), ".simple_shell_history", '/');
	/* read history from file */
	readFromFile(file, h_head, hstryPtr);

	status = 1;
	/* ignore cntrl+C */
	signal(SIGINT, SIG_IGN);
 	while (1)
	{
		if (status == 0)
			break;
		_puts("$ ");
		status = _getline(&input, STDIN_FILENO);
		addHistory(h_head, input, hstryPtr);
		/* discard the begining spaces */
		input = linep_withoutspaces(input);
		if (*input != '\0')
		{
			/* command separator */
			cmds = tokenize(input, ';');
			if (cmds)
			{
				while (*cmds)
				{
					/* add cyclic alias */
					temp = findAlias(a_head, *cmds);
					/* check if an alias is not pointing to itself */
					if (temp != NULL && (_strcmp(temp->key, temp->value) != 0))
					{
						temp = find_aliasToalias(a_head, temp->value);
						*cmds = temp->value;
					}
					tokens = tokenize(*cmds, ' ');
					if (tokens)
					{
						excute(tokens);
						_free(tokens);
					}
					cmds++;
				}
			}
			else
			{
				/* add cyclic alias */
				temp = findAlias(a_head, *cmds);
				/* check if an alias is not pointing to itself */
				if (temp != NULL && (_strcmp(temp->key, temp->value) != 0))
				{
					temp = find_aliasToalias(a_head, temp->value);
					*cmds = temp->value;
				}
				tokens = tokenize(*cmds, ' ');
				if (tokens)
				{
					excute(tokens);
					_free(tokens);
				}
			}
			_free(cmds);
		} /* input if block ends */
	}
	/* need to read history before exit */
	ext(NULL);
}
