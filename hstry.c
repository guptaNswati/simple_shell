#include "shell.h"

hstory *addHistory(hstory **head, char *input)
{
	hstory *new, *temp;

	printf("in add\n");
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
