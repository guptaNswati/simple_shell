#include "shell.h"

/**
* *_realloc -  reallocates a memory block using malloc and free
* @ptr: void pointer
* @old_size: already allocated size
* @new_size: new size to allocate
* Return: pointer to newly allocated memory or null
**/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned char *np;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		_free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		ptr = _malloc(new_size * sizeof(void *));
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}
	np = _malloc(new_size * sizeof(char));
	if (np == NULL)
		return (NULL);
	i = 0;
	if (new_size > old_size)
	{
		while (i < old_size)
		{
			np[i] = ((char *)ptr)[i];
			i++;
		}
		_free(ptr);
		return (np);
	}
	/* if new_size < old_size */
	while (i < new_size)
	{
		np[i] = ((char *)ptr)[i];
		i++;
	}
	_free(ptr);
	return (np);
}

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

int _ref_mem(void *p, char *action)
{
	static save_mem *head = NULL;

	if (_strcmp(action, "create") == 0)
		return (add_mem(&p, &head));
	else if (_strcmp(action, "remove child") == 0)
		return (remove_child_mem(&p, &head));
	else if (_strcmp(action, "remove") == 0)
		return (remove_mem(&p, &head));

	return (-1);
}

void *_malloc(unsigned int size)
{
	void *p;
	int status;

	p = malloc(size);
	if (p == NULL)
		return (NULL);

	status = _ref_mem(p, "create");
	if (status < 0)
		return (NULL);

	return (p);
}

void _free(void *ptr)
{
	_ref_mem(ptr, "remove");
}
