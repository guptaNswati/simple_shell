#include "shell.h"

void cd_data(void)
{
	_puts(BBLU"\ncd"RESET);
	_puts(": cd [dir]\n");
	_puts("  Change the shell working directory.\n\n");
	_puts("  Change the current directory to DIR. The default ");
	_puts("DIR is the value of the HOME shell variable.\n\n");
	_puts(RED"  Optional DIR inputs"RESET);
	_puts(":\n");
	_puts("  -\tchanges to previous directory.\n");
	_puts("  ..\tchange to parent directory.\n");
	_puts("  $HOME\tchange to home directory.\n\n");
}

void env_data(char *cmd)
{
	_puts(BBLU"\n");
	_puts(cmd);
	_puts(RESET": ");
	_puts(cmd);
	_puts("\n\tPrint all of the environment.\n\n");
	_puts("\tPrint the name and value pairs for all ");
	_puts("environment variables.\n\n");
}

void exit_data(void)
{
	_puts(BBLU"\nexit"RESET);
	_puts(": exit [n]\n");
	_puts("\tExit the shell.\n\n");
	_puts("\tExits the shell with a status of N. If N is omitted, ");
	_puts("the exit status is that of the last command executed.\n\n");
}

void help_data(void)
{
	_puts(BBLU"\nhelp:"RESET);
	_puts(" help [pattern ...]\n");
	_puts("  Display information about builtin commands.\n\n");
	_puts("  Displays brief summaries of builtin commands. ");
	_puts("  If PATTERN is specified, gives detailed help on all ");
	_puts("commands matching PATTERN, otherwise the list of ");
	_puts("help topics is printed.\n\n");
	_puts(RED"  Arguments"RESET);
	_puts(":\n");
	_puts("  PATTERN\tPattern is always compared from left to ");
	_puts("right, looking at each letters that match. ");
	_puts("If User passes 'p', all help builtin commands ");
	_puts("starting with 'p' will be printed.\n\n");
}

void setenv_data(void)
{
	_puts(BBLU"\nsetenv"RESET);
	_puts(": setenv name value\n");
	_puts("  Add an environment variable.\n\n");
	_puts("  Adds the environement variable NAME to the environment. ");
	_puts("The value of NAME is set to VALUE.\n\n");
}

void unsetenv_data(void)
{
	_puts(BBLU"\nunsetenv"RESET);
	_puts(": unsetenv name\n");
	_puts("  Remove an environment variable.\n\n");
	_puts("  Removes the environment variable NAME from the ");
	_puts("environment.\n\n");
}
