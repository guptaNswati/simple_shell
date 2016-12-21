#include "shell.h"

hstory *addHistory(char *input, int *nodeCount)
{
	hstory *new, *temp, **head;
	int limit;

	head = getHistoryHead();
	new = _malloc(sizeof(hstory));
	if (new == NULL)
		return (NULL);

	new->input = _strcpy(input, _strlen(input));
	if (new->input == NULL)
	{
		_free(new);
		return (NULL);
	}
	new->next = NULL;

	if (*head == NULL)
	{
		*head = new;
		*nodeCount += 1;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
		*nodeCount += 1;
		if (*nodeCount > 10) /* replace with HSTRYLIMIT*/
			popHead(nodeCount);
	}
	return (new);
}

hstory *popHead(int *nodeCount)
{
	hstory *temp, **head;

	head = getHistoryHead();
	temp = *head;
	*head = (*head)->next;
	free(temp);
	temp = NULL;
	*nodeCount -= 1;
	return (*head);

}


int readFromFile(char *file, int *nodeCount)
{
	int fd, numNodes, i, j;
	char *input, *tokn, **tokns;
	ssize_t count;
	struct stat st;
	off_t filsiz;
	hstory **head;

	head = getHistoryHead();
	numNodes = 0;
	if (stat(file, &st) == 0)
	{
		filsiz = st.st_size;
		input = _malloc(sizeof(char) * filsiz);
		if (input == NULL)
			return (-1);
		fd = open(file, O_RDONLY);
	        if (fd == -1)
		{
			_puts("could not open to read ");
			_puts(file);
			_puts("\n");
			_free(input);
			return (-1);
		}
		count = read(fd, input, filsiz);
		if (count == -1 || count != filsiz)
		{
			close(fd);
			_free(input);
			return (-1);
		}
		printf("input: %s\n", input);

		tokns = tokenize(input, '\n');
		if (tokns == NULL)
			return (numNodes);

		printf("PRINTING TOKENS:\n");
		for (i = 0; tokns[i]; i++)
		{
			for (j = 0; tokns[i][j]; j++)
				printf("tokens[%d][%d]: %c\n", i, j, tokns[i][j]);
		}

		while (*tokns)
		{
			addHistory(*tokns, nodeCount);
			numNodes++, tokns++;
		}
	}
        close(fd);
        return (numNodes);
}

int writeHstorytofile(char *file)
{
	int fd, count, inptLen;
	hstory **head, *temp;

	head = getHistoryHead();
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		_puts("could not open to write ");
		_puts(file);
		_puts("\n");
		return (-1);
	}
	if (head != NULL)
	{
		temp = *head;
		while (temp)
		{
			inptLen = _strlen(temp->input);
			count = write(fd, temp->input, inptLen);
			if (count == -1 || count != inptLen)
				return (-1);
			count = write(fd, "\n", 1);
			if (count == -1)
				return (-1);
			temp = temp->next;
		}
		close(fd);
		return (0);
	}
	close(fd);
	return (-1);
}

void printHistory(char **str)
{
	int i, j;
	hstory *start;
	hstory **head;

	head = getHistoryHead();
	if (head == NULL)
	{
		_puts("No history\n");
		return;
	}

	i = 0;
	start = *head;
	while (start)
	{
		_puts("[");
		_puts_num(i);
		_puts("]");
		_puts(start->input);
		if (start->input[_strlen(start->input) - 2] != '\n')
			_puts("\n");
		start = start->next;
		i++;
	}
	/* return the head after iterating */
/*	*head = start;*/
}
