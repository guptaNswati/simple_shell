#include "shell.h"

int main()
{
        char *input, **tokens, **spce;
	int i;

/*	signal(SIGINT, SIG_IGN); */
	while((i = _getline(&input, STDIN_FILENO)) != -1)
	{
		tokens = tokenize(input, ';');
		if (tokens == NULL)
			continue;
		while (*tokens)
		{
			spce = tokenize(*tokens, ' ');
/*			if (spce != NULL)
			{
				while (*spce)
				{
					printf("\n[tokens2] %s\n", *spce);
					spce++;
				}
				} */
			printf("\n[tokens] %s\n", *tokens);
			tokens++;
		}
	}
	return (0);
}
