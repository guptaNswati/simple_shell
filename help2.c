#include "shell.h"

/**
 * history_data - print details about history built-in
 */
void history_data(void)
{
	_puts(BBLU"\nhistory:"RESET);
	_puts(" history\n");
	_puts("  Displays a list of the last commands ran.\n\n");
	_puts("  Displays an ordered list of commands ran in the shell. ");
	_puts("History should be persistent, so commands from previous ");
	_puts("sessions should be saved and displayed in future sessions. ");
	_puts("The max amount of commands saved is 4096.\n\n");
	return;
}

/**
 * setenv_data - print details about setenv built-in
 */
void setenv_data(void)
{
	_puts(BBLU"\nsetenv"RESET);
	_puts(": setenv name=value\n");
	_puts("  Add an environment variable.\n\n");
	_puts("  Adds the environement variable NAME to the environment. ");
	_puts("The value of NAME is set to VALUE.\n\n");
	return;
}

/**
 * unsetenv_data - print details about unsetenv built-in
 */
void unsetenv_data(void)
{
	_puts(BBLU"\nunsetenv"RESET);
	_puts(": unsetenv name\n");
	_puts("  Remove an environment variable.\n\n");
	_puts("  Removes the environment variable NAME from the ");
	_puts("environment.\n\n");
	return;
}
