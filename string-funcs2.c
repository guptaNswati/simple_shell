#include "shell.h"

/**
 * _puts - print a buffer.
 * @buffer: buffer passed
 * @size: number of bytes to print
 */
void _puts(char *buffer, int size)
{
	write(1, buffer, size);
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
