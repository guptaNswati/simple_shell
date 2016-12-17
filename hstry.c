#include "shell.h"

hstory *addHistory(hstory **head, char *input)
{
	hstory *new, *temp;
	int limit;

	new = malloc(sizeof(hstory));
	if (new == NULL)
		return (NULL);

	new->input = _strcpy(input, _strlen(input));
	if (new->input == NULL)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;

	if (*head == NULL)
		*head = new;

	else if ((*head)->next == NULL)
		(*head)->next = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (new);
}

hstory *popHead(hstory **head)
{
	hstory *temp;

	temp = *head;
	*head = (*head)->next;
	free(temp);
	temp = NULL;
	return (*head);

}
void printHistory(hstory **head)
{
	int i;

	i = 0;
	while (*head)
	{
		printf("[%d] %s \n", i, (*head)->input);
		*head = (*head)->next;
		i++;
	}
}

int writeHstorytofile(const char *file, hstory **head)
{
	int fd, count, inptLen;
	char *inpt;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | S_IRUSR | S_IWUSR);
		if (fd == -1)
			return (-1);
	if (*head)
	{
		while (*head)
		{
			inptLen = _strlen((*head)->input) + 1;
			inpt = _strcat2(inpt, "\n");
			count = write(fd, inpt, inptLen);
			if (count == -1 || count != inptLen)
				return (-1);
			*head = (*head)->next;
		}
	}
	close(fd);
	return (0);
}

int readFromFile(const char *file, hstory **head)
{
	int fd, numNodes;
	char *input;
	ssize_t bufr, count;
	FILE *strm;

	input = NULL;
	bufr = 0;
	numNodes = 0;
	strm = fopen(file, "r");
	/*  fd = open(strm, O_RDONLY);
	    if (fd == -1) */
	if (strm == NULL)
		return (numNodes);
	while (1)
	{
		count = getline(&input, &bufr, strm);
		if (count == -1)
		{
			close(fd);
			return (numNodes);
		}
		addHistory(head, input);
		numNodes++;
	}
        close(fd);
        return (numNodes);
}
