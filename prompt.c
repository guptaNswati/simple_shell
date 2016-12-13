#include "shell.h"

char *read_input()
{
	char *line;
	ssize_t bufr;

	line = NULL;
	bufr = 0;
	if (getline(&line, &bufr, stdin) == -1)
		return NULL;
	return line;
}

char **split_input(char *input)
{
	int i;
	char **tokens, *tokn;

	tokens = malloc(1024 * sizeof(char *));
	if (tokens == NULL)
	{
		dprintf(STDERR_FILENO, "allocation error\n");
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

	pid = fork();
	if (pid == -1)
	{
		dprintf(STDERR_FILENO, "Error forking\n");
		exit(0);
	}
	if (pid == 0)
	{
		if (execve(tokens[0], tokens, NULL) == -1)
			dprintf(STDERR_FILENO, "child process error\n");
	}
	else
		wait(&status);
}

void prompt(void)
{
 	char *input, **tokens;

	printf("$ ");
	do
	{
		input = read_input();
		if (input != NULL)
			printf("$ ");
		tokens = split_input(input);
	       	excute(tokens);
		free(input);
		free(tokens);
	}
	while (input != NULL);
}
int main(int argc, char **argv)
{
	prompt();
	return (0);
}
