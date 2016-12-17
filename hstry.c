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
		printf("lets see whats up in write history\n");
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
	char *input, *tokn;
	ssize_t count;
	struct stat st;
	off_t filsiz;

	numNodes = 0;
	if (stat(file, &st) == 0)
	{
		filsiz = st.st_size;
		input = malloc(sizeof(char) * filsiz);
		if (input == NULL)
			return (numNodes);
		fd = open(file, O_RDONLY);
	        if (fd == -1)
		{
			free(input);
			return (numNodes);
		}
		count = read(fd, input, filsiz);
		if (count == -1 || count != filsiz)
		{
			close(fd);
			free(input);
			return (numNodes);
		}
		tokn = strtok(input, "\n");
		while (tokn != NULL)
		{
			printf("input: %s\n", tokn);
			addHistory(head, tokn);
			numNodes++;
			tokn = strtok(NULL, "\n");
		}
	}
        close(fd);
        return (numNodes);
}
