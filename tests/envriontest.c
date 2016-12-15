#include "shell.h"

int main(int argc, char **agv, char **env)
{
	extern char **environ;

	printf("env %s\n", *env);
	printf("env p %p\n", *env);
	printf("enviorn %s\n",*environ);
	printf("environ p %p\n", *env);
	printf("Oh! they are same\n");
	return (0);
}
