#include "shell.h"

void alias_data(void)
{
	_puts(BBLU"\nalias"RESET);
	_puts(": alias [key] [value]\n");
	_puts("  Users can save commands within Aliases.\n\n");
	_puts("  Aliases are variables that store a value. Users can ");
	_puts("view all aliases, view a single alias, or set/reset an ");
	_puts("alias.\n\n");
	_puts(RED"  Arguments"RESET);
	_puts(":\n");
	_puts("  KEY\tKey is the name used to call the alias. If given ");
	_puts("without a value, shell will return the key and ");
	_puts("value of the alias given, if found.\n");
	_puts("  VALUE\tValue can only be given if a key is given. This ");
	_puts("allows the User to create or edit an alias with value given.");
}

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
	_puts("If PATTERN is specified, gives detailed help on all ");
	_puts("commands matching PATTERN, otherwise the list of ");
	_puts("help topics is printed.\n\n");
	_puts(RED"  Arguments"RESET);
	_puts(":\n");
	_puts("  PATTERN\tPattern is always compared from left to ");
	_puts("right, looking at each letters that match. ");
	_puts("If User passes 'p', all help builtin commands ");
	_puts("starting with 'p' will be printed.\n\n");
}

void history_data(void)
{
	_puts(BBLU"\nhistory:"RESET);
	_puts(" history\n");
	_puts("  Displays a list of the last commands ran.\n\n");
	_puts("  Displays an ordered list of commands ran in the shell. ");
	_puts("History should be persistent, so commands from previous ");
	_puts("sessions should be saved and displayed in future sessions. ");
	_puts("The max amount of commands saved is 4096.\n\n");
}

void setenv_data(void)
{
	_puts(BBLU"\nsetenv"RESET);
	_puts(": setenv name=value\n");
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
