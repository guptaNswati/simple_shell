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
	if (tokens = NULL)
	{
		dprintf(STDERR_FILENO, "allocation error\n");
		exit (0);
	}
	tokn = strtok(input, " ");
	for (i = 0; tokn != NULL; i++)
		tokens[i] = tokn;
	tokens[i] = '\0';
	return (tokens);
}

int excute(char **tokens)
{
	pid_t pid, wpid;
	int status;

	if (tokens == NULL)
		return (-1);

	pid = fork();
	if (pid == 0)
	{
		if (execvp(tokens[0], tokens) == -1)
			dprintf(STDERR_FILENO, "child process error\n");
		exit (0);
	}
	else if (pid < 0)
		dprintf(STDERR_FILENO, "Error forking\n");

	else
	{
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

void prompt(void)
{
	char *input, **tokens;
	int status;

	do
	{
		printf("$ ");
		input = read_input();
		tokens = split_input(input);
		status = excute(tokens);
		free(input);
		free(tokens);
	}
	while (status);
}
int main(int argc, char **argv)
{
	prompt();
	return (0);
}
