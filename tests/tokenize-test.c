#include "shell.h"

int main()
{
	char *input, **cmd;

	input = NULL;
	cmd = NULL;
	while (_getline(&input, STDIN_FILENO) != 0)
	{
		/* discard the begining spaces */
		input = linep_withoutspaces(input);
		/* command separator */
		cmd = tokenize(input, ' ');
	}
	return (0);
}
