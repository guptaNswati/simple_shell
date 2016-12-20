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
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			printf("[node in add] %s\n", temp->input);
			temp = temp->next;
		}
		temp->next = new;
	}
	return (new);
}

hstory *popHead(hstory **head)
{
	hstory *temp;

	printf("poping head\n");
	temp = *head;
	printf("[tmp in pop] %s\n", temp->input);
	*head = (*head)->next;
	free(temp);
	temp = NULL;
	return (*head);

}


int readFromFile(const char *file, hstory **head)
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
		/*tokn = strtok(input, "\n"); */
		tokns = tokenize(input, '\n');
		if (tokns == NULL)
			return (numNodes);
		while (*tokns)
		{
			printf("[last char in read] %c\n", _strlen(*tokns) - 1);
			printf("[token in raed] %s\n", *tokns);
			addHistory(head, *tokns);
			numNodes++, tokns++;
/*			tokn = strtok(NULL, "\n"); */
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
		printf("could not open %s in write", file);
		return (-1);
	}
	if (head != NULL)
	{
		while (*head)
		{
			inptLen = _strlen((*head)->input);
			printf("[node from write] %s\n", (*head)->input);
			count = write(fd, (*head)->input, inptLen);
			/*	if (count == -1 || count != inptLen)
				return (-1); */
			count = write(fd, "\n", 1);
			/*	if (count == -1)
                                return (-1); */
			*head = (*head)->next;
		}
		close(fd);
		return (0);
	}
	close(fd);
	return (-1);
}

void printHistory(hstory **head)
{
	int i;
	hstory *start;


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
