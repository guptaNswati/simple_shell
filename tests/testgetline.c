#include "shell.h"

int main()
{
        char *input, **tokens;
	int i;

	/*i = _getline(&input, STDIN_FILENO);
	_line(input); */

/*	signal(SIGINT, SIG_IGN); */
	while((i = _getline(&input, STDIN_FILENO)) != -1)
	{
		tokens = tokenize(input, ' ');
		if (tokens == NULL)
			continue;
		while (*tokens)
		{
			printf("\n[tokens] %s\n", *tokens);  
			tokens++;
		}
/*			printf("\n[input] %s\n", input);
			printf("[i] %d\n", i); */
	}
	return (0);
}

/**
* run of _getline is as expected :)
**/
