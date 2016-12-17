#include "shell.h"

/* Ref: https://sourcecodebrowser.com/pecomato/0.0.15/gnu-getline_8c_source.html*/

ssize_t _getline(char **lineptr, int fd)
{
 	/* limiting user input to 1204 chars */
	static int bufsz = BUFRSIZE;
	int readCount, charsRead, totalRead;

	*lineptr = malloc(sizeof(char) * bufsz);
	if (*lineptr == NULL)
		return (-1);
	charsRead = 0;
	while ((readCount = read(fd, *lineptr, bufsz - charsRead)) != -1)
	{
		/* if line is less than 1204 chars, null terminate the string and return */
		if (readCount < bufsz - charsRead)
		{
			(*lineptr)[readCount + charsRead] = '\0';
			printf("[_getline < bufsz] %s\n", *lineptr);
			return (readCount);
		}
		/* else more memory is needed */
 		*lineptr = _realloc(*lineptr, bufsz, 2 * bufsz);
		if (*lineptr == NULL)
			return (-1);
		charsRead += readCount;
/*		printf("[_getline > bufsz] %s\n", *lineptr); */
	}
/*	if (readCount == 0)
	return (-1); */
	return (charsRead);
}
