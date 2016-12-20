#include "shell.h"

int main()
{
	char *fileaddrss = _getenv("HOME");
	char *file = _strcat(fileaddrss, ".simple_shell_history", '/');
	static hstory *head = NULL;
	int hstryCount = readFromFile("/home/vagrant/simple_shell/.simple_shell_history", &head);
	printf("[count] %d\n", hstryCount);
	addHistory(&head, "1");
	hstryCount++;
	addHistory(&head, "2");
	hstryCount++;
	addHistory(&head, "3");
	hstryCount++;
	if (hstryCount > 2)
		popHead(&head);
        addHistory(&head, "4");
	hstryCount++;
	printHistory(&head);
	writeHstorytofile("/home/vagrant/simple_shell/.simple_shell_history", &head);
	return (0);
}
