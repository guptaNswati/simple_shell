#include "shell.h"

static hstory *head = NULL;

char **split_input(char *input)
{
	int i;
	char **tokens, *tokn;

	tokens = malloc(1024 * sizeof(char *));
 	if (tokens == NULL)
	{
		dprintf(STDERR_FILENO, "Allocation Error\n");
		exit (0);
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

	pid = fork();
	if (pid == -1)
	{
		dprintf(STDERR_FILENO, "Forking Error\n");
		exit(0);
	}
	if (pid == 0)
	{
		if (tokens[0][0] != '/')
		{
			if (_strcmp(tokens[0], "history") == 0)
				printHistory(&head);
			if (find_builtins(tokens) == -1)
				check_path(tokens);
		}
		else
		{
			if (execve(tokens[0], tokens, NULL) == -1)
				dprintf(STDERR_FILENO, "No such file or directory\n");
		}
	}
	else
		wait(&status);
}

void prompt(void)
{
 	char *input, **tokens;
	int terminator, hstryCount;
	ssize_t bufr;

	input = NULL;
	bufr = 0;
	terminator = 1;
	/* ignore cntrl+C */
	signal(SIGINT, SIG_IGN);
	hstryCount = 0;
	while (1)
	{
		printf("$ ");
		terminator = getline(&input, &bufr, stdin);
		if (terminator == -1)
			exit(0);
		addHistory(&head, input);
		hstryCount++;
		if (hstryCount > HSTRYLIMIT)
			popHead(&head);
		tokens = split_input(input);
		excute(tokens);
		free(tokens);
	}
	free(input);
	writeHstorytofile(&head);
}
