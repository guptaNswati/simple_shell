#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct strLL
{
	char *str;
	struct strLL *next;
} strLL;

typedef struct in_built
{
	char *s;
	void (*func) ();
} in_built;

typedef struct environsLL
{
	char *name;
	char *value;
	struct environsLL *next;
} environsLL;

int checkEnv(char *name);
int _strlen(char *str);
char *_strcpy(char *strng, int i);
int _strcmp(char *s1, char *s2);
char **deepDupe(char **args);
char *_strcat(char *str1, char *str2, char formatter);
void chng_dr(char **str, environsLL **head);
void ext(char **str, environsLL **head);
void hlp(char **str, environsLL **head);
void hstry(char **str, environsLL **head);
void printEnv(char **str, environsLL **head);
char *_getenv(char *name, environsLL **head);
void _setenv(char **str, environsLL **head);
void _unsetenv(char **str, environsLL **head);
char **split_input(char *input);
int find_builtins(char **tokens, environsLL **head);
void env_add_node(environsLL **head, char *name, char *value);
strLL *createPathLL(char *value);
strLL *createEnvLL(environsLL **head);
void check_path(char **tokens, strLL **path);
void excute(char **tokens, environsLL **head, strLL **path);
void prompt(void);



#endif
