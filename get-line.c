#include "shell.h"

ssize_t _getline(char **lineptr, int fd)
{
	int count;
	int bufr = 1024;

	*lineptr = malloc(sizeof(char) * bufr);
	if (*lineptr == NULL)
		return (-1);

	count = read(fd, *lineptr, bufr);
	if (count == -1)
	{
		free(*lineptr);
		return (-1);
	}
	return (count);
}
