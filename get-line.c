#include "shell.h"

void _line(char *lineptr)
{
	int i, j;
	char *tmp, *line, **tokens;

	tmp = lineptr;
	i = 0;
	while (*lineptr)
	{
		if (*lineptr == '\n')
		{
			line = malloc(sizeof(char) * i + 1);
			if (line == NULL)
				return;
			for (j = 0; j < i; j++, tmp++)
				line[j] = *tmp;
			line[j] = '\0';
			printf("[line] %s\n", line);
			/* set temp to begining of new line */
			tmp = lineptr + 1;
			i = 0;
		}
		/*	tokens = split_input(line); */
		i++;
		lineptr++;
	}
}


/* Ref: https://sourcecodebrowser.com/pecomato/0.0.15/gnu-getline_8c_source.html*/

ssize_t _getline(char **lineptr, int fd)
{
 	/* default line length */
	static const int bufsz = BUFRSIZE;
	int readCount, charsRead;

	*lineptr = malloc(sizeof(char) * bufsz);
	if (*lineptr == NULL)
		return (-1);

	readCount = read(fd, *lineptr, bufsz);
	/* error checking */
	if (readCount == -1)
		return (-1);
	if (readCount < bufsz)
		return (readCount);
	/* else needs more memory */
	charsRead = readCount; /* increment the pointer to what is already read */
	/* allocate more memory */
	*lineptr = _realloc(*lineptr, bufsz, 2 * bufsz);
	if (*lineptr == NULL)
		return (-1);
 	while ( (readCount = read(fd, *lineptr + charsRead, bufsz)) != 0)
	{
		*lineptr = _realloc(*lineptr, bufsz, 2 * bufsz);
		if (*lineptr == NULL)
			return (-1);
		charsRead += readCount;
	}
		printf("[input outside] %s\n", *lineptr);
	return (charsRead);
}
