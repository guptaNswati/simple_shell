#include "shell.h"

void promptUser()
{
	char *input, **tokens;
	int hstryCount;
	int *hstryPtr = &hstryCount;
/*	static hstory *head = NULL; */

	const char *file = "/home/vagrant/simple_shell/.simple_shell_history";
	readFromFile(file, &head, hstryPtr);
	printf("[hstry count] %d\n", *hstryPtr);
	printf("$ ");
	while (_getline(&input, STDIN_FILENO) != -1)
	{
		addHistory(&head, input, hstryPtr);
		printf("[hstry count] %d\n", *hstryPtr);
		tokens = tokenize(input, ' ');
		if (tokens)
		{
			excute(tokens);
			free(tokens);
			printf("$ ");
		}
		/* need to read history before exit */
		writeHstorytofile(file, &head);
	}
	free(input);
}
