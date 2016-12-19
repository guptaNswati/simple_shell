#include "shell.h"

char **tokenize(char *lineptr, char dlimtr)
{
	int i, j, indx;
	char *tmp, *line, **tokens;

	/* limit the size of input to be processed */
	tokens = malloc(sizeof(char *) * BUFRSIZE);
	if (tokens == NULL)
		return (NULL);

	tmp = lineptr;
	i = 0;
	indx = 0;
	while (*lineptr && indx < BUFRSIZE)
	{
		if (*lineptr == dlimtr)
		{
			line = malloc(sizeof(char) * i + 1);
			if (line == NULL)
				return (NULL);
			for (j = 0; j < i; j++, tmp++)
				line[j] = *tmp;
			line[j] = '\0';
			tokens[indx++] = line;
			/* set temp to begining of new line */
			tmp = lineptr + 1;
			i = 0;
		}
		/*	tokens = split_input(line); */
		i++;
		lineptr++;
	}
	/* could not find the delimiter */
	if (indx == 0)
	{
		tokens[indx] = tmp;
		return (tokens);
	}
	/* theres more to be read, discard it and return null */
	if (*lineptr != '\0')
	{
		dprintf(STDERR_FILENO, "Killed\n");
		return (NULL);
	}
	tokens[indx++] = tmp;
	tokens[indx] = NULL;
	return (tokens);
}


/* Ref: https://sourcecodebrowser.com/pecomato/0.0.15/gnu-getline_8c_source.html*/

ssize_t _getline(char **lineptr, int fd)
{
 	/* default line length */
	static int bufsz = BUFRSIZE;
	int readCount, charsRead;

	*lineptr = malloc(sizeof(char) * bufsz);
	if (*lineptr == NULL)
		return (-1);
	charsRead = 0;
	while ((readCount = read(fd, *lineptr + charsRead, bufsz)) != 0)
	{
		if (readCount == -1)
			return (-1);
		/* exit when find a new line */
		if (*(*lineptr + readCount + charsRead - 1) == '\n')
		{
			charsRead += readCount; /* increment the pointer to what is already read */
			return (charsRead);
		}
                /* else needs more memory */
		*lineptr = _realloc(*lineptr, bufsz, 2 * bufsz);
		if (*lineptr == NULL)
			return (-1);
		bufsz *= 2;
		charsRead += readCount; /* increment the pointer to what is already read */
	}
	return (readCount);
}
