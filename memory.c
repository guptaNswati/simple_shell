#include "shell.h"

/**
* _realloc -  reallocates a memory block using malloc and free
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

/**
 * _ref_mem - Helper function that calls a memory add or remove function
 * @p: pointer to save in node, or remove from linked list
 * @action: string literal that determines which function to call
 * Return: -1 on error, else return value returned from other function call
 */
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

/**
 * _malloc - Malloc and save a pointer to malloc'd space for memory linked list
 * @size: size to malloc
 * Return: pointer to malloc or NULL on error
 */
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

/**
 * _free - Free based on pointer passed
 * @ptr: pointer to malloc'd memory to free, or if NULL, free all memory nodes
 */
void _free(void *ptr)
{
	_ref_mem(ptr, "remove");
}
