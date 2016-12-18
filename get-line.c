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
	while (*lineptr)
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
			printf("[line] %s\n", line);
			/* set temp to begining of new line */
			tmp = lineptr + 1;
			printf("[temp] %s\n", tmp);
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
		printf("[temp outside] %s\n", tmp);
		return (tokens);
	}
	tokens[indx++] = tmp;
	tokens[indx] = NULL;
	return (tokens);
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
