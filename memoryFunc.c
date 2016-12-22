#include "shell.h"

/**
 * add_mem - Add a node to the memory linked list
 * @p: pointer to memory allocation
 * @head: head of memory linked list
 * Return: 1 on success, else return -1 on error
 */
int add_mem(void **p, save_mem **head)
{
	save_mem *newnode;

	/*create node */
	newnode = malloc(sizeof(save_mem));
	if (newnode == NULL)
		return (-1);
	newnode->loc = *p;

	if (!*head)
	{
		newnode->next = NULL;
		*head = newnode;
	}
	else
	{
		/* prepend to LL, FIFO */
		newnode->next = *head;
		*head = newnode;
	}

	return (1);
}

/**
 * remove_child_mem - Removes child process allocated memory.
 * @p: pointer to stop freeing.
 * @head: head of memory linked list
 * Return: 1 on success, 0 if all memory free'd
 */
int remove_child_mem(void **p, save_mem **head)
{
	save_mem *tmp, *hold;

	tmp = *head;
	while (tmp)
	{
		hold = tmp;
		tmp = tmp->next;
		if (hold->loc != NULL)
			free(hold->loc);
		free(hold);

		if (*p == tmp->loc)
			return (1);
	}

	return (0);
}

/**
 * remove_mem - Removes a single memory node or all memory nodes.
 * @p: if given, remove this node, else remove all nodes
 * @head: head of memory linked list
 * Return: 1 on success, or 0 if no nodes were free'd
 */
int remove_mem(void **p, save_mem **head)
{
	save_mem *tmp, *hold;

	tmp = *head;
	if (*p == NULL)
	{
		/* remove and free all nodes */
		while (tmp)
		{
			hold = tmp;
			tmp = tmp->next;
			if (hold->loc != NULL)
				free(hold->loc);
			free(hold);
		}
		*head = NULL;
		return (1);
	}

	/* remove only *p */
	hold = tmp;
	while (tmp)
	{
		if (tmp->loc == *p)
		{
			if (hold == tmp)
				*head = tmp->next;
			else
				hold->next = tmp->next;

			free(tmp->loc);
			free(tmp);
			return (1);
		}
		hold = tmp;
		tmp = tmp->next;
	}

	return (0);
}
