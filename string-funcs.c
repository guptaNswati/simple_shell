#include "shell.h"

/**
* _strlen - calculates a length of a given string
* @str: pointer to chars
* Return: lenght of string
**/
int _strlen(char *str)
{
	int len;

	for (len = 0; str[len] != '\0'; len++)
		;
	return (len);
}

/**
* _strcpy - copies a given string and returns a copy
* @strng: pointer to chars to be copied
* @i: number of chars to be copied
* Return: pointer to copy
**/
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

/**
* _strcmp - compares two strings
* @s1: string 1
* @s2: string 2
* Return: if both strings are same 0, else -1
**/
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


/**
* _strcat2 - concatenates two strings
* @str1: string 1
* @str2: string 2
* Retrun: pointer to new concatenated string
**/
char *_strcat2(char *str1, char *str2)
{
	char *new;
        int i, j;

        new = malloc(sizeof(char) * (_strlen(str1) + _strlen(str2) + 1));
        if (new == NULL)
                return (NULL);

        for (i = 0; str1[i] != '\0'; i++)
                new[i] = str1[i];
        for (j = 0; str2[j] != '\0'; j++, i++)
                new[i] = str2[j];

        new[i] = '\0';
        return (new);

}


/**
* _strcat - concatenates two strings adding a fomatter in between
* @str1: string 1
* @str2: string 2
* @formatter: char to add in between
* Return: pointer to new string
**/
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
