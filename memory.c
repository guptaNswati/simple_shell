#include "shell.h"

static save_mem **head = NULL;

void add_mem(void *p)
{
	save_mem *newnode;

	/*create node */
	newnode = malloc(sizeof(save_mem));
	newnode->loc = &p;

	if (!head)
	{
		printf("hi\n");
		newnode->next = NULL;
		head = p;
		if (**(head->next) == NULL)
			printf("TRUE\n");
	}
	else
	{
		printf("prepending..\n");
		/* prepend to LL, FIFO */
		newnode->next = *head;
		*head = newnode;
	}

	printf("New node created: %p\n", &newnode);
}

void remove_mem(void *p)
{
	save_mem *tmp, *hold;

	tmp = *head;
	if (p == NULL)
	{
		/* remove and free all nodes */
		while (tmp)
		{
			hold = tmp;
			tmp = tmp->next;
			free(hold->loc);
			free(hold);
		}
		printf("Removed all nodes...\n");
	}
	printf("inside mid of remove_mem\n");
	//remove only *p
	while (tmp)
	{
		if (&tmp->loc == p)
		{
			if (!hold)
			{
				printf("inside setting head\n");
				*head = tmp->next;
			}
			else
			{
				hold->next = tmp->next;
			}

			free(tmp->loc);
			printf("akdjl\n");
			free(tmp);
			break;
		}
		hold = tmp;
		tmp = tmp->next;
	}

	printf("Removing nodes done\n");
}

void _ref_mem(void *p, char *action)
{
/*	static save_mem *head = NULL;*/
	save_mem *newnode;

	if (_strcmp(action, "create") == 0)
		add_mem(p);
	else if (_strcmp(action, "remove") == 0)
		remove_mem(p);
}

void *_malloc(unsigned int size)
{
	void *p;

	p = malloc(size);
	if (p == NULL)
		return (NULL);

	_ref_mem(p, "create");

	return (p);
}

void _free(void *ptr)
{
	_ref_mem(ptr, "remove");
}

void printLL()
{
	save_mem *tmp;
	int i;

	i = 1;
	tmp = *head;
	while (tmp != NULL)
	{
		printf("%d. pointer: %p\n", i, tmp);
		tmp = tmp->next;
		i++;
	}

	printf("end of printLL\n");
}

int main(void)
{

	char *a;
	int i, size;

	size = 2;

	a = _malloc(10);
	a[0] = 'a';
	a[1] = 'b';
	printLL();
	_free(a);
	printf("---\n");
	printLL();
/*
	for (i = 0; i < 20; i++)
	{
		_malloc(size);
	}
*/
/*	printf("PRINTING with printLL\n");
	printLL();
	printf("Done printing\n");
*/
	return (0);
}
