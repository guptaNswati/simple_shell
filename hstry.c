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

hstory popHead(hstory **head)
{
	hstory temp;

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

int writeHstorytofile(FILE, hstory **head)
{
	int fd, count, inptLen;

	fd = open(FILE, O_WRONLY | S_IWUSR)
		if (fd == -1)
			return (-1);
	if (*head)
	{
		while (*head)
		{
			inptLen = _strlen((*head)->input);
			count = write(fd, (*head)->input"\n", inptLen + 1);
			if (count == -1 || count != inptLen)
				return (-1);
			*head = (*head)->next;
		}
	}
	close(fd);
	return (0);
}

int readFromFile(FILE, hstory **head)
{
	int fd, count, i;
	char input;
	char bufr[BUFRSIZE];

        fd = open(FILE, O_RDONLY)
                if (fd == -1)
                        return (-1);
	while (1)
	{
		i = 0;
		while (input != '\n')
		{
			count = read(fd, input, 1);
			if (count = -1)
				return (-1);
			bufr[i++] = input;
		}
		bufr[i++] = '\0';
		addHistory(head, bufr);
	}
        close(fd);
        return (0);
}
