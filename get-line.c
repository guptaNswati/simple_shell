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
	charsRead = 0;
	while ((readCount = read(fd, *lineptr + charsRead, bufsz)) != 0)
	{
		if (readCount != bufsz)
		{
			charsRead += readCount; /* increment the pointer to what is already read */
			return (charsRead);
		}
                /* else needs more memory */
		*lineptr = _realloc(*lineptr, bufsz, 2 * bufsz);
		if (*lineptr == NULL)
			return (-1);
		charsRead += readCount; /* increment the pointer to what is already read */
	}
	return (readCount);
}
