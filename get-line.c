#include "shell.h"

/* Ref: https://sourcecodebrowser.com/pecomato/0.0.15/gnu-getline_8c_source.html*/

ssize_t _getline(char **lineptr, int fd)
{
	/* limiting user input to 1204 chars */
	static int bufsz = BUFSIZE;
	int readCount;

	*lineptr = malloc(sizeof(char) * count);
	if (*lineptr == NULL)
		return (-1);
	while (readCount(read, fd, *lineptr, bufsz) != -1)
	{
		/* if line is less than 1204 chars, null terminate the string and return */
		if (readCount < bufsz)
		{
			(*lineptr)[readCount] = '\0';
			return (readCount);
		}
		/* else more memory is needed */
		bufsz = 2 * BUFSIZE;
		/* write our own realloc */
		*lineptr = relloc(*lineptr, bufsz);
		if (*lineptr == NULL)
			return (-1);
	}
	if (readCount == 0)
		return (-1);
	return (readCount);
}
