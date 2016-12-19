#include "shell.h"

int _strlen(char *str)
{
	int len;

	for (len = 0; str[len] != '\0'; len++)
		;
	return (len);
}

char *_strcpy(char *strng, int i)
{
	int j;
	char *res;

	res = _malloc(sizeof(res) * (i + 1));
	if (res == NULL)
		return (NULL);
	for (j = 0; j < i; j++)
	{
		res[j] = *strng;
		strng++;
	}
	res[j] = '\0';
	return (res);
}

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		if (s1[i] == '\0')
			return (1);
		if (s1[i] != s2[i])
			return (-1);
	}
	return (0);
}

char *_strcat(char *str1, char *str2, char formatter)
{
	char *new;
	int i, j;

	new = _malloc(sizeof(char) * (_strlen(str1) + _strlen(str2) + 2));
	if (new == NULL)
		return (NULL);

	for (i = 0; str1[i] != '\0'; i++)
		new[i] = str1[i];

	new[i] = formatter;
	i++;

	for (j = 0; str2[j] != '\0'; j++, i++)
		new[i] = str2[j];

	new[i] = '\0';
	return (new);
}


char *_strtok(char *str, char *delim)
{
	strLL *head, *tmp;
	char *strg;
	int i;

	if (str == NULL)
		return (NULL);

	tmp = head;
	while (str[i] != '\0')
	{
		/* hit the first delimiter */
		if (str[i] == *delim)
		{
			strg = _strcpy(str, i);
			return (strg);
/*			head = malloc(sizeof(strLL));
			if (head == NULL)
				return (NULL);
			strg = _strcpy(str, i);
			printf("%s\n", strg);
			head->str = strg;
			head = head->next; */
			i = 0;
		}
		i++;
	}
	return (NULL);
}
