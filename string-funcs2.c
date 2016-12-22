#include "shell.h"

/**
 * _puts - print a buffer to stdout.
 * @buffer: buffer passed
 */
void _puts(char *buffer)
{
	int size;

	size = _strlen(buffer);
	write(STDOUT_FILENO, buffer, size);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 */
void _putchar(char c)
{
	write(1, &c, 1);
}

/**
 * _atoi - Convert a string to integer.
 * @s: char array string
 * Description: Adjusted to only take valid positive numbers.
 * Return: first integer found in string
 */
int _atoi(char *s)
{
	int i;
	int value, sign;

	/* return -1 (false) if not valid number */
	if (s[0] > '9' || s[0] < '0')
		return -1;

	value = 0;
	sign = -1;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			if (value < 0)
				value = (value * 10) - (s[i] - '0');
			else
				value = (s[i] - '0') * -1;

			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
		}
	}
	if (sign < 0)
		value *= -1;

	return (value);
}

/**
 * _puts_num - convert integer to string
 * @n: number to convert
 */
void _puts_num(int n)
{
	int power;
	int hold;

	power = 1;
	if (n < 0)
	{
		n *= -1;
		_putchar('-');
	}
	hold = n;

	while (hold > 9)
	{
		power *= 10;
		hold /= 10;
	}

	while (power > 0)
	{
		if (power > 9)
		{
			_putchar((n / power % 10) + '0');
			power /= 10;
		}
		if (power == 1)
		{
			_putchar(n % 10 + '0');
			power = 0;
		}
	}
}

/**
 * parse_path - used to parse path variable, but can perform basic tokenization
 * @path: string passed to parse
 * @dlimtr: delimiter to split string by
 * Return: an array of strings
 */
char **parse_path(char *path, char dlimtr)
{
	int i, j, hold, indx;
	char **paths, *tmp;

	if (*path == '\0')
		return (NULL);

	paths = _malloc(sizeof(char *) * BUFRSIZE);
	if (paths == NULL)
		return (NULL);

	indx = 0;
	for (i = 0, hold = 0; path[i]; i++)
	{
		if (path[i] == dlimtr)
		{
			tmp = _malloc(sizeof(char) * (i - hold));
			if (tmp == NULL)
				return (NULL);
			for (j = 0; hold < i; j++, hold++)
			{
				if (path[hold] == dlimtr)
					hold++;
				tmp[j] = path[hold];
			}
			tmp[j++] = '\0';

			paths[indx++] = tmp;
		}
	}
	return (paths);
}
