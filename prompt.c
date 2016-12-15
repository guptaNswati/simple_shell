#include "shell.h"

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
	int terminator;
	ssize_t bufr;

	input = NULL;
	bufr = 0;
	terminator = 1;
	/* ignore cntrl+C */
	signal(SIGINT, SIG_IGN);
	while (terminator != -1)
	{
		printf("$ ");
		terminator = getline(&input, &bufr, stdin);
		tokens = split_input(input);
		excute(tokens);
		free(tokens);
	}
	free(input);
	_exit(0);
}
