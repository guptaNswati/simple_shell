#include "shell.h"

static hstory *head = NULL;

char **split_input(char *input)
{
	int i;
	char **tokens, *tokn;
	char *tmp; /* refactor this */

	tmp = "test";
	tokens = _malloc(1024 * sizeof(char *));
 	if (tokens == NULL)
	{
		dprintf(STDERR_FILENO, "Allocation Error\n");
		ext(&tmp);
	}
	tokn = strtok(input, " \n");
	i = 0;
	while (tokn != NULL)
	{
		tokens[i] = tokn;
		i++;
		tokn = strtok(NULL, " \n");
	}
	tokens[i] = NULL;
	return (tokens);
}

void excute(char **tokens)
{
	pid_t pid, wpid;
	int status, i;
	char *path, *tokn, *concat;
	char *tmp;  /* refactor this */

	tmp = "test";
	if (tokens[0][0] != '/')
	{
		if (_strcmp(tokens[0], "history") == 0)
			printHistory(&head);

		if (find_builtins(tokens) == 0)
			return;
	}

	pid = fork();
	if (pid == -1)
	{
		dprintf(STDERR_FILENO, "Forking Error\n");
		ext(&tmp);
	}
	if (pid == 0)
	{
		if (tokens[0][0] != '/')
			check_path(tokens);
		else if (execve(tokens[0], tokens, NULL) == -1)
			dprintf(STDERR_FILENO, "No such file or directory\n");
		_free(tokens);
	}
	else
		waitpid(pid, &status, 0);
}

void prompt(void)
{
 	char *input, **tokens;
	int terminator;
	ssize_t bufr;
	char *tmp; /* refactor this */

	tmp = "test";
	terminator = 1;
	/* ignore cntrl+C */
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		printf("$ ");
		terminator = getline(&input, &bufr, stdin);
		if (terminator == -1)
		{
			printf("\n");
			_exit(2);
		}
		_ref_mem(&input, "create");
		addHistory(&head, input);
		tokens = split_input(input);
		excute(tokens);
		_free(tokens);
	}
	_free(input);
}
