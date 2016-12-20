#include "shell.h"

void cd_data(void)
{
	printf(BBLU"\ncd"RESET": cd [dir]\n");
	printf("  Change the shell working directory.\n\n"
	       "  Change the current directory to DIR. The default "
	       "DIR is the value of the HOME shell variable.\n\n"
	       RED"  Optional DIR inputs"RESET":\n"
	       "  -\tchanges to previous directory.\n"
	       "  ..\tchange to parent directory.\n"
	       "  $HOME\tchange to home directory.\n\n");
}

void env_data(char *cmd)
{
	printf(BBLU"\n%s"RESET": %s\n"
	       "\tPrint all of the environment.\n\n"
	       "\tPrint the name and value pairs for all "
	       "environment variables.\n\n", cmd, cmd);
}

void exit_data(void)
{
	printf(BBLU"\nexit"RESET": exit [n]\n"
	       "\tExit the shell.\n\n"
	       "\tExits the shell with a status of N. If N is omitted, "
	       "the exit status is that of the last command executed.\n\n");
}

void help_data(void)
{
	printf(BBLU"\nhelp:"RESET" help [pattern ...]\n"
	       "  Display information about builtin commands.\n\n"
	       "  Displays brief summaries of builtin commands. "
	       "  If PATTERN is specified, gives detailed help on all "
	       "commands matching PATTERN, otherwise the list of "
	       "help topics is printed.\n\n"
	       RED"  Arguments"RESET":\n"
	       "  PATTERN\tPattern is always compared from left to "
	       "right, looking at each letters that match. "
	       "If User passes 'p', all help builtin commands "
	       "starting with 'p' will be printed.\n\n");
}

void setenv_data(void)
{
	printf(BBLU"\nsetenv"RESET": setenv name value\n"
	       "  Add an environment variable.\n\n"
	       "  Adds the environement variable NAME to the environment. "
	       "The value of NAME is set to VALUE.\n\n");
}

void unsetenv_data(void)
{
	printf(BBLU"\nunsetenv"RESET": unsetenv name\n"
	       "  Remove an environment variable.\n\n"
	       "  Removes the environment variable NAME from the "
	       "environment.\n\n");
}
