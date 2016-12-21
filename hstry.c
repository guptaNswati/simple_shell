#include "shell.h"

/**
* addHistory - adds user input to history linked list and
* pops head if list is bigger than HSTRYLIMIT
* @input: user input
* @nodeCount: pointer to history count
* Return: pointer to newly added history node
**/
hstory *addHistory(char *input, int *nodeCount)
{
	hstory *new, *temp, **head;

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
		if (*nodeCount > HSTRYLIMIT) /* replace with HSTRYLIMIT*/
			popHead(nodeCount);
	}
	return (new);
}

/**
* popHead - removes head of the history list and subtract node count
* @nodeCount: pointer to history count
* Return: pointer to new head
**/
hstory *popHead(int *nodeCount)
{
	hstory *temp, **head;

	head = getHistoryHead();
	temp = *head;
	*head = (*head)->next;
	_free(temp);
	temp = NULL;
	*nodeCount -= 1;
	return (*head);

}

/**
* readFromFile - reads history from file and populate the linkedlist
* @file: pointer to name of file
* @nodeCount: pointer to history count
* Return: number of added added to list or -1 on error
**/
int readFromFile(char *file, int *nodeCount)
{
	int fd, numNodes;
	char *input, **tokns;
	ssize_t count;
	struct stat st;
	off_t filsiz;

	numNodes = 0;
	if (stat(file, &st) == 0)
	{
		filsiz = st.st_size;
		input = _malloc(sizeof(char) * filsiz + 1);
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
			addHistory(*tokns, nodeCount);
			numNodes++, tokns++;
		}
	}
        close(fd);
        return (numNodes);
}

/**
* writeHstorytofile - writes history to histro file from history list
* @file: pointer to file name
* Return: 0 on success, -1 on error
**/
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
			if (temp->input[inptLen - 1] != '\n')
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

/**
* printHistory - prints history list
* @str: pointer to input as part of builtin prototype
* Return: nothing
**/
void printHistory(char **str)
{
	int i;
	hstory *start, **head;
	UNUSED(str);

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
		_puts("] ");
		_puts(start->input);

		if (start->input[_strlen(start->input) - 1] != '\n')
			_puts("\n");

		start = start->next;
		i++;
	}
	/* return the head after iterating */
/*	*head = start;*/
}
