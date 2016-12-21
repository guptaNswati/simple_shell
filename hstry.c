#include "shell.h"

hstory *addHistory(hstory **head, char *input, int *nodeCount)
{
	hstory *new, *temp;
	int limit;

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
		if (*nodeCount > 4) /* replace with HSTRYLIMIT*/
			popHead(head, nodeCount);
	}
	return (new);
}

hstory *popHead(hstory **head, int *nodeCount)
{
	hstory *temp;

	temp = *head;
	*head = (*head)->next;
	free(temp);
	temp = NULL;
	*nodeCount -= 1;
	return (*head);

}


int readFromFile(const char *file, hstory **head, int *nodeCount)
{
	int fd, numNodes;
	char *input, *tokn, **tokns;
	ssize_t count;
	struct stat st;
	off_t filsiz;

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
		tokns = tokenize(input, '\n');
		if (tokns == NULL)
			return (numNodes);
		while (*tokns)
		{
			addHistory(head, *tokns, nodeCount);
			numNodes++, tokns++;
		}
	}
        close(fd);
        return (numNodes);
}

int writeHstorytofile(const char *file, hstory **head)
{
	int fd, count, inptLen;

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
		while (*head)
		{
			inptLen = _strlen((*head)->input);
			count = write(fd, (*head)->input, inptLen);
			if (count == -1 || count != inptLen)
				return (-1);
			count = write(fd, "\n", 1);
			if (count == -1)
                                return (-1);
			*head = (*head)->next;
		}
		close(fd);
		return (0);
	}
	close(fd);
	return (-1);
}

void printHistory(void **head)
{
	int i;
	hstory *start;

	(hstory **)head;
	if (head == NULL)
	{
		_puts("No history\n");
		return;
	}

	i = 0;
	start = *head;
	while (*head)
	{
		_puts("[");
		write(STDOUT_FILENO, &n, 1);
		_puts("]");
		_puts((*head)->input);
		_puts("\n");
		*head = (*head)->next;
		i++;
	}
	/* return the head after iterating */
	*head = start;
}
