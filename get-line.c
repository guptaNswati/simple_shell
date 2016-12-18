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
	int readCount, charsRead, totalRead;

	*lineptr = malloc(sizeof(char) * bufsz);
	if (*lineptr == NULL)
		return (-1);
	charsRead = 0;
	signal(SIGINT, SIG_IGN);
	while ((readCount = read(fd, *lineptr, 12)) != 0)
	{
		_line(*lineptr);
		/* if line is less than 1204 chars, null terminate the string and return */
		/*	if (readCount < bufsz - charsRead)
		{
			(*lineptr)[readCount + charsRead] = '\0';
			printf("[_getline < bufsz] %s\n", *lineptr);
			return (readCount);
			} */
		/* else more memory is needed */
 		*lineptr = _realloc(*lineptr, bufsz, 2 * bufsz);
		if (*lineptr == NULL)
			return (-1);
		charsRead += readCount;
/*		printf("[_getline > bufsz] %s\n", *lineptr); */
	}
/*	if (readCount == 0)
	return (-1); */
/*	_line(*lineptr); */
	return (12);
}
