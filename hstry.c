#include "shell.h"

hstry *addHistory(hstry *head, char *input)
{
	hstry *new, *temp;

	new = malloc(sizeof(hstry));
	if (new == NULL)
		return (NULL);

	new->input = strcpy(input, _strlen(input));
	if (new->str == NULL)
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
	return (head);
}

void printHistory(hstry *head)
{
	int i;

	i = 0;
	while (head)
	{
		printf("[%d] %s \n", i, head->input);
		head = head->next;
		i++;
	}
}

void hstry(hstry *head)
{
        printf("In history\n");
        printHistory(head);
}
