#include "shell.h"

int main()
{
        char *input;
	int i;

	/*i = _getline(&input, STDIN_FILENO);
	_line(input); */

	signal(SIGINT, SIG_IGN);
	while((i = _getline(&input, STDIN_FILENO)) != 0)
	{
		/*	printf("\n[input] %s\n", input);
			printf("[i] %d\n", i); */
	}
	return (0);
}

/**
* run of _getline is as expected :)
**/
