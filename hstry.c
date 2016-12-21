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


int readFromFile(const char *file, int *nodeCount)
{
	int fd, numNodes;
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
			printf("could not open in read %s", file);
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
		/*tokn = strtok(input, "\n"); */
		tokns = tokenize(input, '\n');
		if (tokns == NULL)
			return (numNodes);
		while (*tokns)
		{
			addHistory(*tokns, nodeCount);
			numNodes++, tokns++;
/*			tokn = strtok(NULL, "\n"); */
		}
	}
        close(fd);
        return (numNodes);
}

int writeHstorytofile(const char *file)
{
	int fd, count, inptLen;
	hstory **head;

	head = getHistoryHead();
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		printf("could not open %s in write", file);
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

void printHistory(char **str)
{
	int i;
	hstory *start;
	hstory **head;

	head = getHistoryHead();
	if (head == NULL)
	{
		printf("No history\n");
		return;
	}

	i = 0;
	start = *head;
	while (*head)
	{
		printf("[%d] %s \n", i, (*head)->input);
		*head = (*head)->next;
		i++;
	}
	/* return the head after iterating */
	*head = start;
}
