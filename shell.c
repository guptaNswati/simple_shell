#include "shell.h"

void promptUser()
{
	char *input, **tokens;

	printf("$ ");
	while (_getline(&input, STDIN_FILENO) != -1)
	{
		tokens = tokenize(input, ' ');
		if (tokens)
		{
			excute(tokens);
			free(tokens);
			printf("$ ");
		}
	}
	free(input);
}
