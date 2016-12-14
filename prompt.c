#include "shell.h"

char **split_input(char *input)
{
	int i;
	char **tokens, *tokn;

	tokens = malloc(1024 * sizeof(char *));
	if (tokens == NULL)
	{
		dprintf(STDERR_FILENO, "Allocation Error\n");
		exit (0);
	}
	tokn = strtok(input, " \n");
	i = 0;
	while (tokn != NULL)
	{
		tokens[i] = tokn;
		i++;
		tokn = strtok(NULL, " \n");
	}
	return (tokens);
}

char *_strcat(const char *str1, const char *str2, char formatter)
{
	char *new;
	int i, j;

	new = malloc(sizeof(char) * (_strlen(str1) + _strlen(str2) + 2));
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

void excute(char **tokens)
{
	pid_t pid, wpid;
	int status, i;
	char *path, *tokn, *concat;

	pid = fork();
	if (pid == -1)
	{
		dprintf(STDERR_FILENO, "Forking Error\n");
		exit(0);
	}
	if (pid == 0)
	{
		if (tokens[0][0] != '/')
		{
			if (strcmp(tokens[0], "env") == 0 || strcmp(tokens[0], "printenv") == 0)
			{
				printf("Whyyyyyy\n");
				printEnv();
			}
			else
			{
				path = _getenv("PATH");
				tokn = strtok(path, ":");
				while (tokn)
				{
					concat = _strcat(tokn, tokens[0], '/');
					if (concat)
					{
						if (execve(concat, tokens, NULL) != -1)
							break;
						tokn = strtok(NULL, ":");
					}
				}
			}
		}
		else
		{
			if (execve(tokens[0], tokens, NULL) == -1)
				dprintf(STDERR_FILENO, "No such file or directory\n");
		}
	}
	else
		wait(&status);
}

void prompt(void)
{
 	char *input, **tokens;
	int terminator;
	ssize_t bufr;

	input = NULL;
	bufr = 0;
	terminator = 1;
	while (terminator != -1)
	{
		printf("$ ");
		terminator = getline(&input, &bufr, stdin);
		tokens = split_input(input);
	       	excute(tokens);
		/*		free(input); */
		free(tokens);
	}
	free(input);
}
