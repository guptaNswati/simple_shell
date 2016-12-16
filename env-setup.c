#include "shell.h"

extern char **environ;

void env_add_node(environsLL **head, char *name, char *value)
{
	environsLL *tmp, *newnode;
	int i, j;

	tmp = *head;
	newnode = malloc(sizeof(environsLL));
	if (newnode == NULL)
		exit(3);
	newnode->name = name;
	newnode->value = value;
	newnode->next = NULL;
	if (tmp == NULL)
		*head = newnode;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newnode;
	}
}

strLL *createPathLL(char *value)
{
	strLL *head, *tmp, *newnode;
	int i, j, k, len;
	char *cpstr;

	len = _strlen(value);
	tmp = NULL;
	for (i = 0, j = 0; i < len; i++)
	{
		if (value[i] == ':' || value[i] == '\0')
		{
			cpstr = malloc(i + 1);
			for (k = 0; j < i; j++, k++)
				cpstr[k] = value[j];
			cpstr[k] = '\0';

			newnode = malloc(sizeof(strLL));
			newnode->str = cpstr;
			newnode->next = NULL;

			if (tmp == NULL)
			{
				tmp = newnode;
				head = newnode;
			}
			else
			{
				tmp->next = newnode;
				tmp = tmp->next;
			}
			j++;
		}
	}

	return (head);
}

strLL *createEnvLL(environsLL **head)
{
        environsLL *tmp, *newnode;
	strLL *hold;
        char *name, *value;
        int i, j, nlen, tlen, trigger;

        tmp = *head;
        for (i = 0; environ[i]; i++)
        {
                trigger = 1;
                for (nlen = 0, tlen = 0; environ[i][tlen]; tlen++)
                {
                        if (environ[i][tlen] == '=')
                                trigger = 0;
                        if (trigger)
                                nlen++;
		}
                /* tlen is entire length minus name length */
                tlen = tlen - nlen;

                name = malloc(nlen);
                for (j = 0; j < nlen; j++)
                        name[j] = environ[i][j];

                value = malloc(tlen);
                for (j++; j < (nlen + tlen); j++)
                        value[j - nlen - 1] = environ[i][j];

		/* if PATH found, create strLL for PATH */
		if (_strcmp(name, "PATH") == 0)
			hold = createPathLL(value);

		env_add_node(head, name, value);
        }
	return (hold);
}

/**
 * NOTE: Temporary function to test
 */
void print_envLL(environsLL **head)
{
	environsLL *tmp;
	int i;

	tmp = *head;
	i = 0;
	while(tmp != NULL)
	{
		printf("%d\n", i);
		printf("%s %s\n", tmp->name, tmp->value);
		tmp = tmp->next;
		i++;
	}
}

/**
 * NOTE: Temporary function to test
 */
void print_path(strLL **head)
{
	strLL *tmp;
	int i;

	tmp = *head;
	while (tmp != NULL)
	{
		printf("%d\n", i);
		printf("%s\n", tmp->str);
		i++;
		tmp = tmp->next;
	}
}
/*
int main(void)
{
        environsLL *head;
	strLL *path;

	head = NULL;
	printf("Starting...\n\n");
	path = createEnvLL(&head);

	print_envLL(&head);

	print_path(&path);

	printf("Ended...\n\n");
}
*/
