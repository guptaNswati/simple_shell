#include "shell.h"

static hstory *head = NULL;

char **split_input(char *input)
{
	int i;
	char **tokens, *tokn;

	tokens = _malloc(1024 * sizeof(char *));
 	if (tokens == NULL)
	{
		dprintf(STDERR_FILENO, "Allocation Error\n");
		ext(&input);  /* TEST */
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
	char *path, *tokn, *concat, *p;

	if (tokens[0][0] != '/')
	{
		if (_strcmp(tokens[0], "history") == 0)
		{
			printHistory(&head);
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

void prompt(void)
{
 	char *input, **tokens;
	ssize_t bufr;

	bufr = 0;
	input = NULL;
	/* ignore cntrl+C */
	signal(SIGINT, SIG_IGN);

	printf("$ ");
	while ((getline(&input, &bufr, stdin)) != -1)
/*while (getline(&input, &bufr, stdin) != -1) */
	{
		printf("[INPUT] %s\n", input);
		addHistory(&head, input);
		if (input[0] != '\n')
		{
			tokens = split_input(input);
			excute(tokens);
		}
		_free(tokens);
		printf("$ ");
	}
	ext(NULL);
}
