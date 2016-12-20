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
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	return (*head);
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
	hstory *start;

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

int writeHstorytofile(const char *file, hstory **head)
{
	int fd, count, inptLen;
	char *inpt;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		printf("could not open %s in write", file);
		return (-1);
	}
	if (*head != NULL)
	{
		while (*head)
		{
			inptLen = _strlen((*head)->input);
			count = write(fd, (*head)->input, _strlen((*head)->input));
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
			return (-1);
		fd = open(file, O_RDONLY);
	        if (fd == -1)
		{
			printf("could not open in read %s", file);
			free(input);
			return (-1);
		}
		count = read(fd, input, filsiz);
		if (count == -1 || count != filsiz)
		{
			close(fd);
			free(input);
			return (-1);
		}
		tokn = strtok(input, "\n");
		while (tokn)
		{
			addHistory(head, tokn);
			numNodes++;
			tokn = strtok(NULL, "\n");
		}
	}
        close(fd);
        return (numNodes);
}
